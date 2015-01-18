#pragma once

#include "BreathFirstSearch.h"
#include "Edge.h"
#include "internal/GenericDiGraph.h"
#include "internal/GenericGraph.h"
#include <vector>


namespace algorithm
{
   class ShortestPathFrom
   {
   public:
      ShortestPathFrom(GenericDiGraph<Edge> const&, size_t from);
      ShortestPathFrom(GenericGraph<Edge>   const&, size_t from);

      bool                 hasPathTo   (size_t to) const;
      std::vector<size_t>  pathTo      (size_t to) const;
      size_t               pathLengthTo(size_t to) const;

   private:
      void fillPathNodes(size_t to, std::vector<size_t>& nodes) const;

   private:
      BFS<Edge> m_bfs;
      size_t m_from;
      std::vector<size_t> m_sources;
   };
}
