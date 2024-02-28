/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

const int BTN_B_PIN = 15;
const int BTN_PIN = 13;

volatile int flagbtn_b=0;
volatile int flagbtn_p=0;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4 && gpio == BTN_B_PIN) { // fall edge
    flagbtn_b=1;
  }
  if (events == 0x4 && gpio == BTN_PIN) { // fall edge
    flagbtn_p=1;
  }
  
}

int main() {
    stdio_init_all();
    
    gpio_init(BTN_B_PIN);
    gpio_set_dir(BTN_B_PIN, GPIO_IN);
    gpio_pull_up(BTN_B_PIN);
    
    gpio_init(BTN_PIN);
    gpio_set_dir(BTN_PIN, GPIO_IN);
    gpio_pull_up(BTN_PIN);

    gpio_set_irq_enabled_with_callback( BTN_PIN_G, GPIO_IRQ_EDGE_RISE, true, &btn_callback);

    gpio_set_irq_enabled_with_callback( BTN_PIN_G, GPIO_IRQ_EDGE_RISE, true, &btn_callback);
    
    
    while (true) {
        if(fagbtn_b){
            printf("clicou no azul");
        }
        if(fagbtn_p){
            printf("clicou no preto");
        }
    }
}
