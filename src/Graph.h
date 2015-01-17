#pragma once

#include "Edge.h"
#include "internal/GenericGraph.h"


namespace algorithm
{
   //--------------------------------------------------------------------------
   // Unweighted and undirected Graph
   //--------------------------------------------------------------------------

   using Graph = GenericGraph<Edge>;

   Graph graphFrom(std::istream&);
   void  graphTo  (std::ostream&, Graph const&);
}
