cmake_minimum_required(VERSION 3.19)
project(budgie-nes C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

set(CMAKE_C_STANDARD 99)

add_executable(budgie-nes
        src/main.c src/nes.c src/nes.h src/vm/cpu.c src/vm/cpu.h src/vm/ppu.c src/vm/ppu.h
        src/vm/apu.c src/vm/apu.h src/vm/rom.c src/vm/rom.h src/helpers/io.c src/helpers/io.h
        src/helpers/bit_fields.c src/helpers/bit_fields.h
              )