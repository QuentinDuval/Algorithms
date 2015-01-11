#include "PriorityQueueTests.h"
#include "PriorityQueue.h"
#include "utils/TestUtils.h"

#include <string>


namespace algorithm
{
   void priorityQueueTests()
   {
      MaxPriorityIndexedQueue<std::string, int> queue;
      queue.add("A", 1);
      queue.add("B", 3);
      queue.add("C", 2);

      assert("B" == queue.top());
      assert("B" == queue.top());
      queue.pop();
      assert("C" == queue.top());
      queue.pop();
      assert("A" == queue.top());
      queue.pop();

      ExceptionChecker<EmptyQueueException> checker;
      checker.assertE([&queue]{ queue.pop(); });
      checker.assertE([&queue]{ queue.top(); });
   }
}
