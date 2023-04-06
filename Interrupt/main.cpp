#include "gpio_pin.h"
#include "uart.h"
#include "fifo.h"

bool buttonState;
int estado = 0;
void func();
char XOR[2];
int aux =0;
int count =0;

GPIO ledVerde(8, GPIO::OUTPUT);
GPIO ledVermelho(7, GPIO::OUTPUT);
GPIO button(2, GPIO::INT_RISE, func);

UART uart(9600);

void func()
{
    buttonState = 1;
}

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

void loop()
{
    switch (estado)
    {
    case 0: // xor
        ledVerde.set();
        ledVermelho.clear();

        if (uart.avaliable() > 0)
        {
            if (aux == 0)
            {
                XOR[0] = '\0';
                aux++;
            }
            else
            {
                uart.get(XOR[1]);
                uart.put(XOR[0] ^ XOR[1]);
                XOR[0] = XOR[1];
            }
        }

        if (buttonState == 1)
        {
            XOR[0] ='\0';
            XOR[1] ='\0';
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
        if (uart.avaliable() > 0)
        {
            count++;
            uart.get(XOR[0]);
            uart.put(count);
        }
        if (buttonState == 1)
        {
            count = 0;
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
}

int main()
{
    setup();
    while (true)
        loop();
}