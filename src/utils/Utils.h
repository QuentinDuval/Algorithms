#pragma once

#include <iterator>
#include <sstream>
#include <string>


namespace algorithm
{
   template<typename Iterator>
   class Range
   {
   public:
      Range(Iterator first, Iterator last)
         : m_first(first), m_last(last) {}

      Iterator begin()  const { return m_first; }
      Iterator end()    const { return m_last; }

      size_t   size()   const { return std::distance(m_first, m_last); }
      bool     empty()  const { return m_first == m_last; }
      void     pop()          { ++m_first; }

   private:
      Iterator m_first;
      Iterator m_last;
   };

   template<typename Iterator>
   Range<std::reverse_iterator<Iterator>> reverseRange(Range<Iterator> const& r)
   {
      std::reverse_iterator<Iterator> rbegin(r.end());
      std::reverse_iterator<Iterator> rend(r.begin());
      return Range<std::reverse_iterator<Iterator>>(rbegin, rend);
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
