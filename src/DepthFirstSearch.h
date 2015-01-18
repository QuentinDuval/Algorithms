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
      using OnMarked = GraphSearch<Edge>::OnMarked;
      using OnPathTaken = GraphSearch<Edge>::OnPathTaken;

   public:
      explicit DFS(DiGraph const& g)
         : GraphSearch(g.vertexCount())
         , m_graph(g)
      {}

      explicit DFS(GenericGraph<Edge> const& g)
         : DFS(g.toDiGraph())
      {}

      void postOrderFrom(size_t v, OnMarked onAdjVisited)
      {
         static OnPathTaken nullListener = [](Edge const&){};
         searchImpl(v, onAdjVisited, nullListener);
      }

   private:
      void searchImpl(size_t v, OnPathTaken listener) override
      {
         static OnMarked nullListener = [](size_t){};
         searchImpl(v, nullListener, listener);
      }

      void searchImpl(size_t v, OnMarked onAdjVisited, OnPathTaken listener)
      {
         if (isMarked(v))
            return;

         mark(v);
         searchImplRec(v, onAdjVisited, listener);
      }

      //void searchImplRec(size_t v, OnMarked onAdjVisited, OnPathTaken listener)
      //{
      //   for (auto e : m_graph.edgesFrom(v))
      //   {
      //      auto a = e.to();
      //      if (isMarked(a))
      //         continue;
      //
      //      listener(e);
      //      mark(a);
      //      searchImplRec(a, onAdjVisited, listener);
      //   }
      //   onAdjVisited(v);
      //}

      void searchImplRec(size_t v, OnMarked onAdjVisited, OnPathTaken listener)
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
               if (!isMarked(ne.to()))
                  stack.push_back(ne);
         }
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
