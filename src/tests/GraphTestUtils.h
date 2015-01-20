#pragma once
#include "Graph.h"
#include "DiGraph.h"
#include "WeightedGraph.h"


namespace algorithm
{
   Graph          twoDimPlane(size_t dim);
   WeightedGraph  twoDimWeightedPlane(size_t dim);
   DiGraph        topLeftBottomRightPlane(size_t dim);
}
