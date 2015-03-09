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
      BitStream encoderOut;
      encoding.decode(input, encoderOut);

      std::string out;
      while (8 <= encoderOut.toRead())
         out += encoderOut.readChar();
      return out;
   }
}
