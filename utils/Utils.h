#pragma once

#include <iterator>
#include <sstream>
#include <string>


namespace algorithm
{
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
