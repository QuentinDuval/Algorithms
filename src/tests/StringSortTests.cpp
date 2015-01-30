#include "tests/StringSortTests.h"

#include "Sort.h"
#include "StringSort.h"

#include <assert.h>

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
}
