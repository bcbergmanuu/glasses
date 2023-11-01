#include <stdio.h>
#include <stdlib.h>
#include <pico/stdlib.h>
#include "hardware/spi.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "hardware/gpio.h"
#include <stdbool.h>
#include <math.h>

#include <string.h>

void test() {
  for(int x = 0; x < 5;  x++) {
    gpio_put(18, x%2==0);
    gpio_put(19, x%2!=0);
    sleep_ms(1000);
  }
  
}

void main()
{
  int userinput = 0;
  stdio_init_all();
  gpio_init(18);
  gpio_init(19);
  
  gpio_set_dir(18, GPIO_OUT);        
  gpio_set_dir(19, GPIO_OUT);        

  while (true)
  {
    userinput = getchar();
    switch (userinput)
    {
    case '0':
      gpio_put(18, 0);
      gpio_put(19, 0);
      printf("0");
      break;
    case '1':
      gpio_put(18, 0);
      gpio_put(19, 1);
      printf("1");
      break;
    case '2':
      gpio_put(18, 1);
      gpio_put(19, 0);
      printf("2");
      break;
    case '3':
      gpio_put(18, 1);
      gpio_put(19, 1);
      printf("3");
      break;
    case '4':
      test();
      break;
    default:
      printf("no valid input");
      break;
    }
  }
}