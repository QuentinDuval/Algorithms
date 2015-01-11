#include "tests/GraphTests.h"

#include "Graph.h"
#include "utils/TestUtils.h"
#include <assert.h>


namespace algorithm
{
   void graphTests()
   {
      Graph g(5);
      g.addEdge(0, 1);
      g.addEdge(0, 1);
      g.addEdge(1, 2);

      assert(5 == g.vertexCount());
      assert(3 == g.edgeCount());
   }
}
