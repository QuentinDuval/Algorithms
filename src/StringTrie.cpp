#include "StringTrie.h"


namespace algorithm
{
   StringTrie::StringTrie()
      : m_contains(UCHAR_MAX + 1, false)
      , m_subTries(UCHAR_MAX + 1)
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

   size_t StringTrie::toIndex(string_it it) const
   {
      return *it - CHAR_MIN;
   }

   bool StringTrie::insert(string_it start, string_it end)
   {
      auto next = start + 1;
      if (next == end)
      {
         if (m_contains[toIndex(start)])
            return false;

         m_contains[toIndex(start)] = true;
         ++m_count;
         return true;
      }
      
      auto& subTrie = m_subTries[toIndex(start)];
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
         if (!m_contains[toIndex(start)])
            return false;

         m_contains[toIndex(start)] = false;
         --m_count;
         return true;
      }

      auto& subTrie = m_subTries[toIndex(start)];
      if (!subTrie)
         return false;

      if (!subTrie->remove(next, end))
         return false;

      if (subTrie->m_count == 0)
         subTrie.reset();

      --m_count;
      return true;
   }

   bool StringTrie::search(string_it start, string_it end) const
   {
      auto next = start + 1;
      if (next == end)
         return m_contains[toIndex(start)];

      auto& subTrie = m_subTries[toIndex(start)];
      return subTrie ? subTrie->search(next, end) : false;
   }
}
