#pragma once

#include <iterator>
#include <memory>


namespace algorithm
{
   template<typename T>
   class LinkedList
   {
   public:
      class iterator;
      
   private:
      struct Node
      {
         Node(T const& value, std::unique_ptr<Node> next)
            : m_value(value)
            , m_next(std::move(next)){}

         T m_value;
         std::unique_ptr<Node> m_next;
      };

   public:
      LinkedList() = default;
      ~LinkedList() = default;
      LinkedList(LinkedList const&) = delete;
      LinkedList& operator=(LinkedList const&) = delete;

      iterator begin()
      {
         return iterator(&m_head);
      }

      iterator end()
      {
         return iterator(nullptr);
      }

      void pushFront(T const& t)
      {
         m_head = std::make_unique<Node>(t, std::move(m_head));
      }

      /** Insert the value just before the iterator */
      void insert(T const& t, iterator it)
      {
         if (it == begin())
            return pushFront(t);

         iterator prev = begin();
         for (iterator next = begin(); next != it; prev = next++);
         (*prev.m_node)->m_next = std::make_unique<Node>(t, std::move((*prev.m_node)->m_next));
      }

   public:
      class iterator
         : public std::iterator<std::forward_iterator_tag, T>
      {
      public:
         iterator& operator++()
         {
            std::unique_ptr<Node>& node = *m_node;
            if (node->m_next) m_node = &(node->m_next);
            else m_node = nullptr;
            return *this;
         }

         iterator operator++(int)
         {
            iterator ret = *this;
            ++(*this);
            return ret;
         }

         bool operator==(iterator const& other) const
         {
            return m_node == other.m_node;
         }

         bool operator!=(iterator const& other) const
         {
            return m_node != other.m_node;
         }

         T& operator*() const
         {
            return (*m_node)->m_value;
         }

         std::unique_ptr<Node>& operator->() const
         {
            return (*m_node)->m_value;
         }

      private:
         iterator(std::unique_ptr<Node>* node) : m_node(node) {}
         std::unique_ptr<Node>* m_node;
         friend LinkedList;
      };

   private:
      std::unique_ptr<Node> m_head;
   };
}
