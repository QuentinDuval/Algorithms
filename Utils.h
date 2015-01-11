#pragma once

#include <algorithm>
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

   template<typename T>
   std::string toString(T const& t)
   {
      std::ostringstream os;
      os << t;
      return os.str();
   }
}
