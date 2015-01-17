#include "WeightedDiGraph.h"
#include "utils/Utils.h"


namespace algorithm
{
   WeightedEdge::WeightedEdge(size_t from, size_t to, double weight)
      : m_from(from)
      , m_to(to)
      , m_weight(weight)
   {}

   size_t WeightedEdge::from() const
   {
      return m_from;
   }

   size_t WeightedEdge::to() const
   {
      return m_to;
   }

   double WeightedEdge::weight() const
   {
      return m_weight;
   }

   WeightedEdge WeightedEdge::reverse() const
   {
      return WeightedEdge(to(), from(), m_weight);
   }

   //--------------------------------------------------------------------------

   WeightedDiGraph weightedDiGraphFrom(std::istream& is)
   {
      return WeightedDiGraph::createFrom(is, [](std::istream& is) {
         size_t from, to = 0;
         double w = 0.;
         is >> from >> to >> w;
         return WeightedEdge(from, to, w);
      });
   }

   void serializeTo(std::ostream&, WeightedDiGraph const&)
   {

   }
}
