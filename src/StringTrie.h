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


   template<typename T>
   class StringTrie
   {
   public:
      using Key = std::string;
      using KeyIt = Key::const_iterator;

   public:
      StringTrie();
      ~StringTrie() = default;

      bool insert(Key const& k, T const& val)
      {
         return insert(begin(k), end(k), val);
      }

      bool insert(KeyIt start, KeyIt end, T const&);

      bool remove(Key const& k)
      {
         return remove(begin(k), end(k));
      }

      Key longestPrefixOf(Key const& k) const
      {
         return longestPrefixOf(begin(k), end(k));
      }

      Key longestPrefixOf(KeyIt start, KeyIt end) const
      {
         Key acc, longest;
         longestPrefixOf(start, end, acc, longest);
         return longest;
      }

      T const* search(Key const& k) const
      {
         return search(begin(k), end(k));
      }
      
      size_t size() const
      {
         return m_count;
      }

   private:
      using SubTrie = std::unique_ptr<StringTrie>;
      using SubTrieMap = std::unordered_map<char, SubTrie>;

      void longestPrefixOf(KeyIt start, KeyIt end, Key& acc, Key& ret) const;
      bool remove(KeyIt start, KeyIt end);
      T const* search(KeyIt start, KeyIt end) const;

   private:
      size_t m_count;
      std::pair<bool, T> m_value;
      SubTrieMap m_subTries;
   };
}

#include "StringTrie.inl.h"
