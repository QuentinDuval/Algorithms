#pragma once

#include "utils/Functors.h"

#include <vector>
#include <utility>


namespace algorithm
{
   struct EmptyQueueException : public std::logic_error
   {
      EmptyQueueException() : std::logic_error("Priority queue is empty") {}
   };

   template<typename Key, typename Less = std::less<Key>>
   class MaxPriorityQueue
   {
   public:
      template<typename Iter>
      MaxPriorityQueue(Less less, Iter first, Iter last);
      explicit MaxPriorityQueue(Less less);
      MaxPriorityQueue();

      void add(Key k)
      {
         m_keys.push_back(k);
         swim(size() - 1);
      }

      Key const& top() const
      {
         if (empty()) throw EmptyQueueException();
         return m_keys.at(0);
      }

      void pop()
      {
         if (empty()) throw EmptyQueueException();
         swap(0, size() - 1);
         m_keys.pop_back();
         sink(0);
      }

      Key removeTop()
      {
         Key k = top();
         pop();
         return k;
      }

      bool   empty() const { return m_keys.empty(); }
      size_t size()  const { return m_keys.size(); }

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
      bool   hasFather  (size_t c) const { return c > 0; }
      bool   hasChild   (size_t f) const { return fstChild(f) < size(); }
      bool   hasSndChild(size_t f) const { return sndChild(f) < size(); }

   private:
      Less m_less;
      std::vector<Key> m_keys;
   };

   //--------------------------------------------------------------------------

   template<typename Key, typename Less = std::less<Key>>
   using MinPriorityQueue = MaxPriorityQueue<Key, utils::ReverseCompare<Less>>;

   //--------------------------------------------------------------------------

   template<typename T, typename Priority, typename Less = std::less<Priority>>
   class MaxPriorityIndexedQueue
   {
   public:
      MaxPriorityIndexedQueue() : m_impl(utils::comparingWith(utils::GetSecond(), Less())) {}
      explicit MaxPriorityIndexedQueue(Less less) : m_impl(utils::comparingWith(utils::GetSecond(), less)) {}

      void add(T k, Priority p)
      {
         m_impl.add(std::make_pair(std::move(k), std::move(p)));
      }

      T const& top() const    { return m_impl.top().first; }
      void     pop()          { return m_impl.pop(); }
      T        removeTop()    { return m_impl.removeTop().first; }
      bool     empty() const  { return m_impl.empty(); }
      size_t   size() const   { return m_impl.size(); }

   private:
      MaxPriorityQueue<std::pair<T, Priority>, utils::ComparingWith<utils::GetSecond, Less>> m_impl;
   };

   template<typename T, typename Priority, typename Less = std::less<Priority>>
   using MinPriorityIndexedQueue = MaxPriorityIndexedQueue<T, Priority, utils::ReverseCompare<Less>>;
}

#include "PriorityQueue.inl.h"
