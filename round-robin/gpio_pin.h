#ifndef __GPIO_PIN_H
#define __GPIO_PIN_H

class GPIO
{
private:
    unsigned char mask;

    unsigned char * PORTX;
    unsigned char * DDRX;
    unsigned char * PINX;
    

    static unsigned char * PORTD;
    static unsigned char * DDRD;
    static unsigned char * PIND;

    static unsigned char * PORTB;
    static unsigned char * DDRB;
    
    static unsigned char * PINB;
    static unsigned char * MCUCR; 

public:
    enum GPIO_Direction_t 
    {
        OUTPUT = 0,
        INPUT = 1,
        PULL_UP = 2,
    
    };

    GPIO(int pin, GPIO_Direction_t dir);
    ~GPIO();

    void set(bool state);
    void set();
    void clear();
    bool get();
};




#endif

