#include "CapacityGraph.h"


namespace algorithm
{
   CapacityGraph capacityGraphFrom(std::istream& is)
   {
      return CapacityGraph::createFrom(is, [](std::istream& is) {
         size_t from, to = 0;
         double c = 0.;
         is >> from >> to >> c;
         return CapacityEdge(from, to, c);
      });
   }

   void capacityGraphTo(std::ostream& os, CapacityGraph const& g)
   {
      CapacityGraph::serializeTo(g, os, [](std::ostream& os, CapacityEdge const& e) {
         os << e.from() << " " << e.to() << " " << e.capacity();
      });
   }
}
