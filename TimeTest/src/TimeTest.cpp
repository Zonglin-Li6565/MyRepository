//============================================================================
// Name        : TimeTest.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>      /* printf */
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */

int main ()
{
  int x[100];
  time_t start_a, end_a, start_b, end_b;
  double seconds_a, seconds_b;
  time(&start_a);
  int t = 0;
  for(int i = 0; i < 100000; i++) {
	  for(int j = 0; j < 100000; j++) {
		  t += x[5];
	  }
  	  t %= 1000;
  }
  time(&end_a);
  seconds_a = difftime(end_a,start_a);
  time(&start_b);
  int p = 0, k = x[5];
  for(int i = 0; i < 100000; i++) {
  	for(int j = 0; j < 100000; j++) {
  		p += k;
  	}
  }
  time(&end_b);
  seconds_b = difftime(end_b,start_b);
  printf ("running time of a = %.4f, running time of b = %.4f ", seconds_a, seconds_b);

  return 0;
}
