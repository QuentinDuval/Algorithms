#pragma once
#include "GraphExceptions.h"
#include "internal/GenericDiGraph.h"
#include "utils/Algorithms.h"
#include "utils/Utils.h"

#include <functional>
#include <vector>


namespace algorithm
{
   //--------------------------------------------------------------------------
   // Weighted and directed Graph
   //--------------------------------------------------------------------------

   class WeightedEdge
   {
   public:
      WeightedEdge(size_t from, size_t to, double weight);
      ~WeightedEdge() = default;

      size_t from() const;
      size_t to() const;
      double weight() const;
      WeightedEdge reverse() const;

   private:
      size_t m_from;
      size_t m_to;
      double m_weight;
   };

   using WeightedDiGraph = GenericDiGraph<WeightedEdge>;


   //--------------------------------------------------------------------------
   // Helpers
   //--------------------------------------------------------------------------

   WeightedDiGraph weightedDiGraphFrom(std::istream&);
   void serializeTo(std::ostream&, WeightedDiGraph const&);
}
