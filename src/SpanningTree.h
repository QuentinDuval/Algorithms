#pragma once

#include "Edge.h"
#include "Graph.h"
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
      SpanningTree(Graph const&);

      size_t connectedComponentCount() const;
      utils::Range<edge_it> edges(size_t ccId) const;

   private:
      std::vector<Edges> m_trees;
   };

   //--------------------------------------------------------------------------

   class LazyPrimMinimumSpanningTree
   {
   public:
      using Edges = std::vector<WeightedEdge>;
      using edge_it = Edges::const_iterator;

   public:
      explicit LazyPrimMinimumSpanningTree(WeightedGraph const&);
      size_t connectedComponentCount() const;
      utils::Range<edge_it> edges(size_t ccId) const;

   private:
      std::vector<Edges> m_trees;
   };

   //--------------------------------------------------------------------------

   class EagerPrimMinimumSpanningTree
   {
   public:
      using Edges = std::vector<WeightedEdge>;
      using edge_it = Edges::const_iterator;

   public:
      explicit EagerPrimMinimumSpanningTree(WeightedGraph const&);
      size_t connectedComponentCount() const;
      utils::Range<edge_it> edges(size_t ccId) const;

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
      explicit KruskalMinimumSpanningTree(WeightedGraph const&);
      utils::Range<edge_it> edges() const;

   private:
      Edges m_tree;
   };
}
