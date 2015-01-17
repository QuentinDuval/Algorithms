#pragma once

#include "GraphSearch.h"
#include "internal/GenericDiGraph.h"
#include "internal/GenericGraph.h"
#include <deque>


namespace algorithm
{
   template<typename Edge>
   class BFS : public GraphSearch
   {
   public:
      using DiGraph  = GenericDiGraph<Edge>;
      using OnMarked = GraphSearch::OnMarked;

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

      void searchFrom(size_t v)
      {
         searchFrom(v, [](size_t){});
      }

      void searchFrom(size_t v, OnMarked listener)
      {
         std::deque<size_t> toScan;
         toScan.push_back(v);

         while (!toScan.empty())
         {
            auto current = toScan.front();
            toScan.pop_front();
            if (isMarked(current))
               continue;

            listener(current);
            mark(current);

            for (auto neighbor : m_graph.adjacents(current))
               if (!isMarked(neighbor))
                  toScan.push_back(neighbor);
         }
      }

   protected:
      DiGraph const& m_graph;
   };
}
