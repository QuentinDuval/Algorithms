#include "tests/GraphTests.h"

#include "SpanningTree.h"
#include "Graph.h"
#include "WeightedGraph.h"
#include "utils/TestUtils.h"
#include "utils/Timer.h"

#include <iostream>


namespace algorithm
{
   static void graphTreeTests()
   {
      Graph g(6);
      std::vector<Edge> inputs{ { 0, 1 }, { 0, 2 }, { 1, 2 }, { 3, 4 } };
      for (auto& e : inputs)
         g.addEdge(e);

      SpanningTree spt(g);
      assert(3 == spt.connectedComponentCount());
      assert(2 == spt.edges(0).size());
      assert(1 == spt.edges(1).size());
      assert(0 == spt.edges(2).size());
   }

   void spanningTreeTests()
   {
      graphTreeTests();
   }
}
