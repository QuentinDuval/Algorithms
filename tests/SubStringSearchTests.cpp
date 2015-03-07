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
      assert(12 == search("ababababababababac", "ababac"));

      assert(std::string::npos == search("searching for random strings", "ramdon"));
      assert(std::string::npos == search("searching for random strings", ""));
      assert(std::string::npos == search("", "ramdon"));
   }

   template<typename SearchImpl>
   void performanceTests(SearchImpl search, std::string const& algorithmName)
   {
      std::cout << " * " << algorithmName << std::endl;
      const size_t N = 20000000;
      const size_t M = 50;
      const std::string text(N, 'a');

      utils::showTimeLog(std::cout, "1 b, 49 a", [&]{ search(text, "b" + std::string(M - 1, 'a')); });
      utils::showTimeLog(std::cout, "1 a, 49 b", [&]{ search(text, "a" + std::string(M - 1, 'b')); });
      utils::showTimeLog(std::cout, "49 a, 1 b", [&]{ search(text, std::string(M - 1, 'a') + "b"); });
      utils::showTimeLog(std::cout, "49 b, 1 a", [&]{ search(text, std::string(M - 1, 'b') + "a"); });
   }

   //--------------------------------------------------------------------------

   void subStringSearchTests()
   {
      basicTests(BruteForceSearch::search);
      basicTests(BoyerMooreSearch::search);
      basicTests(RabinKarpSearch::search);
      basicTests(KMPSearchFullDfa::search);
      basicTests(KMPSearchBorder::search);
   }

   void subStringSearchPerfTests()
   {
      std::cout << std::endl << "[String search timings] (in milliseconds)" << std::endl;
      std::cout << "(searching a string made of 'a' only)" << std::endl;
      performanceTests(BruteForceSearch::search, "Brute Force");
      performanceTests(BoyerMooreSearch::search, "Boyer Moore");
      performanceTests(RabinKarpSearch::search, "Rabin Karp");
      performanceTests(KMPSearchFullDfa::search, "KMP search (dfa)");
      performanceTests(KMPSearchBorder::search, "KMP search (border)");
   }
}

