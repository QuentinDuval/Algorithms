#include "Graph.h"
#include "utils/Utils.h"


namespace algorithm
{
   Graph::Graph(size_t vertexCount)
      : m_adjacencyLists(vertexCount)
   {}

   size_t Graph::vertexCount() const
   {
      return m_adjacencyLists.size();
   }

   size_t Graph::edgeCount() const
   {
      size_t count = accumulate(m_adjacencyLists, 0,
         [](size_t s, AdjacencyList const& adj){ return s + adj.size(); });
      return count / 2;
   }

   void Graph::addEdge(size_t x, size_t y)
   {
      checkVertexId(x);
      checkVertexId(y);
      m_adjacencyLists[x].push_back(y);
      m_adjacencyLists[y].push_back(x);
   }

   size_t Graph::addVertex()
   {
      m_adjacencyLists.emplace_back(AdjacencyList());
      return m_adjacencyLists.size() - 1;
   }

   Graph::edge_iterator Graph::beginAdj(size_t v) const
   {
      checkVertexId(v);
      return begin(m_adjacencyLists[v]);
   }

   Graph::edge_iterator Graph::endAdj(size_t v) const
   {
      checkVertexId(v);
      return end(m_adjacencyLists[v]);
   }

   void Graph::checkVertexId(size_t id) const
   {
      if (id >= m_adjacencyLists.size())
         throw InvalidVertex(id);
   }

   size_t adjacentCount(Graph const& g, size_t v)
   {
      return std::distance(g.beginAdj(v), g.endAdj(v));
   }
}
