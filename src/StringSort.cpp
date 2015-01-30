#include "StringSort.h"
#include "utils/Algorithms.h"
#include "utils/Utils.h"

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

      static void msbSort(Range<string_it> range, size_t k)
      {
         if (range.size() < 2)
            return;

         /** Count the different characters at index k */
         size_t charCounts[UCHAR_MAX + 1] = { 0 };
         for (auto& s : range)
            charCounts[charAt(s, k)] += 1;

         /** Easy optimization, all characters are equal, then just check the next */
         if (std::end(charCounts) != std::find(std::begin(charCounts), std::end(charCounts), range.size()))
            return msbSort(range, k + 1);

         /** Compute the start position of each bucket */
         size_t bucketStarts[UCHAR_MAX + 1] = { 0 }; //TODO - use iterators instead
         size_t bucketEnds[UCHAR_MAX + 1] = { 0 };
         for (size_t c = 1; c < UCHAR_MAX + 1; ++c)
         {
            bucketStarts[c] = bucketStarts[c - 1] + charCounts[c - 1];
            bucketEnds[c] = bucketStarts[c];
         }

         /** Move the elements in the corresponding buckets */
         for (size_t c = 0; c < UCHAR_MAX + 1; ++c)
         {
            while (bucketEnds[c] < bucketStarts[c] + charCounts[c])
            {
               std::string& str = *(range.begin() + bucketEnds[c]);
               size_t kthChar = charAt(str, k);
               if (kthChar == c)
               {
                  ++(bucketEnds[c]);
               }
               else
               {
                  std::string& toExchange = *(range.begin() + bucketEnds[kthChar]);
                  std::swap(str, toExchange);
                  ++(bucketEnds[kthChar]);
               }
            }
         }

         /** Recurse on each bucket */
         for (size_t c = 1; c < UCHAR_MAX + 1; ++c)
         {
            auto b = range.begin() + bucketStarts[c];
            auto e = range.begin() + bucketEnds[c];
            msbSort({ b, e }, k + 1);
         }
      }
   };

   void MSBSort::sort(std::vector<std::string>& strings)
   {
      MSBSortImpl::msbSort({ strings.begin(), strings.end() }, 0);
   }
}
