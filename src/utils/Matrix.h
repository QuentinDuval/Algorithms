#pragma once
#include <vector>


namespace algorithm
{
   template<typename T>
   class Matrix
   {
   public:
      Matrix(size_t w, size_t h, T const& val)
         : m_width(w)
         , m_height(h)
         , m_data(w * h, val)
      {}

      Matrix(size_t w, size_t h)
         : Matrix(w, h, T())
      {}

      Matrix(size_t w, size_t h, std::initializer_list<T> const& init)
         : Matrix(w, h)
      {
         size_t i = 0;
         for (auto d : init)
         {
            at(i % m_width, i / m_width) = d;
            ++i;
         }
      }

      ~Matrix() = default;

      size_t width()  const { return m_width; }
      size_t height() const { return m_height; }

      T&       at(size_t x, size_t y)        { return m_data[x + m_width * y]; }
      T const& at(size_t x, size_t y) const  { return m_data[x + m_width * y]; }

   private:
      size_t m_width;
      size_t m_height;
      std::vector<T> m_data;
   };
}
