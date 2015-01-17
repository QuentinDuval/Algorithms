#include "WeightedDiGraph.h"
#include "utils/Utils.h"


namespace algorithm
{
   WeightedEdge::WeightedEdge(size_t to, double weight)
      : m_to(to)
      , m_weight(weight)
   {}

   size_t WeightedEdge::to() const
   {
      return m_to;
   }

   double WeightedEdge::weight() const
   {
      return m_weight;
   }

   //--------------------------------------------------------------------------

   WeightedDiGraph weightedDiGraphFrom(std::istream& is)
   {
      return WeightedDiGraph::createFrom(is, [](std::istream& is) {
         size_t to = 0;
         double w = 0.;
         is >> to;
         is >> w;
         return WeightedEdge(to, w);
      });
   }

   void serializeTo(std::ostream&, WeightedDiGraph const&)
   {

   }
}
