#include "GraphTests.h"

#include "ConnectedComponents.h"
#include "Graph.h"
#include "WeightedGraph.h"
#include "GraphTestUtils.h"
#include "utils/TestUtils.h"
#include "utils/Timer.h"

#include <iostream>


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

   static void stronglyCCTests()
   {
      DiGraph g1 = make2DTopLeftBottomRightPlane(4);
      ConnectedComponents cc1(g1);
      assert(16 == cc1.componentCount());

      DiGraph g2 = makeReversed(g1);
      ConnectedComponents cc2(g2);
      assert(16 == cc2.componentCount());

      DiGraph g3 = make2DPlane(4).toDiGraph();
      ConnectedComponents cc3(g3);
      assert(1 == cc3.componentCount());
   }

   void connectedComponentsTests()
   {
      graphCCTests();
      weightedGraphCCTests();
      stronglyCCTests();
   }
}
