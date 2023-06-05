#include <stdio.h>


/*
  advantages:  time complexity : O(N)
  disadvantages : space complexity : O(N)

*/

int n = 1000;
int arr[1001]; // n + 1
int fourthMethod(int n) {
  //dp bottom up approach

  arr[0] = 0;
  arr[1] = 1;
  arr[2] = 2;

  for (int i = 3; i < n + 1; i++)
    arr[i] = arr[i - 2] + arr[i - 3];

  return arr[n];
}


/*
  advantages:  time complexity : O(N ^ 2)
  disadvantages : space complexity : O(N)

*/


int memor[1000];

int thirdMethod(int n) {
  //top down approach
  // using memoization
  if (n == 0)
    return 0;
  if (n == 1)
    return 1;
  if (n == 2)
    return 2;

  int ret = memor[n];
  if (ret != -1)
    return ret;

  return memor[n] = secondMethod(n - 3) + secondMethod(n - 2);
}

/*
  advantages:  time complexity : O(2 ^ N)
  disadvantages : space complexity : O(c)

*/

int secondMethod(int n) {
  if (n == 0)
    return 0;
  if (n == 1)
    return 1;
  if (n == 2)
    return 2;

  return secondMethod(n - 3) + secondMethod(n - 2);
}


/*
  advantages:  time complexity : O(N)
  disadvantages : space complexity : O(c)

*/

int firstMethod(int n) {
  int a = 0;
  int b = 1;
  int c = 2;


  for (int i = 3; i <= n; i++) {
    int d = a + b;
    a = b;
    b = c;
    c = d;
  }

  return c;
}



int main() {
  printf("%d\n", firstMethod(10));
  printf("%d\n", secondMethod(10));
  printf("%d\n", thirdMethod(10));
  printf("%d\n", fourthMethod(10));

  return 0;
}
