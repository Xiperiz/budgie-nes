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
#include "cpu.h"

struct nes_cpu6502*
nes_cpu_create(void)
{
    struct nes_cpu6502* buffer = malloc(sizeof(struct nes_cpu6502));
    if (buffer == NULL) return NULL;

    buffer->ram = malloc(NES_MEMORY_SIZE);
    if (buffer->ram == NULL)
    {
        free(buffer);

        return NULL;
    }

    buffer->pc = 0;
    buffer->x  = 0;
    buffer->y  = 0;
    buffer->a  = 0;
    buffer->s  = 0;
    buffer->p  = 0;

    return buffer;
}

void
nes_cpu_free(struct nes_cpu6502* obj)
{
    free(obj->ram);
    free(obj);
}

uint8_t
nes_cpu_ram_read_word(struct nes_cpu6502* obj, uint16_t addr)
{
    if (addr >= 0x0800 && addr <= 0x1FFF)
    {
        // Mirror of 0x0000 - 0x07FF

        return nes_cpu_ram_read_word(obj, addr - 0x0800);
    }
    else if (addr >= 0x2008 && addr <= 0x3FFF)
    {
        // Mirror of $2000-2007 (repeats every 8 bytes)
        // TODO ((addr - 0x2008) % 8 or something similar)

        return 0;
    }
    else
    {
        return obj->ram[addr];
    }
}

void
nes_cpu_ram_write_word(struct nes_cpu6502* obj, uint16_t addr, uint8_t val)
{
    if (addr >= 0x0800 && addr <= 0x1FFF)
    {
        // Mirror of 0x0000 - 0x07FF
        nes_cpu_ram_write_word(obj, addr - 0x0800, val);
    }
    else if (addr >= 0x2008 && addr <= 0x3FFF)
    {
        // Mirror of $2000-2007 (repeats every 8 bytes)
        // TODO ((addr - 0x2008) % 8 or something similar)

        return;
    }
    else
    {
        obj->ram[addr] = val;
    }
}

uint16_t
nes_cpu_ram_read_double_word(struct nes_cpu6502* obj, uint16_t addr)
{
    // TODO
    (void)obj;
    (void)addr;

    return 0;
}

void
nes_cpu_ram_write_double_word(struct nes_cpu6502* obj, uint16_t addr, uint16_t val)
{
    // TODO
    (void)obj;
    (void)addr;
    (void)val;
}
