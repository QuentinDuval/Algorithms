#include "SubStringSearchTests.h"
#include "SubStringSearch.h"
#include "Timer.h"

#include <assert.h>
#include <iostream>


namespace algorithm
{
   template<typename SearchImpl>
   void basicTests(SearchImpl search)
   {
      static const std::string text = "searching for random strings";
      assert(0 == search("searching for random strings", "searching"));
      assert(9 == search("searching for random strings", " "));
      assert(21 == search("searching for random strings", "strings"));

      assert(std::string::npos == search("searching for random strings", "ramdon"));
      assert(std::string::npos == search("searching for random strings", ""));
      assert(std::string::npos == search("", "ramdon"));
   }

   template<typename SearchImpl>
   void performanceTests(SearchImpl search, std::string const& algorithmName)
   {
      std::cout << " * " << algorithmName << std::endl;
      const size_t N = 1000000;
      const size_t M = 100;

      showTime(std::cout, [=]{ search(std::string(N, 'a'), std::string(M, 'b')); });
      showTime(std::cout, [=]{ search(std::string(N, 'a'), std::string(M-1, 'a') + "b"); });
   }

   //--------------------------------------------------------------------------

   void subStringSearchTests()
   {
      basicTests(BruteForceSearch::search);
      std::cout << std::endl << "[String search timings] (in milliseconds)" << std::endl;
      performanceTests(BruteForceSearch::search, "Brute force");
   }
}

