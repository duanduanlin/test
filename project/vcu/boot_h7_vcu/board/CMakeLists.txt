# add the sources here
set(sources
    main.c  
    board.c
    syscall_newlib.c
    can_driver.c
)

# callback cmake module
include(file)
add_src_list(${sources})
