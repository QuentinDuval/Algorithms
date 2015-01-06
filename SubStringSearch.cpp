#include "SubStringSearch.h"
#include <vector>


namespace algorithm
{
   size_t BruteForceSearch::search(std::string const& text, std::string const& pattern)
   {
      if (pattern.empty() || text.empty())
         return std::string::npos;

      size_t m = pattern.size();
      for (size_t i = 0; i <= text.size() - m; ++i)
      {
         size_t j = 0;
         while (j < m && pattern[j] == text[i + j]) ++j;
         if (j == m)
            return i;
      }
      return std::string::npos;
   }


   size_t BoyerMooreSearch::search(std::string const& text, std::string const& pattern)
   {
      const size_t n = pattern.size();
      std::vector<size_t> alphabet(CHAR_MAX - CHAR_MIN, std::string::npos);
      for (size_t k = 0; k < n; ++k)
         alphabet[pattern[k] - CHAR_MIN] = k;

      for (size_t i = n - 1; i < text.size();)
      {
         size_t s = i - n + 1;
         size_t j = i;
         while (pattern[j - s] == text[j])
         {
            if (j == s) return s;
            --j;
         }

         size_t skip = alphabet[pattern[j - s]];
         if (skip == std::string::npos)
            i = i + n;
         else if (skip < j)
            i = j - skip;
         else
            ++i;
      }
      return std::string::npos;
   }
}
