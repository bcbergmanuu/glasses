#include <stdio.h>
#include <stdlib.h>
#include <pico/stdlib.h>
#include "hardware/structs/pwm.h"
#include "hardware/pwm.h"
//#include "hardware/spi.h"
//#include "FreeRTOSConfig.h"
//#include "FreeRTOS.h"
//#include "task.h"
//#include "semphr.h"
//#include "hardware/gpio.h"
//#include <stdbool.h>
//#include <math.h>
//#include "hardware/regs/dreq.h"

#include <string.h>

void initpwm() {
  //Tell GPIO 0 and 1 they are allocated to the PWM
  gpio_set_function(20, GPIO_FUNC_PWM);
  gpio_set_function(19, GPIO_FUNC_PWM);
  gpio_set_function(18, GPIO_FUNC_PWM);
  


  // Find out which PWM slice is connected to GPIO 0
  uint slice_num = pwm_gpio_to_slice_num(20);
  uint slice_num19 = pwm_gpio_to_slice_num(19);
  uint slice_num18 = pwm_gpio_to_slice_num(18);

  pwm_set_clkdiv(slice_num, 256); 
  pwm_set_clkdiv(slice_num19, 256); 
  pwm_set_clkdiv(slice_num18, 256); 
  
  pwm_set_wrap(slice_num, 512);
  pwm_set_wrap(slice_num19, 512);
  pwm_set_wrap(slice_num18, 512);
    
  pwm_set_chan_level(slice_num, PWM_CHAN_A, 256);    
  pwm_set_chan_level(slice_num19, PWM_CHAN_B, 256);
  //pwm_set_chan_level(slice_num19, PWM_CHAN_A , 256);
  pwm_set_chan_level(slice_num18, PWM_CHAN_A, 256);  
  
  pwm_set_enabled(slice_num, true);
  pwm_set_enabled(slice_num19, true);
  pwm_set_enabled(slice_num18, true);
}

void enableA() {
  gpio_set_outover(18, GPIO_OVERRIDE_INVERT);  
}

void disableA() {
  gpio_set_outover (18, GPIO_OVERRIDE_NORMAL);
}

void enableB() {
  gpio_set_outover(20, GPIO_OVERRIDE_INVERT);  
}

void disableB() {
  gpio_set_outover (20, GPIO_OVERRIDE_NORMAL);
}

void main()
{
  int userinput = 0, currentstate = 0;
  stdio_init_all();
  initpwm();

  while (true)
  {    
    userinput = getchar();
    switch (userinput)
    {
    case '0':
      disableB();
      disableA();
      currentstate = 0;
      printf("0\n");
      break;
    case '1':
      disableB();
      enableA();
      currentstate = 1;
      printf("1\n");
      break;
    case '2':
      enableB();
      disableA();
      currentstate = 2;
      printf("2\n");
      break;
    case '3':
      enableB();
      enableA();
      currentstate = 3;
      printf("3\n");
      break;
    case '4':
      printf("%i\n", currentstate);
      break;
    default:
      printf("no valid input");
      break;
    }  
  }


  
  

  while(1) {
    tight_loop_contents();;
  }

}