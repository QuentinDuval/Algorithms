#pragma once

#include <functional>
#include <vector>


namespace algorithm
{
   //template<typename T>
   //class RedBlackTreeSet
   //{
   //public:


   //private:

   //};

   //--------------------------------------------------------------------------

   //template<typename T>
   //class LinkedHashSet
   //{
   //public:


   //private:


   //};

   //--------------------------------------------------------------------------

   template<
      typename Key,
      typename Compare = std::equal_to<Key>,
      typename Hasher = std::hash<Key>
   >
   class DenseHashSet
   {
   public:
      using key_marking = std::vector<bool>;
      using key_container = std::vector<Key>;
      class key_iterator;

   public:
      DenseHashSet() : DenseHashSet(Compare(), Hasher()) {}
      ~DenseHashSet() = default;

      DenseHashSet(Compare comp, Hasher hash)
         : m_comp(comp), m_hash(hash)
         , m_count(0), m_marked(10, false), m_keys(10)
      {}

      key_iterator begin() const
      {
         return key_iterator(*this, 0);
      }

      key_iterator end() const
      {
         return key_iterator(*this, m_keys.size());
      }

      size_t size() const
      {
         return std::distance(begin(), end());
      }

      key_iterator find(Key const& k) const
      {
         const size_t start = startIndex(k);
         for (size_t i = start; i != prevIndex(start); i = nextIndex(i))
         {
            if (!m_marked[i])
               return end();

            if (m_comp(k, m_keys[i]))
               return key_iterator(*this, i);
         }
         return end();
      }

      bool contains(Key const& k) const
      {
         return find(k) != end();
      }

      bool insert(Key const& k)
      {
         if (contains(k))
            return false;

         insert_(k);
         ++m_count;
         loadFactorCheck();
         return true;
      }

      /** Invalidates the iterators because of load factors */
      void erase(key_iterator it)
      {
         key_container toReinsert;
         erase_(it, toReinsert);
         for (auto& k : toReinsert)
            insert_(k);

         loadFactorCheck();
      }

      /** Invalidates the iterators because of load factors */
      void erase(key_iterator first, key_iterator last)
      {
         //Do it now, as iterators are invalidated afterwards
         m_count -= std::distance(first, last);

         key_container toReinsert;
         for (; first != last; ++first)
            erase_(first, toReinsert);

         for (auto& k : toReinsert)
            insert_(k);

         loadFactorCheck();
      }

   private:
      void insert_(Key const& k)
      {
         size_t i = emptySpotFrom(startIndex(k));
         m_marked[i] = true;
         m_keys[i] = k;
      }

      void erase_(key_iterator it, key_container& toReinsert)
      {
         size_t start = it.getPos();
         m_marked[start] = false;
         --m_count;

         key_container keys;
         start = nextIndex(start);
         size_t end = emptySpotFrom(start);
         for (size_t i = start; i != end; i = nextIndex(i))
         {
            keys.push_back(m_keys[i]);
            m_marked[i] = false;
         }
      }

      void loadFactorCheck()
      {
         size_t upperBound = m_keys.size() / 2;
         if (m_count > upperBound)
            resize(2 * m_keys.size());
         else if (m_count < upperBound / 4)
            resize(m_keys.size() / 2);
      }

      void resize(size_t size)
      {
         key_container keys;
         keys.reserve(m_keys.size());
         for (size_t i = 0; i < m_keys.size(); ++i)
         {
            if (m_marked[i])
               keys.push_back(m_keys[i]);
         }

         m_marked = key_marking(size, false);
         m_keys.resize(size);
         for (auto& k : keys)
            insert_(k);
      }

      size_t emptySpotFrom(size_t start) const
      {
         for (size_t i = start; i != prevIndex(start); i = nextIndex(i))
            if (!m_marked[i])
               return i;
         return 0; //Not reachable by construction
      }

      size_t startIndex(Key const& k) const
      {
         return m_hash(k) % m_keys.size();
      }

      size_t nextIndex(size_t i) const
      {
         return (i + 1) % m_keys.size();
      }

      size_t prevIndex(size_t i) const
      {
         if (0 < i) return i - 1;
         else return m_keys.size() - 1;
      }

   private:
      Compare m_comp;
      Hasher m_hash;
      size_t m_count;

      key_marking m_marked;
      key_container m_keys;
   };
}

#include "Set.inl.h"
