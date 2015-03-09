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

   void BitStream::writeChar(unsigned char c)
   {
      unsigned char mask = 0x80;
      for (size_t i = 0; i < 8; ++i)
      {
         writeBit(c & mask ? true : false);
         mask = mask >> 1;
      }
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
      assert(8 <= toRead());
      unsigned char val = 0;
      for (size_t i = 0; i < 8; ++i)
      {
         val = val << 1;
         val |= (readBit() ? 1 : 0);
      }
      return val;
   }
}
