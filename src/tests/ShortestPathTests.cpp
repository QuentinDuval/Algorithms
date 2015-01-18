#include "tests/ShortestPathTests.h"

#include "DiGraph.h"
#include "Graph.h"
#include "ShortestPath.h"
#include "utils/Algorithms.h"

#include <assert.h>
#include <iostream>
#include <sstream>


namespace algorithm
{
   void shortestPathTests()
   {
      //Two dimentional plane
      size_t dim = 4;
      Graph g(dim * dim);
      for (size_t i = 0; i < g.vertexCount(); ++i)
      {
         size_t x = i % dim;
         if (x < 3)
            g.addEdge({ i, i + 1 });

         size_t y = i / dim;
         if (y < 3)
            g.addEdge({ i, i + dim });
      }

      //Testing Manhattan distance
      ShortestPathFrom sp(g, 0);
      for (size_t i = 0; i < g.vertexCount(); ++i)
      {
         assert(true == sp.hasPathTo(i));
         size_t x = i % dim;
         size_t y = i / dim;
         size_t expectedLength = x + y;
         assert(expectedLength == sp.pathLengthTo(i));
      }

      //Testing paths
      assert(equal(sp.pathTo(15), std::vector<size_t>{1, 2, 3, 7, 11, 15}));
   }
}
