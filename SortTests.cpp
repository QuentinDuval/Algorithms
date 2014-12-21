#include "SortTests.h"

#include "Sort.h"
#include "Timer.h"
#include "Utils.h"
#include <functional>
#include <iostream>
#include <vector>


namespace algorithm
{
   static std::vector<int> orderedSet(size_t size)
   {
      std::vector<int> data(size, 0);
      generate(data, 0, [](int i) { return i + 1; });
      return data;
   }

   //--------------------------------------------------------------------------

   template<typename Algorithm>
   void sortBasicTest(std::string const& algorithmName)
   {
      std::cout << algorithmName  << " (milliseconds)" << std::endl;
      std::vector<int> v1 = orderedSet(100000);

      showTime(std::cout, [&](){ Algorithm::sort(v1, std::less<int>()); });
      showTime(std::cout, [&](){ Algorithm::sort(v1, std::greater<int>()); });
   }

   //--------------------------------------------------------------------------

   void sortingTests()
   {
      sortBasicTest<SelectionSort>  ("* Selection sort");
      sortBasicTest<BubbleSort>     ("* Bubble sort");
      sortBasicTest<QuickSort>      ("* Quick sort");
   }
}
