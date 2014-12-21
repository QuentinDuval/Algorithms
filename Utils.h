#pragma once

#include <assert.h>
#include <sstream>
#include <string>


namespace algorithm
{
   template<typename FwdIter, typename ValueType, typename NextFct>
   void generate(FwdIter first, FwdIter last, ValueType const& val, NextFct next)
   {
      for (auto nextVal = val; first != last; ++first)
      {
         *first = nextVal;
         nextVal = next(nextVal);
      }
   }

   template<typename Container, typename ValueType, typename NextFct>
   void generate(Container& cont, ValueType const& val, NextFct next)
   {
      generate(begin(cont), end(cont), val, next);
   }

   template<typename T>
   std::string toString(T const& t)
   {
      std::ostringstream os;
      os << t;
      return os.str();
   }
}
