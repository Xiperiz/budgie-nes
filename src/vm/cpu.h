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

#ifndef BNES_CPU_H
#define BNES_CPU_H

#include <stdint.h>
#include <stdio.h>

#define NES_MEMORY_SIZE 0xFFFF + 1

struct nes_cpu6502
{
    uint8_t a, x, y, s, p;
    uint16_t pc;
    uint8_t* ram;
};

struct nes_cpu6502* nes_cpu_create(void);
void nes_cpu_free(struct nes_cpu6502* obj);
uint8_t nes_cpu_ram_read_word(struct nes_cpu6502* obj, uint16_t addr);
void nes_cpu_ram_write_word(struct nes_cpu6502* obj, uint16_t addr, uint8_t val);
uint16_t nes_cpu_ram_read_double_word(struct nes_cpu6502* obj, uint16_t addr);
void nes_cpu_ram_write_double_word(struct nes_cpu6502* obj, uint16_t addr, uint16_t val);

// Debug functions
static inline void nes_cpu_debug_info_stdout(struct nes_cpu6502* obj)
{
    printf("pc: %i \n"
           "x:  %i \n"
           "y:  %i \n"
           "a:  %i \n"
           "s:  %i \n"
           "p:  %i \n",
           obj->pc, obj->x, obj->y, obj->a, obj->s, obj->p);
}


#endif //BNES_CPU_H
