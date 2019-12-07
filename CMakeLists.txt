CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

PROJECT(legacy)

# disable debug define because code won't compile
add_compile_definitions(NDEBUG)

set(PLT_BUILD_TYPE STATIC)

if(UNIX)
    add_compile_definitions(plt PLT_SYSTEM_LINUX=1)
elseif(WIN32)
    add_compile_definitions(plt PLT_SYSTEM_NT=1)
endif()

add_subdirectory(plt)
add_subdirectory(ks)
add_subdirectory(oncrpc)
add_subdirectory(fbs_dienste)
