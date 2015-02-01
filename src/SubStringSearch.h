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

   struct KMPSearchFullDfa
   {
      static size_t search(std::string const& text, std::string const& pattern);
   };

   struct KMPSearchBorder
   {
      static size_t search(std::string const& text, std::string const& pattern);
   };

   //TODO - Add the regex parser
}
