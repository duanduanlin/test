#include "led.h"
#include "app.h"

void task_led_entry(uint32_t period)
{
    static struct timer_pcb timer_pcb = {0};

    if (is_run_time(&timer_pcb, period))
    {
        if (sys_ops_api->task_led_callback != 0)
            sys_ops_api->task_led_callback();
    }
}
