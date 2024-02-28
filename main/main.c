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
const int BUZZER = 5;

volatile bool flagbtn_b=false;
volatile bool flagbtn_p=false;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4 && gpio == BTN_B_PIN) { // fall edge
    flagbtn_b=true;
  }
  if (events == 0x4 && gpio == BTN_PIN) { // fall edge
    flagbtn_p=true;
  }
}

void gera_som(int buzzer_pin, int frequencia, int duracao) {
    int periodo = 1000000 / frequencia; // Calcula o período em microssegundos
    int metade_periodo = periodo/ 2;

    for (int i = 0; i < (duracao *1000 / periodo); i++) {
        gpio_put(buzzer_pin, 1);
        sleep_us(metade_periodo); // Metade do período em alto
        gpio_put(buzzer_pin, 0);
        sleep_us(metade_periodo); // Metade do período em baixo
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

    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);

    gpio_set_irq_enabled_with_callback( BTN_B_PIN, GPIO_IRQ_EDGE_FALL, true, &btn_callback);

    gpio_set_irq_enabled_with_callback( BTN_PIN, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
    
    
    while (true) {
        if(flagbtn_b){
            printf("clicou no azul");
            flagbtn_b=false;
            gera_som(BUZZER,1000,100); 

        }
        if(flagbtn_p){
            printf("clicou no preto");
            flagbtn_p=false;
            gera_som(BUZZER,6000,300); 
        }
      sleep_ms(10);
    }
}
