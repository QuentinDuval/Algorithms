#include "StringSort.h"
#include "utils/Algorithms.h"
#include "utils/Functors.h"
#include "utils/Range.h"

#include <array>
#include <numeric>
#include <vector>


namespace algorithm
{
   struct MSBSortImpl
   {
      using string_it = std::vector<std::string>::iterator;

      static size_t charAt(std::string const& str, size_t k)
      {
         if (k < str.size())
            return str[k] - CHAR_MIN;
         return 0;
      }

      static void msbSort(utils::Range<string_it> range, size_t k, size_t w)
      {
         if (w < k || range.size() < 2)
            return;

         /** Count the different characters at index k */
         std::array<size_t, UCHAR_MAX + 1> charCounts = { 0 };
         for (auto& s : range)
            charCounts[charAt(s, k)] += 1;

         /** Easy optimization, all characters are equal, then just check the next */
         if (std::end(charCounts) != std::find(std::begin(charCounts), std::end(charCounts), range.size()))
            return msbSort(range, k + 1, w);

         /** Compute the start position of each bucket */
         std::array<string_it, UCHAR_MAX + 2> bucketStarts = { begin(range) };
         std::array<string_it, UCHAR_MAX + 1> bucketEnds = { begin(range) };
         for (size_t c = 1; c < UCHAR_MAX + 1; ++c)
         {
            bucketStarts[c] = bucketStarts[c-1] + charCounts[c-1];
            bucketEnds[c] = bucketStarts[c];
         }
         bucketStarts[UCHAR_MAX + 1] = end(range);

         /** Move the elements in the corresponding buckets */
         for (size_t c = 0; c < UCHAR_MAX + 1; ++c)
         {
            while (bucketEnds[c] < bucketStarts[c + 1])
            {
               std::string& str = *bucketEnds[c];
               size_t kthChar = charAt(str, k);
               if (kthChar == c)
               {
                  ++(bucketEnds[c]);
               }
               else
               {
                  std::swap(str, *bucketEnds[kthChar]);
                  ++(bucketEnds[kthChar]);
               }
            }
         }

         /** Recurse on each bucket */
         for (size_t c = 0; c < UCHAR_MAX + 1; ++c)
         {
            auto b = bucketStarts[c];
            auto e = bucketStarts[c + 1];
            if (b != e)
               msbSort({ b, e }, k + 1, w);
         }
      }
   };

   void MSBSort::sort(std::vector<std::string>& strings)
   {
      std::vector<std::string>::const_iterator largest =
         std::max_element(begin(strings), end(strings),
         utils::comparingWith([](std::string const& s) { return s.size(); }));

      if (largest != end(strings))
         MSBSortImpl::msbSort({ strings.begin(), strings.end() }, 0, largest->size());
   }
}
