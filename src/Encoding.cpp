#include "Encoding.h"

namespace algorithm
{
   void encodeWith(Encoding& encoding, std::string const& input, OutBitStream& out)
   {
      BitStream encoderIn;
      for (char c : input)
         encoderIn.writeChar(c);
      encoding.encode(encoderIn, out);
   }

   std::string decodeWith(Encoding& encoding, InBitStream& input)
   {
      BitStream output;
      encoding.decode(input, output);
      return readString(output);
   }
}
