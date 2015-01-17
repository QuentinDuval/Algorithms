#pragma once

#include "GraphSearch.h"
#include "internal/GenericDiGraph.h"
#include "internal/GenericGraph.h"
#include <deque>


namespace algorithm
{
   template<typename Edge>
   class BFS : public GraphSearch<Edge>
   {
   public:
      using DiGraph = GenericDiGraph<Edge>;
      using OnMarked = GraphSearch<Edge>::OnMarked;

   public:
      explicit BFS(DiGraph const& g)
         : GraphSearch(g.vertexCount())
         , m_graph(g)
      {}

      explicit BFS(GenericGraph<Edge> const& g)
         : GraphSearch(g.vertexCount())
         , m_graph(g.toDiGraph())
      {}

      virtual ~BFS() = default;

      void searchFrom(size_t v, OnMarked listener)
      {
         if (isMarked(v))
            return;

         std::deque<size_t> toScan;
         toScan.push_back(v);
         mark(v);

         while (!toScan.empty())
         {
            auto current = toScan.front();
            toScan.pop_front();

            for (auto e : m_graph.edgesFrom(current))
            {
               auto a = e.to();
               if (isMarked(a))
                  continue;
               
               listener(e);
               mark(a);
               toScan.push_back(a);
            }
         }
      }

   private:
      DiGraph const& m_graph;
   };
}
