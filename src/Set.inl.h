#pragma once


namespace algorithm
{
   template<
      typename Key,
      typename Compare,
      typename Hasher
   >
   class DenseHashSet<Key, Compare, Hasher>::key_iterator
      : public std::iterator<std::input_iterator_tag, size_t>
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
