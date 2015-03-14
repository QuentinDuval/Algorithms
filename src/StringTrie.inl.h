#pragma once

namespace algorithm
{
   template<typename T>
   StringTrie<T>::StringTrie()
      : m_count(0)
      , m_value(false, T())
      , m_subTries()
   {}

   template<typename T>
   bool StringTrie<T>::insert(KeyIt start, KeyIt end, T const& val)
   {
      if (start == end)
      {
         if (m_value.first)
            return false;

         m_value = std::make_pair(true, val);
         ++m_count;
         return true;
      }

      auto& subTrie = m_subTries[*start];
      if (!subTrie)
         subTrie.reset(new StringTrie<T>);

      if (!subTrie->insert(start + 1, end, val))
         return false;

      ++m_count;
      return true;
   }

   template<typename T>
   void StringTrie<T>::longestPrefixOf(KeyIt start, KeyIt end, Key& acc, Key& longest) const
   {
      if (start == end)
         return;

      if (m_value.first)
         longest = acc;

      auto it = m_subTries.find(*start);
      if (it != m_subTries.end())
      {
         acc += *start;
         it->second->longestPrefixOf(start + 1, end, acc, longest);
      }
   }

   template<typename T>
   bool StringTrie<T>::remove(KeyIt start, KeyIt end)
   {
      if (start == end)
      {
         if (!m_value.first)
            return false;

         m_value.first = false;
         --m_count;
         return true;
      }

      auto it = m_subTries.find(*start);
      if (it == m_subTries.end())
         return false;

      auto& subTrie = it->second;
      if (!subTrie->remove(start + 1, end))
         return false;

      if (subTrie->m_count == 0)
         m_subTries.erase(it);

      --m_count;
      return true;
   }

   template<typename T>
   T const* StringTrie<T>::search(KeyIt start, KeyIt end) const
   {
      if (start == end)
         return m_value.first ? &m_value.second : nullptr;

      auto it = m_subTries.find(*start);
      if (it == m_subTries.end())
         return false;

      return it->second->search(start + 1, end);
   }
}
