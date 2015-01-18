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
         : m_cycle()
      {
         std::vector<Edge> stack;
         std::vector<bool> onStack(g.vertexCount(), false);
         
         auto postOrder = [&](size_t v){
            onStack[v] = false;
            if (!stack.empty())
               stack.pop_back();
         };

         auto onPathTaken = [&](Edge const& e) {
            onStack[e.to()] = true;
            stack.push_back(e);
         };

         auto onAlreadyMarked = [&](Edge const& e) {
            size_t v = e.to();
            if (onStack[v] && !hasCycle())
            {
               auto it = findIf(stack, [v](Edge const& e){ return e.from() == v; });
               std::copy(it, cend(stack), std::back_inserter(m_cycle));
               m_cycle.push_back(e);
            }
         };

         DFS<Edge> dfs(g);
         for (size_t i = 0; i < g.vertexCount() && !hasCycle(); ++i)
         {
            if (dfs.isMarked(i))
               continue;

            onStack[i] = true;
            dfs.searchFrom(i, postOrder, onAlreadyMarked, onPathTaken);
         }
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
      std::vector<Edge> m_cycle;
   };
}
