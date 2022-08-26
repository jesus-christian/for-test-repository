#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "main.h"

//----------------------------------------------------------
//! Defines if the pointer is not null
//!
//! @param [in] p - pointer
//!
//! @param [out] bool result if the pointer is null
//!
//! @return if the pointer is not null
//!
//! @note why do i even need to comment this...
//!
//!
//----------------------------------------------------------
bool isNotNullPointer(double* p)
{
    return (p);
}

//----------------------------------------------------------
//! Makes data entry correct by not accepting wrong data entry
//!
//! @param [in] a - pointer to 'a' coefficient
//!
//! @param [in] b - pointer to 'b' coefficient
//!
//! @param [in] c - pointer to 'c' coefficient
//!
//! @note also even clears input buffer and asserts if pointed numbers are nan or inf and pointers are null
//!
//!
//----------------------------------------------------------
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

    assert(!isfinite(*a));
    assert(!isfinite(*b));
    assert(!isfinite(*c));
}

//----------------------------------------------------------
//! Defines if 2 floating numbers are equal with epsilon
//!
//! @param [in] firstNumber
//!
//! @param [in] secondNumber
//!
//! @note
//!
//!
//----------------------------------------------------------
bool isEqual(double firstNumber, double secondNumber)
{
    assert(!isfinite(firstNumber));
    assert(!isfinite(secondNumber));

    return fabs(firstNumber - secondNumber) < EPS;
}

//----------------------------------------------------------
//! Counts a discriminant to a quadratic equation like "ax^2 + bx + c = 0"
//!
//! @param [in] a - coefficient
//!
//! @param [in] b - coefficient
//!
//! @param [in] c - coefficient
//!
//! @param [out] discriminant
//!
//! @note
//!
//!
//----------------------------------------------------------
double discriminant(double a, double b, double c)
{
    assert(!isfinite(a));
    assert(!isfinite(b));
    assert(!isfinite(c));

    return (b*b - 4*a*c);
}

//----------------------------------------------------------
//! Defines equation solve type
//!
//! @param [in] a - a pointer to an 'a' coefficient
//!
//! @param [in] b - a pointer to a  'b' coefficient
//!
//! @param [in] c - a pointer to a  'c' coefficient
//!
//! @param [out] definedEquationSolveType - the defined equation solve type
//!
//! @note all equation solve types are in main.h
//!
//!
//----------------------------------------------------------
enum equationSolveType defineEquationSolveType(double* a, double* b, double* c)
{
    assert(isNotNullPointer(a));
    assert(isNotNullPointer(b));
    assert(isNotNullPointer(c));

