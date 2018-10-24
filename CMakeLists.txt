cmake_minimum_required(VERSION 3.9)
project(MidiParser)

set(CMAKE_C_STANDARD 11)

add_library(libMidiParser
        base_def.h
        midi_reader.h midi_reader.c
        log.h log.c
        common_util.h common_util.c
        midi_writer.h midi_writer.c
        midi_common.h midi_common.c
        print_util.h print_util.c
        )

link_libraries(libMidiParser m)

add_executable(MidiParser test.c)
