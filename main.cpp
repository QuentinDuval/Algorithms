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

   system("PAUSE");
}
