#include "DiGraph.h"
#include "utils/Utils.h"
#include <cctype>


namespace algorithm
{
   DiGraph::DiGraph(size_t vertexCount)
      : m_adjacencyLists(vertexCount)
   {}

   size_t DiGraph::vertexCount() const
   {
      return m_adjacencyLists.size();
   }

   size_t DiGraph::edgeCount() const
   {
      return m_count;
   }

   void DiGraph::addEdge(size_t x, size_t y)
   {
      checkVertexId(x);
      checkVertexId(y);
      m_adjacencyLists[x].push_back(y);
      ++m_count;
   }

   size_t DiGraph::addVertex()
   {
      m_adjacencyLists.emplace_back(AdjList());
      return m_adjacencyLists.size() - 1;
   }

   Range<DiGraph::edge_it> DiGraph::adjacents(size_t v) const
   {
      checkVertexId(v);
      auto b = begin(m_adjacencyLists[v]);
      auto e = end(m_adjacencyLists[v]);
      return Range<DiGraph::edge_it>(b, e);
   }

   void DiGraph::checkVertexId(size_t id) const
   {
      if (id >= m_adjacencyLists.size())
         throw InvalidVertex(id);
   }

   size_t adjacentCount(DiGraph const& g, size_t v)
   {
      return g.adjacents(v).size();
   }
}
