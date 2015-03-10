#pragma once
#include "Encoding.h"


class HuffmanEncoding
   : public Encoding
{
public:
   void encode(InBitStream& input, OutBitStream& out) override;
   void decode(InBitStream& input, OutBitStream& out) override;
};
