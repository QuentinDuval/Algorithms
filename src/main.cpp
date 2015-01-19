#include "tests/ConnectedComponentTests.h"
#include "tests/GraphSearchTests.h"
#include "tests/GraphTests.h"
#include "tests/PriorityQueueTests.h"
#include "tests/ShortestPathTests.h"
#include "tests/SortTests.h"
#include "tests/SpanningTreeTests.h"
#include "tests/SubStringSearchTests.h"
#include "tests/TopologicalSortTests.h"
#include "tests/UnionFindTests.h"
#include <iostream>
#include <string>

using namespace algorithm;


static bool runPerformanceTests(std::string const& title)
{
   std::cout << std::endl << "Run performance test on " << title << "? ";
   char res;
   std::cin >> res;
   return res == 'y';
}


int main()
{
   graphTests();
   graphSearchTests();
   symbolGraphTests();
   weightedGraphSearchTests();
   symbolGraphSearchTests();
   connectedComponentsTests();
   shortestPathTests();
   cycleTests();
   topologicalSortTests();
   spanningTreeTests();

   unionFindTests();
   unionFindExample();
   priorityQueueTests();
   sortingTests();
   subStringSearchTests();

   if (runPerformanceTests("graphs"))
   {
      shortestPathPerformanceTests();
      unionFindVsCCPerfTests();
   }

   if (runPerformanceTests("sorts"))
      sortingPerfTests();

   if (runPerformanceTests("string searches"))
   {
      subStringSearchPerfTests();
      system("PAUSE");
   }
}
