#pragma once
#include "Graph.h"
#include "DiGraph.h"
#include "WeightedGraph.h"


namespace algorithm
{
   Graph          make2DPlane(size_t dim, bool withDiagonals = false);
   WeightedGraph  make2DWeightedPlane(size_t dim, bool withDiagonals = false);
   WeightedGraph  make2DRandomWeightedPlane(size_t dim, bool withDiagonals = false);

   DiGraph        make2DTopLeftBottomRightPlane(size_t dim, bool withDiagonals = false);
}
