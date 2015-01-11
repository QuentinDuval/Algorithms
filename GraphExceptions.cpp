#include "GraphExceptions.h"
#include "utils/Utils.h"


namespace algorithm
{
   InvalidVertex::InvalidVertex(size_t vertexId)
      : std::domain_error("Invalid vertex: " + toString(vertexId))
   {}
}
