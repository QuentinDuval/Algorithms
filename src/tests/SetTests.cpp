#include "tests/SetTests.h"

#include "Set.h"
#include "utils/Algorithms.h"
#include "utils/Timer.h"

#include <assert.h>
#include <iostream>
#include <string>


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

      //set.erase(set.begin(), set.end());
      //assert(0 == set.size());
      //for (size_t i = 0; i < 30; ++i)
      //   assert(false == set.contains(i));
   }

   static void binarySetTests()
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
      generate(keys, 0, [](size_t i) { return i + 1; });

      std::vector<size_t> shuffledKeys(keys);
      shuffle(shuffledKeys);
      for (auto k : shuffledKeys) set.insert(k);
      assert(true == equal(begin(set), end(set), std::begin(keys)));

      set.erase(set.find(0));
      set.erase(set.find(14));
      set.erase(set.find(29));
      assert(27 == set.size());
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
      binarySetTests();
      linkedHashSetTests();
      denseHashSetTests();
   }

   //--------------------------------------------------------------------------

   template<typename Set>
   void integerSetPerfTests(size_t size)
   {
      Set set;

      std::cout << std::endl << "* Inserts:" << std::endl;
      showTime(std::cout, [&]{
         for (size_t i = 0; i < size; ++i)
            set.insert(i);
      });

      std::cout << std::endl << "* Scan and search:" << std::endl;
      showTime(std::cout, [&]{
         for (auto& k : set)
            assert(true == set.contains(k));
      });

      //std::cout << std::endl << "* Deletes:" << std::endl;
      //showTime(std::cout, [&]{
      //   set.erase(set.begin(), set.end());
      //});
   }

   void setPerfTests()
   {
      size_t size = 1000000;

      std::cout << std::endl << "[Linked Hash Set]" << std::endl;
      integerSetPerfTests<LinkedHashSet<size_t>>(size);

      std::cout << std::endl << "[Dense Hash Set]" << std::endl;
      integerSetPerfTests<DenseHashSet<size_t>>(size);
   }
}
