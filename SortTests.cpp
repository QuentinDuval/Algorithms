#include "SortTests.h"

#include "Sort.h"
#include "Timer.h"
#include "Utils.h"
#include <functional>
#include <iostream>
#include <vector>


namespace algorithm
{
   struct SortTester
   {
      SortTester(size_t size)
         : m_uniformSet(size, 1)
         , m_orderedSet(size, 0)
         , m_randomSet(size, 0)
      {
         std::cout << std::endl << "[Sort timings]" << "(" << size << " entries - in milliseconds)" << std::endl;
         generate(m_orderedSet, 0, [](int i) { return i + 1; });
         generate(m_randomSet, 0, [](int i) { return i + 1; });
         shuffle(m_randomSet);
      }

      template<typename Algorithm>
      void runTest(std::string const& algorithmName)
      {
         std::cout << algorithmName << std::endl;

         std::vector<int> v1 = m_uniformSet;
         showTime(std::cout, [&](){ Algorithm::sort(v1, std::less<int>()); });

         std::vector<int> v2 = m_orderedSet;
         showTime(std::cout, [&](){ Algorithm::sort(v2, std::less<int>()); });
         showTime(std::cout, [&](){ Algorithm::sort(v2, std::greater<int>()); });
         assert(isSorted(v2, std::greater<int>()));

         std::vector<int> v3 = m_randomSet;
         showTime(std::cout, [&](){ Algorithm::sort(v3, std::less<int>()); });
         assert(isSorted(v3, std::less<int>()));
      }

      std::vector<int> m_uniformSet;
      std::vector<int> m_orderedSet;
      std::vector<int> m_randomSet;
   };

   //--------------------------------------------------------------------------

   void sortingTests()
   {
      SortTester tester(50000);
      tester.runTest<SelectionSort>       ("* Selection sort");
      tester.runTest<BubbleSort>          ("* Bubble sort");
      tester.runTest<InsertionSort>       ("* Insertion sort");
      tester.runTest<HeapSort>            ("* Heap sort");
      tester.runTest<SystemHeapSort>      ("* System Heap sort");
      tester.runTest<ThreeWayQuickSort>   ("* Quick sort");
      tester.runTest<MergeSort>           ("* Merge sort");
   }
}
