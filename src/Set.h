#pragma once

#include "utils/Algorithms.h"

#include <functional>
#include <memory>
#include <list>
#include <vector>


namespace algorithm
{
   template<
      typename Key,
      typename Compare = std::less<Key>
   >
   class BinaryTreeSet
   {
   private:
      struct Node
      {
         Node(Key const& k) : Node(nullptr, k) {}
         Node(Node* father, Key const& k)
            : m_father(father)
            , m_value(k)
            , m_count(1)
         {}

         Key m_value;
         size_t m_count;
         Node* m_father;
         std::unique_ptr<Node> m_left;
         std::unique_ptr<Node> m_right;
      };

      class key_iterator;

   public:
      BinaryTreeSet() : BinaryTreeSet(Compare()) {}
      BinaryTreeSet(Compare less) : m_less(less), m_root() {}

      key_iterator begin() const
      {
         key_iterator b(m_root.get());
         b.sinkLeft();
         return b;
      }

      key_iterator end() const
      {
         return key_iterator(nullptr);
      }

      key_iterator find(Key const& key) const
      {
         Node* node = m_root.get();
         while (node)
         {
            if (m_less(key, node->m_value))
               node = node->m_left.get();
            else if (m_less(node->m_value, key))
               node = node->m_right.get();
            else
               return key_iterator(node);
         }
         return end();
      }

      bool contains(Key const& key) const
      {
         return end() != find(key);
      }

      bool insert(Key const& key)
      {
         if (!m_root)
         {
            m_root = std::make_unique<Node>(key);
            return true;
         }

         Node* node = m_root.get();
         while (node)
         {
            if (m_less(key, node->m_value))
            {
               Node* next = node->m_left.get();
               if (!next)
               {
                  node->m_left = std::make_unique<Node>(key);
                  incrementCount_(node);
                  return true;
               }
               node = next;
            }
            else if (m_less(node->m_value, key))
            {
               Node* next = node->m_right.get();
               if (!next)
               {
                  node->m_right = std::make_unique<Node>(key);
                  incrementCount_(node);
                  return true;
               }
               node = next;
            }
            else
            {
               return false;
            }
         }
         return false;
      }

      void erase(key_iterator it)
      {
         if (it == end())
            return;

         Node* node = it.getNode();
         Node* father = node->m_father;

         //TODO - If not children, just erase
         //TODO - If one children, just bring it in place
         //TODO - If two children, go right, sink all way down left, swap these nodes, then delete

         //TODO - Wrong: how to handle the children?
         //if (father->m_left.get() == node)
         //   father->m_left.reset();
         //else if (father->m_right.get() == node)
         //   father->m_right.reset();

         incrementCount_(father, -1);
      }

      size_t size() const
      {
         return m_root ? m_root->m_count : 0;
      }

   private:
      void incrementCount_(Node* node, size_t incr = 1)
      {
         while (node)
         {
            node->m_count += incr;
            node = node->m_father;
         }
      }

   private:
      Compare m_less;
      std::unique_ptr<Node> m_root;
   };

   //--------------------------------------------------------------------------

   //TODO - Red black tree

   //--------------------------------------------------------------------------

   template<
      typename Key,
      typename Compare = std::equal_to<Key>,
      typename Hasher = std::hash<Key>
   >
   class LinkedHashSet
   {
   public:
      using key_list = std::list<Key>;
      using bucket_iterator = typename key_list::const_iterator;
      using buckets = std::vector<key_list>;
      class key_iterator;

   public:
      LinkedHashSet() : LinkedHashSet(Compare(), Hasher()) {}
      LinkedHashSet(Compare comp, Hasher hash) : m_comp(comp), m_hash(hash), m_count(0), m_buckets(10){}
      ~LinkedHashSet() = default;

      key_iterator find(Key const& k) const
      {
         size_t bucketId = bucketIndex(k);
         auto& bucket = m_buckets[bucketId];
         auto it = findIf(bucket, [&](Key const& key) { return m_comp(k, key); });
         if (it == bucket.end())
            return end();

         return key_iterator(*this, bucketId, it);
      }

      bool contains(Key const& k) const
      {
         return find(k) != end();
      }

      bool insert(Key const& k)
      {
         if (!insert_(k))
            return false;

         ++m_count;
         loadFactorCheck();
         return true;
      }

      void erase(key_iterator it)
      {
         erase_(it.getBucketIt());
         --m_count;
         loadFactorCheck();
      }

      void erase(key_iterator first, key_iterator last)
      {
         m_count -= std::distance(first, last);
         for (; first != last; first.nextValidState())
            erase_(first.getBucketIt());
         loadFactorCheck();
      }

      key_iterator begin() const
      {
         return key_iterator(*this, 0, m_buckets[0].begin());
      }

      key_iterator end() const
      {
         size_t e = m_buckets.size() - 1;
         return key_iterator(*this, e, m_buckets[e].end());
      }

      size_t size() const
      {
         return m_count;
      }

   private:
      size_t bucketIndex(Key const& k) const
      {
         return m_hash(k) % m_buckets.size();
      }

      bool insert_(Key const& k)
      {
         auto& bucket = m_buckets[bucketIndex(k)];
         auto it = findIf(bucket, [&](Key const& key) { return m_comp(k, key); });
         if (it != bucket.end())
            return false;

         bucket.push_back(k);
         return true;
      }

      void erase_(bucket_iterator it)
      {
         auto& k = *it;
         auto& bucket = m_buckets[bucketIndex(k)];
         bucket.erase(it);
      }

      void loadFactorCheck()
      {
         size_t upperBound = m_buckets.size() / 2;
         if (m_count > upperBound)
            resize(2 * m_buckets.size());
         else if (m_count < upperBound / 4)
            resize(m_buckets.size() / 2);
      }

      void resize(size_t size)
      {
         //Extracting the buckets and just move them would not work
         std::vector<Key> keys;
         keys.reserve(m_count);
         for (auto& bucket : m_buckets)
            std::copy(bucket.begin(), bucket.end(), std::back_inserter(keys));

         m_buckets = buckets(size); //TODO - Make this more efficient
         for (auto& k : keys)
            insert_(k);
      }

   private:
      Compare m_comp;
      Hasher m_hash;
      size_t m_count;
      buckets m_buckets;
   };


   //--------------------------------------------------------------------------
   // Dense Hash Set
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

         --m_count;
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
         if (start == m_keys.size())
            return;

         m_marked[start] = false;

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
