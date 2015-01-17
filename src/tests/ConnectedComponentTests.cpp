#include "tests/GraphTests.h"

#include "ConnectedComponents.h"
#include "Graph.h"
#include "WeightedGraph.h"
#include "utils/TestUtils.h"


namespace algorithm
{
   static void graphCCTests()
   {
      Graph g(6);
      std::vector<Edge> inputs{ { 0, 1 }, { 0, 2 }, { 1, 2 }, { 3, 4 } };
      for (auto& e : inputs)
         g.addEdge(e);

      ConnectedComponents cc(g);
      assert(3 == cc.componentCount());
      assert(true == cc.connected(0, 0));
      assert(true == cc.connected(0, 2));
      assert(true == cc.connected(3, 4));
      assert(false == cc.connected(0, 3));
      assert(false == cc.connected(3, 5));
   }

   static void weightedGraphCCTests()
   {
      WeightedGraph g(6);
      std::vector<WeightedEdge> inputs{ { 0, 1, 1. }, { 0, 2, 1. }, { 1, 2, 1. }, { 3, 4, 1. } };
      for (auto& e : inputs)
         g.addEdge(e);

      ConnectedComponents cc(g);
      assert(3 == cc.componentCount());
      assert(true == cc.connected(0, 0));
      assert(true == cc.connected(0, 2));
      assert(true == cc.connected(3, 4));
      assert(false == cc.connected(0, 3));
      assert(false == cc.connected(3, 5));
   }

   //--------------------------------------------------------------------------

   void connectedComponentsTests()
   {
      graphCCTests();
      weightedGraphCCTests();
   }
}
