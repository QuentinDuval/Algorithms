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

      bool                 hasPathTo   (size_t to) const;
      std::vector<size_t>  pathTo      (size_t to) const;
      size_t               pathLengthTo(size_t to) const;

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
      bool relax(WeightedEdge const&);

   private:
      size_t m_from;
      std::vector<bool> m_marked;
      std::vector<size_t> m_sources;
      std::vector<double> m_distances;
   };

   //--------------------------------------------------------------------------

   class TopologicalShortestPathFrom
   {
   public:
      TopologicalShortestPathFrom(WeightedDiGraph const&, size_t from);

      bool                 hasPathTo(size_t to) const;
      std::vector<size_t>  pathTo(size_t to) const;
      double               pathLengthTo(size_t to) const;

   private:
      bool relax(WeightedEdge const&);

   private:
      size_t m_from;
      std::vector<bool> m_marked;
      std::vector<size_t> m_sources;
      std::vector<double> m_distances;
   };
}
