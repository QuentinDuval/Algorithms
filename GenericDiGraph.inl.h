#pragma once
#include <cctype>


namespace algorithm
{
   template<typename Edge>
   struct GenericDiGraph<Edge>::vertex_it
      : public std::iterator<std::input_iterator_tag, size_t>
   {
   public:
      vertex_it& operator++()
      {
         ++m_edgeIt;
         return *this;
      }

      vertex_it& operator++(int)
      {
         m_edgeIt++;
         return *this;
      }

      bool operator!=(vertex_it const& rhs) const
      {
         return m_edgeIt != rhs.m_edgeIt;
      }

      bool operator==(vertex_it const& rhs) const
      {
         return m_edgeIt == rhs.m_edgeIt;
      }
      
      size_t operator*() const 
      {
         return m_edgeIt->to();
      }

   private:
      vertex_it(edge_it const& it) : m_edgeIt(it) {}
      edge_it m_edgeIt;
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
            size_t v = 0;
            is >> v;
            g.addEdge(v, readEdge(is));
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
         os << v << " ";
         writeEdge(os, e);
         os << std::endl;
      }
      os << ";";
   }
}
