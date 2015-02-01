#include "WeightedGraph.h"


namespace algorithm
{
   WeightedGraph weightedGraphFrom(std::istream& is)
   {
      return WeightedGraph::createFrom(is, [](std::istream& is) {
         size_t from, to = 0;
         double w = 0.;
         is >> from >> to >> w;
         return WeightedEdge(from, to, w);
      });
   }

   void weightedGraphTo(std::ostream& os, WeightedGraph const& g)
   {
      WeightedGraph::serializeTo(g, os, [](std::ostream& os, WeightedEdge const& e) {
         os << e.from() << " " << e.to() << " " << e.weight();
      });
   }
}
