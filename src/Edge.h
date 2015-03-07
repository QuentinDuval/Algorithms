#pragma once
#include <ostream>


namespace algorithm
{
   class Edge
   {
   public:
      Edge();
      Edge(size_t from, size_t to);
      size_t from() const;
      size_t to() const;
      Edge reverse() const;

   private:
      size_t m_from;
      size_t m_to;
   };

   inline std::ostream& operator<< (std::ostream& os, Edge const& e)
   {
      return os << e.from() << " " << e.to();
   }

   //--------------------------------------------------------------------------

   class WeightedEdge
   {
   public:
      WeightedEdge();
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

   inline std::ostream& operator<< (std::ostream& os, WeightedEdge const& e)
   {
      return os << e.from() << " " << e.to() << " " << e.weight();
   }
}

