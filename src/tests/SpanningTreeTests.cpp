#include "tests/GraphTests.h"

#include "SpanningTree.h"
#include "Graph.h"
#include "WeightedGraph.h"
#include "tests/GraphTestUtils.h"
#include "utils/Algorithms.h"
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

   static void weightedGraphTreeTests()
   {
      WeightedGraph g(6);
      std::vector<WeightedEdge> inputs{ { 0, 1, 5. }, { 0, 2, 1. }, { 1, 2, 1. }, { 3, 4, 1. } };
      for (auto& e : inputs)
         g.addEdge(e);

      MinimumSpanningTree spt(g);
      assert(3 == spt.connectedComponentCount());
      assert(2 == spt.edges(0).size());
      double totalWeight = accumulate(spt.edges(0), 0., [](double weight, WeightedEdge const& e) { return weight + e.weight(); });
      assert(2. == totalWeight);
      assert(1 == spt.edges(1).size());
      assert(0 == spt.edges(2).size());
   }

   void spanningTreeTests()
   {
      graphTreeTests();
      weightedGraphTreeTests();
   }

   //--------------------------------------------------------------------------

   void spanningTreePerfTests()
   {
      size_t dim = 1000;
      WeightedGraph g = twoDimWeightedPlane(dim);

      std::cout << std::endl << "[Minimum spanning tree] Lazy prim's algorithm on " << dim * dim << " nodes." << std::endl;
      showTime(std::cout, [&]{
         MinimumSpanningTree spt(g);
         assert(1 == spt.connectedComponentCount());
         assert((dim * dim - 1) == spt.edges(0).size());
      });
   }
}
