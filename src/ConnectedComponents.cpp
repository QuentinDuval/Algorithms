#include "ConnectedComponents.h"
#include "DepthFirstSearch.h"


namespace algorithm
{
   size_t ConnectedComponents::componentCount() const
   {
      return m_componentCount;
   }

   size_t ConnectedComponents::componentIdOf(size_t vertex) const
   {
      return m_componentIds[vertex];
   }

   bool ConnectedComponents::connected(size_t v, size_t w) const
   {
      return componentIdOf(v) == componentIdOf(w);
   }
}
