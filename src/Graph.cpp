#include "Graph.h"
#include "utils/Utils.h"


namespace algorithm
{
   Graph graphFrom(std::istream& is)
   {
      return Graph::createFrom(is, [](std::istream& is) {
         size_t v, w = 0;
         is >> v >> w;
         return Edge(v, w);
      });
   }

   void graphTo(std::ostream& os, Graph const& g)
   {
      Graph::serializeTo(g, os, [](std::ostream& os, Edge const& e) {
         os << e.from() << " " << e.to();
      });
   }
}
