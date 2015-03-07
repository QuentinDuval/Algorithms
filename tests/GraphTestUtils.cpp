#include "GraphTestUtils.h"

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
   GraphType makePlane(size_t dim, MakeEdge makeEdge, bool withDiagonals)
   {
      GraphType g(dim * dim);
      for (size_t i : g.vertices())
      {
         size_t x = i % dim;
         if (x < dim - 1)
            g.addEdge(makeEdge(i, i + 1));

         size_t y = i / dim;
         if (y < dim - 1)
            g.addEdge(makeEdge(i, i + dim));

         if (withDiagonals && x < dim - 1 && y < dim - 1)
            g.addEdge(makeEdge(i, i + dim + 1));
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

   Graph make2DPlane(size_t dim, bool withDiagnonals)
   {
      return makePlane<Graph>(dim, makeEdge, withDiagnonals);
   }

   WeightedGraph make2DWeightedPlane(size_t dim, bool withDiagnonals)
   {
      return makePlane<WeightedGraph>(dim, makeWeightedEdge, withDiagnonals);
   }

   WeightedGraph make2DRandomWeightedPlane(size_t dim, bool withDiagnonals)
   {
      return makePlane<WeightedGraph>(dim, makeRandomWeightedEdge, withDiagnonals);
   }

   DiGraph make2DTopLeftBottomRightPlane(size_t dim, bool withDiagnonals)
   {
      return makePlane<DiGraph>(dim, makeEdge, withDiagnonals);
   }

   WeightedDiGraph make2DWeightedDiPlane(size_t dim, bool withDiagonals)
   {
      return makePlane<WeightedDiGraph>(dim, makeWeightedEdge, withDiagonals);
   }

   WeightedDiGraph make2DWeightedDiRandomPlane(size_t dim, bool withDiagonals)
   {
      return makePlane<WeightedDiGraph>(dim, makeRandomWeightedEdge, withDiagonals);
   }
}
