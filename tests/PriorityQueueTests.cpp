#include "PriorityQueueTests.h"

#include "PriorityQueue.h"
#include "utils/TestUtils.h"

#include <string>


namespace algorithm
{
   template <typename Queue, typename Result>
   static void checkResults(Queue& queue, std::vector<Result> const& expected)
   {
      for (auto& e : expected)
      {
         assert(e == queue.top());
         assert(e == queue.top());
         queue.pop();
      }

      utils::ExceptionChecker<EmptyQueueException> checker;
      checker.assertE([&queue]{ queue.pop(); });
      checker.assertE([&queue]{ queue.top(); });
   }

   static void queueTests()
   {
      MaxPriorityQueue<std::string> maxQueue;
      MinPriorityQueue<std::string> minQueue;

      for (auto& i : { "A", "C", "B" })
      {
         maxQueue.add(i);
         minQueue.add(i);
      }

      checkResults(maxQueue, std::vector<std::string>{ "C", "B", "A" });
      checkResults(minQueue, std::vector<std::string>{ "A", "B", "C" });
   }

   static void indexedQueueTests()
   {
      MaxPriorityIndexedQueue<std::string, int> maxQueue;
      MinPriorityIndexedQueue<std::string, int> minQueue;

      auto inputs = { std::make_pair("A", 1), std::make_pair("B", 3), std::make_pair("C", 2) };
      for (auto& i : inputs)
      {
         maxQueue.add(i.first, i.second);
         minQueue.add(i.first, i.second);
      }

      checkResults(maxQueue, std::vector<std::string>{ "B", "C", "A" });
      checkResults(minQueue, std::vector<std::string>{ "A", "C", "B" });
   }

   //--------------------------------------------------------------------------

   void priorityQueueTests()
   {
      queueTests();
      indexedQueueTests();
   }
}
