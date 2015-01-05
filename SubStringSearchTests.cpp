#include "SubStringSearchTests.h"
#include "SubStringSearch.h"

#include <assert.h>
#include <iostream>


namespace algorithm
{
   template<typename SearchImpl>
   void test(SearchImpl search)
   {
      static const std::string text = "searching for random strings";
      assert(0 == search("searching for random strings", "searching"));
      assert(9 == search("searching for random strings", " "));
      assert(21 == search("searching for random strings", "strings"));
      assert(std::string::npos == search("searching for random strings", "ramdon"));
   }

   void subStringSearchTests()
   {
      test(BruteForceSearch::search);
   }
}

