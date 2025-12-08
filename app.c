#include "memory_map.h"
#include "header.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>  


__attribute__((section(".meta"), used)) 
const image_header_t app_header = {
    .magic   = IMAGE_MAGIC,
    .length  = 0,
    .crc32   = 0,
    .version = 1
};

void setup_vector_table(void); 


void serial_init(void) {}
void set_output(int pin) {}
void port_pin_toggle_output_level(int pin) {}
#define LED_0_PIN 25

int main() {
  setup_vector_table();
  serial_init();
  set_output(LED_0_PIN);

  printf("App Started! Version: %lu\n", app_header.version);

  while (true) {
    port_pin_toggle_output_level(LED_0_PIN);
    for (volatile int i = 0; i < 100000; ++i) {}
  }
}