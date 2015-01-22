#pragma once

#include "BreathFirstSearch.h"
#include "Edge.h"
#include "DiGraph.h"
#include "Graph.h"
#include "WeightedDiGraph.h"
#include "WeightedGraph.h"
#include <vector>


namespace algorithm
{
   class ShortestPathFrom
   {
   public:
      ShortestPathFrom(DiGraph const&, size_t from);
      ShortestPathFrom(Graph   const&, size_t from);

      ShortestPathFrom(WeightedDiGraph const&, size_t from);
      ShortestPathFrom(WeightedGraph   const&, size_t from);

      bool                 hasPathTo   (size_t to) const;
      std::vector<size_t>  pathTo      (size_t to) const;
      size_t               pathLengthTo(size_t to) const;

   private:
      void fillPathNodes(size_t to, std::vector<size_t>& nodes) const;

   private:
      size_t m_from;
      std::vector<bool> m_marked;
      std::vector<size_t> m_sources;
   };

   //--------------------------------------------------------------------------

   class DijkstraShortestPathFrom
   {
   public:
      DijkstraShortestPathFrom(WeightedDiGraph const&, size_t from);
      DijkstraShortestPathFrom(WeightedGraph   const&, size_t from);

      bool                 hasPathTo(size_t to) const;
      std::vector<size_t>  pathTo(size_t to) const;
      double               pathLengthTo(size_t to) const;

   private:
      void fillPathNodes(size_t to, std::vector<size_t>& nodes) const;

   private:
      size_t m_from;
      std::vector<bool> m_marked;
      std::vector<size_t> m_sources;
      std::vector<double> m_distances;
   };

   //TODO - Add an algorithm for shortest path on weighted digraph with no cycle => topological sort
}
