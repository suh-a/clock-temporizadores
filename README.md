
# Documentação da Atividade 2

Esta documentação descreve detalhadamente a **Atividade 2**, que tem como objetivo controlar três LEDs (azul, vermelho e verde) conectados a um Raspberry Pi Pico W. A lógica do sistema é acionada por um botão e envolve o acendimento simultâneo dos LEDs e seu desligamento sequencial após intervalos específicos.

---

## 1. Objetivo da Atividade

Quando o botão (conectado ao GPIO5) for pressionado:
- **Passo 1:** Todos os três LEDs são acesos simultaneamente.
- **Passo 2:** Após 3 segundos, o LED azul (GPIO12) é desligado.
- **Passo 3:** Após 4 segundos, o LED vermelho (GPIO13) é desligado.
- **Passo 4:** Após 5 segundos, o LED verde (GPIO11) é desligado.
- **Passo 5:** Ao final do ciclo, o sistema retorna ao estado inicial, permitindo um novo acionamento.

---

## 2. Componentes e Conexões

### 2.1. Microcontrolador
- **Raspberry Pi Pico W**

### 2.2. Componentes Utilizados
- **LEDs:**
  - **LED Azul:** Conectado ao pino **GPIO12**
  - **LED Vermelho:** Conectado ao pino **GPIO13**
  - **LED Verde:** Conectado ao pino **GPIO11**
- **Botão de Pressão:**
  - Conectado ao pino **GPIO5** (configurado com _pull-up_ interno, pois o botão está ligado ao GND)
- **Resistores de 330 Ω:**
  - Limitam a corrente dos LEDs

### 2.3. Conexões no Diagrama Wokwi
- **LEDs:**
  - O anodo de cada LED é ligado a um resistor que, por sua vez, está conectado ao respectivo pino GPIO.
  - Os cátodos dos LEDs estão conectados ao GND.
- **Botão:**
  - Um terminal do botão está ligado ao **GPIO5**.
  - O outro terminal está ligado ao **GND**.
  - Com o resistor pull-up ativo, o pino fica em nível alto em repouso e passa a nível baixo quando o botão é pressionado.

---

## 3. Funcionamento do Código

### 3.1. Inicialização (Função `setup()`)

- **Comunicação Serial:**  
  O sistema inicia a comunicação serial por `Serial1` (baud rate de 115200), permitindo a depuração por mensagens no monitor serial.
  
- **Configuração dos Pinos:**  
  - Os pinos dos LEDs (**GPIO12**, **GPIO13** e **GPIO11**) são configurados como **saída**.
  - O pino do botão (**GPIO5**) é configurado como **entrada** com **pull-up** para garantir que, em repouso, o pino esteja em nível alto.

### 3.2. Loop Principal (Função `loop()`)

- **Detecção do Botão com Debounce:**  
  - O código verifica continuamente se o botão foi pressionado (ou seja, se o valor lido em `BUTTON` é `LOW`).
  - Um debounce de 300ms é implementado para evitar leituras repetidas devido a ruídos ou múltiplas detecções em uma única pressão.

- **Acionamento dos LEDs:**  
  - Se o botão for pressionado e o sistema não estiver em processo de execução (`process_running == false`), o tempo atual é registrado e os três LEDs são acesos simultaneamente.
  - Uma mensagem de depuração é enviada via Serial informando que os LEDs foram acesos.

- **Sequência de Desligamento dos LEDs:**  
  - **Após 3 segundos:** O LED azul (GPIO12) é desligado.
  - **Após 4 segundos:** O LED vermelho (GPIO13) é desligado.
  - **Após 5 segundos:** O LED verde (GPIO11) é desligado.
  - Após a conclusão da sequência, a variável de controle é resetada, permitindo que um novo acionamento seja realizado.

---
