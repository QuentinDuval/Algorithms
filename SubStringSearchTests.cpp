#include "SubStringSearchTests.h"
#include "SubStringSearch.h"
#include "Timer.h"
#include "Utils.h"

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
      const size_t N = 10000000;
      const std::string aText(N, 'a');

      for (size_t M : { 10, 100 })
      {
         showTime(std::cout, [&]{ search(aText, "b" + std::string(M - 1, 'a')); });
         showTime(std::cout, [&]{ search(aText, std::string(M - 1, 'a') + "b"); });

         std::string incrPattern(M, ' ');
         generate(incrPattern, 'a', [](char i) { return 'a' + (i - 'a' + 1) % 26; });
         showTime(std::cout, [&]{ search(aText, incrPattern); });
      }
   }

   //--------------------------------------------------------------------------

   void subStringSearchTests()
   {
      basicTests(BruteForceSearch::search);
      basicTests(BoyerMooreSearch::search);
      basicTests(RabinKarpSearch::search);
      basicTests(KMPSearch::search);

      std::cout << std::endl << "[String search timings] (in milliseconds)" << std::endl;
      performanceTests(BruteForceSearch::search, "Brute Force");
      performanceTests(BoyerMooreSearch::search, "Boyer Moore");
      performanceTests(RabinKarpSearch::search, "Rabin Karp");
      performanceTests(KMPSearch::search, "KMP search");
   }
}

