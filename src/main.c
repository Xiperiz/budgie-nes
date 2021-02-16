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

#include <stdio.h>
#include "nes.h"

int
main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    struct nes_vm* vm = nes_vm_create();
    int rom_load_res;
    int rom_move_res;

    if (vm == NULL) return -1;

    rom_load_res = nes_rom_loader_load_rom(vm->rom, "sm.nes");
    if (rom_load_res == -1)
    {
        printf("Unable to open rom file\n");

        return -1;
    }

    if (vm->rom->rom_parse.is_ines2)
    {
        printf("iNES 2.0 is not supported\n");

        return -1;
    }

    if (vm->rom->rom_parse.mapper != 0)
    {
        printf("Mappers are not supported\n");

        return -1;
    }

    rom_move_res = nes_rom_loader_move_rom_to_ram(vm->rom, vm->cpu);
    if (rom_move_res == -1)
    {
        printf("Rom move failed\n");

        return -1;
    }

    nes_cpu_debug_info_stdout(vm->cpu);

    nes_vm_free(vm);

    return 0;
}
