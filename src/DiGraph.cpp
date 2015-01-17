#include "DiGraph.h"


namespace algorithm
{
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
