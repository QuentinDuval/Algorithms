#include "tests/PriorityQueueTests.h"
#include "tests/SortTests.h"
#include "tests/SubStringSearchTests.h"
#include "tests/UnionFindTests.h"
#include <iostream>

using namespace algorithm;


int main()
{
   unionFindTests();
   unionFindExample();
   priorityQueueTests();
   sortingTests();
   subStringSearchTests();

   std::cout << std::endl << "Run performance test?" << std::endl;
   char res;
   std::cin >> res;
   if (res == 'y')
   {
      unionFindPerfTests();
      sortingPerfTests();
      subStringSearchPerfTests();
      system("PAUSE");
   }
}
