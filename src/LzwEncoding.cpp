#include "LzwEncoding.h"
#include "StringTrie.h"

#include <cassert>
#include <cmath>
#include <limits>


namespace algorithm
{
   LzwEncoding::LzwEncoding(size_t codewordSize)
      : m_codewordSize(codewordSize)
      , m_maxCodeWord(static_cast<unsigned int>(std::pow(2, codewordSize + 1) - 1))
   {
      assert(8 < codewordSize);
      assert(codewordSize <= std::numeric_limits<unsigned int>::digits);
   }


   //-----------------------------------------------------------------------------
   // ENCODING
   //-----------------------------------------------------------------------------

   unsigned int fillAlphabet(StringTrie<unsigned int>& codewords)
   {
      unsigned int nextCodeword = 0;
      for (char c = CHAR_MIN; c <= CHAR_MAX; ++c)
         codewords.insert(std::string(1, c), nextCodeword++);
      return nextCodeword;
   }

   void LzwEncoding::encode(InBitStream& inStream, OutBitStream& out)
   {
      StringTrie<unsigned int> codewords;
      unsigned int nextCodeword = fillAlphabet(codewords);
      std::string input = readString(inStream);

      auto current = begin(input);
      while (current != end(input))
      {
         std::string key = codewords.longestPrefixOf(current, end(input));
         out.writeInt(*codewords.search(key), m_codewordSize);

         auto next = current + key.size();
         if (nextCodeword <= m_maxCodeWord && next != end(input))
            codewords.insert(current, next + 1, nextCodeword++);
         current = next;
      }
   }


   //-----------------------------------------------------------------------------
   // DECODING
   //-----------------------------------------------------------------------------

   void LzwEncoding::decode(InBitStream& input, OutBitStream& out)
   {
      //TODO
   }
}
