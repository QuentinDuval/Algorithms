#pragma once

#include "utils/Matrix.h"
#include <exception>
#include <vector>


namespace algorithm
{
   struct Simplex
   {
      using Vector = std::vector<double>;
      using Matrix = utils::Matrix<double>;

      //TODO - Return the allocation with the solution
      static double solve(Vector const& maxCoef, Matrix const& constraintsMatrix, Vector const& constraintsMaxValues);

      //-----------------------------------------------------------------------

      class InvalidInputs
         : std::domain_error
      {
         InvalidInputs();
         friend Simplex;
      };
   };
}
