cmake_minimum_required(VERSION 3.30)

project(toml-c
    VERSION 1.0
    DESCRIPTION "TOML C library"
    HOMEPAGE_URL https://github.com/arp242/toml-c
    LANGUAGES C
)

add_library(toml STATIC toml.c)
set_property(TARGET toml PROPERTY PUBLIC_HEADER toml.h)
set_property(TARGET toml PROPERTY C_STANDARD 99)
