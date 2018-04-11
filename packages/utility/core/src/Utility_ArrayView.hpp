//---------------------------------------------------------------------------//
//!
//! \file   Utility_ArrayView.hpp
//! \author Alex Robinson
//! \brief  The array view class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ARRAY_VIEW_HPP
#define UTILITY_ARRAY_VIEW_HPP

// Std Lib Includes
#include <vector>
#include <array>
#include <tuple>
#include <utility>

// FRENSIE Includes
#include "Utility_View.hpp"
#include "Utility_TypeNameTraits.hpp"
#include "Utility_TypeTraits.hpp"

namespace Utility{

class Slice;

/*! The array view class
 *
 * This class was inspired by the Teuchos::ArrayView class found in
 * the Trilinos Software package
 * (https://trilinos.org/docs/dev/packages/teuchos/doc/html/index.html).
 * \ingroup view
 */
template<typename T>
class ArrayView : public View<T*>
{

public:

  //! Default constructor
  ArrayView();

  //! Iterator constructor
  ArrayView( T* start, T* end );

  //! Range constructor
  ArrayView( T* array_start, const typename ArrayView<T>::size_type array_size );

  //! Vector constructor
  explicit ArrayView( std::vector<T>& vector );

  //! Const vector constructor
  template<typename U>
  explicit ArrayView( const std::vector<U>& vector );

  //! Array constructor
  template<size_t N>
  explicit ArrayView( std::array<T,N>& array );

  //! Const array constructor
  template<typename U,size_t N>
  explicit ArrayView( const std::array<U,N>& array );

  //! Copy constructor
  ArrayView( const ArrayView<T>& other_view );

  //! Const array view copy constructor
  template<typename U>
  ArrayView( const ArrayView<U>& other_view );

  //! Assignment operator
  ArrayView<T>& operator=( const ArrayView<T>& other_view );

  //! Const view assignment operator
  template<typename U>
  ArrayView<T>& operator=( const ArrayView<U>& other_view );

  //! Destructor
  ~ArrayView()
  { /* ... */ }

  //! Fill the array with values
  void fill( const T& value );

  //! Return a sub-array view
  ArrayView<T> operator()( const typename ArrayView<T>::size_type offset,
                           const typename ArrayView<T>::size_type size ) const;

  //! Return a sub-array view
  ArrayView<T> operator|( const Utility::Slice& slice ) const;

  //! Return a const array view
  ArrayView<const typename std::remove_const<T>::type> toConst() const;

  //! Implicitly convert to a const array view
  operator ArrayView<const typename std::remove_const<T>::type>() const;

  //! Return a std::vector
  std::vector<typename std::remove_const<T>::type> toVector() const;

  //! Implicitly convert to a std::vector
  operator std::vector<typename std::remove_const<T>::type>() const;

  //! Return a direct pointer to the memory array used internally
  typename View<T*>::pointer data() const;
};

/*! The slice class
 *
 * Use this class when overloading the | operator to create an ArrayView
 * of a slice of an array
 * \ingroup view
 */
class Slice
{
public:

  //! Constructor
  Slice( const size_t offset, const size_t extent )
    : d_offset( offset ),
      d_extent( extent )
  { /* ... */ }

  //! Tuple constructor
  template<template<typename,typename> class Tuple,
           typename T,
           typename U>
  Slice( const Tuple<T,U>& tuple )
    : d_offset( std::get<0>( tuple ) ),
      d_extent( std::get<1>( tuple ) )
  { /* ... */ }

  //! Tuple move constructor
  template<template<typename,typename> class Tuple,
           typename T,
           typename U>
  Slice( Tuple<T,U>&& tuple )
    : d_offset( std::move( std::get<0>( tuple ) ) ),
      d_extent( std::move( std::get<1>( tuple ) ) )
  { /* ... */ }

  //! C-array constructor
  Slice( const size_t offset_extent[2] )
    : d_offset( offset_extent[0] ),
      d_extent( offset_extent[1] )
  { /* ... */ }

  //! Destructor
  ~Slice()
  { /* ... */ }

  //! Get the offset
  size_t offset() const
  { return d_offset; }

  //! Get the extent
  size_t extent() const
  { return d_extent; }

private:

  // The offset
  size_t d_offset;

