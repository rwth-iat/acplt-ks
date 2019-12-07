CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

PROJECT(legacy)

if(UNIX)
    add_compile_definitions(plt PLT_SYSTEM_LINUX=1)
elseif(WIN32)
    add_compile_definitions(plt PLT_SYSTEM_NT=1)
endif()

# TODO check -fno-implicit-templates

add_subdirectory(plt)
add_subdirectory(ks)
add_subdirectory(fbs_dienste)

