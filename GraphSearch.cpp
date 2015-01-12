#include "GraphSearch.h"
#include "GraphExceptions.h"
#include <deque>


namespace algorithm
{
   DepthFirstSearch::DepthFirstSearch(Graph const& g)
      : m_count(0)
      , m_marked(g.vertexCount(), false)
      , m_graph(g)
   {}

   void DepthFirstSearch::searchFrom(size_t v)
   {
      static auto nullListener = [](size_t){};
      searchFrom(v, nullListener);
   }

   void DepthFirstSearch::searchFrom(size_t v, OnMarked listener)
   {
      if (v >= m_marked.size())
         throw InvalidVertex(v);

      searchImpl(v, listener);
   }

   void DepthFirstSearch::searchImpl(size_t v, OnMarked listener)
   {
      listener(v);
      m_marked[v] = true;
      ++m_count;

      for (auto const& w : m_graph.adjacents(v))
         if (!isMarked(w))
            searchImpl(w, listener);
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

   //--------------------------------------------------------------------------

   BreathFirstSearch::BreathFirstSearch(Graph const& g)
      : m_count(0)
      , m_marked(g.vertexCount(), false)
      , m_graph(g)
   {}

   void BreathFirstSearch::searchFrom(size_t v)
   {
      static OnMarked nullListener = [](size_t){};
      searchFrom(v, nullListener);
   }

   void BreathFirstSearch::searchFrom(size_t v, OnMarked listener)
   {
      if (v >= m_marked.size())
         throw InvalidVertex(v);

      searchImpl(v, listener);
   }

   bool BreathFirstSearch::isMarked(size_t v) const
   {
      if (v >= m_marked.size())
         throw InvalidVertex(v);

      return m_marked[v];
   }

   bool BreathFirstSearch::allMarked() const
   {
      return m_count == m_graph.vertexCount();
   }

   void BreathFirstSearch::searchImpl(size_t v, OnMarked listener)
   {
      std::deque<size_t> toScan;
      toScan.push_back(v);

      while (!toScan.empty())
      {
         auto current = toScan.front();
         toScan.pop_front();

         if (!isMarked(current))
         {
            m_marked[current] = true;
            listener(current);

            for (auto neighbor : m_graph.adjacents(current))
               if (!isMarked(neighbor))
                  toScan.push_back(neighbor);
         }
      }
   }
}
