#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h> // Para uso futuro, se necessário para sincronização mais complexa
#include "pico/stdlib.h" 

// Definições dos pinos GPIO para o LED RGB 
#define LED_VERMELHO_PIN 13 
#define LED_VERDE_PIN 11 
#define LED_AZUL_PIN 12 

// Tempos de exibição das cores em milissegundos 
#define TEMPO_VERMELHO_MS 5000 
#define TEMPO_VERDE_MS 5000 
#define TEMPO_AMARELO_MS 3000 
// Protótipo da tarefa do semáforo
void vSemaforoTask(void *pvParameters);

// Função para controlar o estado dos LEDs
void set_led_state(bool vermelho, bool verde, bool azul) {
    gpio_put(LED_VERMELHO_PIN, vermelho);
    gpio_put(LED_VERDE_PIN, verde);
    gpio_put(LED_AZUL_PIN, azul);
}

int main() {
    // Inicialização do stdio (opcional, para depuração via serial)
    // stdio_init_all();

    // Inicialização dos pinos GPIO como saídas 
    gpio_init(LED_VERMELHO_PIN);
    gpio_set_dir(LED_VERMELHO_PIN, GPIO_OUT);
    gpio_init(LED_VERDE_PIN);
    gpio_set_dir(LED_VERDE_PIN, GPIO_OUT);
    gpio_init(LED_AZUL_PIN);
    gpio_set_dir(LED_AZUL_PIN, GPIO_OUT);

    // Desliga todos os canais do LED no início 
    set_led_state(false, false, false);

    // Cria a tarefa do semáforo 
    xTaskCreate(vSemaforoTask, "SemaforoTask", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    // Inicia o escalonador do FreeRTOS
    vTaskStartScheduler();

    // O programa nunca deve chegar aqui, a menos que haja um erro no escalonador
    while (1) {
        // Loop de erro ou ocioso
    }

    return 0;
}

// Implementação da tarefa do semáforo 
void vSemaforoTask(void *pvParameters) {
    (void) pvParameters; // Evita warning de parâmetro não utilizado

    while (1) {
        // 1. Vermelho 
        set_led_state(true, false, false); // Acende o vermelho
        vTaskDelay(pdMS_TO_TICKS(TEMPO_VERMELHO_MS)); // Espera 5 segundos 

        // Desliga o vermelho antes de acender o próximo
        set_led_state(false, false, false);

        // 2. Verde 
        set_led_state(false, true, false); // Acende o verde
        vTaskDelay(pdMS_TO_TICKS(TEMPO_VERDE_MS)); // Espera 5 segundos 

        // Desliga o verde antes de acender o próximo
        set_led_state(false, false, false);

        // 3. Amarelo (Fusão de vermelho e verde) 
       
        set_led_state(true, true, false);
        vTaskDelay(pdMS_TO_TICKS(TEMPO_AMARELO_MS)); // Espera 3 segundos 

        // Desliga todos os LEDs antes de repetir o ciclo 
        set_led_state(false, false, false);

        // O loop se repete, simulando o ciclo contínuo do semáforo 
    }
}