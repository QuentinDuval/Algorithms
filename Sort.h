#pragma once

#include <functional>
using namespace std::placeholders;


namespace algorithm
{
   template<typename FwdIter, typename Lesser>
   static bool isSorted(FwdIter first, FwdIter last, Lesser less)
   {
      if (first == last)
         return true;

      auto next = first + 1;
      for (; next != last; ++first, ++next)
      {
         if (less(*next, *first))
            return false;
      }
      return true;
   }

   template<typename Container, typename Lesser>
   static bool isSorted(Container const& cont, Lesser less)
   {
      return isSorted(begin(cont), end(cont), less);
   }

   //--------------------------------------------------------------------------

   struct SelectionSort
   {
      template<typename FwdIter, typename Lesser>
      static void sort(FwdIter first, FwdIter last, Lesser less)
      {
         for (; first != last; ++first)
         {
            auto minIt = std::min_element(first, last, less);
            std::swap(*minIt, *first);
         }
      }

      template<typename Container, typename Lesser>
      static void sort(Container& cont, Lesser less)
      {
         sort(begin(cont), end(cont), less);
      }
   };

   //--------------------------------------------------------------------------

   struct InsertionSort
   {
      template<typename BidirIter, typename Lesser>
      static void sort(BidirIter first, BidirIter last, Lesser less)
      {
         if (first == last)
            return;

         for (auto it = first + 1; it != last; ++it)
         {
            for (auto curr = it; curr != first; --curr)
            {
               auto prev = curr - 1;
               if (!less(*curr, *prev))
                  break;
               
               std::swap(*curr, *prev);
            }
         }
      }

      template<typename Container, typename Lesser>
      static void sort(Container& cont, Lesser less)
      {
         sort(begin(cont), end(cont), less);
      }
   };

   //--------------------------------------------------------------------------

   struct BubbleSort
   {
      template<typename FwdIter, typename Lesser>
      static void sort(FwdIter first, FwdIter last, Lesser less)
      {
         if (first == last)
            return;

         for (auto start = first + 1; start != last; --last)
         {
            bool move = false;
            for (auto prev = start - 1, curr = start; curr != last; ++prev, ++curr)
            {
               if (less(*curr, *prev))
               {
                  std::swap(*prev, *curr);
                  move = true;
               }
            }
            if (!move)
               return;
         }
      }

      template<typename Container, typename Lesser>
      static void sort(Container& cont, Lesser less)
      {
         sort(begin(cont), end(cont), less);
      }
   };

   //--------------------------------------------------------------------------

   struct ThreeWayQuickSort
   {
      template<typename FwdIter, typename Lesser>
      static void sort(FwdIter first, FwdIter last, Lesser less)
      {
         if (first == last)
            return;

         shuffle(first, last);
         sortImpl(first, last, less);
      }

      template<typename Container, typename Lesser>
      static void sort(Container& cont, Lesser less)
      {
         sort(begin(cont), end(cont), less);
      }

   private:
      template<typename FwdIter, typename Lesser>
      static void sortImpl(FwdIter first, FwdIter last, Lesser less)
      {
         if (first == last)
            return;

         auto pivot = *first;
         auto lowEnd = std::partition(first, last,  std::bind(less, _1, pivot));
         auto highIt = std::partition(lowEnd, last, logicalNot(std::bind(less, pivot, _1)));

         sortImpl(first, lowEnd, less);
         sortImpl(highIt, last, less);
      }
   };
}

