#pragma once
#include "GraphExceptions.h"
#include "internal/GenericDiGraph.h"
#include "utils/Algorithms.h"
#include "utils/Utils.h"

#include <istream>
#include <iterator>
#include <vector>


namespace algorithm
{
   template<typename Edge>
   class GenericGraph
   {
   public:
      using DiGraphImpl = GenericDiGraph<Edge>;
      using edge_it = typename DiGraphImpl::edge_it;
      using vertex_it = typename DiGraphImpl::vertex_it;
      using destination_it = typename DiGraphImpl::destination_it;

   public:
      explicit GenericGraph(size_t vertexCount) : m_impl(vertexCount) {}
      ~GenericGraph() = default;

      size_t vertexCount() const
      {
         return m_impl.vertexCount();
      }

      size_t edgeCount() const
      {
         return m_impl.edgeCount() / 2;
      }

      void addEdge(Edge const& e)
      {
         m_impl.addEdge(e);
         m_impl.addEdge(e.reverse());
      }

      size_t addVertex()
      {
         return m_impl.addVertex();
      }

      utils::Range<edge_it> edgesFrom(size_t v) const
      {
         return m_impl.edgesFrom(v);
      }

      utils::Range<destination_it> adjacents(size_t v) const
      {
         return m_impl.adjacents(v);
      }

      utils::Range<vertex_it> vertices() const
      {
         return m_impl.vertices();
      }

      DiGraphImpl const& toDiGraph() const
      {
         return m_impl;
      }

      template<typename ReadEdge>
      static GenericGraph<Edge> createFrom(std::istream&, ReadEdge);

      template<typename WriteEdge>
      static void serializeTo(GenericGraph<Edge> const&, std::ostream&, WriteEdge);

   private:
      DiGraphImpl m_impl;
   };

   template<typename Edge>
   size_t adjacentCount(GenericGraph<Edge> const& g, size_t v)
   {
      return g.adjacents(v).size();
   }
}

#include "GenericGraph.inl.h"
