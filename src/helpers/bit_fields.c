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

#include "bit_fields.h"

struct bit_fields_8 bit_fields_8_create(uint8_t n)
{
    struct bit_fields_8 buffer;

    buffer.b0 = (n >> 0) & 1;
    buffer.b1 = (n >> 1) & 1;
    buffer.b2 = (n >> 2) & 1;
    buffer.b3 = (n >> 3) & 1;
    buffer.b4 = (n >> 4) & 1;
    buffer.b5 = (n >> 5) & 1;
    buffer.b6 = (n >> 6) & 1;
    buffer.b7 = (n >> 7) & 1;

    return buffer;
}
