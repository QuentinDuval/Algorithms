#pragma once
#include <functional>
#include <vector>


namespace algorithm
{
   template<typename Edge>
   class GraphSearch
   {
   public:
      /** Called upon starting processing a vertex */
      using OnDiscovered = std::function<bool(size_t)>;

      /** Called upon discovering an edge */
      using OnProcessEdge = std::function<bool(Edge const&)>;

      /** Called upon finishing processing a vertex */
      using OnProcessed = std::function<bool(size_t)>;

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

      void markFrom(size_t v)
      {
         static auto nullListener = [](Edge const&){ return false; };
         searchImpl(v, nullListener);
      }

      void markFrom(size_t v, OnDiscovered onDiscovered)
      {
         if (!isMarked(v))
            onDiscovered(v);

         auto processEdge = [&](Edge const& e)
         {
            auto v = e.to();
            if (!isMarked(v))
               return onDiscovered(v);
            return false;
         };
         searchImpl(v, processEdge);
      }

      void pathsFrom(size_t v, OnProcessEdge onPathTaken)
      {
         auto processEdge = [&](Edge const& e)
         {
            auto v = e.to();
            if (!isMarked(v))
               return onPathTaken(e);
            return false;
         };
         searchImpl(v, processEdge);
      }

   protected:
      void mark(size_t v)
      {
         if (v >= m_marked.size())
            throw InvalidVertex(v);

         m_marked[v] = true;
         ++m_count;
      }

      virtual void searchImpl(size_t v, OnProcessEdge listener) = 0;

   private:
      size_t m_count;
      std::vector<bool> m_marked;
   };
}
