#include "GraphTests.h"

#include "BreathFirstSearch.h"
#include "Cycle.h"
#include "DepthFirstSearch.h"
#include "DirectedCycle.h"
#include "Graph.h"
#include "WeightedGraph.h"
#include "GraphTestUtils.h"
#include "utils/TestUtils.h"
#include "utils/Timer.h"

#include <assert.h>
#include <sstream>


namespace algorithm
{
   template<typename Edge>
   void runTest(GraphSearch<Edge>& search, size_t from, std::string const& expected)
   {
      std::ostringstream str;
      auto out = [&str](size_t v) { str << v; return false; };
      search.markFrom(from, out);
      assert(expected == str.str());
   }

   static void unweightedGraphSearchTests()
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

   static void weightedGraphSearchTests()
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

   static void cycleTests()
   {
      Graph g(10);
      for (size_t i = 1; i < 10; ++i)
         g.addEdge({ i - 1, i });

      Cycle<Edge> c1(g);
      assert(false == c1.hasCycle());

      g.addEdge({ 2, 9 });
      Cycle<Edge> c2(g);
      assert(true == c2.hasCycle());
      assert(8 == c2.cycle().size());
   }

   static void directedCycleTests()
   {
      DiGraph g(10);
      for (size_t i = 1; i < 10; ++i)
         g.addEdge({ i - 1, i });

      DirectedCycle<Edge> c1(g);
      assert(false == c1.hasCycle());

      g.addEdge({ 0, 9 });
      DirectedCycle<Edge> c2(g);
      assert(false == c2.hasCycle());

      g.addEdge({ 9, 2 });
      DirectedCycle<Edge> c3(g);
      assert(true == c3.hasCycle());
      assert(8 == c3.cycle().size());
   }

   void graphSearchTests()
   {
      unweightedGraphSearchTests();
      weightedGraphSearchTests();
      cycleTests();
      directedCycleTests();
   }

   //--------------------------------------------------------------------------
   
   template<typename SearchAlgo>
   static void runPerfTest(size_t dim)
   {
      Graph g     = make2DPlane(dim, true);
      DiGraph dg  = make2DTopLeftBottomRightPlane(dim, true);

      std::cout << "* Graph:" << std::endl;
      utils::showTime(std::cout, [&]{
         SearchAlgo s(g);
         s.markFrom(0);
      });

      std::cout << "* Directed graph:" << std::endl;
      utils::showTime(std::cout, [&]{
         SearchAlgo s(dg);
         s.markFrom(0);
      });
   }

   void graphSearchPerfTests()
   {
      size_t dim = 1000;

      std::cout << std::endl << "[DFS] Graph of size " << dim * dim << std::endl;
      runPerfTest<DFS<Edge>>(dim);

      std::cout << std::endl << "[BFS] Graph of size " << dim * dim << std::endl;
      runPerfTest<BFS<Edge>>(dim);

      std::cout << std::endl << "[Directed cycle] Graph of size " << dim * dim << std::endl;
      
      DiGraph dg = make2DTopLeftBottomRightPlane(dim, true);
      std::cout << "* No cycle:" << std::endl;
      utils::showTime(std::cout, [&]{ DirectedCycle<Edge> s(dg); });

      dg.addEdge({dim * dim - 1, 0});
      std::cout << "* With cycle:" << std::endl;
      utils::showTime(std::cout, [&]{ DirectedCycle<Edge> s(dg); });
   }
}
