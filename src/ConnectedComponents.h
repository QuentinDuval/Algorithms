#pragma once

#include "DepthFirstSearch.h"
#include "TopologicalSort.h"
#include "internal/GenericGraph.h"
#include "internal/GenericDiGraph.h"

#include <vector>


namespace algorithm
{
   class ConnectedComponents
   {
   public:
      template<typename Edge>
      explicit ConnectedComponents(GenericGraph<Edge> const& g)
         : m_componentCount(0)
         , m_componentIds(g.vertexCount(), 0)
      {
         DFS<Edge> dfs(g);
         dfsInOrder(dfs, g.vertices());
      }

      template<typename Edge>
      explicit ConnectedComponents(GenericDiGraph<Edge> const& g)
         : m_componentCount(0)
         , m_componentIds(g.vertexCount(), 0)
      {
         GenericDiGraph<Edge> reversed = makeReversed(g);
         DFS<Edge> dfs(reversed);
         dfsInOrder(dfs, TopologicalSort(g).order()); //It is not really a topological sort but a reversed post order
      }

      size_t componentCount() const
      {
         return m_componentCount;
      }

      size_t componentIdOf(size_t vertex) const
      {
         return m_componentIds[vertex];
      }

      bool connected(size_t v, size_t w) const
      {
         return componentIdOf(v) == componentIdOf(w);
      }

   private:
      template<typename Edge, typename VertexIt>
      void dfsInOrder(DFS<Edge>& dfs, utils::Range<VertexIt> const& range)
      {
         for (auto v : range)
         {
            if (dfs.isMarked(v))
               continue;

            dfs.markFrom(v, [this](size_t w)
            {
               m_componentIds[w] = m_componentCount;
               return false;
            });
            ++m_componentCount;
         }
      }

   private:
      size_t m_componentCount;
      std::vector<size_t> m_componentIds;
   };
}
