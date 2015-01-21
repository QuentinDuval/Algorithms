#pragma once

#include "DiGraph.h"
#include "Edge.h"
#include "Graph.h"
#include "WeightedDiGraph.h"
#include "WeightedGraph.h"
#include <vector>


namespace algorithm
{
   class SpanningTree
   {
   public:
      using Edges = std::vector<Edge>;
      using edge_it = Edges::const_iterator;

   public:
      SpanningTree(DiGraph const&);
      SpanningTree(Graph   const&);

      size_t connectedComponentCount() const;
      Range<edge_it> edges(size_t ccId) const;

   private:
      std::vector<Edges> m_trees;
   };

   //--------------------------------------------------------------------------

   class MinimumSpanningTree
   {
   public:
      using Edges = std::vector<WeightedEdge>;
      using edge_it = Edges::const_iterator;

   public:
      MinimumSpanningTree(WeightedDiGraph const&);
      MinimumSpanningTree(WeightedGraph   const&);

      size_t connectedComponentCount() const;
      Range<edge_it> edges(size_t ccId) const;

   private:
      std::vector<Edges> m_trees;
   };

   //--------------------------------------------------------------------------

   class KruskalMinimumSpanningTree
   {
   public:
      using Edges = std::vector<WeightedEdge>;
      using edge_it = Edges::const_iterator;

   public:
      KruskalMinimumSpanningTree(WeightedDiGraph const&);
      KruskalMinimumSpanningTree(WeightedGraph   const&);

      Range<edge_it> edges() const;

   private:
      Edges m_tree;
   };
}
