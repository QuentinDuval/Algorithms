#pragma once
#include "DepthFirstSearch.h"
#include "DirectedCycle.h"
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
         DirectedCycle<Edge> cycle(g);
         if (cycle.hasCycle())
            return;

         DFS<Edge> dfs(g);
         for (size_t i = 0; i < g.vertexCount(); ++i)
         {
            if (!dfs.isMarked(i))
               dfs.postOrderFrom(i, [this](size_t v) { m_vertices.push_back(v); });
         }
      }

      bool hasOrder() const
      {
         return !m_vertices.empty();
      }

      Range<vertex_it> order() const
      {
         return { rbegin(m_vertices), rend(m_vertices) };
      }

   private:
      std::vector<size_t> m_vertices;
   };
}
