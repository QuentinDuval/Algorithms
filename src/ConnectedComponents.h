#pragma once
#include "DepthFirstSearch.h"
#include "internal/GenericGraph.h"
#include <vector>


namespace algorithm
{
   class ConnectedComponents
   {
   public:
      template<typename Edge>
      ConnectedComponents(GenericGraph<Edge> const& g)
         : m_componentCount(0)
         , m_componentIds(g.vertexCount(), 0)
      {
         DFS<Edge> dfs(g);
         for (size_t i = 0; i < g.vertexCount(); ++i)
         {
            if (dfs.isMarked(i))
               continue;

            dfs.searchFrom(i, [this](size_t v) { m_componentIds[v] = m_componentCount; });
            ++m_componentCount;
         }
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
      size_t m_componentCount;
      std::vector<size_t> m_componentIds;
   };
}
