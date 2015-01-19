#include "tests/GraphTests.h"

#include "TopologicalSort.h"
#include "DiGraph.h"
#include "WeightedDiGraph.h"
#include "tests/GraphTestUtils.h"
#include "utils/Algorithms.h"

#include <assert.h>
#include <iostream>


namespace algorithm
{
   static void basicTopologicalSort()
   {
      DiGraph g(10);
      for (size_t i = 1; i < 10; ++i)
         g.addEdge({ i - 1, i });

      TopologicalSort sort(g);
      assert(true == sort.hasOrder());

      std::vector<size_t> expected = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
      assert(equal(sort.order(), expected));
   }

   static void planeTopologicalSort()
   {
      DiGraph g = topLeftBottomRightPlane(10);
      TopologicalSort sort(g);
      assert(true == sort.hasOrder());
   }

   void topologicalSortTests()
   {
      basicTopologicalSort();
      planeTopologicalSort();
   }
}
