#include "UnionFindTests.h"

#include "TestUtils.h"
#include "Timer.h"
#include "UnionFind.h"
#include "UnionFindExample.h"
#include "Utils.h"

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
      size_t size = 100;
      std::cout << "[Union-Find] Performance test" << std::endl;
      std::cout << "Number of entries: " << size * size << std::endl;

      std::chrono::duration<double, std::milli> duration;
      time(duration, [=](){
         UnionFind uf(size);
         for (size_t i = 0; i < size; ++i)
            for (size_t j = 0; j < size; ++j)
               uf.connect(i, j);
      });
      
      std::cout << "Time spent: " << duration.count() << " milliseconds" << std::endl;
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
