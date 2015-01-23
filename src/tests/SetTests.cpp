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

      for (size_t i = 0; i < 30; ++i)
         assert(true == set.contains(i));
   }
}
