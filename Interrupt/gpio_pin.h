#ifndef __GPIO_PIN_H
#define __GPIO_PIN_H

class GPIO
{
private:

    typedef void (*HandlerFunc_t)(void);

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

    static unsigned char * EIMSK;
    static unsigned char * EICRA;

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

