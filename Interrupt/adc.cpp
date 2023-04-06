#include "adc.h"

volatile unsigned char *ADC::ADMUX = (unsigned char *)0x7C;


extern "C"
{
    void __vector_21() __attribute__((signal));
}

ADC::ADC(int ch, Ref_t referencia){
    this->ch = ch;
    this->ref = ref;
    adcs[ch] = this;




}

// ADC::ADC(int ch) : ref(AVCC) {
//     this->ch = ch;
//     adcs[ch] = this;

// }
ADC::~ADC() {}
float ADC::sample_volt()
{

}
int ADC::sample() {

}
float ADC::sync_sample_volt()
{

}
int ADC::sync_sample() {

}
int ADC::get() {}
bool ADC::start() {}
bool ADC::stop() {}