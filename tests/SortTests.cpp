#include "SortTests.h"

#include "Sort.h"
#include "utils/Algorithms.h"
#include "utils/Timer.h"

#include <assert.h>
#include <functional>
#include <iostream>
#include <string>
#include <vector>


namespace algorithm
{
   struct SortTester
   {
      SortTester(std::ostream& stream, size_t size)
         : m_stream(stream)
         , m_uniformSet(size, 1)
         , m_orderedSet(size, 0)
         , m_randomSet(size, 0)
      {
         stream << std::endl << "[Sort timings]" << "(" << size << " entries - in milliseconds)" << std::endl;
         utils::generate(m_orderedSet, 0, [](int i) { return i + 1; });
         utils::generate(m_randomSet, 0, [](int i) { return i + 1; });
         utils::shuffle(m_randomSet);
      }

      template<typename Algorithm>
      void runTest(std::string const& algorithmName)
      {
         m_stream << algorithmName << std::endl;

         std::vector<int> v1 = m_uniformSet;
         utils::showTime(m_stream, [&](){ Algorithm::sort(v1, std::less<int>()); });

         std::vector<int> v2 = m_orderedSet;
         utils::showTime(m_stream, [&](){ Algorithm::sort(v2, std::less<int>()); });
         utils::showTime(m_stream, [&](){ Algorithm::sort(v2, std::greater<int>()); });
         assert(isSorted(v2, std::greater<int>()));

         std::vector<int> v3 = m_randomSet;
         utils::showTime(m_stream, [&](){ Algorithm::sort(v3, std::less<int>()); });
         assert(isSorted(v3, std::less<int>()));
      }

      std::ostream& m_stream;
      std::vector<int> m_uniformSet;
      std::vector<int> m_orderedSet;
      std::vector<int> m_randomSet;
   };

   //--------------------------------------------------------------------------

   static void runTests(std::ostream& stream, size_t size)
   {
      SortTester tester(stream, size);
      //tester.runTest<SelectionSort>       ("* Selection sort");
      //tester.runTest<BubbleSort>          ("* Bubble sort");
      //tester.runTest<InsertionSort>       ("* Insertion sort");
      tester.runTest<HeapSort>            ("* Heap sort");
      tester.runTest<SystemHeapSort>      ("* System Heap sort");
      tester.runTest<ThreeWayQuickSort>   ("* Quick sort");
      tester.runTest<MergeSort>           ("* Merge sort");
      tester.runTest<SystemSort>          ("* System sort");
   }

   void sortingTests()
   {
      std::ostringstream temp;
      runTests(temp, 10);
   }

   void sortingPerfTests()
   {
      runTests(std::cout, 1000000);
   }
}
