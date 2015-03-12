#include "HuffmanEncoding.h"

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>
#include <unordered_map>

namespace algorithm
{
   namespace
   {
      struct CharFreqNode
      {
         CharFreqNode(char val, long freq) : m_val(val), m_freq(freq) {}

         CharFreqNode(std::unique_ptr<CharFreqNode> left, std::unique_ptr<CharFreqNode> right)
            : m_val('\0')
            , m_freq(left->m_freq + right->m_freq)
            , m_left(std::move(left))
            , m_right(std::move(right))
         {}

         const char m_val;
         const long m_freq;
         std::unique_ptr<CharFreqNode> m_left;
         std::unique_ptr<CharFreqNode> m_right;
      };

      using CharFreqNodePtr = std::unique_ptr < CharFreqNode > ;
      using FrequencyNodes = std::vector < CharFreqNodePtr > ;
      using CharToCodeMapping = std::unordered_map < char, std::vector<bool> > ;

      void encodeTree(CharFreqNodePtr& tree, OutBitStream& out)
      {
         if ('\0' != tree->m_val)
         {
            out.writeBit(true); //Leaf
            out.writeChar(tree->m_val);
         }
         else
         {
            out.writeBit(false);
            encodeTree(tree->m_left, out);
            out.writeBit(false);
            encodeTree(tree->m_left, out);
         }
      }

      CharFreqNodePtr decodeTree(InBitStream& input)
      {
         bool isLeaf = input.readBit();
         if (isLeaf)
         {
            return std::make_unique<CharFreqNode>(input.readChar(), 1);
         }
         else
         {
            CharFreqNodePtr left = decodeTree(input);
            CharFreqNodePtr right = decodeTree(input);
            return std::make_unique<CharFreqNode>(std::move(left), std::move(right));
         }
      }
   }

   //-----------------------------------------------------------------------------
   // ENCODING
   //-----------------------------------------------------------------------------

   static FrequencyNodes countFrequencies(std::string const& input)
   {
      std::unordered_map<char, long> counts;
      for (auto c : input)
         counts[c] += 1;

      FrequencyNodes freqNodes;
      for (auto const& pair : counts)
         freqNodes.emplace_back(std::make_unique<CharFreqNode>(pair.first, pair.second));
      return freqNodes;
   }

   static std::string readFullStream(InBitStream& inStream)
   {
      std::string fullInput;
      fullInput.reserve(inStream.toRead() / 8);
      while (8 <= inStream.toRead())
         fullInput += inStream.readChar();
      return fullInput;
   }

   static CharFreqNodePtr buildCodingTree(std::string const& input)
   {
      FrequencyNodes freqs = countFrequencies(input);
      auto minFreqFirst = [](CharFreqNodePtr const& lhs, CharFreqNodePtr const& rhs){ return lhs->m_freq > rhs->m_freq; };
      std::make_heap(begin(freqs), end(freqs), minFreqFirst);

      //Assemble the nodes two by two, until there is one left, the huffman tree
      while (2 <= freqs.size())
      {
         std::pop_heap(begin(freqs), end(freqs), minFreqFirst);
         CharFreqNodePtr fst = std::move(freqs.back());
         freqs.pop_back();

         std::pop_heap(begin(freqs), end(freqs) - 1, minFreqFirst);
         CharFreqNodePtr snd = std::move(freqs.back());
         freqs.pop_back();

         CharFreqNodePtr treeNode = std::make_unique<CharFreqNode>(std::move(fst), std::move(snd));
         freqs.emplace_back(std::move(treeNode));
         std::push_heap(begin(freqs), end(freqs), minFreqFirst);
      }
      return std::move(freqs.back());
   }

   static void huffmanMappingRec(CharFreqNodePtr& tree, CharToCodeMapping& mapping, std::vector<bool>& acc)
   {
      if ('\0' != tree->m_val)
      {
         mapping[tree->m_val] = acc;
      }
      else
      {
         acc.push_back(false);
         huffmanMappingRec(tree->m_left, mapping, acc);
         acc.back() = true;
         huffmanMappingRec(tree->m_right, mapping, acc);
         acc.pop_back();
      }
   }

   static CharToCodeMapping huffmanMapping(CharFreqNodePtr& tree)
   {
      CharToCodeMapping mapping;
      std::vector<bool> accumulator;
      huffmanMappingRec(tree, mapping, accumulator);
      return mapping;
   }

   void HuffmanEncoding::encode(InBitStream& inStream, OutBitStream& out)
   {
      std::string input = readFullStream(inStream);
      CharFreqNodePtr huffmanTree = buildCodingTree(input);
      CharToCodeMapping mapping = huffmanMapping(huffmanTree);

      encodeTree(huffmanTree, out);
      for (char c : input)
      {
         for (bool b : mapping[c])
            out.writeBit(b);
      }
   }


   //-----------------------------------------------------------------------------
   // DECODING
   //-----------------------------------------------------------------------------

   static void decodeOneChar(CharFreqNodePtr& tree, InBitStream& input, OutBitStream& out)
   {
      if ('\0' == tree->m_val)
      {
         out.writeChar(tree->m_val);
      }
      else if (input.readBit())
      {
         decodeOneChar(tree->m_right, input, out);
      }
      else
      {
         decodeOneChar(tree->m_left, input, out);
      }
   }

   void HuffmanEncoding::decode(InBitStream& input, OutBitStream& out)
   {
      CharFreqNodePtr huffmanTree = decodeTree(input);
      while (0 < input.toRead())
         decodeOneChar(huffmanTree, input, out);
   }
}
