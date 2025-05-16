# add the sources here
set(sources
    canard/libcanard/canard_dsdl.c
    canard/libcanard/canard.c
    port/source/port_canard.c
)

# callback cmake module
add_static_lib_src()
