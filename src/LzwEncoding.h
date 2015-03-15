#pragma once
#include "Encoding.h"


namespace algorithm
{
   class LzwEncoding
      : public Encoding
   {
   public:
      /** The behavior is undefined unless codeword is more than 8 */
      explicit LzwEncoding(size_t codewordSize);

      void encode(InBitStream& input, OutBitStream& out) override;
      void decode(InBitStream& input, OutBitStream& out) override;

   private:
      size_t m_codewordSize;
      unsigned int m_maxCodeWord;
   };
}
