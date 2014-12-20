#pragma once

#include "NonCopyable.h"
#include <exception>
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

      IdType   addId       ();                     /*Basic guaranty*/
      int      count       () const;               /*noexcept*/
      bool     connect     (IdType a, IdType b);   /*Strong guaranty*/
      bool     connected   (IdType a, IdType b);   /*Strong guaranty*/

   public:
      class InvalidId : public std::domain_error
      {
         InvalidId(IdType);
         friend UnionFind;
      };

   private:
      IdType getRoot (IdType a);
      void   linkTo  (IdType a, IdType b);

   private:
      std::vector<IdType> m_fathers;
      std::vector<IdType> m_weights;
   };
}
