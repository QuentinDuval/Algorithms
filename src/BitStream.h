#pragma once

#include <exception>
#include <vector>


namespace algorithm
{
   class InBitStream
   {
   public:
      virtual ~InBitStream() = default;
      virtual size_t        toRead() = 0;
      virtual bool          readBit() = 0;
      virtual unsigned char readChar() = 0;
      virtual unsigned int  readInt(size_t width) = 0;
   };


   class OutBitStream
   {
   public:
      virtual ~OutBitStream() = default;
      virtual void writeBit(bool) = 0;
      virtual void writeChar(unsigned char) = 0;
      virtual void writeInt(unsigned int, size_t width) = 0;
      virtual void writeBits(std::vector<bool> const&) = 0;
   };


   class BitStream
      : public InBitStream
      , public OutBitStream
   {
   public:
      BitStream();
      virtual ~BitStream();

      void writeBit(bool) override;
      void writeChar(unsigned char) override;
      void writeInt(unsigned int, size_t width) override;
      void writeBits(std::vector<bool> const&) override;

      size_t        toRead() override;
      bool          readBit() override;
      unsigned char readChar() override;
      unsigned int  readInt(size_t width) override;

   private:
      size_t m_readPtr;
      std::vector<bool> m_bits;
   };

   std::string readString(InBitStream& inStream);
}
