#pragma once

#include "Utils.h"
#include <vector>


namespace algorithm
{
   template<typename Key, typename Less>
   class MaxPriorityQueue
   {
   public:
      template<typename Iter>
      MaxPriorityQueue(Less less, Iter first, Iter last);
      explicit MaxPriorityQueue(Less less);

      void add(Key k)
      {
         m_keys.push_back(k);
         swim(size() - 1);
      }

      Key const& top() const
      {
         return m_keys.at(0);
      }

      void pop()
      {
         swap(0, size() - 1);
         m_keys.pop_back();
         sink(0);
      }

      bool empty() const
      {
         return m_keys.empty();
      }

      size_t size() const
      {
         return m_keys.size();
      }

   private:
      void   swim       (size_t k); //Bottom-up key re-ordering
      void   sink       (size_t k); //Top-down key re-ordering
      size_t maxChild   (size_t k) const;
      bool   less       (size_t lhs, size_t rhs) const;
      void   swap       (size_t lhs, size_t rhs);

   private:
      size_t father     (size_t c) const { return (c + 1) / 2 - 1; }
      size_t fstChild   (size_t f) const { return (f + 1) * 2 - 1; }
      size_t sndChild   (size_t f) const { return (f + 1) * 2; }
      bool   hasFather  (size_t c) const { return father(c) > 0; }
      bool   hasChild   (size_t f) const { return fstChild(f) < size(); }
      bool   hasSndChild(size_t f) const { return sndChild(f) < size(); }

   private:
      Less m_less;
      std::vector<Key> m_keys;
   };

   //--------------------------------------------------------------------------

   template<typename Key, typename Less>
   using MinPriorityQueue = MaxPriorityQueue<Key, ReverseCompare<Less>>;
}

#include "PriorityQueue.inl.h"
