#include "tests/GraphTestUtils.h"

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
   template<typename GraphType, typename MakeEdge>
   GraphType makePlane(size_t dim, MakeEdge makeEdge)
   {
      GraphType g(dim * dim);
      for (size_t i = 0; i < g.vertexCount(); ++i)
      {
         size_t x = i % dim;
         if (x < dim - 1)
            g.addEdge(makeEdge(i, i + 1));

         size_t y = i / dim;
         if (y < dim - 1)
            g.addEdge(makeEdge(i, i + dim));
      }
      return g;
   }

   static Edge makeEdge(size_t from, size_t to)
   {
      return Edge(from, to);
   }

   static WeightedEdge makeWeightedEdge(size_t from, size_t to)
   {
      return WeightedEdge(from, to, 1.);
   }

   static WeightedEdge makeRandomWeightedEdge(size_t from, size_t to)
   {
      return WeightedEdge(from, to, rand() / (1.0 * RAND_MAX));
   }

   //--------------------------------------------------------------------------

   Graph twoDimPlane(size_t dim)
   {
      return makePlane<Graph>(dim, makeEdge);
   }

   WeightedGraph twoDimWeightedPlane(size_t dim)
   {
      return makePlane<WeightedGraph>(dim, makeWeightedEdge);
   }

   WeightedGraph twoDimRandomWeightedPlane(size_t dim)
   {
      return makePlane<WeightedGraph>(dim, makeRandomWeightedEdge);
   }

   DiGraph topLeftBottomRightPlane(size_t dim)
   {
      return makePlane<DiGraph>(dim, makeEdge);
   }
}
