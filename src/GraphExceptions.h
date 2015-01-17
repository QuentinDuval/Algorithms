#pragma once
#include <stdexcept>


namespace algorithm
{
   struct InvalidVertex : std::domain_error
   {
      InvalidVertex(size_t vertexId);
      InvalidVertex(std::string const& vertexName);
   };
}
