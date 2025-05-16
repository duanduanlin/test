#include "app.h"

sys_ops_t *sys_ops_api;

int is_run_time(struct timer_pcb *p, uint32_t period)
{
    uint32_t cur_tick = sys_ops_api->get_sys_tick();
    if (cur_tick - p->tick >= period)
    {
        p->tick = cur_tick;
        return 1;
    }

    return 0;
}
