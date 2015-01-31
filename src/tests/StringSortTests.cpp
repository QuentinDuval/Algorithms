#include "tests/StringSortTests.h"

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
      std::vector<std::string> strings = 
      {
         "toto", "auto", "tata", "blub", "zerg", "abc"
      };

      MSBSort::sort(strings);
      assert(isSorted(strings));
   }

   //--------------------------------------------------------------------------

   void stringSortingPerfTests()
   {
      size_t dim = 100000;
      std::vector<std::string> strings(dim);
      for (size_t i = 0; i < dim; ++i)
      {
         for (size_t j = i; j != 0; j /= 27)
            strings[i] += ('a' + j - 1);
      }
      shuffle(strings);

      std::cout << std::endl << "[String sort timings]"
         << "(" << dim << " entries - in milliseconds)" << std::endl;

      std::cout << "* Radix sort (" << dim << ")" << std::endl;
      showTime(std::cout, [=]() mutable { MSBSort::sort(strings); });

      std::cout << "* System sort (" << dim << ")" << std::endl;
      showTime(std::cout, [=]() mutable { std::sort(begin(strings), end(strings)); });
   }
}
