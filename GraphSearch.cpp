#include "GraphSearch.h"

#include "GraphExceptions.h"


namespace algorithm
{
   DepthFirstSearch::DepthFirstSearch(Graph const& g)
      : m_count(0)
      , m_marked(g.vertexCount(), false)
      , m_graph(g)
   {}

   void DepthFirstSearch::searchFrom(size_t v)
   {
      if (v >= m_marked.size())
         throw InvalidVertex(v);

      searchImpl(v);
   }

   void DepthFirstSearch::searchImpl(size_t v)
   {
      m_marked[v] = true;
      ++m_count;

      for (auto w : m_graph.adjacents(v))
         if (!isMarked(w))
            searchImpl(w);
   }

   bool DepthFirstSearch::isMarked(size_t v) const
   {
      if (v >= m_marked.size())
         throw InvalidVertex(v);

      return m_marked[v];
   }

   bool DepthFirstSearch::allMarked() const
   {
      return m_count == m_graph.vertexCount();
   }
}
