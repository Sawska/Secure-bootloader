#pragma once
#include <stdint.h>

#define IMAGE_MAGIC 0xDEADBEEF

typedef struct {
    uint32_t magic;      
    uint32_t length;     
    uint32_t crc32;      
    uint32_t version;    
} image_header_t;