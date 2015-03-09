#include "RunLengthEncoding.h"


namespace algorithm
{
   void RunLengthEncoding::encode(InBitStream& input, OutBitStream& out)
   {
      bool lastBit = false;
      unsigned char count = 0;
      while (0 < input.toRead())
      {
         bool bit = input.readBit();
         if (bit != lastBit)
         {
            out.writeChar(count);
            count = 1;
            lastBit = bit;
         }
         else if (count == 255)
         {
            out.writeChar(count);
            out.writeChar(0);
            count = 1;
         }
         else
         {
            ++count;
         }
      }

      if (count)
      {
         out.writeChar(count);
      }
   }

   void RunLengthEncoding::decode(InBitStream& input, OutBitStream& out)
   {
      bool bit = false;
      while (8 <= input.toRead())
      {
         unsigned char count = input.readChar();
         for (size_t i = 0; i < count; ++i)
            out.writeBit(bit);
         bit = !bit;
      }
   }
}
