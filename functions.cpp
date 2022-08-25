#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "main.h"

bool isNotNullPointer(double* p)
{
    return (!p);
}
void makeDataEntryCorrect(double* a, double* b, double* c)
{
    
    while (scanf("%lg %lg %lg", a, b, c) != 3)
    {
        /*
        assert(isNotNullPointer(a));
        assert(isNotNullPointer(b));
        assert(isNotNullPointer(c));

        assert(!isnan(*a));
        assert(!isnan(*b));
        assert(!isnan(*c));
        */
        printf("Data entry is not correct, please try again\n");
        while (getchar() != '\n')
        {
            continue;
        }
    }
    while (getchar() != '\n')
    {
        continue;
    }
}
bool isEqual(double firstNumber, double secondNumber)
{
    return fabs(firstNumber - secondNumber) < EPS;
}
double discriminant(double a, double b, double c)
{
    return (b*b - 4*a*c);
}
enum equationSolveType defineEquationSolveType(double* a, double* b, double* c)
{
    
    if      (isEqual(*a, 0.0) && isEqual(*b, 0.0) && isEqual(*c, 0.0))
        return INFINITY_AMOUNT_OF_ROOTS;
    else if (isEqual(*a, 0.0) && isEqual(*b, 0.0))
        return NO_ROOTS;
    else if (isEqual(*a, 0.0))
        return LINEAR; 
    else
    {
        double d = discriminant(*a, *b, *c);
        if (isEqual(d, 0.0))
        {
            *c = *b;
            *b = 2 * (*a);
            *a = 0.0;
            return LINEAR;
        }
        else if (d < 0.0)
            return NO_ROOTS;
        else
            return QUADRATIC;
    }
}
void solveLinearEquation             (double b, double c, double* firstRoot)
{
    double root = -c / b;
    *firstRoot = root;
}
void solveQuadraticEquation(double a, double b, double c, double* firstRoot, double* secondRoot)
{
    double d = discriminant(a, b, c);
    double squareRoot = sqrt(d);

    *firstRoot =  (-b - squareRoot) / (2*a);
    *secondRoot = (-b + squareRoot) / (2*a);
}
void solveEquation(double a, double b, double c)
{
    double firstRoot = 0.0, secondRoot = 0.0;
    enum equationSolveType definedEquationSolveType = defineEquationSolveType(&a, &b, &c);

    switch (definedEquationSolveType)
    {
        case NO_ROOTS:
            printf("There are no roots\n");
            break;
        case INFINITY_AMOUNT_OF_ROOTS:
            printf("There are infinity amount of roots\n");
            break;
        case LINEAR:
            solveLinearEquation                 (b, c, &firstRoot);
            printf("There is 1 root: %.2lg\n",          firstRoot); 
            break;
        case QUADRATIC:
            solveQuadraticEquation           (a, b, c, &firstRoot, &secondRoot);
            printf("There are 2 roots: %.2lg, %.2lg\n", firstRoot, secondRoot);
            break;
        default:
            break;
    }
}
