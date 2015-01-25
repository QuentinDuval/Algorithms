#pragma once
#include <cctype>


namespace algorithm
{
   template<typename Edge>
   struct GenericDiGraph<Edge>::destination_it
      : public std::iterator<std::input_iterator_tag, size_t>
   {
   public:
      destination_it& operator++()
      {
         ++m_edgeIt;
         return *this;
      }

      bool operator!=(destination_it const& rhs) const
      {
         return m_edgeIt != rhs.m_edgeIt;
      }

      bool operator==(destination_it const& rhs) const
      {
         return m_edgeIt == rhs.m_edgeIt;
      }
      
      size_t operator*() const 
      {
         return m_edgeIt->to();
      }

   private:
      destination_it(edge_it const& it) : m_edgeIt(it) {}
      edge_it m_edgeIt;
      friend GenericDiGraph<Edge>;
   };

   //--------------------------------------------------------------------------

   template<typename Edge>
   struct GenericDiGraph<Edge>::vertex_it
      : public std::iterator<std::input_iterator_tag, size_t>
   {
   public:
      vertex_it& operator++()
      {
         ++m_vertex_index;
         return *this;
      }

      bool operator!=(vertex_it const& rhs) const
      {
         return m_vertex_index != rhs.m_vertex_index;
      }

      bool operator==(vertex_it const& rhs) const
      {
         return m_vertex_index == rhs.m_vertex_index;
      }

      size_t operator*() const
      {
         return m_vertex_index;
      }

   private:
      vertex_it(size_t v) : m_vertex_index(v) {}
      size_t m_vertex_index;
      friend GenericDiGraph<Edge>;
   };

   //--------------------------------------------------------------------------

   template<typename Edge>
   template<typename ReadEdge>
   GenericDiGraph<Edge> GenericDiGraph<Edge>::createFrom(std::istream& is, ReadEdge readEdge)
   {
      size_t vertexCount = 0;
      is >> vertexCount;

      GenericDiGraph<Edge> g(vertexCount);
      while (is)
      {
         int next = is.peek();
         if (next == ';')
            break;

         if (!std::isdigit(next))
         {
            is.get();
         }
         else
         {
            g.addEdge(readEdge(is));
         }
      }
      return g;
   }

   template<typename Edge>
   template<typename WriteEdge>
   void GenericDiGraph<Edge>::serializeTo(GenericDiGraph<Edge> const& g, std::ostream& os, WriteEdge writeEdge)
   {
      os << std::endl << g.vertexCount() << std::endl;
      for (size_t v = 0; v < g.vertexCount(); ++v)
      for (auto e : g.edgesFrom(v))
      {
         writeEdge(os, e);
         os << std::endl;
      }
      os << ";";
   }
}
