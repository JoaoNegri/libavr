#include "gpio_pin.h"

    unsigned char * GPIO::PORTD = (unsigned char *) 0x2B;
    unsigned char * GPIO::DDRD = (unsigned char *) 0x2A;
    unsigned char * GPIO::PIND = (unsigned char *) 0x29;
    
    unsigned char * GPIO::PORTB = (unsigned char *) 0x25;
    unsigned char * GPIO::DDRB = (unsigned char *) 0x24;
    unsigned char * GPIO::PINB = (unsigned char *) 0x23;
    
    unsigned char * GPIO::MCUCR = (unsigned char *) 0x55;


//construtor: configura a direção do pino
GPIO::GPIO(int pin, GPIO_Direction_t dir)
{

    if (pin <8)
    {
        PORTX = PORTD;
        DDRX = DDRD;
        PINX = PIND;
        mask = 1 << pin;

    } else if ( pin < 14){
        mask = 1 << (pin-8);
        PORTX = PORTB;
        DDRX = DDRB;
        PINX = PINB;
    }
    


    if(dir == OUTPUT){

        *DDRX |= mask;
        // *PORTX = *PORTX | mask;

    }else if (dir == INPUT)
    {
        *DDRX = *DDRX & ~mask;
        
    }else if (dir == PULL_UP){
        *MCUCR &= ~(unsigned char)1<<4;
        *DDRX &= ~mask;
        *PORTX |= mask;
    }
    



}

GPIO::~GPIO() {}

    //Set: escrever valor do pino com 'state'/
    void GPIO::set(bool state){

    }

    void GPIO::set(){
        *PORTX |= mask;
    }
    void GPIO::clear(){
        *PORTX &= ~mask;
    }
    bool GPIO::get(){
        return *PINX & mask;
    }