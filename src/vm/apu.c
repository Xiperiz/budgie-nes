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
#include "apu.h"

struct nes_apu*
nes_apu_create(void)
{
    struct nes_apu* buffer = malloc(sizeof(struct nes_apu));

    if (buffer == NULL) return NULL;

    buffer->_placeholder = 0;

    return buffer;
}

void
nes_apu_free(struct nes_apu* obj)
{
    free(obj);
}
