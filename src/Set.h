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
      using key_iterator = typename key_container::const_iterator;

   public:
      DenseHashSet() : DenseHashSet(Compare(), Hasher()) {}
      ~DenseHashSet() = default;

      DenseHashSet(Compare comp, Hasher hash)
         : m_comp(comp), m_hash(hash)
         , m_load_factor(0.5), m_count(0)
         , m_marked(10, false), m_keys(10)
      {}


      bool insert(Key const& k)
      {
         if (contains(k))
            return false;

         const size_t start = startIndex(k);
         size_t i = start;
         while (i != start - 1)
         {
            if (!m_marked[i])
               break;
            i = (i + 1) % m_keys.size();
         }

         //Ensure by construction that there will be a spot
         m_marked[i] = true;
         m_keys[i] = k;
         ++m_count;

         //Check the load factor afterwards
         if (m_count > size() * m_load_factor)
            resize(2 * size());
         return true;
      }

      key_iterator begin() const
      {
         return m_keys.begin();
      }

      key_iterator end() const
      {
         return m_keys.end();
      }

      size_t size() const
      {
         return m_keys.size();
      }

      key_iterator find(Key const& k) const
      {
         const size_t start = startIndex(k);
         for (size_t i = start; i != start - 1; i = (i + 1) % m_keys.size())
         {
            //End of range in which the key could be
            if (!m_marked[i])
               return end();

            if (m_comp(k, m_keys[i]))
               return begin() + i;
         }
         return end();
      }

      bool contains(Key const& k) const
      {
         return find(k) != end();
      }

      void erase(key_iterator it)
      {
         //TODO
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
            insert(k);
      }

      size_t startIndex(Key const& k) const
      {
         return m_hash(k) % m_keys.size();
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
