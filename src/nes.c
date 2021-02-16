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
#include "nes.h"

struct nes_vm*
nes_vm_create(void)
{
    struct nes_vm* buffer = malloc(sizeof(struct nes_vm));
    if (buffer == NULL) return NULL;

    buffer->rom = nes_rom_loader_create();
    if (buffer->rom == NULL)
    {
        free(buffer);

        return NULL;
    }

    buffer->cpu = nes_cpu_create();
    if (buffer->cpu == NULL)
    {
        nes_rom_loader_free(buffer->rom);
        free(buffer);

        return NULL;
    }

    buffer->ppu = nes_ppu_create();
    if (buffer->ppu == NULL)
    {
        nes_rom_loader_free(buffer->rom);
        nes_cpu_free(buffer->cpu);
        free(buffer);

        return NULL;
    }

    buffer->apu = nes_apu_create();
    if (buffer->apu == NULL)
    {
        nes_rom_loader_free(buffer->rom);
        nes_cpu_free(buffer->cpu);
        nes_ppu_free(buffer->ppu);
        free(buffer);

        return NULL;
    }

    return buffer;
}

void
nes_vm_free(struct nes_vm* obj)
{
    nes_rom_loader_free(obj->rom);
    nes_cpu_free(obj->cpu);
    nes_apu_free(obj->apu);
    nes_ppu_free(obj->ppu);

    free(obj);
}

int
nes_vm_load_rom(struct nes_vm* obj)
{
    uint64_t prg_rom_size_bytes = obj->rom->rom_parse.prg_rom_size * 16384;
    uint64_t chr_rom_size_bytes = obj->rom->rom_parse.chr_rom_size * 8192;

    // 16 for header, 0 or 512 for trainer
    uint64_t prg_rom_start_addr = 16 + (obj->rom->rom_parse.has_trainer ? 512 : 0);
    uint64_t chr_rom_start_addr = prg_rom_start_addr + prg_rom_size_bytes;

    // Mapper 0 only implemented so this code only works for mapper 0
    if (obj->rom->rom_parse.prg_rom_size == 1)
    {
        // 16kb (NROM-128)
        // TODO Mirror 0x8000 - 0xBFFF
        printf("NROM-128 is not supported \n");

        return -1;
    }
    else if (obj->rom->rom_parse.prg_rom_size == 2)
    {
        // 32kb (NROM-256)

        // CPU
        const uint64_t mapper_0_starting_addr = 0x8000;
        for (uint64_t i = 0; i < prg_rom_size_bytes; i++)
        {
            nes_cpu_ram_write_word(obj->cpu, i + mapper_0_starting_addr,
                                   obj->rom->rom_raw_data[prg_rom_start_addr + i]);
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