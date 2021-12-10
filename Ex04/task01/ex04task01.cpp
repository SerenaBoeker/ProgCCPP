#include <iostream>

/** 
* @brief Compares two numbers and returns the maximum of the two.
*
* @param x first number
* @param y second number
*/
#define MAXM(x,y) ( (x) > (y) ? (x) : (y) )

/**
 * @brief Compares two integers and returns the maximum of the two.
 * 
 * @param x first integer
 * @param y second integer
 * @return int the maximum of x and y
 */
int maxf(int x, int y) {
  std::cout << "In maxf(int)" << std::endl;
  return MAXM(x,y);
}

/**
 * @brief Compares two doubles and returns the maximum of the two.
 * 
 * @param x first double
 * @param y second double
 * @return double the maximum of x and y
 */
double maxf(double x, double y) {
  std::cout << "In maxf(double)"  << std::endl;
  return MAXM(x, y);
}


int main(void) {
  int a = 10, b = 20;
  std::cout << "MAXM1 = " << MAXM(a,b)      << std::endl;
  std::cout << "MAXM2 = " << MAXM(a,b+0.2)  << std::endl;
  std::cout << "MAXM3 = " << MAXM(a,b++)    << std::endl;
  std::cout << "maxf1 = " << maxf(a,b)      << std::endl;
  // what's the problem with the following line?
  //std::cout << "maxf = " << maxf(a,b+0.2) << std::endl;
  std::cout << "maxf2 = " << maxf(a+0.1,b+0.2)  << std::endl;
  std::cout << "maxf3 = " << maxf(a,b++)        << std::endl;
  std::cout << "a = " << a << ", b = " << b     << std::endl;
}