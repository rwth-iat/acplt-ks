
add_library(plt ${PLT_BUILD_TYPE}
        src/alloc.cpp
        src/array.cpp
        src/container.cpp
        src/debug.cpp
        src/handle.cpp
        src/hashtable.cpp
        src/list.cpp
        src/log.cpp
        src/logstream.cpp
        src/priorityqueue.cpp
        src/rtti.cpp
        src/string.cpp
        src/time.cpp)

target_include_directories(plt PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)