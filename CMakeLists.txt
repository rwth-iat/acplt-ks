CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

PROJECT(acplt-ks)

# disable debug define because code won't compile otherwise
add_compile_definitions(NDEBUG)

# option for static/dynamic build
option(BUILD_DYNAMIC "build libraries dynamic" OFF)

if (${BUILD_DYNAMIC})
    set(PLT_BUILD_TYPE SHARED)
else()
    set(PLT_BUILD_TYPE STATIC)
endif ()

# handle building of oncrpc when needed
if(WIN32 OR CYGWIN)
    # windows and cygwin need separate rpc library
    set(BUILD_RPC True)
else()
    set(BUILD_RPC False)
endif()

# set SYSTEM define
if(UNIX)
    add_compile_definitions(PLT_SYSTEM_LINUX=1)
elseif(WIN32)
    add_compile_definitions(PLT_SYSTEM_NT=1)
endif()

# add subfolders
add_subdirectory(plt)
add_subdirectory(oncrpc)
add_subdirectory(ks)

# define install rules
if(${BUILD_DYNAMIC})
    install(TARGETS plt ks kscln
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib)
    if(${BUILD_RPC})
        install(TARGETS rpc
                RUNTIME DESTINATION bin
                LIBRARY DESTINATION lib)
    endif()
endif ()
