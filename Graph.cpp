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

   Graph Graph::createFrom(std::istream& is)
   {
      DiGraph dg = DiGraph::createFrom(is);
      Graph g(dg.vertexCount());
      for (size_t v = 0; v < dg.vertexCount(); ++v)
         for (auto w : dg.adjacents(v))
            g.addEdge(w, v);
      return g;
   }

   size_t adjacentCount(Graph const& g, size_t v)
   {
      return g.adjacents(v).size();
   }

   void serializeTo(std::ostream& os, Graph const& g)
   {
      //TODO - Remove duplicated edges
   }
}
