#include "uart.h"

volatile unsigned char *UART::UBRR0H = (unsigned char *)0xC5;
volatile unsigned char *UART::UBRR0L = (unsigned char *)0xC4;
volatile unsigned char *UART::UCSRA = (unsigned char *)0xC0;
volatile unsigned char *UART::UCSRB = (unsigned char *)0xC1;
volatile unsigned char *UART::UCSRC = (unsigned char *)0xC2;
volatile unsigned char *UART::UDR = (unsigned char *)0xC6;
    


FIFO<char,UART::tamFIFO> UART::fifoTx;
FIFO<char,UART::tamFIFO> UART::fifoRx;

const long FOSC = 16000000;

extern "C"
{
    void __vector_18() __attribute__((signal));
    void __vector_19() __attribute__((signal));
}

void UART::intTxHandler()
{
    if (fifoTx.getSize() != 0){
        char c;
        fifoTx.get(c);
        *UDR = c;
    }else{
        *UCSRB = *UCSRB &  (0xff & (~(1<<5))); // desativa interrupão do udr
    }
}

void UART::intRxHandler()
{
    fifoRx.put(*UDR);
}

// interrupçaão rx completo, devo pegar o dado e colocar na fifoRx
void __vector_18()
{
    UART::intRxHandler();
}
// Tx completo, devo colocar mais um dado da fifo para transmissão
void __vector_19()
{
    UART::intTxHandler();
}

UART::UART(long baudrate)
{
    unsigned int ubrr = 0; // baud rate (datasheet)

    ubrr = FOSC / (16 * baudrate) - 1;

    // configurar para 8N1@57600
    *UBRR0H = (unsigned char)(ubrr >> 8);
    *UBRR0L = (unsigned char)ubrr;
    *UCSRB = (1 << 4) | (1 << 3) | (1<<7);
    *UCSRC = (3 << 1);  
}

UART::~UART()
{
}

void UART::syncPut(const char c)
{

    // aguarda o TX estar livre
    while (!(*UCSRA & (1 << 5)))
    {
    }

    *UDR = c;
}
char UART::syncGet()
{
    while (true)
    {
        if (*UCSRA & 1 << 7)
        {
            return *UDR;
        }
    }
}
void UART::syncPuts(const char *c)
{
    char letra = c[0];
    for (int i = 1; letra != '\0'; i++)
    {
        syncPut(letra);
        letra = c[i];
    }
}

// Adiciona um byte na FIFO de TX
int UART::put(const char c)
{
    int aux = fifoTx.put(c);
    *UCSRB = *UCSRB | (1<<5); // ativa interrupão do udr
    return aux;

}
// recebe um byte e coloca na FIFO de RX
int UART::get(char &info)
{
    return fifoRx.get(info);
}

int UART::avaliable(){
    return fifoRx.getSize();
}

void UART::puts(const char *c)
{
    char letra = c[0];
    for (int i = 1; letra != '\0'; i++)
    {

        fifoTx.put(letra);
        letra = c[i];
    }
    *UCSRB = *UCSRB | (1<<5); // ativa interrupão do udr
}