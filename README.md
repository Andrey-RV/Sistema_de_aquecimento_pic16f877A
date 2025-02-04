# Sistema de Controle de Temperatura com PIC16F877A

Sistema embarcado desenvolvido como protótipo miniaturizado para controle de um forno, desenvolvido durante a disciplina de Microprocessadores e Microcontroladores
no curso de Engenharia Elétrica.

## 📋 Visão Geral
Controlador de temperatura baseado no microcontrolador PIC16F877A com:
- Seleção de temperatura (30°C a 70°C)
- Configuração de tempo de aquecimento (30s a 5min)
- Interface gráfica via LCD 16x2
- Controle do elemento de aquecimento via PWM e ventoinhas
- Possibilidade de pausar, retomar ou cancelar o processo de aquecimento a qualquer momento

## 🚀 Funcionalidades
  - Navegação via teclado matricial
  - Visualização em tempo real no LCD de informações de temperatura atual e tempo restante
  - Formatação automática de tempo (MM:SS)

- **Controle Preciso**
  - Leitura de temperatura via sensor analógico
  - Regulação PWM (2.5kHz)
  - Sistema de ventilação auxiliar

- **Segurança**
  - Interrupção de emergência via botão
  - Proteção contra superaquecimento
  - Indicador sonoro (buzzer)

## 🛠 Hardware Utilizado
| Componente              | Especificações                 |
|-------------------------|--------------------------------|
| Microcontrolador        | PIC16F877A                     |
| Display                 | LCD 16x2 (modo 4 bits)         |
| Teclado                 | Matricial 2x2                  |
| Sensor de Temperatura   | LM35                           |
| Fonte                   | 5V DC                          |
| Elemento de aquecimento | Resistor de potência 10W       |
| Ventoinha               | 5V DC                          |
