#include "tests/ShortestPathTests.h"

#include "DiGraph.h"
#include "Graph.h"
#include "ShortestPath.h"
#include "tests/GraphTestUtils.h"
#include "utils/Algorithms.h"
#include "utils/Timer.h"

#include <assert.h>
#include <iostream>
#include <sstream>


namespace algorithm
{
   static void graphShortestPathTests()
   {
      //Two dimentional plane
      const size_t dim = 4;
      Graph g = twoDimPlane(dim);

      //Testing Manhattan distance
      ShortestPathFrom sp(g, 0);
      for (size_t i = 0; i < g.vertexCount(); ++i)
      {
         size_t expectedLength = i % dim + i / dim;
         assert(true == sp.hasPathTo(i));
         assert(expectedLength == sp.pathLengthTo(i));
      }

      //Testing paths
      assert(equal(sp.pathTo(15), std::vector<size_t>{1, 2, 3, 7, 11, 15}));
   }

   static void weightedGraphShortestPathTests()
   {
      //Two dimentional plane
      const size_t dim = 4;
      WeightedGraph g = twoDimWeightedPlane(dim);

      //Testing Manhattan distance
      DijkstraShortestPathFrom sp(g, 0);
      for (size_t i = 0; i < g.vertexCount(); ++i)
      {
         double expectedLength = i % dim + i / dim;
         assert(true == sp.hasPathTo(i));
         assert(expectedLength == sp.pathLengthTo(i));
      }

      //Testing paths
      assert(equal(sp.pathTo(15), std::vector<size_t>{1, 5, 6, 7, 11, 15}));
   }

   void shortestPathTests()
   {
      graphShortestPathTests();
      weightedGraphShortestPathTests();
   }

   //--------------------------------------------------------------------------

   void shortestPathPerformanceTests()
   {
      size_t dim = 1000;

      Graph g = twoDimPlane(dim, true);
      std::cout << std::endl << "[Shortest path] Unweighed graph of size " << dim * dim << std::endl;
      showTime(std::cout, [&]{
         ShortestPathFrom sp(g, 0);
      });

      WeightedGraph wg = twoDimRandomWeightedPlane(dim, true);
      std::cout << std::endl << "[Shortest path] Weighed graph of size " << dim * dim << std::endl;
      showTime(std::cout, [&]{
         DijkstraShortestPathFrom sp(wg, 0);
      });
   }
}
