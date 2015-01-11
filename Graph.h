#pragma once

#include "GraphExceptions.h"
#include "utils/Algorithms.h"
#include <vector>


namespace algorithm
{
   class Graph
   {
   public:
      using AdjacencyList  = std::vector<size_t>;
      using const_iterator = AdjacencyList::const_iterator;

   public:
      Graph(size_t vertexCount)
         : m_adjacencyLists(vertexCount)
      {}

      ~Graph() = default;

      size_t vertexCount() const
      {
         return m_adjacencyLists.size();
      }

      size_t edgeCount() const
      {
         size_t count = accumulate(m_adjacencyLists, 0,
            [](size_t s, AdjacencyList const& adj){ return s + adj.size(); });
         return count / 2;
      }

      void addEdge(size_t x, size_t y)
      {
         checkVertexId(x);
         checkVertexId(y);
         m_adjacencyLists[x].push_back(y);
         m_adjacencyLists[y].push_back(x);
      }

      const_iterator beginAdj(size_t v) const
      {
         checkVertexId(v);
         return begin(m_adjacencyLists[v]);
      }

      const_iterator endAdj(size_t v) const
      {
         checkVertexId(v);
         return end(m_adjacencyLists[v]);
      }

   private:
      void checkVertexId(size_t id) const
      {
         if (id >= m_adjacencyLists.size())
            throw InvalidVertex(id);
      }

   private:
      std::vector<AdjacencyList> m_adjacencyLists;
   };
}
