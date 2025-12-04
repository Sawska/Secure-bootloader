#include "memory_map.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>  


void setup_vector_table(void);


void serial_init(void) {}
void set_output(int pin) {}
void port_pin_toggle_output_level(int pin) {}
#define LED_0_PIN 25

int main() {

  setup_vector_table();


  serial_init();
  set_output(LED_0_PIN);

  printf("App Started!\n");


  while (true) {
    port_pin_toggle_output_level(LED_0_PIN);
    

    for (volatile int i = 0; i < 100000; ++i) {}
  }
}