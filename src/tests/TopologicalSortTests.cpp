#include "tests/GraphTests.h"

#include "TopologicalSort.h"
#include "DiGraph.h"
#include "WeightedDiGraph.h"
#include "utils/Algorithms.h"

#include <assert.h>
#include <iostream>


namespace algorithm
{
   void topologicalSortTests()
   {
      DiGraph g(10);
      for (size_t i = 1; i < 10; ++i)
         g.addEdge({ i - 1, i });

      TopologicalSort sort(g);
      assert(true == sort.hasOrder());

      auto expected = {0,1,2,3,4,5,6,7,8,9};
      assert(equal(sort.order(), expected));
   }
}
