#pragma once

#include "utils/Algorithms.h"

#include <functional>
#include <memory>
#include <list>
#include <vector>


namespace algorithm
{
   template<
      typename Node,
      typename Key,
      typename Compare = std::less<Key>
   >
   class AbstractBinaryTreeSet
   {
   protected:
      class key_iterator;

   public:
      AbstractBinaryTreeSet() : AbstractBinaryTreeSet(Compare()) {}
      AbstractBinaryTreeSet(Compare less) : m_less(less), m_root() {}

      key_iterator begin() const
      {
         Node* b = Node::sinkLeft(m_root.get());
         return key_iterator(b);
      }

      key_iterator end() const
      {
         return key_iterator(nullptr);
      }

      key_iterator find(Key const& key) const
      {
         Node* node = m_root.get();
         while (node)
         {
            if (m_less(key, node->m_value))
               node = node->m_left.get();
            else if (m_less(node->m_value, key))
               node = node->m_right.get();
            else
               return key_iterator(node);
         }
         return end();
      }

      bool contains(Key const& key) const
      {
         return end() != find(key);
      }

      size_t size() const
      {
         return m_root ? m_root->m_count : 0;
      }

   protected:
      std::unique_ptr<Node>& incomingLink(Node& node)
      {
         if (!node.m_father)
            return m_root;
         if (node.m_father->m_left.get() == &node)
            return node.m_father->m_left;
         return node.m_father->m_right;
      }

      static void incrementCount_(Node* node, size_t incr = 1)
      {
         while (node)
         {
            node->m_count += incr;
            node = node->m_father;
         }
      }

   protected:
      Compare m_less;
      std::unique_ptr<Node> m_root;
   };

   //--------------------------------------------------------------------------

   template<typename Key>
   struct AbstractNode
   {
      AbstractNode(Key const& k) : m_value(k), m_count(0) {}
      Key m_value;
      size_t m_count;
   };

   template<typename Key>
   struct BstNode : AbstractNode<Key>
   {
      BstNode(BstNode* father, Key const& k)
         : AbstractNode<Key>(k), m_father(father) {}

      BstNode* m_father;
      std::unique_ptr<BstNode> m_left;
      std::unique_ptr<BstNode> m_right;

      static BstNode* sinkLeft(BstNode* node)
      {
         while (node && node->m_left)
            node = node->m_left.get();
         return node;
      }
   };

   template<
      typename Key,
      typename Compare = std::less<Key>
   >
   class BinaryTreeSet
      : public AbstractBinaryTreeSet<BstNode<Key>, Key, Compare>
   {
   private:
      using Node = BstNode<Key>;

   public:
      BinaryTreeSet() : BinaryTreeSet(Compare()) {}
      BinaryTreeSet(Compare less) : AbstractBinaryTreeSet(less) {}

      bool insert(Key const& key)
      {
         return insert_(nullptr, m_root, key);
      }

      void erase(key_iterator it)
      {
         if (it == end())
            return;

         Node& node = *(it.getNode());
         erase_(incomingLink(node), node);
      }

      void erase(key_iterator first, key_iterator last)
      {
         auto prev = begin();
         auto start = std::distance(begin(), first);
         for (decltype(start) i = 0; i < start - 1; ++i)
            ++prev;

         while (first != last)
         {
            erase(first);
            first = start ? prev++ : begin();
         }
      }

   private:
      bool insert_(Node* father, std::unique_ptr<Node>& currentNode, Key const& key)
      {
         if (!currentNode)
         {
            currentNode = std::make_unique<Node>(father, key);
            incrementCount_(currentNode.get());
            return true;
         }
         else if (m_less(key, currentNode->m_value))
         {
            return insert_(currentNode.get(), currentNode->m_left, key);
         }
         else if (m_less(currentNode->m_value, key))
         {
            return insert_(currentNode.get(), currentNode->m_right, key);
         }
         return false;
      }

      void erase_(std::unique_ptr<Node>& incomingLink, Node& node)
      {
         //If two children, go right, sink all way down left, swap these nodes, then delete
         if (node.m_right && node.m_left)
         {
            Node* nextHigher = Node::sinkLeft(node.m_right.get());
            std::swap(nextHigher->m_value, node.m_value);
            erase(key_iterator(nextHigher));
            return;
         }

         //Otherwise, replace the incoming node from father:
         Node* father = node.m_father;
         if (node.m_left)
         {
            node.m_left->m_father = father;
            incomingLink = move(node.m_left);
         }
         else if (node.m_right)
         {
            node.m_right->m_father = father;
            incomingLink = move(node.m_right);
         }
         else
         {
            incomingLink.reset();
         }
         incrementCount_(father, -1);
      }
   };

