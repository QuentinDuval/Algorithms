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
      : public Edge
   {
   public:
      WeightedEdge();
      WeightedEdge(size_t from, size_t to, double weight);
      ~WeightedEdge() = default;

      double weight() const;
      WeightedEdge reverse() const;

   private:
      double m_weight;
   };

   inline std::ostream& operator<< (std::ostream& os, WeightedEdge const& e)
   {
      return os << e.from() << " " << e.to() << " " << e.weight();
   }

   //--------------------------------------------------------------------------

   class CapacityEdge
      : public Edge
   {
   public:
      CapacityEdge();
      CapacityEdge(size_t from, size_t to, double capacity);
      ~CapacityEdge() = default;

      double flow() const;
      double capacity() const;
      CapacityEdge reverse() const;

   private:
      double m_flow;
      double m_capacity;
   };

   inline std::ostream& operator<< (std::ostream& os, CapacityEdge const& e)
   {
      return os << e.from() << " " << e.to() << " " << e.capacity();
   }
}

