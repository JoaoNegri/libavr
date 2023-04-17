#ifndef __GPIO_PIN_H
#define __GPIO_PIN_H

class GPIO
{
private:

    typedef void (*HandlerFunc_t)(void);

    unsigned char mask;

    unsigned volatile char * PORTX;
    unsigned volatile char * DDRX;
    unsigned volatile char * PINX;
    

    static volatile unsigned char * PORTD;
    static volatile unsigned char * DDRD;
    static volatile unsigned char * PIND;

    static volatile unsigned char * PORTB;
    static volatile unsigned char * DDRB;
    static volatile unsigned char * PINB;

    static volatile unsigned char * PORTC;
    static volatile unsigned char * DDRC;
    static volatile unsigned char * PINC;

    static volatile unsigned char * MCUCR; 

    static volatile unsigned char * EIMSK;
    static volatile unsigned char * EICRA;

public:

    static HandlerFunc_t int0_handler;
    static HandlerFunc_t int1_handler;
    

    enum GPIO_Direction_t 
    {
        OUTPUT = 0,
        INPUT = 1,
        PULL_UP = 2,
        INT_LOW = 3,
        INT_CHANGE = 4,
        INT_FALL = 5,
        INT_RISE = 6
    
    };

    

    GPIO(int pin, GPIO_Direction_t dir, HandlerFunc_t func =0);
    ~GPIO();

    void set(bool state);
    void set();
    void clear();
    bool get();
};




#endif

