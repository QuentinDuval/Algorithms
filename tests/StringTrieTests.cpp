#include "StringTrieTests.h"

#include "StringTrie.h"
#include "utils/Algorithms.h"
#include "utils/Timer.h"

#include <assert.h>
#include <iostream>


namespace algorithm
{
   void stringTrieTests()
   {
      StringTrie t;
      auto inputs = { "alpha", "beta", "alpha-numeric" };
      
      for (auto& s : inputs) assert(true == t.insert(s));
      for (auto& s : inputs) assert(true == t.search(s));
      for (auto& s : inputs) assert(false == t.insert(s));
      assert(3 == t.size());

      assert(false == t.search("a"));
      assert(false == t.search("alpha-"));

      for (auto& s : inputs) assert(true == t.remove(s));
      assert(0 == t.size());

      for (auto& s : inputs) assert(true == t.insert(s));
      for (auto& s : inputs) assert(true == t.search(s));
   }

   void stringTriePerfTests()
   {
      size_t dim = 100000;
      std::vector<std::string> strings(dim);
      for (size_t i = 0; i < dim; ++i)
      {
         for (size_t j = i; j != 0; j /= UCHAR_MAX)
            strings[i] += ('a' + j - 1);
      }
      utils::shuffle(strings);

      std::cout << std::endl << "[String trie timings]" << std::endl;
      StringTrie t;

      std::cout << "* Inserts" << std::endl;
      utils::showTime(std::cout, [&]() { for (auto& s : strings) t.insert(s); });

      std::cout << "* Searches" << std::endl;
      utils::showTime(std::cout, [&]() { for (auto& s : strings) t.search(s); });

      std::cout << "* Removals" << std::endl;
      utils::showTime(std::cout, [&]() { for (auto& s : strings) t.remove(s); });
   }
}
