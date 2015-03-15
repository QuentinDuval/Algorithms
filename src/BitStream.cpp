#include "BitStream.h"

#include <cassert>

namespace algorithm
{
   BitStream::BitStream()
      : m_readPtr(0)
   {}

   BitStream::~BitStream()
   {}

   void BitStream::writeBit(bool b)
   {
      m_bits.push_back(b);
   }

   void BitStream::writeInt(unsigned int val, size_t width)
   {
      unsigned char mask = 1 << (width - 1);
      for (size_t i = 0; i < width; ++i)
      {
         writeBit(val & mask ? true : false);
         mask = mask >> 1;
      }
   }

   void BitStream::writeChar(unsigned char c)
   {
      writeInt(c, 8);
   }

   void BitStream::writeBits(std::vector<bool> const& bits)
   {
      m_bits.insert(end(m_bits), begin(bits), end(bits));
   }

   size_t BitStream::toRead()
   {
      return m_bits.size() - m_readPtr;
   }

   bool BitStream::readBit()
   {
      assert(1 <= toRead());
      return m_bits.at(m_readPtr++);
   }

   unsigned char BitStream::readChar()
   {
      return static_cast<unsigned char>(readInt(8));
   }

   unsigned int BitStream::readInt(size_t width)
   {
      assert(width <= toRead());
      unsigned int val = 0;
      for (size_t i = 0; i < width; ++i)
      {
         val = val << 1;
         val |= (readBit() ? 1 : 0);
      }
      return val;
   }

   //--------------------------------------------------------------------------

   std::string readString(InBitStream& inStream)
   {
      std::string fullInput;
      fullInput.reserve(inStream.toRead() / 8);
      while (8 <= inStream.toRead())
         fullInput += inStream.readChar();
      return fullInput;
   }
}
