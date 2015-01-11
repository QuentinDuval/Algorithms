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

   class Graph
   {
   public:
      using AdjList = std::vector<size_t>;
      using edge_it = AdjList::const_iterator;

   public:
      explicit Graph(size_t vertexCount);
      ~Graph() = default;

      size_t         vertexCount () const;
      size_t         edgeCount   () const;
      void           addEdge     (size_t x, size_t y);
      size_t         addVertex   ();
      Range<edge_it> adjacents   (size_t v) const;

   private:
      void checkVertexId(size_t id) const;

   private:
      std::vector<AdjList> m_adjacencyLists;
   };


   //--------------------------------------------------------------------------
   // Helpers
   //--------------------------------------------------------------------------

   size_t adjacentCount (Graph const& g, size_t v);
   Graph  createFrom    (std::istream&);
   void   serializeTo   (std::ostream&, Graph const&);
}
