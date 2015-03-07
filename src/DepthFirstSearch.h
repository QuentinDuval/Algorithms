#pragma once

#include "GraphSearch.h"
#include "SymbolGraph.h"
#include "internal/GenericDiGraph.h"
#include "internal/GenericGraph.h"

#include <functional>
#include <stack>
#include <vector>


namespace algorithm
{
   template<typename Edge>
   class DFS : public GraphSearch<Edge>
   {
   public:
      using DiGraph = GenericDiGraph<Edge>;
      using Graph = GenericGraph<Edge>;

      using OnDiscovered = GraphSearch<Edge>::OnDiscovered;
      using OnProcessed = GraphSearch<Edge>::OnProcessed;
      using OnProcessEdge = GraphSearch<Edge>::OnProcessEdge;

   public:
      explicit DFS(DiGraph const& g)
         : GraphSearch(g.vertexCount())
         , m_graph(g)
      {}

      explicit DFS(Graph const& g)
         : DFS(g.toDiGraph())
      {}

      void postOrderFrom(size_t v, OnProcessed postOrder)
      {
         searchFrom(v, [](size_t){ return false; }, postOrder, [](Edge const&){ return false; });
      }

      void searchFrom(size_t v, OnDiscovered onDiscovered, OnProcessed postOrder, OnProcessEdge processEdge)
      {
         if (!isMarked(v))
            searchImplIter(v, onDiscovered, postOrder, processEdge);
      }

   private:
      void searchImpl(size_t v, OnDiscovered onDiscovered, OnProcessEdge processEdge) override
      {
         searchFrom(v, onDiscovered, [](size_t){ return false; }, processEdge);
      }

      /** Iterative implementation emulating the stack */
      void searchImplIter(size_t v, OnDiscovered onDiscovered, OnProcessed postOrder, OnProcessEdge processEdge)
      {
         auto edges = m_graph.edgesFrom(v);
         using StackedRange = std::pair<size_t, decltype(edges)>;
         std::stack<StackedRange, std::vector<StackedRange>> stack;
         stack.emplace(v, edges);
         mark(v);
         onDiscovered(v);

         while (!stack.empty())
         {
            auto& range = stack.top().second;
            if (range.empty())
            {
               postOrder(stack.top().first);
               stack.pop();
               continue;
            }
            
            auto e = range.begin();
            range.pop();

            auto c = e->to();
            if (processEdge(*e))
               return;

            if (!isMarked(c))
            {
               mark(c);
               onDiscovered(c);
               auto nextRange = m_graph.edgesFrom(c);
               stack.emplace(c, nextRange);
            }
         }
      }

   private:
      DiGraph const& m_graph;
   };
}
