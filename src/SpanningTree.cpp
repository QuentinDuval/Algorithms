#include "SpanningTree.h"


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
      return{ begin(m_trees[ccId]), end(m_trees[ccId]) };
   }
}
