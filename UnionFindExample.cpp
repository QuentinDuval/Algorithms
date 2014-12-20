#include "UnionFindExample.h"


namespace algorithm
{
   SocialNetwork::NameAlreadyTaken::NameAlreadyTaken(std::string const& name)
      : std::domain_error("Name already taken: " + name)
   {}

   SocialNetwork::UnknownAccount::UnknownAccount(std::string const& name)
      : std::domain_error("Unknown account: " + name)
   {}

   SocialNetwork::SocialNetwork()
      : m_accountUnion(0)
   {}

   void SocialNetwork::addAccount(AccountId const& name)
   {
      auto ret = m_accounts.insert(std::make_pair(name, 0));
      if (ret.second == false)
         throw NameAlreadyTaken(name);

      ret.first->second = m_accountUnion.addId();
   }

   UnionFind::IdType SocialNetwork::getAccountId(AccountId const& name) const
   {
      auto idIt = m_accounts.find(name);
      if (idIt == m_accounts.end())
         throw UnknownAccount(name);
      return idIt->second;
   }

   void SocialNetwork::connect(AccountId const& a, AccountId const& b)
   {
      m_accountUnion.connect(getAccountId(a), getAccountId(b));
   }

   bool SocialNetwork::connected(AccountId const& a, AccountId const& b)
   {
      return m_accountUnion.connected(getAccountId(a), getAccountId(b));
   }
}
