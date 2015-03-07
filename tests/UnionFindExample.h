#pragma once

#include "UnionFind.h"
#include "utils/NonCopyable.h"

#include <exception>
#include <memory>
#include <string>
#include <unordered_map>


namespace algorithm
{
   /** Example with people joining a network (This example could be made generic) */
   class SocialNetwork
      : public utils::NonCopyable
   {
   public:
      using AccountId = std::string;
      using AccountMap = std::unordered_map<std::string, UnionFind::IdType>;

   public:
      SocialNetwork();
      ~SocialNetwork() = default;

      void addAccount(AccountId const&); /* Basic guaranty */
      void connect   (AccountId const&, AccountId const&); /* Strong guaranty */
      bool connected (AccountId const&, AccountId const&); /* Strong guaranty */

   public:
      class NameAlreadyTaken : std::domain_error
      {
         NameAlreadyTaken(std::string const&);
         friend SocialNetwork;
      };

      class UnknownAccount : std::domain_error
      {
         UnknownAccount(std::string const&);
         friend SocialNetwork;
      };

   private:
      UnionFind::IdType getAccountId(AccountId const&) const;

   private:
      UnionFind   m_accountUnion;
      AccountMap  m_accounts;
   };
}
