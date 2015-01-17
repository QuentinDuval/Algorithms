#pragma once
#include <functional>
#include <vector>


namespace algorithm
{
   class GraphSearch
   {
   public:
      using OnMarked = std::function<void(size_t)>;

   public:
      GraphSearch(size_t vertexCount);
      virtual ~GraphSearch() = default;

      bool           isMarked    (size_t v) const;
      bool           allMarked   () const;
      void           mark        (size_t v);
      void           searchFrom  (size_t v);
      virtual void   searchFrom  (size_t v, OnMarked listener) = 0;

   private:
      size_t m_count;
      std::vector<bool> m_marked;
   };
}
