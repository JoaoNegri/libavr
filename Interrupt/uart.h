#ifndef __UART_H__
#define __UART_H__
#include "fifo.h"


class UART
{
private:

    typedef void (*HandlerFunc_t)(void);

    static const unsigned int tamFIFO = 32;
    static volatile unsigned char * UBRR0H;
    static volatile unsigned char * UBRR0L;
    static volatile unsigned char * UCSRA;
    static volatile unsigned char * UCSRB;
    static volatile unsigned char * UCSRC;
    static volatile unsigned char * UDR;

    static FIFO<char,tamFIFO> fifoTx;
    static FIFO<char,tamFIFO> fifoRx;

public:
    static void intTxHandler();
    static void intRxHandler();

    UART(long baudrate); //default: 8N1@57600
    ~UART();
    void syncPut(const char c);
    char syncGet();
    void syncPuts(const char * c);
    int put(const char c);
    int get(char & info);
    void puts(const char * c);
    static int avaliable();
    
};


#endif
