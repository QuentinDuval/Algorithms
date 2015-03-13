#include "StringTrie.h"


namespace algorithm
{
   StringTrie::StringTrie()
      : m_isValue(false)
      , m_subTries()
   {}

   bool StringTrie::insert(std::string const& s)
   {
      if (s.empty()) return false;
      return insert(begin(s), end(s));
   }

   bool StringTrie::remove(std::string const& s)
   {
      if (s.empty()) return false;
      return remove(begin(s), end(s));
   }

   bool StringTrie::search(std::string const& s) const
   {
      if (s.empty()) return false;
      return search(begin(s), end(s));
   }

   size_t StringTrie::size() const
   {
      return m_count;
   }

   //--------------------------------------------------------------------------

   bool StringTrie::insert(string_it start, string_it end)
   {
      auto next = start + 1;
      if (next == end)
      {
         if (m_isValue)
            return false;

         m_isValue = true;
         ++m_count;
         return true;
      }

      auto& subTrie = m_subTries[*start];
      if (!subTrie)
         subTrie.reset(new StringTrie);

      if (!subTrie->insert(next, end))
         return false;

      ++m_count;
      return true;
   }

   bool StringTrie::remove(string_it start, string_it end)
   {
      auto next = start + 1;
      if (next == end)
      {
         if (!m_isValue)
            return false;

         m_isValue = false;
         --m_count;
         return true;
      }

      auto it = m_subTries.find(*start);
      if (it == m_subTries.end())
         return false;

      auto& subTrie = it->second;
      if (!subTrie->remove(next, end))
         return false;

      if (subTrie->m_count == 0)
         m_subTries.erase(it);

      --m_count;
      return true;
   }

   bool StringTrie::search(string_it start, string_it end) const
   {
      auto next = start + 1;
      if (next == end)
         return m_isValue;

      auto it = m_subTries.find(*start);
      if (it == m_subTries.end())
         return false;

      return it->second->search(next, end);
   }
}
