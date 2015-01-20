#include "SpanningTree.h"
#include "PriorityQueue.h"


namespace algorithm
{
   SpanningTree::SpanningTree(GenericDiGraph<Edge> const& g)
      : m_trees()
   {
      DFS<Edge> dfs(g);
      for (size_t v = 0; v < g.vertexCount(); ++v)
      {
         if (dfs.isMarked(v))
            continue;

         Edges edges;
         dfs.pathsFrom(v, [&edges](Edge const& e){ edges.push_back(e); });
         m_trees.emplace_back(std::move(edges));
      }
   }

   SpanningTree::SpanningTree(GenericGraph<Edge> const& g)
      : SpanningTree(g.toDiGraph())
   {}

   size_t SpanningTree::connectedComponentCount() const
   {
      return m_trees.size();
   }

   Range<SpanningTree::edge_it> SpanningTree::edges(size_t ccId) const
   {
      return Range<SpanningTree::edge_it>{ begin(m_trees[ccId]), end(m_trees[ccId]) };
   }

   //--------------------------------------------------------------------------

   MinimumSpanningTree::MinimumSpanningTree(GenericDiGraph<WeightedEdge> const& g)
      : m_trees()
   {
      //Prim's algorithm
      auto less = [](WeightedEdge const& lhs, WeightedEdge const& rhs) { return lhs.weight() < rhs.weight(); };

      MinPriorityQueue<WeightedEdge, decltype(less)> edgeQueue(less);
      std::vector<bool> marked(g.vertexCount(), false);

      for (size_t v = 0; v < g.vertexCount(); ++v)
      {
         if (marked[v])
            continue;

         m_trees.emplace_back();
         marked[v] = true;
         for (auto e : g.edgesFrom(v))
            edgeQueue.add(e);

         while (!edgeQueue.empty())
         {
            auto e = edgeQueue.top();
            edgeQueue.pop();
            if (marked[e.to()])
               continue;

            auto w = e.to();
            marked[w] = true;
            m_trees.back().push_back(e);
            for (auto e : g.edgesFrom(w))
               if (!marked[e.to()])
                  edgeQueue.add(e);
         }
      }
   }

   MinimumSpanningTree::MinimumSpanningTree(GenericGraph<WeightedEdge> const& g)
      : MinimumSpanningTree(g.toDiGraph())
   {}

   size_t MinimumSpanningTree::connectedComponentCount() const
   {
      return m_trees.size();
   }

   Range<MinimumSpanningTree::edge_it> MinimumSpanningTree::edges(size_t ccId) const
   {
      return Range<MinimumSpanningTree::edge_it>{ begin(m_trees[ccId]), end(m_trees[ccId]) };
   }
}
