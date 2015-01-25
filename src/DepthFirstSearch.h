#pragma once

#include "GraphSearch.h"
#include "SymbolGraph.h"
#include "internal/GenericDiGraph.h"
#include "internal/GenericGraph.h"

#include <functional>
#include <vector>


namespace algorithm
{
   template<typename Edge>
   class DFS : public GraphSearch<Edge>
   {
   public:
      using DiGraph = GenericDiGraph<Edge>;
      using Graph = GenericGraph<Edge>;
      using OnMarked = GraphSearch<Edge>::OnMarked;
      using OnPathTaken = GraphSearch<Edge>::OnPathTaken;
      using OnAlreadyFound = std::function<bool(Edge const&)>;

   public:
      explicit DFS(DiGraph const& g)
         : GraphSearch(g.vertexCount())
         , m_graph(g)
      {}

      explicit DFS(Graph const& g)
         : DFS(g.toDiGraph())
      {}

      void postOrderFrom(size_t v, OnMarked postOrder)
      {
         searchFrom(v, postOrder, [](Edge const&){ return false; }, [](Edge const&){});
      }

      void searchFrom(size_t v, OnMarked postOrder, OnAlreadyFound onAlreadyMarked, OnPathTaken pathTaken)
      {
         if (isMarked(v))
            return;

         mark(v);
         searchImplIter(v, postOrder, onAlreadyMarked, pathTaken);
      }

   private:
      void searchImpl(size_t v, OnPathTaken listener) override
      {
         searchFrom(v, [](size_t){}, [](Edge const&){ return false; }, listener);
      }

      /** Iterative implementation emulating the stack */
      void searchImplIter(size_t v, OnMarked onAdjVisited, OnAlreadyFound onAlreadyMarked, OnPathTaken listener)
      {
         auto edges = m_graph.edgesFrom(v);
         using StackedRange = std::pair<size_t, decltype(edges)>;
         std::vector<StackedRange> stack{ { v, edges } };

         while (!stack.empty())
         {
            auto& range = stack.back().second;
            if (range.empty())
            {
               onAdjVisited(stack.back().first);
               stack.pop_back();
               continue;
            }
            
            auto e = range.begin();
            auto c = e->to();
            range.pop();

            if (!isMarked(c))
            {
               listener(*e);
               mark(c);
               auto nextRange = m_graph.edgesFrom(c);
               stack.emplace_back(c, nextRange);
            }
            else if (onAlreadyMarked(*e))
            {
               return;
            }
         }
      }

      /** Alternate iterative implementation when the post-order is not needed (faster) */
      void searchImplIter2(size_t v, OnPathTaken onAlreadyMarked, OnPathTaken listener)
      {
         auto initEdges = reverseRange(m_graph.edgesFrom(v));
         std::vector<Edge> stack(begin(initEdges), end(initEdges));
         
         while (!stack.empty())
         {
            auto e = stack.back();
            auto c = e.to();
            stack.pop_back();
            if (isMarked(c))
               continue;

            listener(e);
            mark(c);
            for (auto ne : reverseRange(m_graph.edgesFrom(c)))
            {
               if (!isMarked(ne.to()))
                  stack.push_back(ne);
               else
                  onAlreadyMarked(ne);
            }
         }
      }

      /** Recursive implementation: leads to stack overflows for big graphs */
      void searchImplRec(size_t v, OnMarked onAdjVisited, OnAlreadyFound onAlreadyMarked, OnPathTaken listener)
      {
         for (auto e : m_graph.edgesFrom(v))
         {
            auto a = e.to();
            if (isMarked(a))
            {
               if (onAlreadyMarked(e));
                  return;
               continue;
            }

            listener(e);
            mark(a);
            searchImplRec(a, onAdjVisited, onAlreadyMarked, listener);
         }
         onAdjVisited(v);
      }

   private:
      DiGraph const& m_graph;
   };

   //--------------------------------------------------------------------------

   template<typename T>
   class SymbolDepthFirstSearch
   {
   public:
      using OnMarked = std::function<void(T const&)>;

   public:
      explicit SymbolDepthFirstSearch(SymbolGraph<T> const& g)
         : m_dfs(g.underlyingGraph())
         , m_graph(g)
      {}

      ~SymbolDepthFirstSearch() = default;

      void searchFrom(T const& v)
      {
         static OnMarked nullListener = [](T const&){};
         searchFrom(v, nullListener);
      }

      void searchFrom(T const& v, OnMarked listener)
      {
         size_t vid = m_graph.idFromSymbol(v);
         m_dfs.markFrom(vid, [this, &listener](size_t v){ listener(m_graph.symbolFromId(v)); });
      }

      bool isMarked(T const& v) const
      {
         size_t vid = m_graph.idFromSymbol(v);
         return m_dfs.isMarked(vid);
      }

      bool allMarked() const
      {
         return m_dfs.allMarked();
      }

   private:
      DFS<Edge> m_dfs;
      SymbolGraph<T> const& m_graph;
   };
}
