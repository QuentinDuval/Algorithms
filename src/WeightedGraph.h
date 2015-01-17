#pragma once

#include "Edge.h"
#include "internal/GenericGraph.h"


namespace algorithm
{
   //--------------------------------------------------------------------------
   // Weighted and directed Graph
   //--------------------------------------------------------------------------

   using WeightedGraph = GenericGraph<WeightedEdge>;

   WeightedGraph weightedGraphFrom(std::istream&);
   void weightedGraphTo(std::ostream&, WeightedGraph const&);
}
