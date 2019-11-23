cmake_minimum_required(VERSION 3.15)
project(IceCLimbers C)

set(CMAKE_C_STANDARD 99)


add_executable(IceCLimbers main.c)

INCLUDE_DIRECTORIES( allegro/5.0.11/include )

LINK_DIRECTORIES( allegro/5.0.11/lib )


TARGET_LINK_LIBRARIES(IceCLimbers  allegro_acodec
        allegro_audio
        allegro_color
        allegro_dialog
        allegro_image
        allegro_main
        allegro_memfile
        allegro_physfs
        allegro_primitives
        allegro_ttf
        allegro_font
        allegro)