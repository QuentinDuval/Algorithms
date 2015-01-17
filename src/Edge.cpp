#include "DiGraph.h"


namespace algorithm
{
   Edge::Edge(size_t from, size_t to)
      : m_from(from), m_to(to)
   {}

   size_t Edge::from() const
   {
      return m_from;
   }

   size_t Edge::to() const
   {
      return m_to;
   }

   Edge Edge::reverse() const
   {
      return Edge(to(), from());
   }

   //--------------------------------------------------------------------------

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
}
