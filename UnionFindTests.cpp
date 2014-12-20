#include "UnionFindTests.h"
#include "UnionFind.h"
#include <assert.h>


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
      //TODO
   }

   void unionFindTests()
   {
      basicTest();
      boundaryCheckTest();
   }
}
