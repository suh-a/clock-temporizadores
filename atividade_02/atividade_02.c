#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

// Definição dos pinos
#define LED_BLUE 12   
#define LED_RED  13   
#define LED_GREEN 11  
#define BUTTON 5     

// Variáveis globais
volatile bool timer_running = false;
volatile int current_state = 0;

// Protótipos das funções
bool led_sequence_callback(struct repeating_timer *rt);
void button_callback(uint gpio, uint32_t events);

bool debounce() {
    static uint32_t last_button_time = 0;
    uint32_t current_time = to_ms_since_boot(get_absolute_time());

    if (current_time - last_button_time < 200) { // 200ms de debounce
        return false;
    }

    last_button_time = current_time;
    return true;
}

bool led_sequence_callback(struct repeating_timer *rt) {
    switch(current_state) {
        case 0:
            gpio_put(LED_RED, 1);
            gpio_put(LED_BLUE, 1);
            gpio_put(LED_GREEN, 1);
            current_state++;
            break;
            
        case 1:
            gpio_put(LED_RED, 1);
            gpio_put(LED_BLUE, 0);
            gpio_put(LED_GREEN, 1);
            current_state++;
            break;
            
        case 2:
            gpio_put(LED_RED, 0);
            gpio_put(LED_BLUE, 0);
            gpio_put(LED_GREEN, 1);
            current_state++;
            break;
            
        case 3:
            gpio_put(LED_RED, 0);
            gpio_put(LED_BLUE, 0);
            gpio_put(LED_GREEN, 0);
            timer_running = false;
            current_state = 0; // Reiniciar o estado
            return false; // Encerra o timer
    }
    return true;
}

void button_callback(uint gpio, uint32_t events) {
    gpio_acknowledge_irq(gpio, events); // Garante que a interrupção foi reconhecida

    if (!debounce())
        return;

    if (!timer_running) {
        timer_running = true;
        current_state = 0;  // Reinicia a sequência do início
        static struct repeating_timer timer;
        add_repeating_timer_ms(3000, led_sequence_callback, NULL, &timer);
        led_sequence_callback(NULL);  // Inicia a sequência imediatamente
    }
}

int main() {
    stdio_init_all();

    // Inicialização dos GPIOs
    gpio_init(LED_BLUE);
    gpio_init(LED_RED);
    gpio_init(LED_GREEN);
    gpio_init(BUTTON);

    // Configuração da direção dos GPIOs
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(BUTTON, GPIO_IN);

    // Configuração do pull-up para o botão
    gpio_pull_up(BUTTON);

    // Configuração da interrupção do botão (detecta borda de descida)
    gpio_set_irq_enabled_with_callback(BUTTON, 
                                       GPIO_IRQ_EDGE_FALL, 
                                       true, 
                                       &button_callback);

    // Estado inicial: todos os LEDs apagados
    gpio_put(LED_BLUE, 0);
    gpio_put(LED_RED, 0);
    gpio_put(LED_GREEN, 0);

    // Loop principal (fica em espera ativa)
    while(1) {
        tight_loop_contents();
    }

    return 0;
}
