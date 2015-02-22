#pragma once


namespace algorithm
{
   template<
      typename Node,
      typename Key
   >
   class BinaryTreeSetIterator
      : public std::iterator<std::input_iterator_tag, Key>
   {
   public:
      explicit BinaryTreeSetIterator(Node* node) : m_node(node) {}
      ~BinaryTreeSetIterator() = default;

      BinaryTreeSetIterator& operator++()
      {
         //If the node has a left child
         if (m_node->m_right)
         {
            m_node = m_node->m_right.get();
            m_node = Node::sinkLeft(m_node);
            return *this;
         }

         //Otherwise, find first father for which the current node is at left
         Node* father = m_node->m_father;
         while (father && father->m_left.get() != m_node)
         {
            m_node = father;
            father = m_node->m_father;
         }
         m_node = father;
         return *this;
      }

      BinaryTreeSetIterator operator++(int)
      {
         BinaryTreeSetIterator out = *this;
         return ++out;
      }

      bool operator!=(BinaryTreeSetIterator const& rhs) const
      {
         return m_node != rhs.m_node;
      }

      bool operator==(BinaryTreeSetIterator const& rhs) const
      {
         return m_node == rhs.m_node;
      }

      Key const& operator*() const
      {
         return m_node->m_value;
      }

      Node* getNode() const
      {
         return m_node;
      }

   private:
      Node* m_node;
   };
}
