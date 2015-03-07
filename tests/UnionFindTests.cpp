#include "UnionFindTests.h"

#include "ConnectedComponents.h"
#include "Graph.h"
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

      utils::ExceptionChecker<UnionFind::InvalidId> tester;
      tester.assertE([&]{ uf.connect(1, 11); });
      tester.assertE([&]{ uf.connect(11, 1); });
      tester.assertE([&]{ uf.connected(1, 11); });
      tester.assertE([&]{ uf.connected(11, 1); });
      assert(10 == uf.count());
   }

   void unionFindTests()
   {
      basicTest();
      boundaryCheckTest();
   }

   //--------------------------------------------------------------------------

   void unionFindVsCCPerfTests()
   {
      const size_t size  = 50000;
      const size_t links = 1000000;
      std::cout << std::endl << "[Union-Find vs CC] Performance test ("
         << size << " entries, " << links << " links)" << std::endl;

      std::vector<size_t> sources(links);
      utils::generate(sources, 0, [=](int i) { return (i + 1) % size; });
      std::vector<size_t> destinations(sources);

      utils::shuffle(sources);
      utils::shuffle(destinations);

      std::cout << "* Union-Find:" << std::endl;
      utils::showTime(std::cout, [&]{
         UnionFind uf(size);
         for (size_t i = 0; i < links; ++i)
            uf.connect(sources[i], destinations[i]);
         for (size_t i = 0; i < links; ++i)
            assert(true == uf.connected(sources[i], destinations[i]));
      });

      std::cout << "* Connected-Components:" << std::endl;
      utils::showTime(std::cout, [&]{
         Graph g(size);
         for (size_t i = 0; i < links; ++i)
            g.addEdge({ sources[i], destinations[i] });

         ConnectedComponents cc(g);
         for (size_t i = 0; i < links; ++i)
            assert(true == cc.connected(sources[i], destinations[i]));
      });

      std::cout << "* Strongly Connected-Components:" << std::endl;
      utils::showTime(std::cout, [&]{
         Graph g(size);
         for (size_t i = 0; i < links; ++i)
            g.addEdge({ sources[i], destinations[i] });

         ConnectedComponents cc(g.toDiGraph());
         for (size_t i = 0; i < links; ++i)
            assert(true == cc.connected(sources[i], destinations[i]));
      });
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
