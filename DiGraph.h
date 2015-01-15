#pragma once

#include "GraphExceptions.h"
#include "utils/Algorithms.h"
#include "utils/Utils.h"

#include <istream>
#include <vector>


namespace algorithm
{
   //--------------------------------------------------------------------------
   // Unweighted and undirected Graph
   //--------------------------------------------------------------------------

   class DiGraph
   {
   public:
      using AdjList = std::vector<size_t>;
      using edge_it = AdjList::const_iterator;

   public:
      explicit DiGraph(size_t vertexCount);
      ~DiGraph() = default;

      size_t         vertexCount () const;
      size_t         edgeCount   () const;
      void           addEdge     (size_t x, size_t y);
      size_t         addVertex   ();
      Range<edge_it> adjacents   (size_t v) const;

   public:
      static DiGraph createFrom  (std::istream&);

   private:
      void checkVertexId(size_t id) const;

   private:
      size_t m_count;
      std::vector<AdjList> m_adjacencyLists;
   };


   //--------------------------------------------------------------------------
   // Helpers
   //--------------------------------------------------------------------------

   size_t   adjacentCount(DiGraph const& g, size_t v);
   DiGraph  makeReversed (DiGraph const& g);
   void     serializeTo  (std::ostream&, DiGraph const&);
}

