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
   template<typename GraphType>
   GraphType makePlane(size_t dim)
   {
      GraphType g(dim * dim);
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


   Graph twoDimPlane(size_t dim)
   {
      return makePlane<Graph>(dim);
   }

   DiGraph topLeftBottomRightPlane(size_t dim)
   {
      return makePlane<DiGraph>(dim);
   }
}
