#pragma once

#include "BitStream.h"
#include <string>

namespace algorithm
{
   /** Interface for any encoding / decoding engine */
   struct Encoding
   {
   public:
      virtual ~Encoding() = default;
      virtual void encode(InBitStream& input, OutBitStream& out) = 0;
      virtual void decode(InBitStream& input, OutBitStream& out) = 0;
   };


   /** Helpers */
   void encodeWith(Encoding& encoding, std::string const& input, OutBitStream& out);
   std::string decodeWith(Encoding& encoding, InBitStream& input);
}
