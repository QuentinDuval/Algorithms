#pragma once
#include <chrono>


namespace algorithm
{
   //-----------------------------------------------------------------------------
   // Allows timing the execution of a function, with perfect forwarding of the arguments
   //-----------------------------------------------------------------------------

   template <typename Duration>
   struct ScopedTimer
   {
      using Clock = std::chrono::high_resolution_clock;
      using TimePoint = std::chrono::time_point < Clock, Duration > ;

      ScopedTimer(Duration& duration) : m_duration(duration), m_start(Clock::now()) {}
      ~ScopedTimer() { m_duration = Clock::now() - m_start; }

   private:
      Duration& m_duration;
      TimePoint m_start;
   };

   template<typename Duration, typename Fct, typename... Args>
   auto time(Duration& duration, Fct&& fct, Args&&... args)
      -> decltype(fct(forward<Args>(args)...))
   {
      ScopedTimer<Duration> timer(duration);
      return fct(forward<Args>(args)...);
   }
}
