#include "ShortestPathTests.h"

#include "DiGraph.h"
#include "Graph.h"
#include "ShortestPath.h"
#include "GraphTestUtils.h"
#include "utils/Algorithms.h"
#include "utils/Timer.h"

#include <assert.h>
#include <cmath>
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
      assert(utils::equal(sp.pathTo(15), std::vector<size_t>{1, 2, 3, 7, 11, 15}));
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
      assert(utils::equal(sp.pathTo(15), std::vector<size_t>{1, 5, 9, 10, 11, 15}));
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

   static void floydWarshallShortestPathTests()
   {
      const size_t dim = 4;
      WeightedGraph g = make2DWeightedPlane(dim);

      FloydWarshallShortestPath sp(g);
      for (size_t i : g.vertices())
      {
         double expectedLength = i % dim + i / dim;
         assert(expectedLength == sp.pathLength(0, i));
      }
   }

   static double noEstimations (size_t, size_t)
   {
      return 0.;
   };

   static double manhattanDistance(size_t dim, size_t from, size_t to)
   {
      int fromX = from % dim;
      int fromY = from / dim;
      int toX = to % dim;
      int toY = to / dim;
      return abs(fromX - toX) + abs(fromY - toY);
   };

   static void aStarShortestPathFromToTests()
   {
      const size_t dim = 4;
      WeightedGraph g = make2DWeightedPlane(dim);

      AStarShortestPathFromTo dijkstra(g, noEstimations);
      assert(6. == dijkstra.shortestPath(0, 15).first);

      AStarShortestPathFromTo aStar(g, [dim](size_t from, size_t to) { return manhattanDistance(dim, from, to); });
      assert(6. == aStar.shortestPath(0, 15).first);
   }

   void shortestPathTests()
   {
      graphShortestPathTests();
      weightedGraphShortestPathTests();
      dagShortestPathTests();
      bellmanFordShortestPathTests();
      floydWarshallShortestPathTests();
      aStarShortestPathFromToTests();
   }

   //--------------------------------------------------------------------------

   void shortestPathPerformanceTests()
   {
      size_t dim = 1000;

      Graph g = make2DPlane(dim, true);
      std::cout << std::endl << "[Shortest path] Unweighed graph of size " << dim * dim << std::endl;
      utils::showTime(std::cout, [&]{
         ShortestPathFrom sp(g, 0);
      });

      WeightedGraph wg = make2DRandomWeightedPlane(dim, true);
      std::cout << std::endl << "[Shortest path] Weighed graph of size (Dijkstra) " << dim * dim << std::endl;
      utils::showTime(std::cout, [&]{
         DijkstraShortestPathFrom sp(wg, 0);
      });

      std::cout << std::endl << "[Shortest path] Weighed graph of size (Bellman-Ford) " << dim * dim << std::endl;
      utils::showTime(std::cout, [&]{
         BellmanFordShortestPathFrom sp(wg, 0);
      });

      WeightedDiGraph dag = make2DWeightedDiPlane(dim, true);
      std::cout << std::endl << "[Shortest path] Weighed graph of size (Topological) " << dim * dim << std::endl;
      utils::showTime(std::cout, [&]{
         TopologicalShortestPathFrom sp(dag, 0);
      });

      std::cout << std::endl << "[Single shortest path] (Dijkstra) Unweighed graph of size " << dim * dim << std::endl;
      utils::showTime(std::cout, [&]{
         AStarShortestPathFromTo sp(wg, noEstimations);
         sp.shortestPath(0, dim * dim - 1);
      });

      std::cout << std::endl << "[Single shortest path] (A*) Unweighed graph of size " << dim * dim << std::endl;
      utils::showTime(std::cout, [&]{
         AStarShortestPathFromTo sp(wg, [dim](size_t from, size_t to) { return manhattanDistance(dim, from, to); });
         sp.shortestPath(0, dim * dim - 1);
      });
   }
}
