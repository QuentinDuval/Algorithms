#pragma once
#include <functional>
#include <vector>


namespace algorithm
{
   template<typename Edge>
   class GraphSearch
   {
   public:
      using OnMarked = std::function<void(size_t)>;

   public:
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

      void GraphSearch::mark(size_t v)
      {
         if (v >= m_marked.size())
            throw InvalidVertex(v);
         m_marked[v] = true;
         ++m_count;
      }

      void GraphSearch::markFrom(size_t v)
      {
         static auto nullListener = [](size_t){};
         searchFrom(v, nullListener);
      }

      virtual void markFrom(size_t v, OnMarked listener) = 0;

   private:
      size_t m_count;
      std::vector<bool> m_marked;
   };
}
