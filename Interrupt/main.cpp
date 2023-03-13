#include"gpio_pin.h"

int buttonState;
int estado = 0;


void func(){
buttonState = button.get();

  switch (estado)
  {
  case 0:
    
    if (buttonState == 1){
      estado = 1;
      led.set();
    }
    
    break;  
    case 1:
    
    if (buttonState == 0){
      estado = 3;
    }
    
    break;
      case 3:
    
    if (buttonState == 1){
      estado = 4;
      led.clear();

    }
    
    break;
        case 4:
    
    if (buttonState == 0){
      estado = 0;
    }
    
    break;
  default:
    break;
  }
}
GPIO led(8, GPIO::OUTPUT);
GPIO button(3, GPIO::INT_RISE,func);


void setup()
{
      __asm__("sei");
}

void delay(unsigned int times) {
    while(times--) {
        unsigned int x = 0xffff;
        while(x--);
    }
}



void loop()
{
}

int main()
{
    setup();
    while(true) loop();
}