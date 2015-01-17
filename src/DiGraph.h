#pragma once

#include "Edge.h"
#include "internal/GenericDiGraph.h"


namespace algorithm
{
   //--------------------------------------------------------------------------
   // Unweighted and directed Graph
   //--------------------------------------------------------------------------

   using DiGraph = GenericDiGraph<Edge>;

   DiGraph  diGraphFrom (std::istream&);
   void     diGraphTo   (std::ostream&, DiGraph const&);
}

