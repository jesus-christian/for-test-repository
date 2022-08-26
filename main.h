#ifndef _MAIN_H
#define _MAIN_H

const int True = 1;
const int False = 0;

static const double EPS = 1e-7;

#define swap(x,y) do {\
    typeof(x) _x = x; \
    typeof(y) _y = y; \
    x = _y;           \
    y = _x;           \
    } while(0)

enum equationSolveType
{
    NO_ROOTS,
    INFINITY_AMOUNT_OF_ROOTS,
    LINEAR,
    QUADRATIC
};

bool isNotNullPointer(double* p);
void makeDataEntryCorrect(double* a, double* b, double* c);
bool isEqual(double firstNumber, double secondNumber);
double discriminant(double a, double b, double c);
enum equationSolveType defineEquationSolveType(double* a, double* b, double* c);
void solveLinearEquation             (double b, double c, double* firstRoot);
void solveQuadraticEquation(double a, double b, double c, double* firstRoot, double* secondRoot);
void solveEquation(double a, double b, double c, enum equationSolveType* definedEquationSolveType, double* firstRoot, double* secondRoot);
void printResultsOfSolvedEquation(enum equationSolveType definedEquationSolveType, double firstRoot, double secondRoot);
int oneUnitTest            (double a, double b, double c, enum equationSolveType expectedEquationSolveType, double firstExpectedRoot, double secondExpectedRoot);
void unitTests();

#endif
