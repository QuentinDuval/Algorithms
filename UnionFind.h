#pragma once
#include "NonCopyable.h"

#include <vector>


namespace algorithm
{
   //TODO - Add policies to choose the synchronization mechanism?
   //TODO - Add a good example with people joining a social network (with map to connect to ids)
   class UnionFind
      : public NonCopyable
   {
   public:
      using IdType = std::size_t;

   public:
      UnionFind(IdType elementCount);
      ~UnionFind() = default;

      int  count     () const;
      bool connect   (IdType a, IdType b);
      bool connected (IdType a, IdType b);
      
      //TODO - Add boundary checks
      //TODO - Add the possiblity to add new ids (non-connected ones)

   private:
      IdType getRoot (IdType a);
      void   linkTo  (IdType a, IdType b);

   private:
      std::vector<IdType> m_fathers;
      std::vector<IdType> m_weights;
   };
}
