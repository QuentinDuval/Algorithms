#pragma once

#include <vector>

namespace algorithm
{
   template<typename T>
   typename std::vector<T>::const_iterator binarySearch(std::vector<T> const& values, T const& val)
   {
      int low = 0;
      int end = values.size() - 1;
      while (low <= end)
      {
         int mid = (low + end) / 2;
         if (values[mid] == val)
            return begin(values) + mid;

         if (val < values[mid])
            end = mid - 1;
         else
            low = mid + 1;
      }

      return values.end();
   }
}
