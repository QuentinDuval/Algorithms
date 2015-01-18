#include "tests/GraphTests.h"

#include "DiGraph.h"
#include "DirectedCycle.h"
#include "Graph.h"
#include "SymbolGraph.h"
#include "WeightedDiGraph.h"
#include "utils/TestUtils.h"

#include <assert.h>
#include <iostream>
#include <sstream>


namespace algorithm
{
   void graphTests()
   {
      Graph g(5);
      g.addEdge({0, 1});
      g.addEdge({0, 1});
      g.addEdge({1, 2});

      assert(5 == g.vertexCount());
      assert(3 == g.edgeCount());

      assert(2 == adjacentCount(g, 0));
      assert(3 == adjacentCount(g, 1));
      assert(1 == adjacentCount(g, 2));
      assert(0 == adjacentCount(g, 3));
      assert(0 == adjacentCount(g, 4));

      ExceptionChecker<InvalidVertex> tester;
      tester.assertE([&]{ g.addEdge({1, 5}); });
      tester.assertE([&]{ g.addEdge({5, 1}); });
      tester.assertE([&]{ g.adjacents(5); });

      g.addVertex();
      assert(0 == adjacentCount(g, 5));

      std::istringstream stream("5 \n 0 1 \n 1 2 \n 1 3 \n 1 4; 1 5 ");
      Graph g2 = graphFrom(stream);
      assert(5 == g2.vertexCount());
      assert(4 == g2.edgeCount());

      WeightedDiGraph wg(5);
      wg.addEdge({0, 1, 1. });
      wg.addEdge({0, 2, 1. });
      wg.addEdge({3, 4, 2. });

      assert(5 == wg.vertexCount());
      assert(3 == wg.edgeCount());

      for (auto e : wg.edgesFrom(0))
         std::cout << e.to() << std::endl;

      for (auto w : wg.adjacents(3))
         std::cout << w << std::endl;
   }

   //--------------------------------------------------------------------------

   void cycleTests()
   {
      DiGraph g(10);
      for (size_t i = 1; i < 10; ++i)
         g.addEdge({ i - 1, i });

      DirectedCycle<Edge> c1(g, 0);
      assert(false == c1.hasCycle());

      g.addEdge({ 0, 9 });
      DirectedCycle<Edge> c2(g, 0);
      assert(false == c2.hasCycle());

      g.addEdge({ 9, 2 });
      DirectedCycle<Edge> c3(g, 0);
      assert(true == c3.hasCycle());

      for (auto e : c3.cycle())
         std::cout << e << std::endl;
   }

   //--------------------------------------------------------------------------

   void symbolGraphTests()
   {
      auto inputs = { "a", "b", "c", "d", "e" };
      SymbolGraph<std::string> g(begin(inputs), end(inputs));
      g.addEdge("a", "b");
      g.addEdge("a", "c");
      g.addEdge("d", "e");

      assert(5 == g.vertexCount());
      assert(3 == g.edgeCount());
   }
}
