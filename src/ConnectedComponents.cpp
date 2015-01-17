#include "ConnectedComponents.h"
#include "DepthFirstSearch.h"


namespace algorithm
{
   ConnectedComponents::ConnectedComponents(Graph const& g)
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

   size_t ConnectedComponents::componentCount() const
   {
      return m_componentCount;
   }

   size_t ConnectedComponents::componentIdOf(size_t vertex) const
   {
      return m_componentIds[vertex];
   }

   bool ConnectedComponents::connected(size_t v, size_t w) const
   {
      return componentIdOf(v) == componentIdOf(w);
   }
}
