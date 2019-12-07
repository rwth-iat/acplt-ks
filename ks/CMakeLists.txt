
add_compile_definitions(NDEBUG)

add_library(ks STATIC
        #src/abspath.cpp
        src/array.cpp
        #src/avmodule.cpp
        #src/avsimplemodule.cpp
        #src/avticket.cpp
        #src/client.cpp
        #src/clntpath.cpp
        #src/commobject.cpp
        #src/connection.cpp
        #src/connectionmgr.cpp
        src/conversions.cpp
        src/event.cpp
        #src/from_local.cpp
        #src/histdomain.cpp
        #src/history.cpp
        src/histparams.cpp
        #src/hostent.cpp
        #src/hostinaddrset.cpp
        #src/inaddrset.cpp
        #src/interserver.cpp
        #src/manager.cpp
        #src/manager2.cpp
        src/mask.cpp
        #src/ntservice.cpp
        #src/objecttree.cpp
        src/objmgrparams.cpp
        #src/package.cpp
        src/path.cpp
        src/props.cpp
        src/propsv1.cpp
        src/register.cpp
        src/result.cpp
        src/rpc.cpp
        #src/rpcproto.cpp
        src/selector.cpp
        #src/server.cpp
        src/serviceparams.cpp
        #src/simpleserver.cpp
        #src/sorter.cpp
        src/string.cpp
        #src/svrbase.cpp
        #src/svrobjects.cpp
        #src/svrrpcctx.cpp
        #src/svrsimpleobjects.cpp
        #src/svrtransport.cpp
        src/templates.cpp
        src/time.cpp
        #src/unix_manager.cpp
        src/value.cpp
        #src/variables.cpp
        #src/w95service.cpp
        src/xdr.cpp
        #src/xdrmemstream.cpp
        #src/xdrtcpcon.cpp
        #src/xdrudpcon.cpp
        )

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

target_compile_definitions(ks PRIVATE PLT_USE_BUFFERED_STREAMS=1)

target_include_directories(ks PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

target_link_libraries(ks plt)
#target_link_libraries(kssvr ks)
target_link_libraries(kscln plt ks)