   //--------------------------------------------------------------------------

   template<typename Key>
   struct RbtNode : AbstractNode<Key>
   {
      RbtNode(RbtNode* father, Key const& k)
         : AbstractNode<Key>(k)
         , m_father(father)
         , m_incomingRed(father ? true : false)
      {}

      RbtNode* m_father;
      bool m_incomingRed;
      std::unique_ptr<RbtNode> m_left;
      std::unique_ptr<RbtNode> m_right;

      static RbtNode* sinkLeft(RbtNode* node)
      {
         while (node && node->m_left)
            node = node->m_left.get();
         return node;
      }
   };

   template<
      typename Key,
      typename Compare = std::less<Key>
   >
   class RedBlackTreeSet
      : public AbstractBinaryTreeSet<RbtNode<Key>, Key, Compare>
   {
   private:
      using Node = RbtNode<Key>;

   public:
      RedBlackTreeSet() : RedBlackTreeSet(Compare()) {}
      RedBlackTreeSet(Compare less) : AbstractBinaryTreeSet(less) {}

      bool insert(Key const& key)
      {
         return insert_(nullptr, m_root, key);
      }

   private:
      bool insert_(Node* father, std::unique_ptr<Node>& currentNode, Key const& key)
      {
         if (!currentNode)
         {
            currentNode = std::make_unique<Node>(father, key);
            incrementCount_(currentNode.get());
            return true;
         }

         bool modified = false;
         if (m_less(key, currentNode->m_value))
         {
            modified = insert_(currentNode.get(), currentNode->m_left, key);
         }
         else if (m_less(currentNode->m_value, key))
         {
            modified = insert_(currentNode.get(), currentNode->m_right, key);
         }
         if (!modified)
            return false;

         if (!isRedLinkTo(currentNode->m_left) && isRedLinkTo(currentNode->m_right))
         {
            rotateLeft(currentNode, currentNode->m_right);
         }
         if (isRedLinkTo(currentNode->m_left) && currentNode->m_left && isRedLinkTo(currentNode->m_left->m_left))
         {
            rotateRight(currentNode, currentNode->m_left);
         }
         if (isRedLinkTo(currentNode->m_left) && isRedLinkTo(currentNode->m_right))
         {
            switchColors(currentNode);
         }
         return true;
      }

      bool isRedLinkTo(std::unique_ptr<Node>& node) const
      {
         if (!node) return false;
         return node->m_incomingRed;
      }

      void rotateLeft(std::unique_ptr<Node>& topNode, std::unique_ptr<Node>& rightChild)
      {
         std::unique_ptr<Node> newTop = std::move(rightChild);
         std::unique_ptr<Node> oldTop = std::move(topNode);
         newTop->m_father = oldTop->m_father;
         oldTop->m_father = newTop.get();
         std::swap(oldTop->m_count, newTop->m_count);

         if (newTop->m_left)
         {
            oldTop->m_right = std::move(newTop->m_left);
            oldTop->m_right->m_father = oldTop.get();
         }
         
         newTop->m_left = std::move(oldTop);
         topNode = std::move(newTop);
      }

      void rotateRight(std::unique_ptr<Node>& topNode, std::unique_ptr<Node>& leftChild)
      {
         std::unique_ptr<Node> newTop = std::move(leftChild);
         std::unique_ptr<Node> oldTop = std::move(topNode);
         newTop->m_father = oldTop->m_father;
         oldTop->m_father = newTop.get();
         std::swap(oldTop->m_count, newTop->m_count);

         if (newTop->m_right)
         {
            oldTop->m_left = std::move(newTop->m_right);
            oldTop->m_left->m_father = oldTop.get();
         }

         newTop->m_right = std::move(oldTop);
         topNode = std::move(newTop);
      }

      void switchColors(std::unique_ptr<Node>& node)
      {
         node->m_left->m_incomingRed = false;
         node->m_right->m_incomingRed = false;
         node->m_incomingRed = true;
      }
   };
}

#include "Set.inl.h"
