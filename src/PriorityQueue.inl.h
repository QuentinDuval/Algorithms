#pragma once
#include "PriorityQueue.h"


namespace algorithm
{
   template<typename Key, typename Less>
   MaxPriorityQueue<Key, Less>::MaxPriorityQueue()
      : m_less(), m_keys()
   {}

   template<typename Key, typename Less>
   MaxPriorityQueue<Key, Less>::MaxPriorityQueue(Less less)
      : m_less(less), m_keys()
   {}

   template<typename Key, typename Less>
   template<typename Iter>
   MaxPriorityQueue<Key, Less>::MaxPriorityQueue(Less less, Iter first, Iter last)
      : m_less(less), m_keys(first, last)
   {
      size_t lastSubHeap = size() / 2;
      for (size_t k = 0; k <= lastSubHeap; ++k)
         sink(lastSubHeap - k);
   }

   template<typename Key, typename Less>
   void MaxPriorityQueue<Key, Less>::swim(size_t k)
   {
      while (hasFather(k))
      {
         size_t f = father(k);
         if (!less(f, k)) break;
         swap(f, k);
         k = f;
      }
   }

   template<typename Key, typename Less>
   void MaxPriorityQueue<Key, Less>::sink(size_t k)
   {
      while (hasChild(k))
      {
         int c = maxChild(k);
         if (!less(k, c)) break;
         swap(k, c);
         k = c;
      }
   }

   template<typename Key, typename Less>
   size_t MaxPriorityQueue<Key, Less>::maxChild(size_t k) const
   {
      size_t child = fstChild(k);
      if (hasSndChild(k) && less(child, sndChild(k)))
         return sndChild(k);
      return child;
   }

   template<typename Key, typename Less>
   bool MaxPriorityQueue<Key, Less>::less(size_t lhs, size_t rhs) const
   {
      return m_less(m_keys[lhs], m_keys[rhs]);
   }

   template<typename Key, typename Less>
   void MaxPriorityQueue<Key, Less>::swap(size_t lhs, size_t rhs)
   {
      std::swap(m_keys[lhs], m_keys[rhs]);
   }
}
