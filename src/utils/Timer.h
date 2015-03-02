#pragma once
#include <chrono>
#include <iostream>


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

   //-----------------------------------------------------------------------------
   // Helpers to display the results
   //-----------------------------------------------------------------------------

   template<typename Unit = std::milli, typename Fct, typename... Args>
   void showTime(std::ostream& output, Fct&& fct, Args&&... args)
   {
      std::chrono::duration<double, Unit> duration;
      time(duration, fct, std::forward<Args>(args)...);
      output << " - Time spent: " << duration.count() << std::endl;
   }

   template<typename Unit = std::milli, typename Fct, typename... Args>
   void showTimeLog(std::ostream& output, std::string const& text, Fct&& fct, Args&&... args)
   {
      std::chrono::duration<double, Unit> duration;
      time(duration, fct, std::forward<Args>(args)...);
      output << " - Time spent (" << text << "): " << duration.count() << std::endl;
   }
}
