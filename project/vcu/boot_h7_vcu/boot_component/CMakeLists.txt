# add the sources here
set(sources
    app.c
    bl.c
    com.c
    crc16.c
    led.c
    param.c
    hal_boot.c
)

# callback cmake module
include(file)
add_src_list(${sources})