  // the extent
  size_t d_extent;
};

/*! Create a slice object
 * \ingroup view
 */
inline Slice slice( size_t offset, size_t extent )
{
  return Slice( offset, extent );
}

/*! Create an array view of a std::vector
 * \ingroup view
 */
template<typename T>
inline ArrayView<T> arrayView( std::vector<T>& vector )
{
  return ArrayView<T>( vector );
}

/*! Create a const array view of a std::vector
 * \ingroup view
 */
template<typename T>
inline ArrayView<const T> arrayView( const std::vector<T>& vector )
{
  return ArrayView<const T>( vector );
}

/*! Create a const array view of a std::vector
 * \ingroup view
 */
template<typename T>
inline ArrayView<const T> arrayViewOfConst( const std::vector<T>& vector )
{
  return ArrayView<const T>( vector );
}

/*! Create an array view of a std::array
 * \ingroup view
 */
template<typename T, size_t N>
inline ArrayView<T> arrayView( std::array<T,N>& array )
{
  return ArrayView<T>( array );
}

/*! Create a const array view of a std::array
 * \ingroup view
 */
template<typename T, size_t N>
inline ArrayView<const T> arrayView( const std::array<T,N>& array )
{
  return ArrayView<const T>( array );
}

/*! Create a const array view of a std::array
 * \ingroup view
 */
template<typename T, size_t N>
inline ArrayView<const T> arrayViewOfConst( const std::array<T,N>& array )
{
  return ArrayView<const T>( array );
}

/*! Const cast array view
 * \ingroup view
 */
template<typename T2, typename T1>
inline ArrayView<T2> av_const_cast( const ArrayView<T1>& array_view )
{
  return ArrayView<T2>( const_cast<T2*>( array_view.begin() ),
                        array_view.size() );
}

/*! Reinterpret cast array view
 * \ingroup view
 */
template<typename T2, typename T1>
inline ArrayView<T2> av_reinterpret_cast( const ArrayView<T1>& array_view )
{
  return ArrayView<T2>( reinterpret_cast<T2*>( const_cast<ArrayView<T1>&>(array_view).begin() ),
                        reinterpret_cast<T2*>( const_cast<ArrayView<T1>&>(array_view).end() ) );
}

/*! \brief Partial specialization of IsSequenceContainerWithContiguousMemory
 * for Utility::ArrayView
 * \ingroup view
 * \ingroup type_traits
 */
template<typename T>
struct IsSequenceContainerWithContiguousMemory<Utility::ArrayView<T> > : public std::true_type
{ /* ... */ };

/*! Partial specialization of ToStringTraits for Utility::ArrayView
 * \ingroup view
 * \ingroup to_string_traits
 */
template<typename T>
struct ToStringTraits<Utility::ArrayView<T> > : public ToStringTraits<Utility::View<T*> >
{ /* ... */ };

/*! Partial specialization of Utility::TypeNameTraits for Utility::ArrayView
 * \ingroup view
 * \ingroup type_name_traits
 */
template<typename T>
struct TypeNameTraits<Utility::ArrayView<T> >
{
  //! Get the type name
  static inline std::string name()
  { return std::string("Utility::ArrayView<") + Utility::typeName<T>()+">"; }
};

/*! Partial specialization of ComparisonTraits for Utility::ArrayView
 * \ingroup view
 * \ingroup comparison_traits
 */
template<typename T>
struct ComparisonTraits<Utility::ArrayView<T> > : public ComparisonTraits<Utility::View<T*> >
{ /* ... */ };

} // end Utility namespace

namespace std{

//! Partial specialization of common_type for Utility::ArrayView
template<typename T>
struct common_type<Utility::ArrayView<T>,Utility::ArrayView<const T> >
{
  typedef Utility::ArrayView<const T> type;
};

//! Partial specialization of common_type for Utility::ArrayView
template<typename T>
struct common_type<Utility::ArrayView<const T>,Utility::ArrayView<T> >
{
  typedef Utility::ArrayView<const T> type;
};

} // end std namespace

//---------------------------------------------------------------------------//
// Template includes
//---------------------------------------------------------------------------//

#include "Utility_ArrayView_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_ARRAY_VIEW_HPP

//---------------------------------------------------------------------------//
// end Utility_ArrayView.hpp
//---------------------------------------------------------------------------//
