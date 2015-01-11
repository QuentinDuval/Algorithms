#pragma once

#include <algorithm>
#include <assert.h>
#include <iterator>
#include <random>
#include <sstream>
#include <string>


namespace algorithm
{
   template<typename FwdIter, typename ValueType, typename NextFct>
   void generate(FwdIter first, FwdIter last, ValueType const& val, NextFct next)
   {
      for (auto nextVal = val; first != last; ++first)
      {
         *first = nextVal;
         nextVal = next(nextVal);
      }
   }

   template<typename Container, typename ValueType, typename NextFct>
   void generate(Container& cont, ValueType const& val, NextFct next)
   {
      generate(begin(cont), end(cont), val, next);
   }

   template<typename Container, typename Predicate>
   typename Container::const_iterator findIf(Container const& cont, Predicate pred)
   {
      return std::find_if(begin(cont), end(cont), pred);
   }

   template<typename Container, typename Lesser>
   typename Container::const_iterator minBy(Container const& cont, Lesser less)
   {
      return std::min_element(begin(cont), end(cont), less);
   }

   template<typename Iterator>
   void shuffle(Iterator first, Iterator last)
   {
      std::random_device rd;
      std::mt19937 g(rd());
      std::shuffle(first, last, g);
   }

   template<typename Container>
   void shuffle(Container& cont)
   {
      shuffle(begin(cont), end(cont));
   }

   //--------------------------------------------------------------------------

   template<typename Iterator>
   void advance(Iterator& current, Iterator end,
      typename std::iterator_traits<Iterator>::difference_type n = 1)
   {
      for (int i = 0; i < n && current != end; ++i)
         ++current;
   }

   template<typename Iterator>
   Iterator next(Iterator current, Iterator end,
      typename std::iterator_traits<Iterator>::difference_type n = 1)
   {
      auto ret = current;
      advance(ret, end, n);
      return ret;
   }

   //--------------------------------------------------------------------------

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

   template<typename Projection, typename Less>
   ComparingWith<Projection, Less> comparingWith(Projection proj, Less less)
   {
      return ComparingWith<Projection, Less>(proj, less);
   }

   //--------------------------------------------------------------------------

   template<typename T>
   std::string toString(T const& t)
   {
      std::ostringstream os;
      os << t;
      return os.str();
   }
}
