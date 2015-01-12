#include "GraphSearch.h"
#include "GraphExceptions.h"
#include <deque>


namespace algorithm
{
   GraphSearch::GraphSearch(Graph const& g)
      : m_count(0)
      , m_marked(g.vertexCount(), false)
      , m_graph(g)
   {}

   void GraphSearch::searchFrom(size_t v)
   {
      static auto nullListener = [](size_t){};
      searchFrom(v, nullListener);
   }

   void GraphSearch::searchFrom(size_t v, OnMarked listener)
   {
      if (v >= m_marked.size()) throw InvalidVertex(v);
      searchImpl(v, listener);
   }

   bool GraphSearch::isMarked(size_t v) const
   {
      if (v >= m_marked.size()) throw InvalidVertex(v);
      return m_marked[v];
   }

   bool GraphSearch::allMarked() const
   {
      return m_count == m_graph.vertexCount();
   }

   //--------------------------------------------------------------------------

   DepthFirstSearch::DepthFirstSearch(Graph const& g)
      : GraphSearch(g)
   {}

   void DepthFirstSearch::searchImpl(size_t v, OnMarked listener)
   {
      if (isMarked(v))
         return;

      listener(v);
      m_marked[v] = true;
      ++m_count;

      for (auto const& neighbor : m_graph.adjacents(v))
         searchImpl(neighbor, listener);
   }

   //--------------------------------------------------------------------------

   BreathFirstSearch::BreathFirstSearch(Graph const& g)
      : GraphSearch(g)
   {}

   void BreathFirstSearch::searchImpl(size_t v, OnMarked listener)
   {
      std::deque<size_t> toScan;
      toScan.push_back(v);

      while (!toScan.empty())
      {
         auto current = toScan.front();
         toScan.pop_front();
         if (isMarked(current))
            continue;
         
         listener(current);
         m_marked[current] = true;
         ++m_count;

         for (auto neighbor : m_graph.adjacents(current))
            if (!isMarked(neighbor))
               toScan.push_back(neighbor);
      }
   }
}
