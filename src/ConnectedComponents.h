#pragma once

#include "DepthFirstSearch.h"
#include "internal/GenericGraph.h"
#include "internal/GenericDiGraph.h"

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
         for (size_t v : g.vertices())
         {
            if (dfs.isMarked(v))
               continue;

            dfs.markFrom(v, [this](size_t w) { m_componentIds[w] = m_componentCount; });
            ++m_componentCount;
         }
      }

      template<typename Edge>
      ConnectedComponents(GenericDiGraph<Edge> const& g)
         : m_componentCount(0)
         , m_componentIds(g.vertexCount(), 0)
      {
         std::vector<size_t> vertexStack;
         vertexStack.reserve(g.vertexCount());

         DFS<Edge> dfs(g);
         for (size_t v : g.vertices())
         {
            if (!dfs.isMarked(v))
               dfs.postOrderFrom(v, [this, &vertexStack](size_t w) { vertexStack.push_back(w); });
         }

         GenericDiGraph<Edge> reversed = makeReversed(g);
         DFS<Edge> reversedDfs(reversed);
         for (auto b = vertexStack.rbegin(); b != vertexStack.rend(); ++b)
         {
            size_t v = *b;
            if (reversedDfs.isMarked(v))
               continue;

            reversedDfs.markFrom(v, [this](size_t w) { m_componentIds[w] = m_componentCount; });
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
