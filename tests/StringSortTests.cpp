#include "StringSortTests.h"

#include "Sort.h"
#include "StringSort.h"
#include "utils/Algorithms.h"
#include "utils/Timer.h"

#include <algorithm>
#include <assert.h>
#include <iostream>


namespace algorithm
{
   void stringSortingTests()
   {
      std::vector<std::string> randomStrings = 
      {
         "toto", "auto", "tata", "blub", "zerg", "abc"
      };

      MSBSort::sort(randomStrings);
      assert(isSorted(randomStrings));
   }

   //--------------------------------------------------------------------------

   void stringSortingPerfTests()
   {
      size_t dim = 100000;
      std::vector<std::string> randomStrings(dim);
      for (size_t i = 0; i < dim; ++i)
      {
         for (size_t j = i; j != 0; j /= 27)
            randomStrings[i] += ('a' + j - 1);
      }
      utils::shuffle(randomStrings);

      std::vector<std::string> sameStrings(dim, "aaa");

      std::cout << std::endl << "[String sort timings]"
         << "(" << dim << " entries - in milliseconds)" << std::endl;

      std::cout << "* Radix sort (" << dim << ")" << std::endl;
      utils::showTime(std::cout, [=]() mutable { MSBSort::sort(randomStrings); });
      utils::showTime(std::cout, [=]() mutable { MSBSort::sort(sameStrings); });

      std::cout << "* System sort (" << dim << ")" << std::endl;
      utils::showTime(std::cout, [=]() mutable { std::sort(begin(randomStrings), end(randomStrings)); });
      utils::showTime(std::cout, [=]() mutable { std::sort(begin(sameStrings), end(sameStrings)); });
   }
}
