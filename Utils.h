#pragma once

#include <algorithm>
#include <assert.h>
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

   template<typename T>
   std::string toString(T const& t)
   {
      std::ostringstream os;
      os << t;
      return os.str();
   }
}
