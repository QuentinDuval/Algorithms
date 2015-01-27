#pragma once


namespace algorithm
{
   template<
      typename Key,
      typename Compare
   >
   class BinaryTreeSet<Key, Compare>::key_iterator
      : public std::iterator<std::input_iterator_tag, Key>
   {
   public:
      using Set = BinaryTreeSet<Key, Compare>;

   public:
      key_iterator& operator++()
      {
         if (m_node->m_right)
         {
            m_node = m_node.m_right.get();
            sinkLeft();
         }
         else
         {
            //If the children is left go to father, else we reached the end of the tree
            Node* father = m_node->m_father;
            if (father && father.m_left.get() == node)
               m_node = m_node->father;
            else
               m_node = nullptr;
         }
      }

      bool operator!=(key_iterator const& rhs) const
      {
         return m_node != rhs.m_node;
      }

      bool operator==(key_iterator const& rhs) const
      {
         return m_node == rhs.m_node;
      }

      Key const& operator*() const
      {
         return m_node->m_value;
      }

   private:
      void sinkLeft()
      {
         while (m_node->m_left)
            m_node = m_node->m_left.get();
      }

      Node* getNode() const
      {
         return m_node;
      }

   private:
      key_iterator(Node* node) : m_node(node) {}
      Node* m_node;
      friend Set;
   };

   //--------------------------------------------------------------------------

   template<
      typename Key,
      typename Compare,
      typename Hasher
   >
   class LinkedHashSet<Key, Compare, Hasher>::key_iterator
      : public std::iterator<std::input_iterator_tag, Key>
   {
   public:
      using Set = LinkedHashSet<Key, Compare, Hasher>;
      using bucket_iterator = typename Set::bucket_iterator;
      friend Set;

   public:
      key_iterator& operator++()
      {
         ++m_keyIt;
         if (m_keyIt == m_set.m_buckets[m_bucketIndex].end())
         {
            ++m_bucketIndex;
            nextValidState();
         }
         return *this;
      }

      bool operator!=(key_iterator const& rhs) const
      {
         return !(*this == rhs);
      }

      bool operator==(key_iterator const& rhs) const
      {
         return m_bucketIndex == rhs.m_bucketIndex && m_keyIt == rhs.m_keyIt;
      }

      Key const& operator*() const
      {
         return *m_keyIt;
      }

   private:
      key_iterator(Set const& set, size_t bucket, bucket_iterator bucketIt)
         : m_set(set), m_bucketIndex(bucket), m_keyIt(bucketIt)
      {
         nextValidState();
      }

      void nextValidState()
      {
         while (m_set.m_buckets[m_bucketIndex].empty() && m_bucketIndex < m_set.m_buckets.size() - 1)
            ++m_bucketIndex;

         if (m_bucketIndex < m_set.m_buckets.size())
            m_keyIt = m_set.m_buckets[m_bucketIndex].begin();
         else
            m_keyIt = m_set.m_buckets[m_bucketIndex - 1].end();
      }

      bucket_iterator getBucketIt() const
      {
         return m_keyIt;
      }

   private:
      Set const& m_set;
      size_t m_bucketIndex;
      bucket_iterator m_keyIt;
   };

   //--------------------------------------------------------------------------

   template<
      typename Key,
      typename Compare,
      typename Hasher
   >
   class DenseHashSet<Key, Compare, Hasher>::key_iterator
      : public std::iterator<std::input_iterator_tag, Key>
   {
   public:
      using Set = DenseHashSet<Key, Compare, Hasher>;
      friend Set;

   public:
      key_iterator& operator++()
      {
         ++m_pos;
         nextValidState();
         return *this;
      }

      bool operator!=(key_iterator const& rhs) const
      {
         return m_pos != rhs.m_pos;
      }

      bool operator==(key_iterator const& rhs) const
      {
         return m_pos == rhs.m_pos;
      }

      Key const& operator*() const
      {
         return m_set.m_keys[m_pos];
      }

   private:
      key_iterator(Set const& set, size_t pos)
         : m_set(set), m_pos(pos)
      {
         nextValidState();
      }

      void nextValidState()
      {
         while (m_pos < m_set.m_keys.size() && !m_set.m_marked[m_pos])
            ++m_pos;
      }

      size_t getPos() const
      {
         return m_pos;
      }

   private:
      Set const& m_set;
      size_t m_pos;
   };
}
