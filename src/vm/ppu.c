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
#include "ppu.h"

struct nes_ppu*
nes_ppu_create(void)
{
    struct nes_ppu* buffer = malloc(sizeof(struct nes_ppu));
    if (buffer == NULL) return NULL;

    buffer->memory = malloc(NES_PPU_MEMORY_SIZE);
    if (buffer->memory == NULL)
    {
        free(buffer);

        return NULL;
    }

    return buffer;
}

void
nes_ppu_free(struct nes_ppu* obj)
{
    free(obj->memory);
    free(obj);
}

uint8_t
nes_ppu_memory_read_word(struct nes_ppu* obj, uint16_t addr)
{
    if (addr >= 0x3000 && addr <= 0x3EFF)
    {
        // Mirror of 0x2000 - 0x2EFF

        return obj->memory[(addr - 0x3000) + 0x2000];
    }
    else if (addr >= 0x3F20 && addr <= 0x3FFF)
    {
        // Mirror of 0x3F00 - 0x3F1F

        return obj->memory[(addr - 0x3F20) + 0x3F00];
    }
    else
    {
        return obj->memory[addr];
    }
}

void
nes_ppu_memory_write_word(struct nes_ppu* obj, uint16_t addr, uint8_t val)
{
    if (addr >= 0x3000 && addr <= 0x3EFF)
    {
        // Mirror of 0x2000 - 0x2EFF

        obj->memory[(addr - 0x3000) + 0x2000] = val;
    }
    else if (addr >= 0x3F20 && addr <= 0x3FFF)
    {
        // Mirror of 0x3F00 - 0x3F1F

        obj->memory[(addr - 0x3F20) + 0x3F00] = val;
    }
    else
    {
        obj->memory[addr] = val;
    }
}
