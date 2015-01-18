#include "tests/ShortestPathTests.h"

#include "DiGraph.h"
#include "Graph.h"
#include "ShortestPath.h"
#include "utils/Algorithms.h"
#include "utils/Timer.h"

#include <assert.h>
#include <iostream>
#include <sstream>


namespace algorithm
{
   static Graph twoDimPlane(size_t dim)
   {
      Graph g(dim * dim);
      for (size_t i = 0; i < g.vertexCount(); ++i)
      {
         size_t x = i % dim;
         if (x < dim - 1)
            g.addEdge({ i, i + 1 });

         size_t y = i / dim;
         if (y < dim - 1)
            g.addEdge({ i, i + dim });
      }
      return g;
   }

   void shortestPathTests()
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

   //--------------------------------------------------------------------------

   void shortestPathPerformanceTests()
   {
      size_t size = 1000;
      Graph g = twoDimPlane(size);

      std::cout << std::endl << "[Shortest path] Unweighed graph of size " << size * size << std::endl;
      showTime(std::cout, [&]{
         ShortestPathFrom sp(g, 0);
      });
   }
}
