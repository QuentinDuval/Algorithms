#include "WeightedDiGraph.h"


namespace algorithm
{
   WeightedDiGraph weightedDiGraphFrom(std::istream& is)
   {
      return WeightedDiGraph::createFrom(is, [](std::istream& is) {
         size_t from, to = 0;
         double w = 0.;
         is >> from >> to >> w;
         return WeightedEdge(from, to, w);
      });
   }

   void serializeTo(std::ostream& os, WeightedDiGraph const& g)
   {
      WeightedDiGraph::serializeTo(g, os, [](std::ostream& os, WeightedEdge const& e) {
         os << e.from() << " " << e.to() << " " << e.weight();
      });
   }
}
