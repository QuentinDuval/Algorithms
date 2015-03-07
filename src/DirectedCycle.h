#pragma once
#include "DepthFirstSearch.h"
#include "internal/GenericDiGraph.h"
#include "utils/Algorithms.h"
#include <vector>


namespace algorithm
{
   template<typename Edge>
   class DirectedCycle
   {
   public:
      DirectedCycle(GenericDiGraph<Edge> const& g)
      {
         DFS<Edge> dfs(g);
         for (size_t i : g.vertices())
         {
            if (hasCycle()) break;
            if (!dfs.isMarked(i))
               searchCycleFrom(dfs, g, i);
         }
      }

      DirectedCycle(GenericDiGraph<Edge> const& g, size_t from)
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
      void searchCycleFrom(DFS<Edge>& dfs, GenericDiGraph<Edge> const& g, size_t from)
      {
         std::vector<Edge> stack;
         std::vector<bool> onStack(g.vertexCount(), false);

         auto postOrder = [&](size_t v)
         {
            onStack[v] = false;
            if (!stack.empty())
               stack.pop_back();
            return false;
         };

         auto processEdge = [&](Edge const& e)
         {
            auto v = e.to();
            if (onStack[v])
            {
               auto startCycle = utils::findIf(stack, [v](Edge const& e){ return e.from() == v; });
               std::copy(startCycle, cend(stack), std::back_inserter(m_cycle));
               m_cycle.push_back(e);
               return true;
            }

            if (!dfs.isMarked(v))
            {
               onStack[v] = true;
               stack.push_back(e);
            }
            return false;
         };

         onStack[from] = true;
         dfs.searchFrom(from, postOrder, processEdge);
      }

   private:
      std::vector<Edge> m_cycle;
   };
}
