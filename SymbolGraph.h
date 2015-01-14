#pragma once
#include "Graph.h"
#include <unordered_map>
#include <vector>


namespace algorithm
{
   template<typename T>
   class SymbolGraph
   {
   public:
      template<typename InputIter>
      explicit SymbolGraph(InputIter first, InputIter last)
         : m_graph(std::distance(first, last))
         , m_idsToSymbols(first, last)
         , m_symbolToIds()
      {
         for (size_t i = 0; first != last; ++i, ++first)
            m_symbolToIds[*first] = i;
      }

      size_t vertexCount() const
      {
         return m_graph.vertexCount();
      }

      size_t edgeCount() const
      {
         return m_graph.edgeCount();
      }

      void addEdge(T const& x, T const& y)
      {
         m_graph.addEdge(idFromSymbol(x), idFromSymbol(y));
      }

      size_t addVertex(T const& v)
      {
         m_graph.addVertex();
         m_symbolToIds[v] = m_graph.size() - 1;
      }

      std::vector<T> adjacents(T const& v) const
      {
         std::vector<T> out;
         auto range = m_graph.adjacents(idFromSymbol(v));
         std:transform(begin(range), end(range), std::back_inserter(out),
            [this](size_t v) { return symbolFromId(v); });
         return out;
      }

      size_t idFromSymbol(T const& v) const
      {
         auto vid = m_symbolToIds.find(v);
         if (vid == m_symbolToIds.end())
            throw InvalidVertex(toString(v));
         return vid->second;
      }

      T const& symbolFromId(size_t id) const
      {
         if (id >= m_idsToSymbols.size())
            throw InvalidVertex(id);
         return m_idsToSymbols[id];
      }

      Graph const& underlyingGraph() const
      {
         return m_graph;
      }

   private:
      Graph                         m_graph;
      std::vector<T>                m_idsToSymbols;
      std::unordered_map<T, size_t> m_symbolToIds;
   };
}
