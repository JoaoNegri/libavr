#include "gpio_pin.h"
#include "uart.h"
#include "fifo.h"
#include "adc.h"
#include "stdio.h"
#include "stdlib.h"

bool buttonState;
int estado = 0;
void func();
char XOR[2];
int aux =0;
int count =0;
int info;
GPIO ledVerde(8, GPIO::OUTPUT);
GPIO ledVermelho(7, GPIO::OUTPUT);
GPIO potenciometro(14, GPIO::INPUT);
GPIO button(2, GPIO::INT_RISE, func);

UART uart(9600);
ADC adc(0,ADC::AVCC);

void setup()
{
    __asm__("sei");
}

void delay(unsigned int times)
{
    while (times--)
    {
        unsigned int x = 0xffff;
        while (x--)
            ;
    }
}
void func()
{
    buttonState = 1;
}

float tensao;
void loop()
{       
    switch (estado)
    {
    case 0: // xor
        ledVerde.set();
        ledVermelho.clear();

        adc.start();

        char str[11]; // 6 caracteres + terminador nulo
        
        dtostrf(adc.sample_volt(), 4, 2, str); // converte o valor em ponto flutuante para uma string com 2 casas decimais
        uart.syncPuts(str);

        uart.put(adc.avaliable());

        if (buttonState == 1)
        {

            estado = 1;
        }
        break;
    case 1:
        delay(5);
        estado = 2;
        buttonState = 0;
        break;
    case 2: // acc
        ledVermelho.set();
        ledVerde.clear();

        
        adc.stop();
        
        uart.put(adc.avaliable());
        if (buttonState == 1)
        {
            estado = 3;
        }
        break;
    case 3:
        delay(5);
        estado = 0;
        buttonState = 0;
        break;
    default:
        break;
    }
    delay(5);

}

int main()
{
    setup();
    while (true)
        loop();
}