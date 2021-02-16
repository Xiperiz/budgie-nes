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

#ifndef BNES_PPU_H
#define BNES_PPU_H

#include <stdint.h>

#define NES_PPU_MEMORY_SIZE 0x3FFF + 1

struct nes_ppu
{
    uint8_t* memory;
};

struct nes_ppu* nes_ppu_create(void);
void nes_ppu_free(struct nes_ppu* obj);
uint8_t nes_ppu_memory_read_word(struct nes_ppu* obj, uint16_t addr);
void nes_ppu_memory_write_word(struct nes_ppu* obj, uint16_t addr, uint8_t val);

#endif //BNES_PPU_H
