#include "MaximumFlow.h"

#include <deque>
#include <limits>


namespace algorithm
{
   class FordFulkerson
   {
   public:
      FordFulkerson(CapacityGraph& graph, size_t from, size_t to)
         : m_graph(graph), m_from(from), m_to(to)
      {}

      void compute()
      {
         while (true)
         {
            auto path = findAugmentingPath();
            if (path.empty())
               return;

            augmentPath(path);
         }
      }

   private:
      void augmentPath(std::vector<CapacityEdge*> const& path)
      {
         double maxIncrease = std::numeric_limits<double>::max();
         for (auto* edge : path)
            maxIncrease = std::min(maxIncrease, edge->remainingCapacity());

         for (auto* edge : path)
         {
            auto* resEdge = residualEdge(edge);
            edge->addFlow(maxIncrease);
            resEdge->addFlow(-1 * maxIncrease);
         }
      }

      std::vector<CapacityEdge*> findAugmentingPath()
      {
         size_t size = m_graph.vertexCount();
         std::vector<bool> marked(size, false);
         std::vector<CapacityEdge*> parent(size, nullptr);
         marked[m_from] = true;

         std::deque<size_t> nodeQueue;
         nodeQueue.push_back(m_from);

         while (!nodeQueue.empty())
         {
            size_t node = nodeQueue.back();
            nodeQueue.pop_back();

            for (auto& e : m_graph.edgesFrom(node))
            {
               size_t dest = e.to();
               if (marked[dest] || e.remainingCapacity() <= 0.)
                  continue;

               marked[dest] = true;
               parent[dest] = &e;
               if (dest == m_to)
                  return reconstructPath(parent);
            }
         }
         return std::vector<CapacityEdge*>();
      }

      std::vector<CapacityEdge*> reconstructPath(std::vector<CapacityEdge*> const& parent)
      {
         std::vector<CapacityEdge*> path;
         size_t node = m_to;
         while (node != m_from)
         {
            auto* edge = parent[node];
            path.push_back(edge);
            node = edge->from();
         }
         return path;
      }

      CapacityEdge* residualEdge(CapacityEdge* edge) const
      {
         for (auto& e : m_graph.edgesFrom(edge->to()))
         {
            if (e.to() == edge->from())
               return &e;
         }
         return nullptr;
      }

   private:
      CapacityGraph& m_graph;
      size_t m_from;
      size_t m_to;
   };

   void computeMaximumFlow(CapacityGraph& graph, size_t from, size_t to)
   {
      FordFulkerson ff(graph, from, to);
      ff.compute();
   }
}
