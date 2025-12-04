#include "memory_map.h"
#include <inttypes.h>


extern uint32_t _stext; 

void setup_vector_table(void) {
    uint32_t *vtor = (uint32_t *)0xE000ED08;
    

    uint32_t address = (uint32_t)&_stext;
    

    *vtor = (address & 0xFFFFFFF8);
}