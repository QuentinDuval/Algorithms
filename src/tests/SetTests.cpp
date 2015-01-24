#include "tests/SetTests.h"

#include "Set.h"
#include "utils/Timer.h"

#include <assert.h>
#include <iostream>
#include <string>


namespace algorithm
{
   void setTests()
   {
      DenseHashSet<std::string> stringSet;
      assert(true == stringSet.insert("a"));
      assert(true == stringSet.insert("b"));
      assert(false == stringSet.insert("b"));
      assert(true == stringSet.contains("a"));
      assert(true == stringSet.contains("b"));

      DenseHashSet<size_t> set;
      for (size_t i = 0; i < 30; ++i)
         set.insert(i);

      assert(30 == set.size());
      for (size_t i = 0; i < 30; ++i)
         assert(true == set.contains(i));

      auto it = set.find(0);
      set.erase(it);
      assert(false == set.contains(0));
      assert(29 == set.size());

      for (auto first = set.begin(); first != set.end(); ++first)
         set.erase(first);

      assert(0 == set.size());
      for (size_t i = 0; i < 30; ++i)
         assert(false == set.contains(i));
   }


   void setPerfTests()
   {
      size_t size = 1000000;
      DenseHashSet<size_t> set;

      std::cout << std::endl << "[Dense Hash Set]" << std::endl;

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

      std::cout << std::endl << "* Deletes:" << std::endl;
      showTime(std::cout, [&]{
         for (auto it = set.begin(); it != set.end(); ++it)
            set.erase(it);
      });
   }
}
