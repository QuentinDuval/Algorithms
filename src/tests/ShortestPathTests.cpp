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
      const size_t dim = 4;
      Graph g = make2DPlane(dim);

      //Testing Manhattan distance
      ShortestPathFrom sp(g, 0);
      for (size_t i : g.vertices())
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
      const size_t dim = 4;
      WeightedGraph g = make2DWeightedPlane(dim);

      //Testing Manhattan distance
      DijkstraShortestPathFrom sp(g, 0);
      for (size_t i : g.vertices())
      {
         double expectedLength = i % dim + i / dim;
         assert(true == sp.hasPathTo(i));
         assert(expectedLength == sp.pathLengthTo(i));
      }

      //Testing paths
      assert(equal(sp.pathTo(15), std::vector<size_t>{1, 5, 9, 10, 11, 15}));
   }

   static void dagShortestPathTests()
   {
      const size_t dim = 4;
      WeightedDiGraph g = make2DWeightedDiPlane(dim);

      //Testing Manhattan distance
      TopologicalShortestPathFrom sp(g, 0);
      for (size_t i : g.vertices())
      {
         double expectedLength = i % dim + i / dim;
         assert(true == sp.hasPathTo(i));
         assert(expectedLength == sp.pathLengthTo(i));
      }
   }

   static void bellmanFordShortestPathTests()
   {
      const size_t dim = 4;
      WeightedGraph g = make2DWeightedPlane(dim);

      //Testing Manhattan distance
      BellmanFordShortestPathFrom sp(g, 0);
      for (size_t i : g.vertices())
      {
         double expectedLength = i % dim + i / dim;
         assert(true == sp.hasPathTo(i));
         assert(expectedLength == sp.pathLengthTo(i));
      }
   }

   void shortestPathTests()
   {
      graphShortestPathTests();
      weightedGraphShortestPathTests();
      dagShortestPathTests();
      bellmanFordShortestPathTests();
   }

   //--------------------------------------------------------------------------

   void shortestPathPerformanceTests()
   {
      size_t dim = 1000;

      Graph g = make2DPlane(dim, true);
      std::cout << std::endl << "[Shortest path] Unweighed graph of size " << dim * dim << std::endl;
      showTime(std::cout, [&]{
         ShortestPathFrom sp(g, 0);
      });

      WeightedGraph wg = make2DRandomWeightedPlane(dim, true);
      std::cout << std::endl << "[Shortest path] Weighed graph of size (Dijkstra) " << dim * dim << std::endl;
      showTime(std::cout, [&]{
         DijkstraShortestPathFrom sp(wg, 0);
      });

      WeightedDiGraph dag = make2DWeightedDiPlane(dim, true);
      std::cout << std::endl << "[Shortest path] Weighed graph of size (Topological) " << dim * dim << std::endl;
      showTime(std::cout, [&]{
         TopologicalShortestPathFrom sp(dag, 0);
      });
   }
}
