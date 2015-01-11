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

      assert(2 == adjacentCount(g, 0));
      assert(3 == adjacentCount(g, 1));
      assert(1 == adjacentCount(g, 2));
      assert(0 == adjacentCount(g, 3));
      assert(0 == adjacentCount(g, 4));

      ExceptionChecker<InvalidVertex> tester;
      tester.assertE([&]{ g.addEdge(1, 5); });
      tester.assertE([&]{ g.addEdge(5, 1); });
      tester.assertE([&]{ g.beginAdj(5); });
      tester.assertE([&]{ g.endAdj(5); });

      g.addVertex();
      assert(0 == adjacentCount(g, 5));
   }
}
