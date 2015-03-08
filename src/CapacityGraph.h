#pragma once

#include "Edge.h"
#include "internal/GenericGraph.h"


namespace algorithm
{
   //--------------------------------------------------------------------------
   // Capacity Graph
   //--------------------------------------------------------------------------

   using CapacityGraph = GenericGraph<CapacityEdge>;

   CapacityGraph capacityGraphFrom(std::istream&);
   void capacityGraphTo(std::ostream&, CapacityGraph const&);
}
