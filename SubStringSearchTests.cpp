#include "SubStringSearchTests.h"
#include "SubStringSearch.h"
#include "utils/Timer.h"
#include "utils/Utils.h"

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
      const size_t N = 20000000;
      const std::string text(N, 'a');

      for (size_t M : { 10, 100 })
      {
         showTime(std::cout, [&]{
            search(text, "b" + std::string(M - 1, 'a'));
            search(text, "a" + std::string(M - 1, 'b'));
         });

         showTime(std::cout, [&]{
            search(text, std::string(M - 1, 'a') + "b");
            search(text, std::string(M - 1, 'b') + "a");
         });
      }
   }

   //--------------------------------------------------------------------------

   void subStringSearchTests()
   {
      basicTests(BruteForceSearch::search);
      basicTests(BoyerMooreSearch::search);
      basicTests(RabinKarpSearch::search);
      basicTests(KMPSearch::search);
      basicTests(KMPSearch2::search);

      std::cout << std::endl << "[String search timings] (in milliseconds)" << std::endl;
      performanceTests(BruteForceSearch::search, "Brute Force");
      performanceTests(BoyerMooreSearch::search, "Boyer Moore");
      performanceTests(RabinKarpSearch::search, "Rabin Karp");
      performanceTests(KMPSearch::search, "KMP search");
      performanceTests(KMPSearch2::search, "KMP search (2)");
   }
}

