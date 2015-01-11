#include "tests/PriorityQueueTests.h"
#include "tests/SortTests.h"
#include "tests/SubStringSearchTests.h"
#include "tests/UnionFindTests.h"
#include <iostream>

using namespace algorithm;


static bool runPerformanceTests()
{
   std::cout << std::endl << "Run performance test? ";
   char res;
   std::cin >> res;
   return res == 'y';
}


int main()
{
   unionFindTests();
   unionFindExample();
   priorityQueueTests();
   sortingTests();
   subStringSearchTests();

   if (runPerformanceTests())
   {
      unionFindPerfTests();
      sortingPerfTests();
      subStringSearchPerfTests();
      system("PAUSE");
   }
}
