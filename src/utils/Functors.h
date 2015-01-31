#pragma once
#include <utility>


namespace algorithm
{
   struct GetSecond
   {
      template<typename A, typename B>
      B const& operator() (std::pair<A, B> const& p) const { return p.second; }

      template<typename A, typename B>
      B const& operator() (std::pair<A const, B> const& p) const { return p.second; }
   };

   //--------------------------------------------------------------------------

   template<typename Predicate>
   struct LogicalNot
   {
      LogicalNot(Predicate pred) : m_pred(pred) {}
      Predicate m_pred;

      template<typename T>
      bool operator() (T t)
      {
         return !m_pred(t);
      }
   };

   template<typename Predicate>
   LogicalNot<Predicate> logicalNot(Predicate pred)
   {
      return LogicalNot<Predicate>(pred);
   }

   //--------------------------------------------------------------------------

   template<typename Less>
   struct ReverseCompare
   {
      ReverseCompare() : m_less() {}
      ReverseCompare(Less less) : m_less(less) {}
      Less m_less;

      template<typename T>
      bool operator()(T const& lhs, T const& rhs) const
      {
         return m_less(rhs, lhs);
      }
   };

   template<typename Less>
   ReverseCompare<Less> reverseComparison(Less less)
   {
      return ReverseCompare<Less>(less);
   }

   //--------------------------------------------------------------------------

   template<typename Projection>
   struct ComparingWithDefaultLess
   {
      ComparingWithDefaultLess(Projection proj) : m_proj(proj) {}
      Projection m_proj;

      template<typename T>
      bool operator()(T const& lhs, T const& rhs) const
      {
         return m_proj(lhs) < m_proj(rhs);
      }
   };

   template<typename Projection, typename Less>
   struct ComparingWith
   {
      ComparingWith(Projection proj, Less less) : m_proj(proj), m_less(less) {}
      Projection m_proj;
      Less m_less;

      template<typename T>
      bool operator()(T const& lhs, T const& rhs) const
      {
         return m_less(m_proj(lhs), m_proj(rhs));
      }
   };

   template<typename Projection>
   ComparingWithDefaultLess<Projection> comparingWith(Projection proj)
   {
      return ComparingWithDefaultLess<Projection>(proj);
   }

   template<typename Projection, typename Less>
   ComparingWith<Projection, Less> comparingWith(Projection proj, Less less)
   {
      return ComparingWith<Projection, Less>(proj, less);
   }
}
