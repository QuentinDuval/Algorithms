#pragma once
#include "GraphExceptions.h"
#include "utils/Algorithms.h"
#include "utils/Range.h"

#include <istream>
#include <iterator>
#include <vector>


namespace algorithm
{
   template<typename Edge>
   class DiGraphEdgeContract
   {
      template <typename C> static char testTo(decltype(&C::to));
      template <typename C> static long testTo(...);

      template <typename C> static char testFrom(decltype(&C::from));
      template <typename C> static long testFrom(...);

      template <typename C> static char testRev(decltype(&C::reverse));
      template <typename C> static long testRev(...);

   public:
      enum { hasTo   = sizeof(testTo<Edge>(0)) == sizeof(char) };
      enum { hasFrom = sizeof(testFrom<Edge>(0)) == sizeof(char) };
      enum { hasRev  = sizeof(testRev<Edge>(0)) == sizeof(char) };
   };

   //--------------------------------------------------------------------------

   template<typename Edge>
   class GenericDiGraph
   {
      static_assert(DiGraphEdgeContract<Edge>::hasTo,   "Edge does not have method to.");
      static_assert(DiGraphEdgeContract<Edge>::hasFrom, "Edge does not have method from.");
      static_assert(DiGraphEdgeContract<Edge>::hasRev,  "Edge does not have method reverse.");

   public:
      using AdjList = std::vector<Edge>;
      using edge_it = typename AdjList::const_iterator;
      struct destination_it;
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

      void addEdge(Edge const& e)
      {
         checkVertexId(e.from());
         checkVertexId(e.to());
         m_adjacencyLists[e.from()].push_back(e);
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
         return Range<edge_it>(b, e);
      }

      Range<destination_it> adjacents(size_t v) const
      {
         auto edges = edgesFrom(v);
         auto b = destination_it(begin(edges));
         auto e = destination_it(end(edges));
         return Range<destination_it>(b, e);
      }

      Range<vertex_it> vertices() const
      {
         return Range<vertex_it>(0, vertexCount());
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
      for (size_t v : g.vertices())
         for (auto e : g.edgesFrom(v))
            rg.addEdge(e.reverse());
      return rg;
   }
}

#include "GenericDiGraph.inl.h"
