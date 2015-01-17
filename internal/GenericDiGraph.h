#pragma once
#include "GraphExceptions.h"
#include "utils/Algorithms.h"
#include "utils/Utils.h"

#include <istream>
#include <iterator>
#include <vector>


namespace algorithm
{
   template<typename Edge>
   class EdgeContractSafisfied
   {
      template <typename C> static char test(decltype(&C::to));
      template <typename C> static long test(...);

   public:
      enum { value = sizeof(test<Edge>(0)) == sizeof(char) };
   };


   template<typename Edge>
   class GenericDiGraph
   {
      static_assert(EdgeContractSafisfied<Edge>::value, "Edge must have a method: size_t to() const");

   public:
      using AdjList = std::vector<Edge>;
      using edge_it = typename AdjList::const_iterator;
      struct vertex_it;

   public:
      explicit GenericDiGraph(size_t vertexCount)
         : m_count(0), m_adjacencyLists(vertexCount)
      {}

      ~GenericDiGraph() = default;

      size_t vertexCount() const
      {
         return m_adjacencyLists.size();
      }

      size_t edgeCount() const
      {
         return m_count;
      }

      void addEdge(size_t from, Edge const& e)
      {
         checkVertexId(from);
         checkVertexId(e.to());
         m_adjacencyLists[from].push_back(e);
         ++m_count;
      }

      size_t addVertex()
      {
         m_adjacencyLists.emplace_back(AdjList());
         return m_adjacencyLists.size() - 1;
      }

      Range<edge_it> edgesFrom(size_t v) const
      {
         checkVertexId(v);
         auto b = begin(m_adjacencyLists[v]);
         auto e = end(m_adjacencyLists[v]);
         return Range<GenericDiGraph::edge_it>(b, e);
      }

      Range<vertex_it> adjacents(size_t v) const
      {
         auto edges = edgesFrom(v);
         auto b = vertex_it(begin(edges));
         auto e = vertex_it(end(edges));
         return Range<GenericDiGraph::vertex_it>(b, e);
      }

      template<typename ReadEdge>
      static GenericDiGraph<Edge> createFrom(std::istream&, ReadEdge);

      template<typename WriteEdge>
      static void serializeTo(GenericDiGraph<Edge> const&, std::ostream&, WriteEdge);

   private:
      void checkVertexId(size_t id) const
      {
         if (id >= m_adjacencyLists.size())
            throw InvalidVertex(id);
      }

   private:
      size_t m_count;
      std::vector<AdjList> m_adjacencyLists;
   };

   template<typename Edge>
   size_t adjacentCount(GenericDiGraph<Edge> const& g, size_t v)
   {
      return g.adjacents(v).size();
   }

   template<typename Edge>
   GenericDiGraph<Edge> makeReversed(GenericDiGraph<Edge> const& g)
   {
      GenericDiGraph<Edge> rg(g.vertexCount());
      for (size_t v = 0; v < g.vertexCount(); ++v)
         for (auto w : g.adjacents(v))
            rg.addEdge(w, v);
      return rg;
   }
}

#include "GenericDiGraph.inl.h"
