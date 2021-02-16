/*
    BudgieNES - NES Emulator Written in C
    Copyright (C) 2021 Xiperiz

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include "../helpers/bit_fields.h"
#include "../helpers/io.h"
#include "rom.h"

struct nes_rom_loader*
nes_rom_loader_create(void)
{
    struct nes_rom_loader* buffer = malloc(sizeof(struct nes_rom_loader));
    if (buffer == NULL) return NULL;

    buffer->rom_raw_data = NULL;
    buffer->rom_path     = NULL;
    buffer->rom_size     = -1;

    return buffer;
}

void
nes_rom_loader_free(struct nes_rom_loader* obj)
{
    free(obj->rom_raw_data);
    free(obj);
}

int
nes_rom_loader_load_rom(struct nes_rom_loader* obj, char* path)
{
    struct ines_rom_data rom_parse;
    struct bit_fields_8 flags6, flags7, flags9, flags10;
    uint8_t* rom_raw_data = read_file_to_bytes(path);
    int64_t rom_size      = read_file_size(path);

    if (rom_raw_data == NULL || rom_size < NES_ROM_MIN_SIZE) return -1;

    // Validate Magic Number
    if (rom_raw_data[0] != 'N' || rom_raw_data[1] != 'E' || rom_raw_data[2] != 'S'
        || rom_raw_data[3] != 0x1A)
    {
        return -1;
    }

    rom_parse.is_valid_ines = true;
    rom_parse.prg_rom_size  = rom_raw_data[4];
    rom_parse.chr_rom_size  = rom_raw_data[5];

    // Extra flags
    flags6  = bit_fields_8_create(rom_raw_data[6]);
    flags7  = bit_fields_8_create(rom_raw_data[7]);
    flags9  = bit_fields_8_create(rom_raw_data[9]);
    flags10 = bit_fields_8_create(rom_raw_data[10]);

    rom_parse.is_mirroring_vertical = flags6.b0;
    rom_parse.has_persistent_memory = flags6.b1;
    rom_parse.has_trainer           = flags6.b2;
    rom_parse.ignore_mirroring      = flags6.b3;

    rom_parse.is_vs_unisystem = flags7.b0;
    rom_parse.is_playchoice   = flags7.b1;
    rom_parse.is_ines2        = ((flags7.b2 << 1) | flags7.b3) == 2;

    rom_parse.prg_rom_size_ines2 = rom_raw_data[8];
    if (rom_parse.prg_rom_size_ines2 == 0) rom_parse.prg_rom_size_ines2 = 1;

    rom_parse.is_pal = flags9.b0;

    rom_parse.tv_system_ines2       = (flags10.b0 << 1) | flags10.b1;
    rom_parse.prg_ram_present_ines2 = flags10.b4;
    rom_parse.has_bus_conficts      = flags10.b6;

    // Mapper Number
    rom_parse.mapper = -1;

    rom_parse.mapper ^= (-(unsigned long)flags6.b4 ^ rom_parse.mapper) & (1UL << 0);
    rom_parse.mapper ^= (-(unsigned long)flags6.b5 ^ rom_parse.mapper) & (1UL << 1);
    rom_parse.mapper ^= (-(unsigned long)flags6.b6 ^ rom_parse.mapper) & (1UL << 2);
    rom_parse.mapper ^= (-(unsigned long)flags6.b7 ^ rom_parse.mapper) & (1UL << 3);
    rom_parse.mapper ^= (-(unsigned long)flags7.b4 ^ rom_parse.mapper) & (1UL << 4);
    rom_parse.mapper ^= (-(unsigned long)flags7.b5 ^ rom_parse.mapper) & (1UL << 5);
    rom_parse.mapper ^= (-(unsigned long)flags7.b6 ^ rom_parse.mapper) & (1UL << 6);
    rom_parse.mapper ^= (-(unsigned long)flags7.b7 ^ rom_parse.mapper) & (1UL << 7);

    // Valid ROM parsed
    obj->rom_raw_data = rom_raw_data;
    obj->rom_parse    = rom_parse;
    obj->rom_size     = rom_size;

    return 0;
}

int
nes_rom_loader_move_rom_to_ram(struct nes_rom_loader* rom, struct nes_cpu6502* cpu)
{
    uint64_t prg_rom_size_bytes = rom->rom_parse.prg_rom_size * 16384;
    uint64_t chr_rom_size_bytes = rom->rom_parse.chr_rom_size * 8192;

    // 16 for header, 0 or 512 for trainer
    uint64_t prg_rom_start_addr = 16 + (rom->rom_parse.has_trainer ? 512 : 0);
    uint64_t chr_rom_start_addr = prg_rom_start_addr + prg_rom_size_bytes;

    // Mapper 0 only implemented so this code only works for mapper 0
    if (rom->rom_parse.prg_rom_size == 1)
    {
        // 16kb (NROM-128)
        // TODO Mirror 0x8000 - 0xBFFF
        printf("NROM-128 is not supported \n");

        return -1;
    }
    else if (rom->rom_parse.prg_rom_size == 2)
    {
        // 32kb (NROM-256)

        // CPU
        const uint64_t mapper_0_starting_addr = 0x8000;
        for (uint64_t i = 0; i < prg_rom_size_bytes; i++)
        {
            nes_cpu_ram_write_word(cpu, i + mapper_0_starting_addr, rom->rom_raw_data[prg_rom_start_addr + i]);
        }

        printf("PGR-ROM with size of %lli loaded\n", prg_rom_size_bytes);

        // TODO PPU
        (void)chr_rom_size_bytes;
        (void)chr_rom_start_addr;
    }
    else
    {
        // Non-zero mapper
        printf("Non-zero mapper\n");

        return -1;
    }

    return 0;
}
