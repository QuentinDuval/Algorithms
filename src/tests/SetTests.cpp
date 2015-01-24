#include "tests/SetTests.h"

#include "Set.h"

#include <assert.h>
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
}
