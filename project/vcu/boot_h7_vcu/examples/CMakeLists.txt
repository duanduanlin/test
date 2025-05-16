# add the sources here
set(sources
    main.c
    # system_stm32f3xx.c
    # startup_stm32f303xc.s
)

# callback cmake module
include(file)
add_src_list(${sources})
