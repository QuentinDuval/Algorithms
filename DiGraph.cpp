#include "DiGraph.h"
#include "utils/Utils.h"
#include <cctype>


namespace algorithm
{
   Edge::Edge(size_t to)
      : m_to(to)
   {}

   size_t Edge::to() const
   {
      return m_to;
   }

   //--------------------------------------------------------------------------

   DiGraph diGraphFrom(std::istream& is)
   {
      return DiGraph::createFrom(is, [](std::istream& is) {
         size_t w = 0;
         is >> w;
         return Edge(w);
      });
   }

   void diGraphTo(std::ostream& os, DiGraph const& g)
   {
      DiGraph::serializeTo(g, os, [](std::ostream& os, Edge const& e) {
         os << e.to();
      });
   }
}
