#include "Simplex.h"


namespace algorithm
{
   Simplex::InvalidInputs::InvalidInputs()
      : std::domain_error("Size of matrix and vector do not match")
   {}


   double Simplex::solve(Vector const& c, Matrix const& a, Vector const& b)
   {
      if (c.size() != a.width() || b.size() != a.height())
         throw InvalidInputs();

      /**
       * Building the simplex matrix:
       * | A I | b |
       * | c 0 | 0 |
       */
      size_t bOffset = a.width() + b.size();
      size_t w = 1 + bOffset;
      size_t h = 1 + a.height();
      Matrix m(w, h, 0.);
      
      /** - Max coefficient line */
      m.at(0, 0) = 1;
      for (size_t x = 0; x < c.size(); ++x)
         m.at(x, a.height()) = c[x];

      /** - Matrix A */
      for (size_t y = 0; y < a.height(); ++y)
         for (size_t x = 0; x < a.width(); ++x)
            m.at(x, y) = a.at(x, y);

      /** - Identity matrix I and bounds b */
      for (size_t i = 0; i < b.size(); ++i)
      {
         m.at(a.width() + i, i) = 1;
         m.at(a.width() + b.size(), i) = b[i];
      }

      /** Run the simplex, starting with the basic solution */
      while (true)
      {
         /** - Find a pivot column: it must have positive coefficient */
         size_t col = c.size();
         for (size_t x = 0; x < c.size(); ++x)
         {
            if (0 < m.at(x, a.height()))
            {
               col = x;
               break;
            }
         }
         if (col == c.size())
            break;

         /** - Find the matching row: the one with the min ratio b[y] / a[col, y] */
         size_t row = 0;
         double ratio = std::numeric_limits<double>::max();
         for (size_t y = 0; y < a.height(); ++y)
         {
            double tempRatio = m.at(bOffset, y) / m.at(col, y);
            if (tempRatio < ratio)
            {
               ratio = tempRatio;
               row = y;
            }
         }

         /** - Re-write the pivot column to normalize and have coeff one for the pivot var */
         double pivotCoeff = m.at(col, row);
         for (size_t x = 0; x < w; ++x)
            m.at(x, row) /= pivotCoeff;

         /** - Substitution: remove from other row the pivot row * pivot coeff in this row */
         for (size_t y = 0; y < h; ++y)
         {
            if (y == row)
               continue;
            
            double pCoeff = m.at(col, y);
            for (size_t x = 0; x < w; ++x)
               m.at(x, y) = m.at(x, y) - m.at(x, row) * pCoeff;
         }
      }

      return -1. * m.at(w - 1, h - 1);
   }
}
