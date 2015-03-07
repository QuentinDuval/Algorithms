#include "SimplexTests.h"

#include "Simplex.h"
#include <iostream>


namespace algorithm
{
   static void brewerProblem()
   {
      Simplex::Vector maximize = { 13, 23 };
      Simplex::Vector limits = { 480, 160, 1190 };
      Simplex::Matrix constraints(2, 3, {
         5, 15,
         4, 4,
         35, 20
      });

      std::cout << Simplex::solve(maximize, constraints, limits) << std::endl;
   }

   void simplexTests()
   {
      brewerProblem();
   }
}
