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

#ifndef BNES_ROM_H
#define BNES_ROM_H

#include <stdbool.h>
#include <stdint.h>
#include "cpu.h"

#define NES_ROM_MIN_SIZE 0

struct ines_rom_data
{
    uint8_t mapper;
    int prg_rom_size_ines2; // As below
    int prg_rom_size;       // In 16KB units (Program Memory)
    int chr_rom_size;       // In 8KB units  (Graphical Memory)
    int tv_system_ines2;
    bool prg_ram_present_ines2;
    bool ignore_mirroring;
    bool has_persistent_memory;
    bool has_bus_conficts;
    bool has_trainer;
    bool is_mirroring_vertical;
    bool is_vs_unisystem;
    bool is_valid_ines;
    bool is_playchoice;
    bool is_ines2;
    bool is_pal;
};

struct nes_rom_loader
{
    struct ines_rom_data rom_parse;
    char* rom_path;
    uint8_t* rom_raw_data;
    int64_t rom_size;
};

struct nes_rom_loader* nes_rom_loader_create(void);
void nes_rom_loader_free(struct nes_rom_loader* obj);
int nes_rom_loader_load_rom(struct nes_rom_loader* obj, char* path);
int nes_rom_loader_move_rom_to_vm(struct nes_rom_loader* rom, struct nes_cpu6502* cpu);

#endif //BNES_ROM_H
