#include "tests/GraphTests.h"

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
      runTest(dfs, 9, "9");

      BreathFirstSearch bfs(g);
      runTest(bfs, 0, "012345768");
      runTest(bfs, 0, "");
      runTest(bfs, 9, "9");
   }
}