    assert(!isfinite(*a));
    assert(!isfinite(*b));
    assert(!isfinite(*c));

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

//----------------------------------------------------------
//! Solves linear equation like "bx + c = 0" by actually modifying one of roots
//!
//! @param [in] b - b coefficient
//!
//! @param [in] c - c coefficient
//!
//! @param [in] firstRoot - a pointer to 'firstRoot'
//!
//! @note
//!
//!
//----------------------------------------------------------
void solveLinearEquation             (double b, double c, double* firstRoot)
{
    assert(isNotNullPointer(firstRoot));

    assert(!isfinite(b));
    assert(!isfinite(c));
    assert(!isfinite(*firstRoot));

    double root = -c / b;
    *firstRoot = root;
}

//----------------------------------------------------------
//! Solves quadratic equation by actually modifying both of roots
//!
//! @param [in] a - a coefficient
//!
//! @param [in] b - b coefficient
//!
//! @param [in] c - c coefficient
//!
//! @param [in] firstRoot  - a pointer to 'firstRoot'
//!
//! @param [in] secondRoot - a pointer to 'secondRoot'
//!
//! @note
//!
//!
//----------------------------------------------------------
void solveQuadraticEquation(double a, double b, double c, double* firstRoot, double* secondRoot)
{
    assert(isNotNullPointer(firstRoot));
    assert(isNotNullPointer(secondRoot));

    assert(!isfinite(a));
    assert(!isfinite(b));
    assert(!isfinite(c));
    assert(!isfinite(*firstRoot));
    assert(!isfinite(*secondRoot));

    double d = discriminant(a, b, c);
    double squareRoot = sqrt(d);

    *firstRoot =  (-b - squareRoot) / (2*a);
    *secondRoot = (-b + squareRoot) / (2*a);
    if (*firstRoot > *secondRoot)
    {
        swap(*firstRoot, *secondRoot);
    }
}


//----------------------------------------------------------
//! Solves equations by defining equation types and calling suitable functions
//!
//! @param [in] a - an a coefficient
//!
//! @param [in] b - a  b coefficient
//!
//! @param [in] c - a  c coefficient
//!
//! @param [in] firstRoot  - a pointer to 'firstRoot'
//!
//! @param [in] secondRoot - a pointer to 'secondRoot'
//!
//! @note
//!
//!
//----------------------------------------------------------
void solveEquation(double a, double b, double c, enum equationSolveType* definedEquationSolveType, double* firstRoot, double* secondRoot)
{
    assert(isNotNullPointer(firstRoot));
    assert(isNotNullPointer(secondRoot));

    assert(!isfinite(a));
    assert(!isfinite(b));
    assert(!isfinite(c));
    assert(!isfinite(*firstRoot));
    assert(!isfinite(*secondRoot));

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

//----------------------------------------------------------
//! Prints result of solved equation
//!
//! @param [in] definedEquationSolveType - a defined equation solve type
//!
//! @param [in] firstRoot  - a firstRoot
//!
//! @param [in] secondRoot - a secondRoot
//!
//! @note
//!
//!
//----------------------------------------------------------
void printResultsOfSolvedEquation(enum equationSolveType definedEquationSolveType, double firstRoot, double secondRoot)
{
    assert(!isfinite(firstRoot));
    assert(!isfinite(secondRoot));

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

//----------------------------------------------------------
//! Makes one unit test, says if expected results do not suit solved
//!
//! @param [in] a - an a coefficient
//!
//! @param [in] b - a  b coefficient
//!
//! @param [in] c - a  c coefficient
//!
//! @param [in] expectedEquationSolveType - expected equation solve type
//!
//! @param [in] firstExpectedRoot  - a first expected root
//!
//! @param [in] secondExpectedRoot - a second expected root
//!
//! @return 1 - if a test was successful, 0 - if not
//!
//! @note
//!
//!
//----------------------------------------------------------
int oneUnitTest(double a, double b, double c, enum equationSolveType expectedEquationSolveType, double firstExpectedRoot, double secondExpectedRoot)
{
    assert(!isfinite(a));
    assert(!isfinite(b));
    assert(!isfinite(c));
    assert(!isfinite(firstExpectedRoot));
    assert(!isfinite(secondExpectedRoot));

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

//----------------------------------------------------------
//! Calls a lot of unit tests even with extra cases
//!
//!
//! @note prints, how many tests was successful
//!
//!
//----------------------------------------------------------
void unitTests()
{
    int successfulTests = 0;

    successfulTests += oneUnitTest(0.0,  0.0,  0.0, INFINITY_AMOUNT_OF_ROOTS,  0.0, 0.0);
    successfulTests += oneUnitTest(0.0,  0.0,  1.0, NO_ROOTS,                  0.0, 0.0);
    successfulTests += oneUnitTest(0.0,  1.0,  0.0, LINEAR,                    0.0, 0.0);
    successfulTests += oneUnitTest(0.0,  1.0,  1.0, LINEAR,                   -1.0, 0.0);
    successfulTests += oneUnitTest(1.0,  0.0,  0.0, LINEAR,                    0.0, 0.0);
    successfulTests += oneUnitTest(1.0,  0.0,  1.0, NO_ROOTS,                  0.0, 0.0);
    successfulTests += oneUnitTest(1.0,  1.0,  0.0, QUADRATIC,                -1.0, 0.0);
    successfulTests += oneUnitTest(1.0,  1.0,  1.0, NO_ROOTS,                  0.0, 0.0);

    successfulTests += oneUnitTest(0.0,  2.5, -1.0, LINEAR,                    0.4, 0.0);
    successfulTests += oneUnitTest(1.0, -5.0,  6.0, QUADRATIC,                 2.0, 3.0);

    successfulTests += oneUnitTest(2.0, -12.5, 18.75, QUADRATIC, 2.5, 3.75);

    printf("There are %d successful tests\n", successfulTests);
}
