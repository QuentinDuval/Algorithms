#pragma once

#include "GraphExceptions.h"
#include "internal/GenericDiGraph.h"
#include "utils/Algorithms.h"
#include "utils/Utils.h"

#include <istream>
#include <vector>


namespace algorithm
{
   class Edge
   {
   public:
      Edge(size_t from, size_t to);
      size_t from() const;
      size_t to() const;
      Edge reverse() const;

   private:
      size_t m_from;
      size_t m_to;
   };

   //--------------------------------------------------------------------------

   class WeightedEdge
   {
   public:
      WeightedEdge(size_t from, size_t to, double weight);
      ~WeightedEdge() = default;

      size_t from() const;
      size_t to() const;
      double weight() const;
      WeightedEdge reverse() const;

   private:
      size_t m_from;
      size_t m_to;
      double m_weight;
   };
}

