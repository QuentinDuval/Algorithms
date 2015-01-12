#pragma once
#include "Graph.h"
#include <functional>
#include <vector>


namespace algorithm
{
   class DepthFirstSearch
   {
   public:
      using OnMarked = std::function<void(size_t)>;

   public:
      explicit DepthFirstSearch(Graph const& g);
      ~DepthFirstSearch() = default;

      void searchFrom   (size_t v);
      void searchFrom   (size_t v, OnMarked listener);
      bool isMarked     (size_t v) const;
      bool allMarked    () const;

   private:
      void searchImpl   (size_t v, OnMarked listener);

   private:
      size_t m_count;
      std::vector<bool> m_marked;
      Graph const& m_graph;
   };
}
