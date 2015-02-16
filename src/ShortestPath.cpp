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

   RelaxBasedShortestPath::RelaxBasedShortestPath(size_t from, size_t order)
      : m_from(from)
      , m_sources(order)
      , m_distances(order, std::numeric_limits<double>::max())
   {}

   bool RelaxBasedShortestPath::hasPathTo(size_t to) const
   {
      return m_distances[to] != std::numeric_limits<double>::max();
   }

   double RelaxBasedShortestPath::pathLengthTo(size_t to) const
   {
      return m_distances[to];
   }

   std::vector<size_t> RelaxBasedShortestPath::pathTo(size_t to) const
   {
      std::vector<size_t> out;
      if (hasPathTo(to))
         fillPathNodes(m_sources, m_from, to, out);
      return out;
   }

   bool RelaxBasedShortestPath::relax(WeightedEdge const& e)
   {
      auto v = e.from();
      auto w = e.to();
      if (m_distances[v] + e.weight() >= m_distances[w])
         return false;

      m_distances[w] = m_distances[v] + e.weight();
      m_sources[w] = v;
      return true;
   }

   //--------------------------------------------------------------------------

   DijkstraShortestPathFrom::DijkstraShortestPathFrom(WeightedDiGraph const& g, size_t from)
      : RelaxBasedShortestPath(from, g.vertexCount())
   {
      //Initialization
      std::vector<bool> marked(g.vertexCount(), false);
      marked[from] = true;
      m_distances[from] = 0.;

      MinPriorityIndexedQueue<size_t, double> nodes;
      for (auto& e : g.edgesFrom(from))
      {
         auto w = e.to();
         relax(e);
         nodes.add(w, m_distances[w]);
      }

      //Start analysing neightbor and relax distances
      while (!nodes.empty())
      {
         auto v = nodes.removeTop();
         if (marked[v])
            continue;

         marked[v] = true;
         for (auto& e : g.edgesFrom(v))
         {
            auto w = e.to();
            if (marked[w])
               continue;

            if (relax(e))
               nodes.add(w, m_distances[w]);
         }
      }
   }

   DijkstraShortestPathFrom::DijkstraShortestPathFrom(WeightedGraph const& g, size_t from)
      : DijkstraShortestPathFrom(g.toDiGraph(), from)
   {}

   //--------------------------------------------------------------------------

   TopologicalShortestPathFrom::TopologicalShortestPathFrom(WeightedDiGraph const& g, size_t from)
      : RelaxBasedShortestPath(from, g.vertexCount())
   {
      m_distances[from] = 0.;

      TopologicalSort sort(g, from);
      for (auto& v : sort.order())
      {
         for (auto& e : g.edgesFrom(v))
            relax(e);
      }
   }

   //--------------------------------------------------------------------------

   BellmanFordShortestPathFrom::BellmanFordShortestPathFrom(WeightedDiGraph const& g, size_t from)
      : RelaxBasedShortestPath(from, g.vertexCount())
   {
      std::vector<size_t> lastChanged(g.vertexCount(), std::numeric_limits<size_t>::max());
      m_distances[from] = 0.;
      lastChanged[from] = 0;

      for (size_t i = 1; i <= g.vertexCount(); ++i)
      {
         bool hasChanged = false;
         for (size_t v : g.vertices())
         {
            if (lastChanged[v] != i - 1)
               continue;

            for (auto& e : g.edgesFrom(v))
            {
               if (!relax(e))
                  continue;
               
               lastChanged[e.to()] = i;
               hasChanged = true;
            }
         }

         if (!hasChanged)
            break;
      }
   }

   BellmanFordShortestPathFrom::BellmanFordShortestPathFrom(WeightedGraph const& g, size_t from)
      : BellmanFordShortestPathFrom(g.toDiGraph(), from)
   {}

   //--------------------------------------------------------------------------

   FloydWarshallShortestPath::FloydWarshallShortestPath(WeightedDiGraph const& g)
      : m_weights(g.vertexCount(), g.vertexCount(), std::numeric_limits<double>::max())
   {
      //Initialization - compute the shortest path with 0 intermediary nodes
      for (size_t v : g.vertices())
      {
         m_weights.at(v, v) = 0;
         for (auto& e : g.edgesFrom(v))
            m_weights.at(v, e.to()) = e.weight();
      }

      //Relaxing the edges - each time considering an additional intermediary node
      for (size_t k : g.vertices())
         for (size_t from : g.vertices())
            for (size_t to : g.vertices())
               m_weights.at(from, to) = std::min(m_weights.at(from, to), m_weights.at(from, k) + m_weights.at(k, to));
   }
   
   FloydWarshallShortestPath::FloydWarshallShortestPath(WeightedGraph const& g)
      : FloydWarshallShortestPath(g.toDiGraph())
   {}

   double FloydWarshallShortestPath::pathLength(size_t from, size_t to) const
   {
      return m_weights.at(from, to);
   }
}
