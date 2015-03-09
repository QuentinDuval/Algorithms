#pragma once

#include "Encoding.h"

namespace algorithm
{
   /** Encodes run of 0 and 1 with a counter of 8 bits */
   class RunLengthEncoding
      : public Encoding
   {
   public:
      void encode(InBitStream& input, OutBitStream& out) override;
      void decode(InBitStream& input, OutBitStream& out) override;
   };
}
