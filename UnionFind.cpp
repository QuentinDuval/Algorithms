#include "UnionFind.h"

#include "Algorithms.h"
#include "Utils.h"


namespace algorithm
{
   UnionFind::UnionFind(IdType elementCount)
      : m_fathers(elementCount, 0)
      , m_weights(elementCount, 1)
   {
      generate(m_fathers, 0, [](IdType in){ return in + 1; });
   }

   UnionFind::IdType UnionFind::addId()
   {
      m_weights.push_back(1);
      m_fathers.push_back(m_fathers.size());
      return m_fathers.back();
   }

   int UnionFind::count() const
   {
      int count = 0;
      for (size_t i = 0; i < m_fathers.size(); ++i)
         if (i == m_fathers[i])
            ++count;
      return count;
   }

   bool UnionFind::connect(IdType a, IdType b)
   {
      IdType ra = getRoot(a);
      IdType rb = getRoot(b);
      if (ra == rb)
         return false;

      if (m_weights[ra] < m_weights[rb])
         linkTo(ra, rb);
      else
         linkTo(rb, ra);
      return true;
   }

   bool UnionFind::connected(IdType a, IdType b)
   {
      return getRoot(a) == getRoot(b);
   }

   void UnionFind::linkTo(IdType ra, IdType rb)
   {
      m_fathers[ra] = rb;
      m_weights[rb] += m_weights[ra];
   };

   UnionFind::IdType UnionFind::getRoot(IdType current)
   {
      if (current >= m_fathers.size())
         throw InvalidId(current);

      std::vector<IdType> path;
      auto root = current;
      for (; root != m_fathers[root]; root = m_fathers[root])
         path.push_back(root);
      
      for (auto i : path)
         m_fathers[i] = root;
      ++(m_weights[root]);
      return root;
   }

   UnionFind::InvalidId::InvalidId(IdType id)
      : std::domain_error("Invalid id: " + toString(id))
   {}
}
