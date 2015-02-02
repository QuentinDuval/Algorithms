#pragma once

#include <memory>
#include <string>
#include <vector>


namespace algorithm
{
   class StringTrie
   {
   public:
      StringTrie();
      ~StringTrie() = default;

      bool insert(std::string const&);
      bool remove(std::string const&);
      bool search(std::string const&) const;
      size_t size() const;

   private:
      using string_it = std::string::const_iterator;
      using subtrie_t = std::unique_ptr<StringTrie>;
      using subtrie_vector = std::vector<subtrie_t>;

      size_t toIndex(string_it) const;
      bool insert(string_it start, string_it end);
      bool remove(string_it start, string_it end);
      bool search(string_it start, string_it end) const;

   private:
      size_t m_count;
      std::vector<bool> m_contains;
      subtrie_vector m_subTries;
   };
}
