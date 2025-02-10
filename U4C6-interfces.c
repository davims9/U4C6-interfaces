#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/uart.h"
#include "hardware/i2c.h"
#include "pico/bootrom.h"
#include "lib/ws2812.pio.h"
#include "lib/ssd1306.h"
#include "lib/button.h"
#include "lib/led.h"
#include "lib/interrupt.h"
#include "lib/numeros.h"

// Configurações da UART
#define UART_ID uart0
#define UART_TX 0
#define UART_RX 1
#define BAUD_RATE 115200
// Configuração da I2C
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C

int main() {
    stdio_init_all();

    // Configuração da UART
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX, GPIO_FUNC_UART);
    gpio_set_function(UART_RX, GPIO_FUNC_UART);

    // inicializa I2C com 400Khz.
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_pull_up(I2C_SDA); // Pull up the data line
    gpio_pull_up(I2C_SCL); // Pull up the clock line
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); // Inicializa o display
    ssd1306_config(&ssd); // Configura o display
    ssd1306_send_data(&ssd); // Envia os dados para o display
  
    // Limpa o display. O display inicia com todos os pixels apagados.
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);

    
    // Inicializa os LEDS
    init_led(LED_GREEN);
    init_led(LED_BLUE);
    // Inicialização do botões e configuração de eventos de interrupção
    init_button_with_interrupt(BUTTON_A, GPIO_IRQ_EDGE_FALL, true);
    init_button_with_interrupt(BUTTON_B, GPIO_IRQ_EDGE_FALL, true);

    // Configuração da matriz de LEDS
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    char input;
    
    //loop da função princiapal
    while(true) {

        if(stdio_usb_connected()) {
            while(true) {
                printf("Digite um letra ou um numero ou * para sair: ");
                scanf("%c", &input);
                if((input>= '0' && input <= '9')
                    || (input >= 'A' && input <= 'Z')
                    || (input >= 'a' && input <= 'z')
                    || input == '*')
                    break;
                printf("Caractere inválido!\n");
            }
            // Exibe o caractere digitado no display
            if((input >= 'A' && input <= 'Z') || 
            (input >= 'a' && input <= 'z')){
                char input_string[20];
                ssd1306_fill(&ssd, false);
                ssd1306_send_data(&ssd);
                ssd1306_draw_string(&ssd, "letra", 10, 20);
                snprintf(input_string, sizeof(input_string), "digitada %c", input);
                ssd1306_draw_string(&ssd, input_string, 10, 30);
                ssd1306_send_data(&ssd);
            }
            else if (input>= '0' && input <= '9')
            {
                char input_string[20];
                ssd1306_fill(&ssd, false);
                ssd1306_send_data(&ssd);
                ssd1306_draw_string(&ssd, "numero", 10, 20);
                snprintf(input_string, sizeof(input_string), "digitado %c", input);
                ssd1306_draw_string(&ssd, input_string, 10, 30);
                ssd1306_send_data(&ssd);
            }
            
            switch (input) {
                case '0': set_one_led(numbers[0], led_r, led_g, led_b); break;
                case '1': set_one_led(numbers[1], led_r, led_g, led_b);; break;
                case '2': set_one_led(numbers[2], led_r, led_g, led_b);; break;
                case '3': set_one_led(numbers[3], led_r, led_g, led_b);; break;
                case '4': set_one_led(numbers[4], led_r, led_g, led_b);; break;
                case '5': set_one_led(numbers[5], led_r, led_g, led_b);; break;
                case '6': set_one_led(numbers[6], led_r, led_g, led_b);; break;
                case '7': set_one_led(numbers[7], led_r, led_g, led_b);; break;
                case '8': set_one_led(numbers[8], led_r, led_g, led_b);; break;
                case '9': set_one_led(numbers[9], led_r, led_g, led_b);; break;
                default:
                    // desliga os leds da matriz quando aperta *
                    set_one_led(numbers[10], led_r, led_g, led_b);
                    printf("\nSaindo\n");
                    break;
            }
        }
        sleep_ms(100);
    }
}