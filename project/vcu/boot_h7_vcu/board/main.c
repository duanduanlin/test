#include "main.h"
// #include "app.h"
#include "board.h"
#include "param.h"
#include "com.h"

void _Error_Handler(char *file, int line)
{
   printf("Hal error @ [%s] line [%d]\r\n",file,line); 
}

int main(void)
{
    // boot_bsp_init();
    // app_entry_define();
    board_init();

    while (1)
    {
        boot_run();
        // reset_uart_rec();
    }
}
