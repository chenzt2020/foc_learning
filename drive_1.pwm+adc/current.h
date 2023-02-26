#ifndef CURRENT_H
#define CURRENT_H

#include "stm32f4xx_hal.h"

extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern ADC_HandleTypeDef hadc3;

class Current {
public:
  float i_a;
  float i_b;
  float i_c;

  inline void get() {
    HAL_ADCEx_InjectedPollForConversion(&hadc1, 1);
    HAL_ADCEx_InjectedPollForConversion(&hadc2, 1);
    HAL_ADCEx_InjectedPollForConversion(&hadc3, 1);
    // i_x = adc_x / 2048.0f
    i_a = HAL_ADCEx_InjectedGetValue(&hadc1, ADC_INJECTED_RANK_1) *
          0.00048828125f;
    i_b = HAL_ADCEx_InjectedGetValue(&hadc2, ADC_INJECTED_RANK_1) *
          0.00048828125f;
    i_c = HAL_ADCEx_InjectedGetValue(&hadc3, ADC_INJECTED_RANK_1) *
          0.00048828125f;
    // avg = (i_a + i_b + i_c) / 3.0f
    avg = (i_a + i_b + i_c) * 0.33333333f;
    i_a = -(i_a - avg);
    i_b = -(i_b - avg);
    i_c = -(i_c - avg);
  }

private:
  float avg;
};

#endif // CURRENT_H
