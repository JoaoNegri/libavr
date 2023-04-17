#ifndef __ADC_H__
#define __ADC_H__
#include "fifo.h"



class ADC
{
public:
  enum Ref_t
  {
    AREF = 0,
    AVCC = 1,
    internal_11 = 3
  };

private:
  Ref_t ref;
  int ch;
  bool running;

  static volatile unsigned char * ADMUX;
  static volatile unsigned char * ADCSRA;
  static volatile unsigned char * ADCH;
  static volatile unsigned char * ADCL;

  static ADC *adcs[7];

  static FIFOCIRC<int,8> fifo;


public:
  static void sampleHandler();

  ADC(int ch, Ref_t ref);
  // ADC(int ch);
  ~ADC();
  float sample_volt();

  int sample(int &info);

  float sync_sample_volt();
  int sync_sample(int &info);
  int get();
  bool start();
  bool stop();
  int avaliable();

};

#endif