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

#ifndef BNES_BIT_FIELDS_H
#define BNES_BIT_FIELDS_H

#include <stdint.h>
#include <stdbool.h>

struct bit_fields_8
{
    bool b0, b1, b2, b3, b4, b5, b6, b7;
};

struct bit_fields_8 bit_fields_8_create(uint8_t n);

#endif //BNES_BIT_FIELDS_H
