#pragma once

#include <memory>
#include <string>
#include <unordered_map>


namespace algorithm
{
   class StringTrieSet
   {
   public:
      StringTrieSet();
      ~StringTrieSet() = default;

      bool insert(std::string const&);
      bool remove(std::string const&);
      bool search(std::string const&) const;
      size_t size() const;

   private:
      using string_it = std::string::const_iterator;
      using subtrie_t = std::unique_ptr<StringTrieSet>;
      using subtrie_map = std::unordered_map<char, subtrie_t>;

      bool insert(string_it start, string_it end);
      bool remove(string_it start, string_it end);
      bool search(string_it start, string_it end) const;

   private:
      size_t m_count;
      bool m_isValue;
      subtrie_map m_subTries;
   };
}
