#pragma once

#include "GraphSearch.h"
#include "internal/GenericDiGraph.h"
#include "internal/GenericGraph.h"
#include <queue>


namespace algorithm
{
   template<typename Edge>
   class BFS : public GraphSearch<Edge>
   {
   public:
      using DiGraph = GenericDiGraph<Edge>;
      using OnPathTaken = GraphSearch<Edge>::OnPathTaken;

   public:
      explicit BFS(DiGraph const& g)
         : GraphSearch(g.vertexCount())
         , m_graph(g)
      {}

      explicit BFS(GenericGraph<Edge> const& g)
         : BFS(g.toDiGraph())
      {}

   private:
      void searchImpl(size_t v, OnPathTaken listener) override
      {
         if (isMarked(v))
            return;

         std::queue<size_t> nodesToScan;
         nodesToScan.push(v);
         mark(v);

         while (!nodesToScan.empty())
         {
            auto current = nodesToScan.front();
            nodesToScan.pop();

            for (auto e : m_graph.edgesFrom(current))
            {
               auto a = e.to();
               if (isMarked(a))
                  continue;
               
               listener(e);
               mark(a);
               nodesToScan.push(a);
            }
         }
      }

   private:
      DiGraph const& m_graph;
   };
}
