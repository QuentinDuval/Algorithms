#include "tests/ConnectedComponentTests.h"
#include "tests/GraphSearchTests.h"
#include "tests/GraphTests.h"
#include "tests/PriorityQueueTests.h"
#include "tests/SetTests.h"
#include "tests/ShortestPathTests.h"
#include "tests/SimplexTests.h"
#include "tests/SortTests.h"
#include "tests/StringTrieTests.h"
#include "tests/StringSortTests.h"
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
   connectedComponentsTests();
   shortestPathTests();
   topologicalSortTests();
   spanningTreeTests();
   setTests();
   stringSortingTests();
   stringTrieTests();
   simplexTests();

   unionFindTests();
   unionFindExample();
   priorityQueueTests();
   sortingTests();
   subStringSearchTests();
   //TODO - Add the max flow

   if (runPerformanceTests("graphs"))
   {
      graphSearchPerfTests();
      topologicalSortPerfTests();
      shortestPathPerformanceTests();
      unionFindVsCCPerfTests();
      spanningTreePerfTests();
   }

   if (runPerformanceTests("collections"))
   {
      setPerfTests();
      stringTriePerfTests();
   }

   if (runPerformanceTests("sorts"))
   {
      stringSortingPerfTests();
      sortingPerfTests();
   }

   if (runPerformanceTests("string searches"))
   {
      subStringSearchPerfTests();
      system("PAUSE");
   }
}
