#pragma once
#include "Graph.h"
#include <functional>
#include <vector>


namespace algorithm
{
   class DepthFirstSearch
   {
   public:
      explicit DepthFirstSearch(Graph const& g);
      ~DepthFirstSearch() = default;

      void searchFrom  (size_t v);
      bool isMarked    (size_t v) const;
      bool allMarked   () const;

   private:
      void searchImpl  (size_t v);

   private:
      size_t m_count;
      std::vector<bool> m_marked;
      Graph const& m_graph;
   };
}
