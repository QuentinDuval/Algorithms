#pragma once
#include <functional>
#include <vector>


namespace algorithm
{
   template<typename Edge>
   class GraphSearch
   {
   public:
      using OnMarked = std::function<void(Edge const&)>;

   public:
      GraphSearch(size_t vertexCount)
         : m_count(0)
         , m_marked(vertexCount, false)
      {}

      bool isMarked(size_t v) const
      {
         if (v >= m_marked.size())
            throw InvalidVertex(v);
         return m_marked[v];
      }

      bool allMarked() const
      {
         return m_count == m_marked.size();
      }

      void mark(size_t v)
      {
         if (v >= m_marked.size())
            throw InvalidVertex(v);
         m_marked[v] = true;
         ++m_count;
      }

      void markFrom(size_t v)
      {
         static auto nullListener = [](Edge const&){};
         searchImpl(v, nullListener);
      }

      void markFrom(size_t v, std::function<void(size_t)> onVertexMarked)
      {
         if (!isMarked(v))
            onVertexMarked(v);

         auto listener = [onVertexMarked](Edge const& e){ onVertexMarked(e.to()); };
         searchImpl(v, listener);
      }

      void searchFrom(size_t v, OnMarked listener)
      {
         searchImpl(v, listener);
      }

   private:
      virtual void searchImpl(size_t v, OnMarked listener) = 0;

   private:
      size_t m_count;
      std::vector<bool> m_marked;
   };
}
