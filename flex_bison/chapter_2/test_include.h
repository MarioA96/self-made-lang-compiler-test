#include <test_include_2.h>

#ifndef MY_FUNCTIONS_H
#define MY_FUNCTIONS_H

// Function declarations (prototypes)
void say_hello();
int add(int a, int b);
double calculate_area(double radius);

// Global constant declaration
extern const double PI;

// Macro definition
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#endif // MY_FUNCTIONS_H