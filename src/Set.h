#pragma once

#include "utils/Algorithms.h"

#include <functional>
#include <memory>
#include <list>
#include <vector>


namespace algorithm
{
   template<typename Node, typename Key>
   class BinaryTreeSetIterator;


   template<
      typename Key,
      typename Compare = std::less<Key>
   >
   class BinaryTreeSet
   {
   private:
      struct Node
      {
         Node(Node* father, Key const& k)
            : m_father(father)
            , m_value(k)
            , m_count(0)
         {}

         Key m_value;
         size_t m_count;
         Node* m_father;
         std::unique_ptr<Node> m_left;
         std::unique_ptr<Node> m_right;

         static Node* sinkLeft(Node* node)
         {
            while (node && node->m_left)
               node = node->m_left.get();
            return node;
         }
      };

      using key_iterator = BinaryTreeSetIterator<Node, Key>;

   public:
      BinaryTreeSet() : BinaryTreeSet(Compare()) {}
      BinaryTreeSet(Compare less) : m_less(less), m_root() {}

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

      size_t size() const
      {
         return m_root ? m_root->m_count : 0;
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

   private:
      Compare m_less;
      std::unique_ptr<Node> m_root;
   };

   //--------------------------------------------------------------------------

   
}

#include "Set.inl.h"
