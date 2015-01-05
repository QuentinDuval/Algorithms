#include "SubStringSearch.h"


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
}
