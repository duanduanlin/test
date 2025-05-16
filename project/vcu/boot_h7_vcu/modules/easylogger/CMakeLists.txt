# add the sources here
set(sources
    port/elog_port.c
    # easylogger/port/elog_port.c
    easylogger/src/elog_async.c
    easylogger/src/elog_buf.c
    easylogger/src/elog_utils.c
    easylogger/src/elog.c
)

# callback cmake module
add_static_lib_src()
