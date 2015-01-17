#pragma once
#include "Graph.h"
#include <vector>


namespace algorithm
{
   class ConnectedComponents
   {
   public:
      ConnectedComponents(Graph const& g);
      ~ConnectedComponents() = default;

      size_t componentCount() const;
      size_t componentIdOf(size_t vertex) const;
      bool   connected(size_t v, size_t w) const;

   private:
      size_t m_componentCount;
      std::vector<size_t> m_componentIds;
   };
}
