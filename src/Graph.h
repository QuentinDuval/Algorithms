#pragma once

#include "GraphExceptions.h"
#include "DiGraph.h"
#include "internal/GenericGraph.h"
#include "utils/Algorithms.h"
#include "utils/Utils.h"

#include <istream>
#include <vector>


namespace algorithm
{
   //--------------------------------------------------------------------------
   // Unweighted and undirected Graph
   //--------------------------------------------------------------------------

   using Graph = GenericGraph<Edge>;


   //--------------------------------------------------------------------------
   // Helpers
   //--------------------------------------------------------------------------

   Graph graphFrom(std::istream&);
   void  graphTo  (std::ostream&, Graph const&);
}
