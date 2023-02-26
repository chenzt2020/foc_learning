#ifndef PWM_H
#define PWM_H

#include "main.h"
#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef htim1;

class PWM {
public:
  inline void start() {
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
    HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
    HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);
  }
  inline void update(float t_a, float t_b, float t_c) {
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, t_a * FOC_TIM_ARR);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, t_b * FOC_TIM_ARR);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, t_c * FOC_TIM_ARR);
  }
  inline void halt() {
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
  }
};

#endif // PWM_H
