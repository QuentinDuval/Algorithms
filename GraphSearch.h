#pragma once
#include "Graph.h"
#include <functional>
#include <vector>


namespace algorithm
{
   class GraphSearch
   {
   public:
      //TODO - Replace by strategy for pre-order & post-order
      using OnMarked = std::function<void(size_t)>;

   public:
      explicit GraphSearch(Graph const& g);
      virtual ~GraphSearch() = default;

      void searchFrom   (size_t v);
      void searchFrom   (size_t v, OnMarked listener);
      bool isMarked     (size_t v) const;
      bool allMarked    () const;

   private:
      virtual void searchImpl   (size_t v, OnMarked listener) = 0;

   protected:
      size_t m_count;
      std::vector<bool> m_marked;
      Graph const& m_graph;
   };

   //--------------------------------------------------------------------------

   class DepthFirstSearch : public GraphSearch
   {
   public:
      explicit DepthFirstSearch(Graph const& g);
      virtual ~DepthFirstSearch() = default;

   private:
      void searchImpl(size_t v, OnMarked listener) override;
   };

   //--------------------------------------------------------------------------

   class BreathFirstSearch : public GraphSearch
   {
   public:
      explicit BreathFirstSearch(Graph const& g);
      virtual ~BreathFirstSearch() = default;

   private:
      void searchImpl(size_t v, OnMarked listener) override;
   };
}
