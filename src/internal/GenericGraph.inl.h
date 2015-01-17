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
      for (size_t v = 0; v < diGraph.vertexCount(); ++v)
         for (auto e : diGraph.edgesFrom(v))
            g.addEdge(e);
      return g;
   }

   template<typename Edge>
   template<typename WriteEdge>
   void GenericGraph<Edge>::serializeTo(GenericGraph<Edge> const& g, std::ostream& os, WriteEdge writeEdge)
   {
      //TODO
   }
}
