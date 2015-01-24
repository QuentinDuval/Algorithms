#include "tests/GraphTests.h"

#include "TopologicalSort.h"
#include "DiGraph.h"
#include "WeightedDiGraph.h"
#include "tests/GraphTestUtils.h"
#include "utils/Algorithms.h"
#include "utils/Timer.h"

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
      DiGraph g = make2DTopLeftBottomRightPlane(10);
      TopologicalSort sort(g);
      assert(true == sort.hasOrder());
   }

   void topologicalSortTests()
   {
      basicTopologicalSort();
      planeTopologicalSort();
   }

   //--------------------------------------------------------------------------

   void topologicalSortPerfTests()
   {
      size_t dim = 1000;
      WeightedDiGraph dag = make2DWeightedDiPlane(dim, true);
      std::cout << std::endl << "[Topological sort] Graph of size " << dim * dim << std::endl;
      showTime(std::cout, [&]{
         TopologicalSort sort(dag);
      });
   }
}
