// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <iomanip>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
        throw out_of_range("Vector size too large");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }


  TDynamicVector(T* arr, size_t s) : sz(s), pMem(new T[sz])
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    if (sz > MAX_VECTOR_SIZE)
        throw out_of_range("Vector size too large");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }


  TDynamicVector(const TDynamicVector& v)
  {
      sz = v.sz;
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
  }


  TDynamicVector(TDynamicVector&& v) noexcept : sz(0), pMem(nullptr)
  {
      swap(*this, v);
  }


  ~TDynamicVector()
  {
      delete[] pMem;
  }


  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this != &v) {
          TDynamicVector tmp(v);
          swap(*this, tmp);
      }
      return *this;
  }


  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this != &v) {
          swap(*this, v);
      }
      return *this; 
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind]
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= sz)
          throw out_of_range("Index out of range");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz)
          throw out_of_range("Index out of range");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) return false;
      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i]) return false;
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++)
          tmp.pMem[i] = pMem[i] + val;
      return tmp;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++)
          tmp.pMem[i] = pMem[i] - val;
      return tmp;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++)
          tmp.pMem[i] = pMem[i] * val;
      return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw out_of_range("sz != v.sz");

      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++)
          tmp.pMem[i] = pMem[i] + v.pMem[i];
      return tmp;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw out_of_range("sz != v.sz");

      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++)
          tmp.pMem[i] = pMem[i] - v.pMem[i];
      return tmp;
  }
  TDynamicVector operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (sz != v.sz)
          throw out_of_range("sz != v.sz");

      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++)
          tmp.pMem[i] = pMem[i] * v.pMem[i];
      return tmp;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    if (s > MAX_MATRIX_SIZE)
        throw out_of_range("Matrix size too large");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

      T& at(size_t i, size_t j)
    {
        if (i >= sz || j >= sz)
            throw out_of_range("too lagre index");
        if (i < 0 || j < 0)
            throw out_of_range("negative index");
        return pMem[i][j];
    }

    const T& at(size_t i, size_t j) const
    {
        if (i >= sz || j >= sz)
            throw out_of_range("too lagre index");
        if (i < 0 || j < 0)
            throw out_of_range("negative index");
        return pMem[i][j];
    }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  size_t size() const noexcept { return sz; }

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz) return false;
      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != m.pMem[i]) return false;
      }
      return true;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix tmp(sz);
      for (size_t i = 0; i < sz; i++)
          tmp[i] = pMem[i] * val;
      return tmp;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != v.size())
          throw out_of_range("Matrix and vector sizes don't match");

      TDynamicVector<T> result(sz);
      for (size_t i = 0; i < sz; i++)
          result[i] = pMem[i] * v;
      return result;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw out_of_range("Matrix sizes don't match for addition");

      TDynamicMatrix tmp(sz);
      for (size_t i = 0; i < sz; i++)
          tmp[i] = pMem[i] + m.pMem[i];
      return tmp;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw out_of_range("Matrix sizes don't match for addition");

      TDynamicMatrix tmp(sz);
      for (size_t i = 0; i < sz; i++)
          tmp[i] = pMem[i] - m.pMem[i];
      return tmp;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw out_of_range("Matrix sizes don't match for addition");

      TDynamicMatrix tmp(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              T sum = T();
              for (size_t k = 0; k < sz; k++) {
                  sum += pMem[i][k] * m.pMem[k][j];
              }
              tmp[i][j] = sum;
          }
      }
      return tmp;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          istr >> v.pMem[i];
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++) {
          for (size_t j = 0; j < v.sz; j++) {
              ostr << setw(5) << v.pMem[i][j] << " ";
          }
          ostr << endl;
      }
      return ostr;
  }
};

#endif
