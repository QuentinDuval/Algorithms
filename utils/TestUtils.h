#pragma once
#include <assert.h>


namespace algorithm
{
   template<typename ExceptionType>
   struct ExceptionChecker
   {
      template<typename Fct, typename... Args>
      void assertE(Fct fct, Args&&... args)
      {
         try {
            fct(std::forward<Args>(args)...);
            assert(false);
         }
         catch (ExceptionType const&) {}
         catch (...) {
            assert(false);
         }
      }
   };
}
