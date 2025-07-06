cmake_minimum_required(VERSION 3.30)

set_property(GLOBAL PROPERTY CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(${CMAKE_CURRENT_SOURCE_DIR}/tinyusb/hw/bsp/family_support.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/pico-extras/external/pico_extras_import.cmake)

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

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 23)

pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/i2s/i2s.pio)

target_sources(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cdc_app.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/uac2_app.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/usb_descriptors.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/dac_config.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/i2s/i2s.c
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/tinyusb/src
    # ${CMAKE_CURRENT_SOURCE_DIR}/toml-c
)

# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/toml-c)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pico-extras)
# target_compile_options(pico_sd_card INTERFACE -w)

target_link_libraries(${PROJECT_NAME} PUBLIC pico_stdlib hardware_pio)

# Configure compilation flags and libraries for the example without RTOS.
# See the corresponding function in hw/bsp/FAMILY/family.cmake for details.
family_configure_device_example(${PROJECT_NAME} noos)

# Uncomment me to enable UART based debugging
pico_enable_stdio_uart(${PROJECT_NAME} 1)
