#pragma once

#include "CapacityGraph.h"


namespace algorithm
{
   /** Compute the maximum flow of the graph */
   double computeMaximumFlow(CapacityGraph& graph, size_t from, size_t to);
}
