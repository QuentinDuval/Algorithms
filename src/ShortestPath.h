#pragma once

#include "BreathFirstSearch.h"
#include "Edge.h"
#include "DiGraph.h"
#include "Graph.h"
#include "WeightedDiGraph.h"
#include "WeightedGraph.h"
#include "utils/Matrix.h"

#include <functional>
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

   class RelaxBasedShortestPath
   {
   public:
      bool hasPathTo(size_t to) const;
      std::vector<size_t> pathTo(size_t to) const;
      double pathLengthTo(size_t to) const;

   protected:
      RelaxBasedShortestPath(size_t from, size_t order);
      ~RelaxBasedShortestPath() = default;

      bool relax(WeightedEdge const& e);

   protected:
      size_t m_from;
      std::vector<size_t> m_sources;
      std::vector<double> m_distances;
   };

   //--------------------------------------------------------------------------

   class DijkstraShortestPathFrom
      : public RelaxBasedShortestPath
   {
   public:
      DijkstraShortestPathFrom(WeightedDiGraph const&, size_t from);
      DijkstraShortestPathFrom(WeightedGraph   const&, size_t from);
   };

   //--------------------------------------------------------------------------

   class TopologicalShortestPathFrom
      : public RelaxBasedShortestPath
   {
   public:
      TopologicalShortestPathFrom(WeightedDiGraph const&, size_t from);
   };

   //--------------------------------------------------------------------------

   class BellmanFordShortestPathFrom
      : public RelaxBasedShortestPath
   {
   public:
      BellmanFordShortestPathFrom(WeightedDiGraph const&, size_t from);
      BellmanFordShortestPathFrom(WeightedGraph   const&, size_t from);
   };

   //--------------------------------------------------------------------------

   class FloydWarshallShortestPath
   {
   public:
      explicit FloydWarshallShortestPath(WeightedDiGraph const&);
      explicit FloydWarshallShortestPath(WeightedGraph   const&);

      double pathLength(size_t from, size_t to) const;

   private:
      Matrix<double> m_weights;
   };

   //--------------------------------------------------------------------------

   class AStarShortestPathFromTo
   {
   public:
      /**
       * Heuristic providing the estimated distance between two points.
       * If it always returns 0, then we simply get Dijsktra.
       */
      using DistanceEstimation = std::function<double(size_t, size_t)>;
      using Path = std::vector<size_t>;

   public:
      AStarShortestPathFromTo(WeightedDiGraph const&, DistanceEstimation);
      AStarShortestPathFromTo(WeightedGraph   const&, DistanceEstimation);

      std::pair<double, Path> shortestPath(size_t from, size_t to) const;

   private:
      WeightedDiGraph const& m_diGraph;
      DistanceEstimation m_distHeuristic;
   };
}
