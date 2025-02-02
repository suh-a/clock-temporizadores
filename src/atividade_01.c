#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_GREEN 11  
#define LED_YELLOW 12 
#define LED_RED 13  

#define GND 8  

// Estado do semáforo
int state = 0;

// Callback do temporizador para alternar os LEDs
bool repeating_timer_callback(struct repeating_timer *t) {
    // Desliga todos os LEDs antes de trocar o estado
    gpio_put(LED_GREEN, 0);
    gpio_put(LED_YELLOW, 0);
    gpio_put(LED_RED, 0);

    // Alterna os estados do semáforo
    switch (state) {
        case 0:
            gpio_put(LED_RED, 1);
            printf("Semáforo: Vermelho \n");
            state = 1;
            break;
        case 1:
            gpio_put(LED_YELLOW, 1);
            printf("Semáforo: Amarelo \n");
            state = 2;
            break;
        case 2:
            gpio_put(LED_GREEN, 1);
            printf("Semáforo: Verde \n");
            state = 0;
            break;
    }
    return true;
}

int main() {
    stdio_init_all();

    // Configuração dos LEDs como saída
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_init(LED_YELLOW);
    gpio_set_dir(LED_YELLOW, GPIO_OUT);
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);

    // Configuração do pino GND
    gpio_init(GND);
    gpio_set_dir(GND, GPIO_OUT);
    gpio_put(GND, 0); // Força GND no GPIO8

    // Inicializa o temporizador periódico (3 segundos)
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop principal - exibe mensagens na serial a cada 1 segundo
    while (true) {
        printf("Sistema rodando...\n");
        sleep_ms(1000);
    }
}
