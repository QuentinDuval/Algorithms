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
         , m_load_factor(0.5), m_count(0)
         , m_marked(10, false), m_keys(10)
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
         for (size_t i = start; i != start - 1; i = nextIndex(i))
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

      void erase(key_iterator it)
      {
         size_t start = it.getPos();
         m_marked[start] = false;

         key_container keys;
         size_t end = emptySpotFrom(start + 1);
         for (size_t i = start + 1; i != end; i = nextIndex(i))
         {
            keys.push_back(m_keys[i]);
            m_marked[i] = false;
         }

         for (auto& k : keys)
            insert_(k);
         --m_count;
      }

   private:
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

      void insert_(Key const& k)
      {
         size_t i = emptySpotFrom(startIndex(k));
         m_marked[i] = true;
         m_keys[i] = k;
      }

      void loadFactorCheck()
      {
         size_t upperBound = static_cast<size_t>(m_keys.size() * m_load_factor);
         if (m_count > upperBound)
            resize(2 * m_keys.size());
      }

      size_t emptySpotFrom(size_t start) const
      {
         for (size_t i = start; i != start - 1; i = nextIndex(i))
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
         return i + 1 % m_keys.size();
      }

   private:
      Compare m_comp;
      Hasher m_hash;

      double m_load_factor;
      size_t m_count;

      key_marking m_marked;
      key_container m_keys;
   };
}

#include "Set.inl.h"
