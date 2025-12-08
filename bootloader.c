#include "memory_map.h"
#include "header.h"
#include <inttypes.h>
#include <stddef.h>
#include <stdbool.h>

#define SCB_VTOR   (*((volatile uint32_t *)0xE000ED08))

uint32_t calculate_crc32(const uint8_t *data, size_t length) {
    uint32_t crc = 0xFFFFFFFF;
    for (size_t i = 0; i < length; i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 1) crc = (crc >> 1) ^ 0xEDB88320;
            else         crc >>= 1;
        }
    }
    return ~crc;
}

static void start_app(uint32_t pc, uint32_t sp) {
    __asm volatile("msr msp, r1 \n bx r0 \n");
}

int main() {
    uint32_t *app_start_addr = (uint32_t *)&__app_start__;
    

    image_header_t *header = NULL;
    for(int i = 0; i < 256; i++) {
        if (app_start_addr[i] == IMAGE_MAGIC) {
            header = (image_header_t *)&app_start_addr[i];
            break;
        }
    }

    bool app_is_valid = false;

    if (header != NULL) {

        uint8_t *data_start = (uint8_t *)(header + 1);
        
        uint32_t calc_crc = calculate_crc32(data_start, header->length);
        
        if (calc_crc == header->crc32) {
            app_is_valid = true;
        }
    }

    if (app_is_valid) {
        uint32_t app_sp = app_start_addr[0];
        uint32_t app_reset = app_start_addr[1];

        SCB_VTOR = ((uint32_t)app_start_addr & 0xFFFFFFF8);
        start_app(app_reset, app_sp);
    }
    

    while(1) {}
}