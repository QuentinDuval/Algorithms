#pragma once

#include "DepthFirstSearch.h"
#include "internal/GenericDiGraph.h"
#include "utils/Algorithms.h"
#include "utils/Range.h"

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
      {
         DFS<Edge> dfs(g);
         m_vertices.reserve(g.vertexCount());
         for (size_t i : g.vertices())
         {
            if (!dfs.isMarked(i))
               dfs.postOrderFrom(i, [this](size_t v) { m_vertices.emplace_back(v); });
         }
      }

      template<typename Edge>
      TopologicalSort(GenericDiGraph<Edge> const& g, size_t from)
      {
         DFS<Edge> dfs(g);
         m_vertices.reserve(g.vertexCount());
         dfs.postOrderFrom(from, [this](size_t v) { m_vertices.emplace_back(v); });
      }

      utils::Range<vertex_it> order() const
      {
         return utils::Range<vertex_it>{ rbegin(m_vertices), rend(m_vertices) };
      }

   private:
      std::vector<size_t> m_vertices;
   };
}
