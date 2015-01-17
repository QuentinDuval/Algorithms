#include "DiGraph.h"
#include "utils/Utils.h"
#include <cctype>


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

   DiGraph diGraphFrom(std::istream& is)
   {
      return DiGraph::createFrom(is, [](std::istream& is) {
         size_t v, w = 0;
         is >> v >> w;
         return Edge(v, w);
      });
   }

   void diGraphTo(std::ostream& os, DiGraph const& g)
   {
      DiGraph::serializeTo(g, os, [](std::ostream& os, Edge const& e) {
         os << e.from() << " " << e.to();
      });
   }
}
