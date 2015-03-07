#include "SetTests.h"

#include "HashSet.h"
#include "Set.h"
#include "utils/Algorithms.h"
#include "utils/Timer.h"

#include <assert.h>
#include <iostream>
#include <set>
#include <string>
#include <unordered_set>


namespace algorithm
{
   template<typename Set>
   void stringSetTests()
   {
      Set stringSet;
      assert(true == stringSet.insert("a"));
      assert(true == stringSet.insert("b"));
      assert(false == stringSet.insert("b"));
      assert(true == stringSet.contains("a"));
      assert(true == stringSet.contains("b"));
      assert(2 == stringSet.size());
   }

   template<typename Set>
   void integerSetTests()
   {
      Set set;
      for (size_t i = 0; i < 30; ++i)
         set.insert(i);

      assert(30 == set.size());
      for (size_t i = 0; i < 30; ++i)
         assert(true == set.contains(i));

      auto it = set.find(0);
      set.erase(it);
      assert(false == set.contains(0));
      assert(29 == set.size());

      for (auto& k : set)
         assert(true == set.contains(k));

      for (size_t i = 0; i < 30; ++i)
         set.erase(set.find(i));
      //set.erase(set.begin(), set.end());
      assert(0 == set.size());
      for (size_t i = 0; i < 30; ++i)
         assert(false == set.contains(i));
   }

   static void binarySearchTreeTests()
   {
      BinaryTreeSet<std::string> stringSet;
      assert(true == stringSet.insert("a"));
      assert(true == stringSet.insert("b"));
      assert(false == stringSet.insert("b"));
      assert(true == stringSet.contains("a"));
      assert(true == stringSet.contains("b"));
      assert(2 == stringSet.size());

      BinaryTreeSet<size_t> set;
      std::vector<size_t> keys(30, 0);
      utils::generate(keys, 0, [](size_t i) { return i + 1; });

      std::vector<size_t> shuffledKeys(keys);
      utils::shuffle(shuffledKeys);
      for (auto k : shuffledKeys) set.insert(k);
      assert(true == equal(begin(set), end(set), std::begin(keys)));

      set.erase(set.find(0));
      set.erase(set.find(14));
      set.erase(set.find(29));
      assert(27 == set.size());

      set.erase(set.find(15), set.end());
      assert(13 == set.size());

      set.erase(set.begin(), set.end());
      assert(0 == set.size());
   }

   static void redBlackTreeTests()
   {
      RedBlackTreeSet<size_t> set;
      
      std::vector<size_t> keys(30, 0);
      utils::generate(keys, 0, [](size_t i) { return i + 1; });
      for (auto k : keys)
         set.insert(k);

      assert(30 == set.size());
      assert(true == equal(begin(set), end(set), std::begin(keys)));
   }

   static void linkedHashSetTests()
   {
      stringSetTests<LinkedHashSet<std::string>>();
      integerSetTests<LinkedHashSet<size_t>>();
   }

   static void denseHashSetTests()
   {
      stringSetTests<DenseHashSet<std::string>>();
      integerSetTests<DenseHashSet<size_t>>();
   }

   void setTests()
   {
      binarySearchTreeTests();
      redBlackTreeTests();
      linkedHashSetTests();
      denseHashSetTests();
   }

   //--------------------------------------------------------------------------

   template<typename Set>
   void integerSetPerfTests(size_t size)
   {
      Set set;

      std::vector<size_t> keys(size, 0);
      utils::generate(keys, 0, [](size_t i) { return i + 1; });
      utils::shuffle(keys);

      std::cout << std::endl << "* Inserts:" << std::endl;
      utils::showTime(std::cout, [&]{
         for (auto i : keys)
            set.insert(i);
      });

      std::cout << std::endl << "* Scan and search:" << std::endl;
      utils::showTime(std::cout, [&]{
         for (auto k : set)
            assert(set.end() != set.find(k));
      });

      std::cout << std::endl << "* Deletes:" << std::endl;
      utils::showTime(std::cout, [&]{
         for (auto k : keys)
            set.erase(set.find(k));
         //set.erase(set.begin(), set.end()); //TODO - for ordered sets
      });
   }

   void setPerfTests()
   {
      size_t size = 1000000;

      std::cout << std::endl << "[Binary Search Tree Set]" << std::endl;
      integerSetPerfTests<BinaryTreeSet<size_t>>(size);

      std::cout << std::endl << "[Red Black BST Set]" << std::endl;
      integerSetPerfTests<RedBlackTreeSet<size_t>>(size);

      std::cout << std::endl << "[Linked Hash Set]" << std::endl;
      integerSetPerfTests<LinkedHashSet<size_t>>(size);

      std::cout << std::endl << "[Dense Hash Set]" << std::endl;
      integerSetPerfTests<DenseHashSet<size_t>>(size);

      std::cout << std::endl << "[C++ std::set]" << std::endl;
      integerSetPerfTests<std::set<size_t>>(size);

      std::cout << std::endl << "[C++ std::unordered_set]" << std::endl;
      integerSetPerfTests<std::unordered_set<size_t>>(size);
   }
}
