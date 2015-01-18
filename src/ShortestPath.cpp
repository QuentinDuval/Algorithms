#include "ShortestPath.h"


namespace algorithm
{
   ShortestPathFrom::ShortestPathFrom(GenericDiGraph<Edge> const& g, size_t from)
      : m_bfs(g)
      , m_from(from)
      , m_sources(g.vertexCount())
   {
      m_sources[from] = from;
      m_bfs.pathsFrom(from, [this](Edge const& e){
         m_sources[e.to()] = e.from();
      });
   }

   ShortestPathFrom::ShortestPathFrom(GenericGraph<Edge> const& g, size_t from)
      : ShortestPathFrom(g.toDiGraph(), from)
   {}

   bool ShortestPathFrom::hasPathTo(size_t to) const
   {
      return m_bfs.isMarked(to);
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
}
