#pragma once

#include "Edge.h"
#include "internal/GenericDiGraph.h"


namespace algorithm
{
   //--------------------------------------------------------------------------
   // Weighted and directed Graph
   //--------------------------------------------------------------------------

   using WeightedDiGraph = GenericDiGraph<WeightedEdge>;

   WeightedDiGraph weightedDiGraphFrom(std::istream&);
   void serializeTo(std::ostream&, WeightedDiGraph const&);
}
