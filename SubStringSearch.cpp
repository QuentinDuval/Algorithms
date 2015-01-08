#include "SubStringSearch.h"
#include <numeric>
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

   //--------------------------------------------------------------------------

   size_t BoyerMooreSearch::search(std::string const& text, std::string const& pattern)
   {
      if (pattern.empty() || text.empty())
         return std::string::npos;

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

   //--------------------------------------------------------------------------

   static bool check(std::string const& text, std::string const& pattern, size_t start)
   {
      return std::equal(pattern.begin(), pattern.end(), text.begin() + start);
   }

   static size_t hashOf(size_t r, size_t q, std::string::const_iterator first, std::string::const_iterator last)
   {
      return std::accumulate(first, last, 0,
         [=](size_t h, char c){ return (h * r + (c - CHAR_MIN)) % q; });
   }

   static size_t charAt(std::string const& s, size_t i)
   {
      return s[i] - CHAR_MIN;
   }

   size_t RabinKarpSearch::search(std::string const& text, std::string const& pattern)
   {
      if (pattern.empty() || text.empty())
         return std::string::npos;

      const size_t n = pattern.size();
      const size_t r = CHAR_MAX - CHAR_MIN;
      const size_t q = 999983; //15485863; //2147483647; //largest prime
      const size_t patternHash = hashOf(r, q, pattern.begin(), pattern.end());

      size_t f = 1; // r ^ (m - 1) % q
      for (size_t i = 0; i < n - 1; ++i)
         f = (f * r) % q;

      size_t hash = hashOf(r, q, text.begin(), text.begin() + n);
      if (hash == patternHash && check(text, pattern, 0))
         return 0;

      for (size_t i = n; i < text.size(); ++i)
      {
         size_t s = i - n + 1;
         size_t toRemove = (f * charAt(text, s - 1)) % q;
         hash = (hash + q - toRemove) % q;
         hash = (hash * r + charAt(text, i) % q) % q;
         if (hash == patternHash && check(text, pattern, s))
            return s;
      }

      return std::string::npos;
   }

   //--------------------------------------------------------------------------

   size_t KMPSearch::search(std::string const& text, std::string const& pattern)
   {
      if (pattern.empty() || text.empty())
         return std::string::npos;

      //Computation of the pattern widest borders
      const size_t n = pattern.size();
      std::vector<size_t> borders(n + 1, 0);
      borders[0] = std::string::npos;

      size_t j = std::string::npos;
      for (size_t i = 0; i < n; ++i)
      {
         while (j != std::string::npos && pattern[i] != pattern[j])
            j = borders[j];

         j = j == std::string::npos ? 0 : j + 1;
         borders[i+1] = j;
      }

      //Search
      size_t s = 0;
      for (size_t i = 0; i < text.size(); ++i)
      {
         while (s != std::string::npos && text[i] != pattern[s])
            s = borders[s];

         s = s == std::string::npos ? 0 : s + 1;
         if (s == n)
            return i + 1 - s;
      }
      return std::string::npos;
   }
}
