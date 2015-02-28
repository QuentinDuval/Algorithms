#include "tests/LinkedListTests.h"

#include "LinkedList.h"
#include "utils/Algorithms.h"

#include <assert.h>
#include <iostream>
#include <list>


namespace algorithm
{
   void linkedListTests()
   {
      LinkedList<int> list;
      list.pushFront(1);
      list.insert(0, list.begin());
      list.insert(2, list.end());

      for (int i : list)
         std::cout << i << std::endl;
   }
}
