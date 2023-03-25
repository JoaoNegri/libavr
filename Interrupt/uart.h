#ifndef __UART_H__
#define __UART_H__


class UART
{
private:
    static volatile unsigned char * UBRR0H;
    static volatile unsigned char * UBRR0L;
    static volatile unsigned char * UCSRA;
    static volatile unsigned char * UCSRB;
    static volatile unsigned char * UCSRC;
    static volatile unsigned char * UDR;

public:
    UART(long baudrate); //default: 8N1@57600
    ~UART();
    void syncPut(const char c);
    char syncGet();
    void syncPuts(const char * c);
    // void syncPut(const char c);
    // char syncGet();
    // void syncPuts(const char * c);
};


#endif
