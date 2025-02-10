#include "interrupt.h"
#include "button.h"
#include "led.h"
#include "pico/bootrom.h"
#include "pico/stdlib.h"
#include "ssd1306.h"
#include <stdio.h>

// Função que lida com eventos de interrupção
void gpio_irq_handler(uint gpio, uint32_t events) {
    // eventos de acionamento de botões
    if(gpio == BUTTON_A || gpio == BUTTON_B) {
        // tratamento de debouncing dos botões
        if(!debouncing(300))
            return;
        if(gpio == BUTTON_A) {
            if(gpio_get(LED_GREEN)) {
                puts("\nLED verde desligado.");

                ssd1306_fill(&ssd, false);
                ssd1306_send_data(&ssd);
                ssd1306_draw_string(&ssd, "LED VERDE", 10, 20);
                ssd1306_draw_string(&ssd, "DESLIGADO", 10, 30);
                ssd1306_send_data(&ssd);
            }
            else {
                puts("\nLED verde ligado.");
                ssd1306_fill(&ssd, false);
                ssd1306_send_data(&ssd);
                ssd1306_draw_string(&ssd, "LED VERDE", 10, 20);
                ssd1306_draw_string(&ssd, "LIGADO", 10, 30);
                ssd1306_send_data(&ssd);
            }
            // muda o estado do led verde
            gpio_put(LED_GREEN, !gpio_get(LED_GREEN));
        }
        if(gpio == BUTTON_B) {
            if(gpio_get(LED_BLUE)) {
                puts("\nLED azul desligado.");
                ssd1306_fill(&ssd, false);
                ssd1306_send_data(&ssd);
                ssd1306_draw_string(&ssd, "LED AZUL", 10, 20);
                ssd1306_draw_string(&ssd, "DESLIGADO", 10, 30);
                ssd1306_send_data(&ssd);
            }
            else {
                puts("\nLED azul ligado.");
                ssd1306_fill(&ssd, false);
                ssd1306_send_data(&ssd);
                ssd1306_draw_string(&ssd, "LED AZUL", 10, 20);
                ssd1306_draw_string(&ssd, "LIGADO", 10, 30);
                ssd1306_send_data(&ssd);
            }
            // muda o estado do led azul
            gpio_put(LED_BLUE, !gpio_get(LED_BLUE));
        }

    }
}