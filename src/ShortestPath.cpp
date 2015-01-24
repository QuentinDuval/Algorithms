#include "ShortestPath.h"

#include "PriorityQueue.h"
#include "TopologicalSort.h"
#include <limits>


namespace algorithm
{
   void fillPathNodes(std::vector<size_t> const& sources, size_t from , size_t to, std::vector<size_t>& nodes)
   {
      if (to == from)
         return;

      fillPathNodes(sources, from, sources[to], nodes);
      nodes.push_back(to);
   }

   //--------------------------------------------------------------------------

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
         fillPathNodes(m_sources, m_from, to, out);
      return out;
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
         relax(e);
         nodes.add(w, m_distances[w]);
      }

      //Start analysis neightbor and relax distances
      while (!nodes.empty())
      {
         auto v = nodes.removeTop();
         if (m_marked[v])
            continue;

         m_marked[v] = true;
         for (auto& e : g.edgesFrom(v))
         {
            auto w = e.to();
            if (m_marked[w])
               continue;

            if (relax(e))
               nodes.add(w, m_distances[w]);
         }
      }
   }

   DijkstraShortestPathFrom::DijkstraShortestPathFrom(WeightedGraph const& g, size_t from)
      : DijkstraShortestPathFrom(g.toDiGraph(), from)
   {}

   bool DijkstraShortestPathFrom::relax(WeightedEdge const& e)
   {
      auto v = e.from();
      auto w = e.to();
      if (m_distances[v] + e.weight() >= m_distances[w])
         return false;

      m_distances[w] = m_distances[v] + e.weight();
      m_sources[w] = v;
      return true;
      
   }

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
         fillPathNodes(m_sources, m_from, to, out);
      return out;
   }

   //--------------------------------------------------------------------------

   TopologicalShortestPathFrom::TopologicalShortestPathFrom(WeightedDiGraph const& g, size_t from)
      : m_from(from)
      , m_marked(g.vertexCount(), false)
      , m_sources(g.vertexCount())
      , m_distances(g.vertexCount(), std::numeric_limits<double>::max())
   {
      m_marked[from] = true;
      m_distances[from] = 0.;

      TopologicalSort sort(g, from);
      for (auto& v : sort.order())
      {
         m_marked[v] = true;
         for (auto& e : g.edgesFrom(v))
            relax(e);
      }
   }

   bool TopologicalShortestPathFrom::relax(WeightedEdge const& e)
   {
      auto v = e.from();
      auto w = e.to();
      if (m_distances[v] + e.weight() >= m_distances[w])
         return false;

      m_distances[w] = m_distances[v] + e.weight();
      m_sources[w] = v;
      return true;

   }

   bool TopologicalShortestPathFrom::hasPathTo(size_t to) const
   {
      return m_marked[to];
   }

   double TopologicalShortestPathFrom::pathLengthTo(size_t to) const
   {
      return m_distances[to];
   }

   std::vector<size_t> TopologicalShortestPathFrom::pathTo(size_t to) const
   {
      std::vector<size_t> out;
      if (hasPathTo(to))
         fillPathNodes(m_sources, m_from, to, out);
      return out;
   }
}
