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


  static ADC *adcs[6];


public:
  ADC(int ch, Ref_t ref);
  // ADC(int ch);
  ~ADC();
  float sample_volt();
  int sample();
  float sync_sample_volt();
  int sync_sample();
  int get();
  bool start();
  bool stop();


};

#endif