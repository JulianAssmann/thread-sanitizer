#include <pthread.h>
#include <iostream>

const int iter_count = 100000;

long int Global;
void *Thread1(void *x)
{
  for (size_t i = 0; i < 100000; i++)
  {
    Global = 42;
  }
  return x;
}

int main()
{
  pthread_t t;
  pthread_create(&t, NULL, Thread1, NULL);
  for (size_t i = 0; i < 100000; i++)
  {
    if (Global == 42)
      std::cout << Global << std::endl;
    Global = 43;
  }
  pthread_join(t, NULL);
  std::cout << Global << std::endl;
  return 0;
}