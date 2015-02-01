#pragma once
#include <cctype>


namespace algorithm
{
   template<typename Edge>
   template<typename ReadEdge>
   GenericGraph<Edge> GenericGraph<Edge>::createFrom(std::istream& is, ReadEdge readEdge)
   {
      auto diGraph = GenericDiGraph<Edge>::createFrom(is, readEdge);

      GenericGraph<Edge> g(diGraph.vertexCount());
      for (size_t v : g.vertices())
         for (auto e : diGraph.edgesFrom(v))
            g.addEdge(e);
      return g;
   }

   template<typename Edge>
   template<typename WriteEdge>
   void GenericGraph<Edge>::serializeTo(GenericGraph<Edge> const& g, std::ostream& os, WriteEdge writeEdge)
   {
      //TODO - Euler path (visits every edge, which is easy, not as the Hamilton path)
   }
}
