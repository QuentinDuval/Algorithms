#pragma once
#include "DepthFirstSearch.h"
#include "internal/GenericDiGraph.h"
#include "utils/Algorithms.h"
#include <vector>


namespace algorithm
{
   class TopologicalSort
   {
   public:
      using vertex_it = std::vector<size_t>::const_reverse_iterator;

   public:
      template<typename Edge>
      TopologicalSort(GenericDiGraph<Edge> const& g)
         : m_vertices()
      {
         DFS<Edge> dfs(g);
         m_vertices.reserve(g.vertexCount());
         for (size_t i = 0; i < g.vertexCount(); ++i)
         {
            if (!dfs.isMarked(i))
               dfs.postOrderFrom(i, [this](size_t v) { m_vertices.push_back(v); });
         }
      }

      template<typename Edge>
      TopologicalSort(GenericDiGraph<Edge> const& g, size_t from)
         : m_vertices()
      {
         DFS<Edge> dfs(g);
         m_vertices.reserve(g.vertexCount());
         dfs.postOrderFrom(from, [this](size_t v) { m_vertices.push_back(v); });
      }

      Range<vertex_it> order() const
      {
         return Range<vertex_it>{ rbegin(m_vertices), rend(m_vertices) };
      }

   private:
      std::vector<size_t> m_vertices;
   };
}
