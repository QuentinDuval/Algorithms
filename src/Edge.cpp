#include "DiGraph.h"


namespace algorithm
{
   Edge::Edge()
      : Edge(0, 0)
   {}

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

   std::ostream& operator<< (std::ostream& os, Edge const& e)
   {
      return os << e.from() << " " << e.to();
   }

   //--------------------------------------------------------------------------

   WeightedEdge::WeightedEdge()
      : WeightedEdge(0, 0, 0.)
   {}

   WeightedEdge::WeightedEdge(size_t from, size_t to, double weight)
      : Edge(from, to)
      , m_weight(weight)
   {}

   double WeightedEdge::weight() const
   {
      return m_weight;
   }

   WeightedEdge WeightedEdge::reverse() const
   {
      return WeightedEdge(to(), from(), m_weight);
   }

   std::ostream& operator<< (std::ostream& os, WeightedEdge const& e)
   {
      return os << e.from() << " " << e.to() << " " << e.weight();
   }

   //--------------------------------------------------------------------------

   CapacityEdge::CapacityEdge()
      : CapacityEdge(0, 0, 0.)
   {}

   CapacityEdge::CapacityEdge(size_t from, size_t to, double capacity)
      : Edge(from, to)
      , m_flow(0.)
      , m_capacity(capacity)
   {}

   double CapacityEdge::flow() const
   {
      return m_flow;
   }

   double CapacityEdge::capacity() const
   {
      return m_capacity;
   }

   CapacityEdge CapacityEdge::reverse() const
   {
      CapacityEdge reversed(to(), from(), capacity());
      reversed.m_flow = m_capacity - m_flow;
      return reversed;
   }

   std::ostream& operator<< (std::ostream& os, CapacityEdge const& e)
   {
      return os << e.from() << " " << e.to() << " " << e.capacity();
   }
}
