
# define ks library
add_library(ks ${PLT_BUILD_TYPE}
        src/array.cpp
        src/conversions.cpp
        src/event.cpp
        src/histparams.cpp
        src/mask.cpp
        src/objmgrparams.cpp
        src/path.cpp
        src/props.cpp
        src/propsv1.cpp
        src/register.cpp
        src/result.cpp
        src/rpc.cpp
        src/selector.cpp
        src/serviceparams.cpp
        src/string.cpp
        src/templates.cpp
        src/time.cpp
        src/value.cpp
        src/xdr.cpp)

target_compile_definitions(ks PRIVATE PLT_USE_BUFFERED_STREAMS=1)

target_include_directories(ks PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

target_link_libraries(ks plt)
if(BUILD_RPC)
    target_link_libraries(ks rpc)
endif()


# define ks server library
#[[ FIXME compile errors
add_library(kssvr STATIC
        src/avticket.cpp
        src/connection.cpp
        src/connectionmgr.cpp
        src/histdomain.cpp
        src/hostinaddrset.cpp
        src/inaddrset.cpp
        src/interserver.cpp
        src/manager.cpp
        src/rpcproto.cpp
        src/server.cpp
        src/simpleserver.cpp
        src/svrbase.cpp
        src/svrobjects.cpp
        src/svrrpcctx.cpp
        src/svrsimpleobjects.cpp
        src/svrtransport.cpp
        src/xdrmemstream.cpp
        src/xdrtcpcon.cpp
        src/xdrudpcon.cpp) ]]

#target_link_libraries(kssvr ks)


# define ks client library
add_library(kscln STATIC
        src/avmodule.cpp
        src/avsimplemodule.cpp
        src/client.cpp
        src/clntpath.cpp
        src/commobject.cpp
        src/history.cpp
        src/hostent.cpp
        src/package.cpp
        src/sorter.cpp
        src/variables.cpp)

target_link_libraries(kscln ks)