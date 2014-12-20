#include "UnionFind.h"
#include "Utils.h"

#include <algorithm>

namespace algorithm
{
   UnionFind::UnionFind(size_t elementCount)
      : m_fathers(elementCount, 0)
      , m_weights(elementCount, 1)
   {
      generate(m_fathers, 0, [](IdType const& in){ return in + 1; });
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

   UnionFind::IdType UnionFind::getRoot(IdType a)
   {
      std::vector<IdType> path;
      auto root = a;
      for (; root != m_fathers[root]; root = m_fathers[root])
         path.push_back(root);
      
      for (auto i : path)
         m_fathers[i] = root;
      ++(m_weights[root]);
      return root;
   }
}
