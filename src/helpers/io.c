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
#include <stdio.h>
#include "io.h"

uint8_t*
read_file_to_bytes(char* path)
{
    FILE* file_ptr = fopen(path, "rb");
    uint8_t* buffer;
    int64_t file_len;

    if (file_ptr == NULL) return NULL;

    fseek(file_ptr, 0, SEEK_END);

    file_len = ftell(file_ptr);

    rewind(file_ptr);

    buffer = malloc(file_len);
    if (buffer == NULL || file_len < 1) return NULL;

    fread(buffer, file_len, 1, file_ptr);
    fclose(file_ptr);

    return buffer;
}

int64_t
read_file_size(char* path)
{
    FILE* file_ptr = fopen(path, "rb");
    int64_t file_len;

    if (file_ptr == NULL) return -1;

    fseek(file_ptr, 0, SEEK_END);

    file_len = ftell(file_ptr);

    fclose(file_ptr);

    return file_len;
}