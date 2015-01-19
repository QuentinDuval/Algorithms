#pragma once

#include "DepthFirstSearch.h"
#include "Edge.h"
#include "internal/GenericDiGraph.h"
#include "internal/GenericGraph.h"
#include <vector>


namespace algorithm
{
   class SpanningTree
   {
   public:
      using Edges = std::vector<Edge>;
      using edge_it = Edges::const_iterator;

   public:
      SpanningTree(GenericDiGraph<Edge> const&);
      SpanningTree(GenericGraph<Edge>   const&);

      size_t connectedComponentCount() const;
      Range<edge_it> edges(size_t ccId) const;

   private:
      std::vector<Edges> m_trees;
   };
}
