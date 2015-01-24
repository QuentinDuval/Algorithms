#pragma once
#include "Graph.h"
#include "DiGraph.h"
#include "WeightedGraph.h"


namespace algorithm
{
   Graph          twoDimPlane(size_t dim, bool withDiagonals = false);
   WeightedGraph  twoDimWeightedPlane(size_t dim, bool withDiagonals = false);
   WeightedGraph  twoDimRandomWeightedPlane(size_t dim, bool withDiagonals = false);
   DiGraph        topLeftBottomRightPlane(size_t dim, bool withDiagonals = false);
}
