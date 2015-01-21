#include "ShortestPath.h"

#include "PriorityQueue.h"
#include <limits>


namespace algorithm
{
   ShortestPathFrom::ShortestPathFrom(DiGraph const& g, size_t from)
      : m_from(from)
      , m_marked(g.vertexCount(), false)
      , m_sources(g.vertexCount())
   {
      m_sources[from] = from;
      m_marked[from] = true;

      BFS<Edge> bfs(g);
      bfs.pathsFrom(from, [this](Edge const& e){
         m_sources[e.to()] = e.from();
         m_marked[e.to()] = true;
      });
   }

   ShortestPathFrom::ShortestPathFrom(Graph const& g, size_t from)
      : ShortestPathFrom(g.toDiGraph(), from)
   {}

   bool ShortestPathFrom::hasPathTo(size_t to) const
   {
      return m_marked[to];
   }

   size_t ShortestPathFrom::pathLengthTo(size_t to) const
   {
      size_t len = 0;
      for (; to != m_from; ++len)
         to = m_sources[to];
      return len;
   }

   std::vector<size_t> ShortestPathFrom::pathTo(size_t to) const
   {
      std::vector<size_t> out;
      if (hasPathTo(to))
         fillPathNodes(to, out);
      return out;
   }

   void ShortestPathFrom::fillPathNodes(size_t to, std::vector<size_t>& nodes) const
   {
      if (to == m_from)
         return;

      fillPathNodes(m_sources[to], nodes);
      nodes.push_back(to);
   }

   //--------------------------------------------------------------------------

   DijkstraShortestPathFrom::DijkstraShortestPathFrom(WeightedDiGraph const& g, size_t from)
      : m_from(from)
      , m_marked(g.vertexCount(), false)
      , m_sources(g.vertexCount())
      , m_distances(g.vertexCount(), std::numeric_limits<double>::max())
   {
      //Initialization
      m_marked[from] = true;
      m_distances[from] = 0.;

      MinPriorityIndexedQueue<size_t, double> nodes;
      for (auto& e : g.edgesFrom(from))
      {
         auto w = e.to();
         m_distances[w] = e.weight();
         m_sources[w] = from;
         nodes.add(w, m_distances[w]);
      }

      //Start analysis neightbor and relax distances
      while (!nodes.empty())
      {
         auto v = nodes.top();
         nodes.pop();
         if (m_marked[v])
            continue;

         m_marked[v] = true;
         for (auto& e : g.edgesFrom(v))
         {
            auto w = e.to();
            if (m_marked[w])
               continue;

            if (m_distances[v] + e.weight() < m_distances[w])
            {
               m_distances[w] = m_distances[v] + e.weight();
               m_sources[w] = v;
            }
            nodes.add(w, m_distances[w]);
         }
      }
   }

   DijkstraShortestPathFrom::DijkstraShortestPathFrom(WeightedGraph const& g, size_t from)
      : DijkstraShortestPathFrom(g.toDiGraph(), from)
   {}

   bool DijkstraShortestPathFrom::hasPathTo(size_t to) const
   {
      return m_marked[to];
   }

   double DijkstraShortestPathFrom::pathLengthTo(size_t to) const
   {
      return m_distances[to];
   }

   std::vector<size_t> DijkstraShortestPathFrom::pathTo(size_t to) const
   {
      std::vector<size_t> out;
      if (hasPathTo(to))
         fillPathNodes(to, out);
      return out;
   }

   void DijkstraShortestPathFrom::fillPathNodes(size_t to, std::vector<size_t>& nodes) const
   {
      if (to == m_from)
         return;

      fillPathNodes(m_sources[to], nodes);
      nodes.push_back(to);
   }
}
