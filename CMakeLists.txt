cmake_minimum_required(VERSION 3.9)
project(MidiParser)

set(CMAKE_C_STANDARD 11)

add_library(libMidiParser midi_reader.c midi_reader.h bit_util.c bit_util.h base_def.h log.c log.h common_util.c common_util.h midi_writer.c midi_writer.h midi_struct.h print_util.c print_util.h)

link_libraries(libMidiParser m)

add_executable(MidiParser test.c)
