#include "gpio_pin.h"
#include "uart.h"

bool buttonState;
int estado = 0;
void func();

GPIO led(8, GPIO::OUTPUT);
GPIO button(2, GPIO::INT_RISE, func);

UART uart;

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

    // uart.puts("abc");
    // delay(5);
    switch (estado)
    {
    case 0:

        if (buttonState == 1)
        {
            estado = 1;
            led.set();
        }

        break;
    case 1:

        delay(5);
        estado = 2;
        buttonState = 0;

        break;
    case 2:

        if (buttonState == 1)
        {
            estado = 3;
            led.clear();
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