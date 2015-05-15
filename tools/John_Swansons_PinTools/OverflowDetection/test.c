/*
**  Jonathan Salwan - 2013-09-04
** 
**  http://shell-storm.org
**  http://twitter.com/JonathanSalwan
** 
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software  Foundation, either  version 3 of  the License, or
**  (at your option) any later version.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_MAX 32

void test4_heap_overflow(char *buff1)
{
  /* 5 bytes overwritten outside the area "42 42 42 42 00" */
  strcpy(buff1, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBB");
}

void test5_stack_overflow(void)
{
  int a, b, i;

  a = 0x90909090;
  b = 0x91919191;

  for (i = 0; i <= sizeof(b); i++)
    *(((unsigned char *)(&b))+i) = 'E';

}

int main(int ac, const char *av[])
{
  char *buff1 = NULL, *buff2 = NULL;
  int i = 0;  

  buff1 = malloc(BUFF_MAX);
  buff2 = malloc(BUFF_MAX);
  if (!buff1 || !buff2)
    return -1;

  /* Test 1 - heap overflow (off-by-one) */
  for (i = 0; i <= BUFF_MAX; i++)
    buff1[i] = 'A';
  
  /* Test 2 - heap overflow (off-by-one) - Via linear buffer buff1->buff2 */
  for (i = 0; i <= BUFF_MAX; i++)
    buff2[i] = 'B';

  /* Test 3 - Use after free */
  free(buff1);
  buff1[16] = 'C';          /* Will match */
  buff1 = malloc(BUFF_MAX);
  buff1[16] = 'C';          /* Will not match */
 
  /* Test 4 - Classical Heap overflow */
  test4_heap_overflow(buff1);

  /* Test 5 - Stack overclow */
  test5_stack_overflow();

  return 0;
}

