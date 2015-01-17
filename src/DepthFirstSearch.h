#pragma once

#include "GraphSearch.h"
#include "SymbolGraph.h"
#include "internal/GenericDiGraph.h"
#include "internal/GenericGraph.h"
#include <functional>


namespace algorithm
{
   template<typename Edge>
   class DFS : public GraphSearch
   {
   public:
      using DiGraph  = GenericDiGraph<Edge>;
      using OnMarked = GraphSearch::OnMarked;

   public:
      explicit DFS(DiGraph const& g)
         : GraphSearch(g.vertexCount())
         , m_graph(g)
      {}

      explicit DFS(GenericGraph<Edge> const& g)
         : GraphSearch(g.vertexCount())
         , m_graph(g.toDiGraph())
      {}

      virtual ~DFS() = default;

      void searchFrom(size_t v, OnMarked listener)
      {
         if (isMarked(v))
            return;

         listener(v);
         mark(v);

         for (auto a : m_graph.adjacents(v))
            searchFrom(a, listener);
      }

   protected:
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
         m_dfs.searchFrom(vid,
            [this, &listener](size_t v){ listener(m_graph.symbolFromId(v)); });
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
