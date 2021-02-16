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

#ifndef BNES_NES_H
#define BNES_NES_H

#include "vm/cpu.h"
#include "vm/ppu.h"
#include "vm/apu.h"
#include "vm/rom.h"

struct nes_vm
{
    struct nes_rom_loader* rom;
    struct nes_cpu6502* cpu;
    struct nes_ppu* ppu;
    struct nes_apu* apu;
};

struct nes_vm* nes_vm_create(void);
void nes_vm_free(struct nes_vm* obj);

#endif //BNES_NES_H
