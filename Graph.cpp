#include "Graph.h"
#include "utils/Utils.h"
#include <cctype>


namespace algorithm
{
   Graph::Graph(size_t vertexCount)
      : m_impl(vertexCount)
   {}

   size_t Graph::vertexCount() const
   {
      return m_impl.vertexCount();
   }

   size_t Graph::edgeCount() const
   {
      return m_impl.edgeCount() / 2;
   }

   void Graph::addEdge(size_t x, size_t y)
   {
      m_impl.addEdge(x, y);
      m_impl.addEdge(y, x);
   }

   size_t Graph::addVertex()
   {
      return m_impl.addVertex();
   }

   Range<Graph::edge_it> Graph::adjacents(size_t v) const
   {
      return m_impl.adjacents(v);
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
      //TODO - Remove duplicated edges
   }
}
