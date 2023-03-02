unsigned char * PORTD = (unsigned char *) 0x2B;
unsigned char * DDRD = (unsigned char *) 0x2A;
unsigned char * PIND = (unsigned char *) 0x29;

unsigned char led_mask = 1 << 5;

int buttonState;
int estado = 0;


void setup()
{
    *DDRD = 0b00100000;    
}

void acendeLed() {
    // Acender Led
    *PORTD |= 0b00100000; 
}

void apagaLed() {
    // Apagar Led
    *PORTD &= 0b11011111; 

}

void delay(unsigned int times) {
    while(times--) {
        unsigned int x = 0xffff;
        while(x--);
    }
}

void loop()
{

  buttonState = !(*PIND & 1 << 3);

  switch (estado)
  {
  case 0:
    
    if (buttonState == 1){
      estado = 1;
      acendeLed();
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
      apagaLed();

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

int main()
{
    setup();
    while(true) loop();
}