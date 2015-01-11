#include "tests/UnionFindTests.h"

#include "UnionFind.h"
#include "UnionFindExample.h"
#include "utils/Algorithms.h"
#include "utils/TestUtils.h"
#include "utils/Timer.h"

#include <assert.h>
#include <iostream>


namespace algorithm
{
   static void basicTest()
   {
      UnionFind uf(10);
      assert(10 == uf.count());
      assert(false == uf.connected(0, 1));
      assert(true == uf.connect(0, 1));
      assert(true == uf.connected(0, 1));
      assert(false == uf.connect(0, 1));
      assert(9 == uf.count());

      std::vector<UnionFind::IdType> ids{ 2, 3, 1 };
      for (auto i : ids)
         uf.connect(i, 4);
      
      ids.push_back(0);
      for (auto i : ids)
         for (auto j : ids)
            assert(true == uf.connected(i, j));
      assert(6 == uf.count());

      auto newId = uf.addId();
      uf.connect(0, newId);
      assert(true == uf.connected(1, newId));
      assert(6 == uf.count());
   }

   static void boundaryCheckTest()
   {
      UnionFind uf(10);

      ExceptionChecker<UnionFind::InvalidId> tester;
      tester.assertE([&]{ uf.connect(1, 11); });
      tester.assertE([&]{ uf.connect(11, 1); });
      tester.assertE([&]{ uf.connected(1, 11); });
      tester.assertE([&]{ uf.connected(11, 1); });
      assert(10 == uf.count());
   }

   static void performanceTest()
   {
      const size_t size = 50000;
      std::cout << "[Union-Find] Performance test" << std::endl;
      std::cout << "Number of entries, union and finds: " << size << std::endl;

      std::vector<size_t> sources(size);
      generate(sources, 0, [](int i) { return i + 1; });
      std::vector<size_t> destinations(sources);

      shuffle(sources);
      shuffle(destinations);

      showTime(std::cout, [&]{
         UnionFind uf(size);
         for (size_t i = 0; i < size; ++i)
            uf.connect(sources[i], destinations[i]);
         for (size_t i = 0; i < size; ++i)
            assert(true == uf.connected(sources[i], destinations[i]));
      });
   }

   void unionFindTests()
   {
      basicTest();
      boundaryCheckTest();
      performanceTest();
   }

   //--------------------------------------------------------------------------

   void unionFindExample()
   {
      SocialNetwork network;
      auto accounts = {
         "John", "Kimberly", "Bill", "Linda",
         "Ruth", "Carol", "Martin", "Scott",
         "Susan", "Jason", "Kevin", "Jones",
         "Helen", "Laura", "James", "Elizabeth"
      };

      for (auto const& a : accounts)
         network.addAccount(a);

      network.connect("Bill", "Linda");
      network.connect("Bill", "Jones");
      network.connect("Laura", "James");
      network.connect("Helen", "Scott");
      network.connect("Bill", "Helen");
      network.connect("Scott", "Jones");

      auto showConnection = [&network](std::string const& a, std::string const& b) {
         std::cout << " - " << a << " is " << (network.connected(a, b) ? "" : "not");
         std::cout << " connected to " << b << std::endl;
      };

      showConnection("Jones", "Linda");
      showConnection("Bill", "Ruth");
   }
}
