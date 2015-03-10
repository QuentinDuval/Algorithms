#include "HuffmanEncoding.h"

#include <algorithm>
#include <utility>
#include <vector>
#include <unordered_map>


using CharFreq = std::pair<const char, long>;
using Frequencies = std::vector<CharFreq>;


//-----------------------------------------------------------------------------
// ENCODING
//-----------------------------------------------------------------------------

static Frequencies countFrequencies(std::string const& input)
{
   std::unordered_map<char, long> counts;
   for (auto c : input)
      counts[c] += 1;

   Frequencies freqs;
   std::remove_copy_if(begin(counts), end(counts), std::back_inserter(freqs), [](CharFreq const& p){ return p.second == 0; });
   return freqs;
}

static std::string readFullStream(InBitStream& inStream)
{
   std::string fullInput;
   fullInput.reserve(inStream.toRead() / 8);
   while (8 <= inStream.toRead())
      fullInput += inStream.readChar();
   return fullInput;
}

void HuffmanEncoding::encode(InBitStream& inStream, OutBitStream& out)
{
   std::string input = readFullStream(inStream);
   Frequencies freqs = countFrequencies(input);

   auto minFreqFirst = [](CharFreq const& lhs, CharFreq const& rhs){ return lhs.second > rhs.second; };
   std::make_heap(begin(freqs), end(freqs), minFreqFirst);
   while (2 <= freqs.empty())
   {
      std::pop_heap(begin(freqs), end(freqs), minFreqFirst);
      CharFreq fst = freqs.back();
      freqs.pop_back();

      std::pop_heap(begin(freqs), end(freqs) - 1, minFreqFirst);
      CharFreq snd = freqs.back();

      //Build the tree

      //Replace the last node

      std::push_heap(begin(freqs), end(freqs), minFreqFirst);
   }

   //TODO - Handle the last element
}


//-----------------------------------------------------------------------------
// DECODING
//-----------------------------------------------------------------------------

void HuffmanEncoding::decode(InBitStream& input, OutBitStream& out)
{

}
