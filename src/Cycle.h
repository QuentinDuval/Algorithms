#pragma once
#include "DepthFirstSearch.h"
#include "internal/GenericGraph.h"
#include "utils/Algorithms.h"
#include <vector>


namespace algorithm
{
   template<typename Edge>
   class Cycle
   {
   public:
      explicit Cycle(GenericGraph<Edge> const& g)
      {
         DFS<Edge> dfs(g);
         for (size_t i : g.vertices())
         {
            if (hasCycle()) break;
            if (!dfs.isMarked(i))
               searchCycleFrom(dfs, g, i);
         }
      }

      Cycle(GenericGraph<Edge> const& g, size_t from)
      {
         DFS<Edge> dfs(g);
         searchCycleFrom(dfs, from, i);
      }

      bool hasCycle() const
      {
         return !m_cycle.empty();
      }

      std::vector<Edge> const& cycle() const
      {
         return m_cycle;
      }

   private:
      void searchCycleFrom(DFS<Edge>& dfs, GenericGraph<Edge> const& g, size_t from)
      {
         size_t size = g.vertexCount();
         std::vector<size_t> parent(size, size + 1);
         std::vector<Edge> parentEdge(size);

         auto processEdge = [&](Edge const& e)
         {
            auto from = e.from();
            auto to = e.to();
            if (!dfs.isMarked(to))
            {
               parent[to] = from;
               parentEdge[to] = e;
            }
            else if (parent[from] != to)
            {
               //Rebuild the cycle: the direction does not matter
               size_t v = from;
               while (v != to)
               {
                  m_cycle.push_back(parentEdge[v]);
                  v = parent[v];
               }
               m_cycle.push_back(e);
               return true;
            }
            return false;
         };

         auto vertexListener = [](size_t v) { return false; };
         dfs.searchFrom(from, vertexListener, vertexListener, processEdge);
      }

   private:
      std::vector<Edge> m_cycle;
   };
}
