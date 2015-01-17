#include "tests/ConnectedComponentTests.h"
#include "tests/GraphSearchTests.h"
#include "tests/GraphTests.h"
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
   graphTests();
   symbolGraphTests();
   graphSearchTests();
   symbolGraphSearchTests();
   connectedComponentsTests();

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
