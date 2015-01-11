#include "Graph.h"
#include "utils/Utils.h"
#include <cctype>


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
         [](size_t s, AdjList const& adj){ return s + adj.size(); });
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
      m_adjacencyLists.emplace_back(AdjList());
      return m_adjacencyLists.size() - 1;
   }

   Range<Graph::edge_it> Graph::adjacents(size_t v) const
   {
      checkVertexId(v);
      auto b = begin(m_adjacencyLists[v]);
      auto e = end(m_adjacencyLists[v]);
      return Range<Graph::edge_it>(b, e);
   }

   void Graph::checkVertexId(size_t id) const
   {
      if (id >= m_adjacencyLists.size())
         throw InvalidVertex(id);
   }

   size_t adjacentCount(Graph const& g, size_t v)
   {
      return g.adjacents(v).size();
   }

   Graph createFrom(std::istream& is)
   {
      size_t vertexCount = 0;
      is >> vertexCount;
      
      Graph g(vertexCount);
      while (is)
      {
         int next = is.peek();
         if (next == ';')
            break;
         
         if (!std::isdigit(next))
         {
            is.get();
         }
         else
         {
            int v = 0, w = 0;
            is >> v >> w;
            g.addEdge(v, w);
         }
      }
      return g;
   }

   void serializeTo(std::ostream& os, Graph const& g)
   {
      //TODO
   }
}
