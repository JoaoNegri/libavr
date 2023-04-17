#include "gpio_pin.h"

    volatile unsigned char * GPIO::PORTD = (unsigned char *) 0x2B;
    volatile unsigned char * GPIO::DDRD = (unsigned char *) 0x2A;
    volatile unsigned char * GPIO::PIND = (unsigned char *) 0x29;
    
    volatile unsigned char * GPIO::PORTB = (unsigned char *) 0x25;
    volatile unsigned char * GPIO::DDRB = (unsigned char *) 0x24;
    volatile unsigned char * GPIO::PINB = (unsigned char *) 0x23;

    volatile unsigned char * GPIO::PORTC = (unsigned char *) 0x28;
    volatile unsigned char * GPIO::DDRC = (unsigned char *) 0x27;
    volatile unsigned char * GPIO::PINC = (unsigned char *) 0x26;
    
    volatile unsigned char * GPIO::MCUCR = (unsigned char *) 0x55;
    volatile unsigned char * GPIO::EIMSK = (unsigned char *) 0x3D;
    volatile unsigned char * GPIO::EICRA = (unsigned char *) 0x69;
    GPIO::HandlerFunc_t GPIO::int0_handler =0;
    GPIO::HandlerFunc_t GPIO::int1_handler =0;

extern "C"{
    void __vector_1 () __attribute__((signal));
    void __vector_2 () __attribute__((signal));
}
void __vector_1(){
  GPIO::int0_handler();
}

void __vector_2(){
  GPIO::int1_handler();
}


//construtor: configura a direção do pino
GPIO::GPIO(int pin, GPIO_Direction_t dir,HandlerFunc_t func)
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
    } else if (pin < 20){
        PORTX = PORTC;
        DDRX = DDRC;
        PINX = PINC;
        mask = 1 << (pin-14);

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
    }else if (pin<8){
        // *MCUCR &= ~(unsigned char)1<<4;
        *DDRX &= ~mask;
        *PORTX |= mask;

        if(pin==2){
            int0_handler = func;
            *EIMSK = *EIMSK | (unsigned char)0x01;
            *EICRA = (*EICRA & (unsigned char)0b11111100) | (unsigned char)(dir -3);
        }else if(pin==3){
            int1_handler = func;
            *EIMSK = *EIMSK | (unsigned char)1 <<1;
            *EICRA = (*EICRA & (unsigned char)0b11110011) | ((unsigned char)(dir -3)<<2);
        }
    }
}

GPIO::~GPIO() {}



//Set: escrever valor do pino com 'state'/
void GPIO::set(bool state){
    if (state){
        set();
        return;
    }else{
        clear();
        return;
    }
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