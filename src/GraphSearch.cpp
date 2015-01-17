#include "GraphSearch.h"
#include "GraphExceptions.h"
#include <deque>


namespace algorithm
{
   GraphSearch::GraphSearch(size_t vertexCount)
      : m_count(0)
      , m_marked(vertexCount, false)
   {}

   bool GraphSearch::isMarked(size_t v) const
   {
      if (v >= m_marked.size())
         throw InvalidVertex(v);
      return m_marked[v];
   }

   bool GraphSearch::allMarked() const
   {
      return m_count == m_marked.size();
   }

   void GraphSearch::searchFrom(size_t v)
   {
      static auto nullListener = [](size_t){};
      searchFrom(v, nullListener);
   }

   void GraphSearch::mark(size_t v)
   {
      if (v >= m_marked.size())
         throw InvalidVertex(v);
      m_marked[v] = true;
      ++m_count;
   }
}
