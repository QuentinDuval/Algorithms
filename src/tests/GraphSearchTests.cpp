#include "tests/GraphTests.h"

#include "ConnectedComponents.h"
#include "Graph.h"
#include "GraphSearch.h"
#include "utils/TestUtils.h"

#include <assert.h>
#include <sstream>


namespace algorithm
{
   static void runTest(GraphSearch& search, size_t from, std::string const& expected)
   {
      std::ostringstream str;
      auto out = [&str](size_t v) { str << v; };
      search.searchFrom(from, out);
      assert(expected == str.str());
   }

   void graphSearchTests()
   {
      Graph g(10);
      std::vector<std::pair<size_t, size_t>> inputs {
         { 0, 1 }, { 0, 2 }, { 0, 3 },
         { 1, 2 }, { 1, 4 }, { 1, 5 },
         { 2, 2 }, { 2, 3 }, { 2, 7 },
         { 3, 6 }, { 3, 7 }, { 3, 8 },
      };

      for (auto p : inputs)
         g.addEdge(p.first, p.second);

      DepthFirstSearch dfs(g);
      runTest(dfs, 0, "012367845");
      runTest(dfs, 0, "");
      assert(false == dfs.allMarked());
      runTest(dfs, 9, "9");
      assert(true == dfs.allMarked());

      BreathFirstSearch bfs(g);
      runTest(bfs, 0, "012345768");
      runTest(bfs, 0, "");
      assert(false == bfs.allMarked());
      runTest(bfs, 9, "9");
      assert(true == bfs.allMarked());
   }

   void connectedComponentsTests()
   {
      Graph g(6);
      std::vector<std::pair<size_t, size_t>> inputs{ { 0, 1 }, { 0, 2 }, { 1, 2 }, { 3, 4 } };

      for (auto p : inputs)
         g.addEdge(p.first, p.second);

      ConnectedComponents cc(g);
      assert(3 == cc.componentCount());
      assert(true == cc.connected(0, 0));
      assert(true == cc.connected(0, 2));
      assert(true == cc.connected(3, 4));
      assert(false == cc.connected(0, 3));
      assert(false == cc.connected(3, 5));
   }

   void symbolGraphSearchTests()
   {
      auto inputs = { "a", "b", "c", "d", "e" };
      SymbolGraph<std::string> g(begin(inputs), end(inputs));
      g.addEdge("a", "b");
      g.addEdge("a", "c");
      g.addEdge("d", "e");

      std::ostringstream str;
      auto out = [&str](std::string const& v) { str << v; };
      SymbolDepthFirstSearch<std::string> dfs(g);
      dfs.searchFrom("a", out);
      dfs.searchFrom("d", out);
      assert("abcde" == str.str());
   }
}
