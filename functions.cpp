#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "main.h"

bool isNotNullPointer(double* p)
{
    return (p);
}

void makeDataEntryCorrect(double* a, double* b, double* c)
{
    
    while (scanf("%lg %lg %lg", a, b, c) != 3)
    { 
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

    assert(isNotNullPointer(a));
    assert(isNotNullPointer(b));
    assert(isNotNullPointer(c));

    assert(!isnan(*a));
    assert(!isinf(*a));
    assert(!isnan(*b));
    assert(!isinf(*b));
    assert(!isnan(*c));
    assert(!isinf(*c));
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
    if (*firstRoot > *secondRoot)
    {
        swap(*firstRoot, *secondRoot);
    }
}

void solveEquation(double a, double b, double c, enum equationSolveType* definedEquationSolveType, double* firstRoot, double* secondRoot)
{
    *firstRoot = 0.0, *secondRoot = 0.0;
    *definedEquationSolveType = defineEquationSolveType(&a, &b, &c);

    switch (*definedEquationSolveType)
    {
        case NO_ROOTS:
            break;

        case INFINITY_AMOUNT_OF_ROOTS:
            break;

        case LINEAR:
            solveLinearEquation                 (b, c, firstRoot);
            break;

        case QUADRATIC:
            solveQuadraticEquation           (a, b, c,   firstRoot,  secondRoot);
            break;
            
        default:
            break;
    }
}

void printResultsOfSolvedEquation(enum equationSolveType definedEquationSolveType, double firstRoot, double secondRoot)
{
    
    switch (definedEquationSolveType)
    {
        case NO_ROOTS:
            printf("There are no roots\n");
            break;

        case INFINITY_AMOUNT_OF_ROOTS:
            printf("There are infinity amount of roots\n");
            break;

        case LINEAR:
            printf("There is 1 root: %.2lg\n",        firstRoot); 
            break;

        case QUADRATIC:
            printf("There are 2 roots: %.2lg, %.2lg\n", firstRoot, secondRoot);
            break;
            
        default:
            break;
    }
}

int oneUnitTest(double a, double b, double c, enum equationSolveType expectedEquationSolveType, double firstExpectedRoot, double secondExpectedRoot)
{
    enum equationSolveType definedEquationSolveType = {};
    double firstSolvedRoot = 0.0, secondSolvedRoot = 0.0;

    solveEquation(a, b, c, &definedEquationSolveType, &firstSolvedRoot, &secondSolvedRoot);

    enum equationSolveType solvedEquationSolveType = defineEquationSolveType(&a, &b, &c);
    
    if (!(solvedEquationSolveType == expectedEquationSolveType && isEqual(firstExpectedRoot, firstSolvedRoot)
          && isEqual(secondExpectedRoot, secondSolvedRoot)))
    {
        printf("FAILED(%lg %lg %lg). SolveType expected: %d solved: %d. Roots expected: %lg %lg solved: %lg %lg\n", a, b, c, expectedEquationSolveType,
                solvedEquationSolveType, firstExpectedRoot, secondExpectedRoot, firstSolvedRoot, secondSolvedRoot);
        return 0;
    }
    else
    {
        printf("SUCCESFUL\n");
        return 1;
    }
}
void unitTests()
{
    oneUnitTest(0.0,  0.0,  0.0, INFINITY_AMOUNT_OF_ROOTS,  0.0, 0.0);
    oneUnitTest(0.0,  0.0,  1.0, NO_ROOTS,                  0.0, 0.0);
    oneUnitTest(0.0,  1.0,  0.0, LINEAR,                    0.0, 0.0);
    oneUnitTest(0.0,  1.0,  1.0, LINEAR,                   -1.0, 0.0);
    oneUnitTest(1.0,  0.0,  0.0, LINEAR,                    0.0, 0.0);
    oneUnitTest(1.0,  0.0,  1.0, NO_ROOTS,                  0.0, 0.0);
    oneUnitTest(1.0,  1.0,  0.0, QUADRATIC,                -1.0, 0.0);
    oneUnitTest(1.0,  1.0,  1.0, NO_ROOTS,                  0.0, 0.0);

    oneUnitTest(0.0,  2.5, -1.0, LINEAR,                    0.4, 0.0);
    oneUnitTest(1.0, -5.0,  6.0, QUADRATIC,                 2.0, 3.0);

    oneUnitTest(2.0, -12.5, 18.75, QUADRATIC, 2.5, 3.75);
}
