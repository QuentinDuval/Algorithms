#pragma once
#include <string>

namespace algorithm
{
   struct BruteForceSearch
   {
      static size_t search(std::string const& text, std::string const& pattern);
   };

   struct BoyerMooreSearch
   {
      static size_t search(std::string const& text, std::string const& pattern);
   };

   struct RabinKarpSearch
   {
      static size_t search(std::string const& text, std::string const& pattern);
   };

   struct KMPSearch
   {
      static size_t search(std::string const& text, std::string const& pattern);
   };
}
