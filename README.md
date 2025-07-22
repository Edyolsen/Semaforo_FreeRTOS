 Semáforo com LED RGB usando FreeRTOS no Raspberry Pi Pico

Este projeto é um exercício prático de sistemas embarcados que implementa um semáforo de trânsito simples, utilizando um LED RGB e o sistema operacional de tempo real (RTOS) **FreeRTOS** no microcontrolador Raspberry Pi Pico.

O objetivo principal é demonstrar o controlo de pinos GPIO, o gerenciamento de tarefas concorrentes e o controlo preciso de tempo num ambiente multitarefa, conceitos fundamentais em sistemas embarcados.

 Funcionalidades

 Simulação de um ciclo completo de semáforo, passando pelos estados **Vermelho**, **Verde** e **Amarelo**.
 Uso de um único LED RGB para representar as três cores do semáforo, incluindo a fusão de cores para criar o amarelo.
 Implementação robusta baseada em tarefas com o FreeRTOS, onde a lógica do semáforo corre independentemente do processador principal.
 Controlo preciso do tempo de cada estado (Vermelho, Verde, Amarelo) utilizando as funções de delay do RTOS.

Hardware Necessário

1x Raspberry Pi Pico (ou Pico W)
1x LED RGB de Cátodo Comum
3x Resistores de 220Ω (ou 330Ω)
1x Protoboard (Breadboard)
Jumpers (fios para conexão)

 Pinagem (Como Montar o Circuito)

A conexão entre o Raspberry Pi Pico e o LED RGB deve ser feita da seguinte forma:

| Componente                | Conexão no Raspberry Pi Pico   |
| :------------------------ | :----------------------------- |
| LED RGB - Terminal Vermelho **GPIO 13  
| LED RGB - Terminal Verde  | **GPIO 11    
| LED RGB - Terminal Azul   | **GPIO 12   
 


 Estrutura do Código

O código foi estruturado para demonstrar o poder de um Sistema Operacional de Tempo Real (RTOS) como o FreeRTOS.

1.  `main()`: Esta função é o ponto de entrada do programa. A sua responsabilidade é apenas inicializar o hardware (os pinos GPIO dos LEDs) e, em seguida, criar e iniciar a tarefa do semáforo (`vSemaforoTask`). Após iniciar o escalonador (`vTaskStartScheduler`), o FreeRTOS assume o controlo total do processador.

2.  vSemaforoTask(): Esta é a tarefa principal, que corre num loop infinito e contém toda a lógica do semáforo. Ela é responsável por:
    Acender e apagar as cores do LED na sequência correta (Vermelho, Verde, Amarelo).
    Utilizar a função `vTaskDelay()` para as pausas. Ao contrário de um `sleep_ms()` tradicional, o `vTaskDelay()` "liberta" o processador durante a espera, permitindo que outras tarefas (se existissem) pudessem ser executadas.

 Como Compilar e Usar

Para compilar este projeto, é necessário ter o ambiente de desenvolvimento para o Raspberry Pi Pico C/C++ SDK configurado.

1.  Configure o `CMakeLists.txt`:** Garanta que as bibliotecas do FreeRTOS estejam incluídas no seu ficheiro `CMakeLists.txt`. Você precisará adicionar `FreeRTOS-Kernel` à sua lista de `target_link_libraries`.

    ```cmake
    Exemplo de como ficaria a linha no CMakeLists.txt
    target_link_libraries(seu_projeto pico_stdlib FreeRTOS-Kernel)
    ```

2.  Compile o Projeto:**
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

3.  Grave no Pico:Pressione o botão BOOTSEL no seu Pico, conecte-o ao computador e arraste o ficheiro `.uf2` gerado (que estará dentro da pasta `build`) para a nova unidade de disco que aparecer.

 Possíveis Melhorias e Próximos Passos

Este projeto serve como uma excelente base para expansões mais complexas:

Semáforo de Pedestres:** Adicionar um botão (GPIO como entrada) e um segundo LED para simular um semáforo de pedestres, utilizando uma segunda tarefa do FreeRTOS.
Modo Noturno: Implementar uma lógica para que, após um certo tempo, o semáforo entre em modo de alerta, piscando apenas o LED amarelo.
Comunicação entre Tarefas: Usar semáforos ou filas do FreeRTOS para que uma tarefa (ex: a que lê o botão do pedestre) possa comunicar e sincronizar com a tarefa que controla as luzes.