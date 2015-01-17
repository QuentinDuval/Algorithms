#pragma once

#include "GraphExceptions.h"
#include "DiGraph.h"
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
      using edge_it = DiGraph::edge_it;
      using vertex_it = DiGraph::vertex_it;

   public:
      explicit Graph(size_t vertexCount);
      ~Graph() = default;

      size_t            vertexCount () const;
      size_t            edgeCount   () const;
      void              addEdge     (size_t x, size_t y);
      size_t            addVertex   ();
      Range<edge_it>    edgesFrom   (size_t v) const;
      Range<vertex_it>  adjacents   (size_t v) const;

   public:
      static Graph      createFrom  (std::istream&);

   private:
      DiGraph m_impl;
   };


   //--------------------------------------------------------------------------
   // Helpers
   //--------------------------------------------------------------------------

   size_t adjacentCount (Graph const& g, size_t v);
   void   serializeTo   (std::ostream&, Graph const&);
}
