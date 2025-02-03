# Documentação da Atividade 1

## Observação
- Esse projeto possui 2 códigos, um feito apenas para simulação no wokwi e o outro para funcionamento na placa.
- O projeto para simulação está acima na pasta da atividade_01, nele o led amarelo está conectado no pino GPIO 12 que orinalmente pertence ao led azul, então se o código for testado na placa ele ira piscar na cor azul e não na cor amarela, pois ele foi feito apenas para a simulação no wokwi.
- O projeto que foi testado na placa está aqui no arquivo README, logo abaixo, junto do vídeo com o funcionamento na minha placa.

## Descrição
Este projeto implementa um semáforo utilizando um Raspberry Pi Pico W. Três LEDs (verde, amarelo e vermelho) são acionados sequencialmente em intervalos regulares, simulando o funcionamento de um semáforo de trânsito.

## Componentes Utilizados
- **Raspberry Pi Pico W**
- **LED Verde** conectado ao GPIO 11
- **LED Amarelo** conectado ao GPIO 12
- **LED Vermelho** conectado ao GPIO 13
- **Resistores de 330Ω** em série com os LEDs
- **Conexão ao GND no GPIO 8**

## Funcionamento
O programa realiza as seguintes etapas:
1. Inicializa os pinos GPIO do Raspberry Pi Pico W para os LEDs e o GND.
2. Configura um temporizador para alternar os LEDs a cada 3 segundos.
3. No callback do temporizador:
   - Desliga todos os LEDs.
   - Acende o LED correspondente ao estado atual do semáforo (vermelho -> amarelo -> verde -> vermelho).
   - Exibe mensagens no terminal indicando o estado do semáforo.
  
## Funcinamento na placa
- Para o funcionamento na placa o código teve que ser levemente alterado, combinando o Led rgb vermelho e verde ligados ao mesmo tempo para resultar na luz amarela.
- Código:
  ![image](https://github.com/user-attachments/assets/0d03c473-65bd-4e07-a045-57a09273cbb7)
  ![image](https://github.com/user-attachments/assets/d363963a-b05e-4332-ae68-1c32f94a4eb6)
  
- Vídeo com o funcionamento na placa:
  https://drive.google.com/file/d/1xGrZY-xykx14ETYl1HkR04P7r54BgdPt/view?usp=sharing



# Documentação da Atividade 2

## Descrição

Tem como objetivo controlar três LEDs (azul, vermelho e verde) conectados a um Raspberry Pi Pico W. A lógica do sistema é acionada por um botão e envolve o acendimento simultâneo dos LEDs e seu desligamento sequencial após intervalos específicos.

---

## 1. Lógica de funcionamento

Quando o botão (conectado ao GPIO5) for pressionado:
- **Passo 1:** Todos os três LEDs são acesos simultaneamente.
- **Passo 2:** Após 3 segundos, o LED azul (GPIO12) é desligado.
- **Passo 3:** Após 4 segundos, o LED vermelho (GPIO13) é desligado.
- **Passo 4:** Após 5 segundos, o LED verde (GPIO11) é desligado.
- **Passo 5:** Ao final do ciclo, o sistema retorna ao estado inicial, permitindo um novo acionamento.

---


### 2. Componentes Utilizados
- **LEDs:**
  - **LED Azul:** Conectado ao pino **GPIO12**
  - **LED Vermelho:** Conectado ao pino **GPIO13**
  - **LED Verde:** Conectado ao pino **GPIO11**
- **Botão de Pressão:**
  - Conectado ao pino **GPIO5** (configurado com _pull-up_ interno, pois o botão está ligado ao GND)
- **Resistores de 330 Ω:**
  - Limitam a corrente dos LEDs

---

## 3. Funcionamento  na placa
- **Observação**
- Quando todas as leds acenderem, o Led RGB ira piscar na luz branca, devido a junção das luzes (vermelha, azul e verde), pois o Led RGB na placa é só um (com 3 entradas GPIO), não há como representar as 3 luzes ao mesmo tempo, por isso a alteração para a luz branca, quando 2 leds (vermelha e verde) estiverem acesas, ele piscara na luz amarela pelo mesmo motivo, e por fim quando apenas 1 (verde) estiver acesa ele piscara na cor verde. 
- Link do video com o funcionamento: https://drive.google.com/file/d/1xJgeLdpOk8-lXU2GliNBmuUyJbgvTMAE/view?usp=sharing





---
