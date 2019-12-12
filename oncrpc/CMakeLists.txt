
if(BUILD_RPC)
    add_library(rpc ${PLT_BUILD_TYPE}
            librpc/auth_non.c
            librpc/auth_uni.c
            librpc/authunix.c
            librpc/bindresv.c
            librpc/clnt_gen.c
            librpc/clnt_per.c
            librpc/clnt_raw.c
            librpc/clnt_sim.c
            librpc/clnt_tcp.c
            librpc/clnt_udp.c
            librpc/get_myad.c
            librpc/getrpcen.c
            librpc/getrpcpo.c
            librpc/nt.c
            librpc/pmap_cln.c
            librpc/pmap_get.c
            librpc/pmap_gma.c
            librpc/pmap_pr.c
            librpc/pmap_pro.c
            librpc/pmap_rmt.c
            librpc/rpc_call.c
            librpc/rpc_comm.c
            librpc/rpc_prot.c
            librpc/svc_auth.c
            librpc/svc_autu.c
            librpc/svc.c
            librpc/svc_raw.c
            librpc/svc_run.c
            librpc/svc_simp.c
            librpc/svc_tcp.c
            librpc/svc_udp.c
            librpc/xdr_arra.c
            librpc/xdr.c
            librpc/xdr_floa.c
            librpc/xdr_mem.c
            librpc/xdr_rec.c
            librpc/xdr_refe.c
            librpc/xdr_stdi.c)

    target_include_directories(rpc PUBLIC ${CMAKE_CURRENT_LIST_DIR}/)

    target_link_libraries(rpc wsock32 advapi32)

    add_executable(portmap librpc/portmap.c)

    target_link_libraries(portmap rpc)

    #librpc/portmap.c
endif()