#include "uart.h"

volatile unsigned char * UART::UBRR0H = (unsigned char *)0xC5;
volatile unsigned char * UART::UBRR0L = (unsigned char *)0xC4;
volatile unsigned char * UART::UCSRA = (unsigned char *)0xC0;
volatile unsigned char * UART::UCSRB = (unsigned char *)0xC1;
volatile unsigned char * UART::UCSRC = (unsigned char *)0xC2;
volatile unsigned char * UART::UDR = (unsigned char *)0xC6;


UART::UART()
{

    unsigned int ubrr = 16; //baud rate (datasheet)
    //configurar para 8N1@57600
    *UBRR0H = (unsigned char) (ubrr >>8);
    *UBRR0L = (unsigned char) ubrr;
    *UCSRB = (1<<4) | (1<<3);
    *UCSRC = (3<< 1);
}

UART::~UART()
{
}

void UART::put(const char c){
    
    //aguarda o TX estar livre
    while (!(*UCSRA & (1<<5))){}
    
    *UDR = c;
}
char UART::get(){
    while(true){
        if (*UCSRA & 1<<7){
            return *UDR;
        }
    }
}
void UART::puts(const char * c){
    char letra = c[0];
    for (int i=1 ; letra !='\0';i++){

        put(letra);
        letra = c[i];
    }


    void put(const char c);
    char get();
    void puts(const char * c);
}