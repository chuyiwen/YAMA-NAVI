#include <time.h>

void my_sleep(unsigned long x)
{

  clock_t s = clock();
  clock_t c;

  do{
    if((c = clock()) == (clock_t)-1)
      break;//return (0);
  }while(10000UL *(c-s)/CLOCKS_PER_SEC <= x);

  //return (1);
}
