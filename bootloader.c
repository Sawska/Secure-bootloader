#include "memory_map.h"
#include <inttypes.h>

#define SCB_VTOR   (*((volatile uint32_t *)0xE000ED08))

static void start_app(uint32_t pc,uint32_t sp) {
    _asm("  \n\
        msr msp,r1  \n\
        bx r0   \n\
        ");
}

int main() {

    uint32_t *app_code = (uint32_t *)&__app_start__;

    uint32_t app_stack_pointer = app_code[0];
    uint32_t app_reset_handler = app_code[1];

    SCB_VTOR = ((uint32_t)app_code & 0xFFFFFFF8);

    start_app(app_reset_handler,app_stack_pointer);
    
    while(1) {}
}