#include <stdio.h>
#include <string.h>
#include "functions.hpp"


int main(int argc, char* argv[])
{
   double a = 0.0, b = 0.0, c = 0.0;
   double firstRoot = 0.0, secondRoot = 0.0;
   enum equationSolveType definedEquationSolveType = {};

   //printf("Enter Solve to solve quadratic equation or Test to launch unit tests\n");

   if (argc != 2)
   {
        printf("You entered not correct numbers of arguments\n");
        return 0;
   }

   if (!strcmp(argv[1], "Solve"))
   {
        printf("Enter 3 coefficients such as a, b, c to solve quadratic equation:\n"); 
        makeDataEntryCorrect(&a, &b, &c);
        solveEquation(a, b, c, &definedEquationSolveType, &firstRoot, &secondRoot);
        printResultsOfSolvedEquation(definedEquationSolveType, firstRoot, secondRoot);
   }
   else if (!strcmp(argv[1], "Test"))
   {
        unitTests();
   }
   else
   {
        printf("You entered not correct command");
   }   

   return 0;
}

