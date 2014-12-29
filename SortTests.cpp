#include "SortTests.h"

#include "Sort.h"
#include "Timer.h"
#include "Utils.h"
#include <functional>
#include <iostream>
#include <vector>


namespace algorithm
{
   static std::vector<int> uniformSet(size_t size)
   {
      return std::vector<int>(size, 1);
   }

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
      std::cout << algorithmName << std::endl;
      const size_t Count = 10000;

      std::vector<int> v1 = uniformSet(Count);
      showTime(std::cout, [&](){ Algorithm::sort(v1, std::less<int>()); });

      std::vector<int> v2 = orderedSet(Count);
      showTime(std::cout, [&](){ Algorithm::sort(v2, std::less<int>()); });
      showTime(std::cout, [&](){ Algorithm::sort(v2, std::greater<int>()); });
   }

   //--------------------------------------------------------------------------

   void sortingTests()
   {
      std::cout << std::endl << "[Sort timings] (milliseconds)" << std::endl;
      sortBasicTest<SelectionSort>  ("* Selection sort");
      sortBasicTest<BubbleSort>     ("* Bubble sort");
      sortBasicTest<InsertionSort>  ("* Insertion sort");
      sortBasicTest<QuickSort>      ("* Quick sort");
   }
}
