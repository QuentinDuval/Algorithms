#include "tests/GraphTests.h"

#include "BreathFirstSearch.h"
#include "DepthFirstSearch.h"
#include "Graph.h"
#include "WeightedGraph.h"
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
      std::vector<Edge> inputs {
         { 0, 1 }, { 0, 2 }, { 0, 3 },
         { 1, 2 }, { 1, 4 }, { 1, 5 },
         { 2, 2 }, { 2, 3 }, { 2, 7 },
         { 3, 6 }, { 3, 7 }, { 3, 8 },
      };

      for (auto e : inputs)
         g.addEdge(e);

      DFS<Edge> dfs(g);
      runTest(dfs, 0, "012367845");
      runTest(dfs, 0, "");
      assert(false == dfs.allMarked());
      runTest(dfs, 9, "9");
      assert(true == dfs.allMarked());

      BFS<Edge> bfs(g);
      runTest(bfs, 0, "012345768");
      runTest(bfs, 0, "");
      assert(false == bfs.allMarked());
      runTest(bfs, 9, "9");
      assert(true == bfs.allMarked());
   }

   void weightedGraphSearchTests()
   {
      WeightedGraph g(10);
      std::vector<WeightedEdge> inputs{
         { 0, 1, 1. }, { 0, 2, 1. }, { 0, 3, 1. },
         { 1, 2, 1. }, { 1, 4, 1. }, { 1, 5, 1. },
         { 2, 2, 1. }, { 2, 3, 1. }, { 2, 7, 1. },
         { 3, 6, 1. }, { 3, 7, 1. }, { 3, 8, 1. },
      };

      for (auto e : inputs)
         g.addEdge(e);

      DFS<WeightedEdge> dfs(g);
      runTest(dfs, 0, "012367845");

      BFS<WeightedEdge> bfs(g);
      runTest(bfs, 0, "012345768");
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
