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
