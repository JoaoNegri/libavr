#include "adc.h"
#include "uart.h"
#include "stdio.h"


volatile unsigned char *ADC::ADMUX = (unsigned char *)0x7C;
volatile unsigned char *ADC::ADCSRA = (unsigned char *)0x7A;
volatile unsigned char *ADC::ADCH = (unsigned char *)0x79;
volatile unsigned char *ADC::ADCL = (unsigned char *)0x78;
  
ADC *ADC::adcs[7];
UART teste(9600);

FIFOCIRC<int,8> ADC::fifo;


extern "C"
{
    void __vector_21() __attribute__((signal));
}

ADC::ADC(int ch, Ref_t referencia) : ref(AVCC){
    if(ch<8){
        // this->adcs[ch] = this;
        *ADMUX = *ADMUX | (unsigned char) (referencia<<6) | (unsigned char) ch;
        // this->ch = ch;
        // this->ref = ref;
        *ADCSRA = *ADCSRA | (1<<7) | 7; // 7 habilita ADC
    }
}
ADC::~ADC() {}

void __vector_21(){
    ADC::sampleHandler();
}

void ADC::sampleHandler(){
    unsigned char low = *ADCL;
    unsigned char high = *ADCH;

    
    int leitura =(high<<8) |  low;

    // teste.syncPut((char)(leitura >> 8)); // imprime o byte alto
    // teste.syncPut((char)leitura); 


    
    fifo.put(leitura);

}

float ADC::sample_volt()
{
    int info;
    sample(info);
    float tensao = info * 4.88 / 1000; // converte o valor do ADC em volts

   return tensao;
}
int ADC::sample(int &info) 
{   
    fifo.get(info);
    return 0;
}
float ADC::sync_sample_volt()
{

}
int ADC::sync_sample(int &info) 
{

    *ADCSRA = *ADCSRA | ((unsigned char)1 << 6); //Inicia conversão

    while (*ADCSRA & ((unsigned char)1 << 6)) // aguarda o fim da conversão
    ;
//lê valores
    char low = *ADCL;
    char high = *ADCH;

    int leitura = (high<<8) | low;
    info = leitura;
    return 0;
}
bool ADC::start() {
    *ADCSRA = *ADCSRA | 1<<3 | 1<< 5 | 1<<6; // liga interrupção
}
bool ADC::stop() {
    *ADCSRA = *ADCSRA & ~(1<<3); // liga interrupção
}


int ADC::avaliable(){
    return fifo.getSize();
}