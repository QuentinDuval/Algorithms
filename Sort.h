#pragma once

#include <functional>
#include <random>
using namespace std::placeholders;


namespace algorithm
{
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
         if (first == --last)
            return;

         for (auto it = first; it != last; ++it)
         {
            auto next = it + 1;
            auto curr = it;
            while (curr != first && less(*next, *curr))
            {
               std::swap(*next, *curr);
               --curr, --next;
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

         auto snd = first + 1;
         for (; snd != last; --last)
         {
            bool move = false;
            for (auto p = first, c = snd ; c != last; ++p, ++c)
            {
               if (less(*c, *p))
               {
                  std::swap(*p, *c);
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

   struct QuickSort
   {
      template<typename FwdIter, typename Lesser>
      static void sort(FwdIter first, FwdIter last, Lesser less)
      {
         if (first == last)
            return;

         std::random_device rd;
         std::mt19937 g(rd());
         std::shuffle(first, last, g);
         sort_(first, last, less);
      }

      template<typename Container, typename Lesser>
      static void sort(Container& cont, Lesser less)
      {
         sort(begin(cont), end(cont), less);
      }

   private:
      template<typename FwdIter, typename Lesser>
      static void sort_(FwdIter first, FwdIter last, Lesser less)
      {
         if (first == last)
            return;

         auto mid = std::partition(first, last, std::bind(less, _1, *first));
         sort_(first, mid, less);
         sort_(mid + 1, last, less);
      }
   };
}

