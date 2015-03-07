#include "GraphTests.h"

#include "DiGraph.h"
#include "Graph.h"
#include "SymbolGraph.h"
#include "WeightedDiGraph.h"
#include "utils/TestUtils.h"

#include <assert.h>
#include <iostream>
#include <sstream>


namespace algorithm
{
   static void undirectedGraphTests()
   {
      Graph g(5);
      g.addEdge({ 0, 1 });
      g.addEdge({ 0, 1 });
      g.addEdge({ 1, 2 });

      assert(5 == g.vertexCount());
      assert(3 == g.edgeCount());

      assert(2 == adjacentCount(g, 0));
      assert(3 == adjacentCount(g, 1));
      assert(1 == adjacentCount(g, 2));
      assert(0 == adjacentCount(g, 3));
      assert(0 == adjacentCount(g, 4));

      utils::ExceptionChecker<InvalidVertex> tester;
      tester.assertE([&]{ g.addEdge({ 1, 5 }); });
      tester.assertE([&]{ g.addEdge({ 5, 1 }); });
      tester.assertE([&]{ g.adjacents(5); });

      g.addVertex();
      assert(0 == adjacentCount(g, 5));

      std::istringstream inStream("5 \n 0 1 \n 1 2 \n 1 3 \n 1 4; 1 5 ");
      Graph g2 = graphFrom(inStream);
      assert(5 == g2.vertexCount());
      assert(4 == g2.edgeCount());

      std::stringstream outStream;
      graphTo(outStream, g2);
      Graph g3 = graphFrom(outStream);
      assert(5 == g3.vertexCount());
      assert(4 == g3.edgeCount());
   }

   static void directedGraphTests()
   {
      WeightedDiGraph wg(5);
      wg.addEdge({ 0, 1, 1. });
      wg.addEdge({ 0, 2, 1. });
      wg.addEdge({ 3, 4, 2. });

      assert(5 == wg.vertexCount());
      assert(3 == wg.edgeCount());

      std::stringstream outStream;
      serializeTo(outStream, wg);
      WeightedDiGraph wg2 = weightedDiGraphFrom(outStream);
      assert(5 == wg2.vertexCount());
      assert(3 == wg2.edgeCount());
   }

   void graphTests()
   {
      undirectedGraphTests();
      directedGraphTests();
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
