//---------------------------------------------------------------------------//
//!
//! \file   PyFrensie_NumPyTypeTraits.hpp
//! \author Alex Robinson
//! \brief  The NumPy type traits class specializations.
//!
//---------------------------------------------------------------------------//

#ifndef PYFRENSIE_NUMPY_TYPE_TRAITS_HPP
#define PYFRENSIE_NUMPY_TYPE_TRAITS_HPP

// FRENSIE Includes
#include "PyFrensie_NumPyTypeTraitsDecl.hpp"
#define NO_IMPORT_ARRAY
#include <numpy_include.h>

namespace PyFrensie{

//! The specialization for signed char
template<>
struct NumPyTypeTraits<signed char>
{
  //! Return the NumPy typecode corresponding to signed char
  static inline int typecode()
  { return NPY_BYTE; }

  //! Return the NumPy typecode corresponding to an instance of signed char
  static inline int instanceTypecode( const signed char instance )
  { return NPY_BYTE; }
};

//! The specialization for unsigned char
template<>
struct NumPyTypeTraits<unsigned char>
{
  //! Return the NumPy typecode corresponding to unsigned char
  static inline int typecode()
  { return NPY_UBYTE; }

  //! Return the NumPy typecode corresponding to an instance of unsigned char
  static inline int instanceTypecode( const unsigned char instance )
  { return NPY_UBYTE; }
};

//! The specialization for short
template<>
struct NumPyTypeTraits<short>
{
  //! Return the NumPy typecode corresponding to short
  static inline int typecode()
  { return NPY_SHORT; }

  //! Return the NumPy typecode corresponding to an instance of short
  static inline int instanceTypecode( const short instance )
  { return NPY_SHORT; }
};

//! The specialization for unsigned short
template<>
struct NumPyTypeTraits<unsigned short>
{
  //! Return the NumPy typecode corresponding to unsigned short
  static inline int typecode()
  { return NPY_USHORT; }

  //! Return the NumPy typecode corresponding to an instance of unsigned short
  static inline int instanceTypecode( const unsigned short instance )
  { return NPY_USHORT; }
};

//! The specialization for int
template<>
struct NumPyTypeTraits<int>
{
  //! Return the NumPy typecode corresponding to int
  static inline int typecode()
  { return NPY_INT; }

  //! Return the NumPy typecode corresponding to an instance of int
  static inline int instanceTypecode( const int instance )
  { return NPY_INT; }
};

//! The specialization for unsigned int
template<>
struct NumPyTypeTraits<unsigned int>
{
  //! Return the NumPy typecode corresponding to unsigned int
  static inline int typecode()
  { return NPY_UINT; }

  //! Return the NumPy typecode corresponding to an instance of unsigned int
  static inline int instanceTypecode( const unsigned int instance )
  { return NPY_UINT; }
};

//! The specialization for long
template<>
struct NumPyTypeTraits<long>
{
  //! Return the NumPy typecode corresponding to long
  static inline int typecode()
  { return NPY_LONG; }

  //! Return the NumPy typecode corresponding to an instance of long
  static inline int instanceTypecode( const long instance )
  { return NPY_LONG; }
};

//! The specialization for unsigned long
template<>
struct NumPyTypeTraits<unsigned long>
{
  //! Return the NumPy typecode corresponding to unsigned long
  static inline int typecode()
  { return NPY_ULONG; }

  //! Return the NumPy typecode corresponding to an instance of unsigned long
  static inline int instanceTypecode( const unsigned long instance )
  { return NPY_ULONG; }
};

//! The specialization for long long
template<>
struct NumPyTypeTraits<long long>
{
  //! Return the NumPy typecode corresponding to long long
  static inline int typecode()
  { return NPY_LONGLONG; }

  //! Return the NumPy typecode corresponding to an instance of long long
  static inline int instanceTypecode( const long long instance )
  { return NPY_LONGLONG; }
};

//! The specialization for unsigned long long
template<>
struct NumPyTypeTraits<unsigned long long>
{
  //! Return the NumPy typecode corresponding to unsigned long long
  static inline int typecode()
  { return NPY_ULONGLONG; }

  //! Return the NumPy typecode corresponding to an instance of unsigned long long
  static inline int instanceTypecode( const unsigned long long instance )
  { return NPY_ULONGLONG; }
};

//! The specialization for float
template<>
struct NumPyTypeTraits<float>
{
  //! Return the NumPy typecode corresponding to float
  static inline int typecode()
  { return NPY_FLOAT; }

  //! Return the NumPy typecode corresponding to an instance of float
  static inline int instanceTypecode( const float instance )
  { return NPY_FLOAT; }
};

//! The specialization for double
template<>
struct NumPyTypeTraits<double>
{
  //! Return the NumPy typecode corresponding to double
  static inline int typecode()
  { return NPY_DOUBLE; }

  //! Return the NumPy typecode corresponding to an instance of double
  static inline int instanceTypecode( const double instance )
  { return NPY_DOUBLE; }
};

} // end PyFrensie namespace

#endif // end PYFRENSIE_NUMPY_TYPE_TRAITS_HPP

//---------------------------------------------------------------------------//
// end PyFrensie_NumPyTypeTraits.hpp
//---------------------------------------------------------------------------//
