
add_library(plt STATIC
        src/alloc.cpp
        src/array.cpp
        src/container.cpp
        src/debug.cpp
        src/handle.cpp
        src/hashtable.cpp
        #src/key.cpp
        src/list.cpp
        src/log.cpp
        src/logstream.cpp
        src/priorityqueue.cpp
        #src/rbtreedict.cpp # needs hpp header that does not exist
        src/rtti.cpp
        src/string.cpp
        src/time.cpp)

target_compile_definitions(plt PRIVATE NDEBUG)

target_include_directories(plt PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)