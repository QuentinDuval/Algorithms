#include "BinarySearchTests.h"

#include "BinarySearch.h"

#include <assert.h>
#include <vector>


namespace algorithm
{
   void binarySearchTests()
   {
      std::vector<int> values = { 1, 2, 5, 8, 8, 10 };
      assert(end(values) != binarySearch(values, 2));

      //assert(end(values) == binarySearch(values, 0));
      //assert(end(values) == binarySearch(values, 4));
      //assert(end(values) == binarySearch(values, 11));
      //for (int v : values)
      //   assert(end(values) != binarySearch(values, v));
   }
}
