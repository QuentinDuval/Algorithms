#pragma once

#include "GraphExceptions.h"
#include "internal/GenericDiGraph.h"
#include "utils/Algorithms.h"
#include "utils/Utils.h"

#include <istream>
#include <vector>


namespace algorithm
{
   //--------------------------------------------------------------------------
   // Unweighted and directed Graph
   //--------------------------------------------------------------------------

   class Edge
   {
   public:
      Edge(size_t to);
      size_t to() const;

   private:
      size_t m_to;
   };

   using DiGraph = GenericDiGraph<Edge>;

   //--------------------------------------------------------------------------
   // Helpers
   //--------------------------------------------------------------------------

   DiGraph  diGraphFrom (std::istream&);
   void     diGraphTo   (std::ostream&, DiGraph const&);
}

