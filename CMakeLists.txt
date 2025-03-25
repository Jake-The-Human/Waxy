cmake_minimum_required(VERSION 3.30)

include(${CMAKE_CURRENT_SOURCE_DIR}/tinyusb/hw/bsp/family_support.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Waxy
    VERSION 0.0.1
    DESCRIPTION "This is attempt to make my own DAC."
    HOMEPAGE_URL https://github.com/Jake-The-Human/Waxy
    LANGUAGES C CXX ASM
)

# Checks this example is valid for the family and initializes the project
family_initialize_project(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR})

# Espressif has its own cmake build system
if(FAMILY STREQUAL "espressif")
    return()
endif()

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/usb_descriptors.c
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/tinyusb/src
)

# Configure compilation flags and libraries for the example without RTOS.
# See the corresponding function in hw/bsp/FAMILY/family.cmake for details.
family_configure_device_example(${PROJECT_NAME} noos)
