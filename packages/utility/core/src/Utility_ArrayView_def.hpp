//---------------------------------------------------------------------------//
//!
//! \file   Utility_ArrayView_def.hpp
//! \author Alex Robinson
//! \brief  The array view class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ARRAY_VIEW_DEF_HPP
#define UTILITY_ARRAY_VIEW_DEF_HPP

namespace Utility{

// Default constructor
template<typename T>
ArrayView<T>::ArrayView()
  : View<T*>()
{ /* ... */ }

// Iterator constructor
template<typename T>
ArrayView<T>::ArrayView( T* start, T* end )
  : View<T*>( start, end )
{ /* ... */ }

// Range constructor
template<typename T>
ArrayView<T>::ArrayView( T* array_start, const size_type array_size )
  : View<T*>( array_start, array_start + array_size )
{ /* ... */ }

// Vector constructor
template<typename T>
ArrayView<T>::ArrayView( std::vector<T>& vector )
  : ArrayView<T>( vector.data(), vector.size() )
{ /* ... */ }

// Const vector constructor
template<typename T>
ArrayView<T>::ArrayView( const std::vector<typename std::enable_if<std::is_const<T>::value,T>::type>& vector )
  : ArrayView<T>( vector.data(), vector.size() )
{ /* ... */ }

// Array constructor
template<typename T>
template<typename N>
ArrayView<T>::ArrayView( std::array<T,N>& array )
  : ArrayView<T>( array.data(), N )
{ /* ... */ }

// Const array constructor
template<typename T>
template<typename N>
ArrayView<T>::ArrayView( const std::array<typename std::enable_if<std::is_const<T>::value,T>::type,N>& array )
  : ArrayView<T>( array.data(), N )
{ /* ... */ }

// Copy constructor
template<typename T>
ArrayView<T>::ArrayView( ArrayView<T>& other_view )
  : View<T*>( other_view )
{ /* ... */ }

// Const array view copy constructor
template<typename T>
template<typename T2>
ArrayView<T>::ArrayView( const ArrayView<typename std::enable_if<std::is_const<T>::value,T2>::type>& other_view )
  : View<T*>( other_view )
{ /* ... */ }

// Assignment operator
template<typename T>
ArrayView<T>& ArrayView<T>::operator=( ArrayView<T>& other_view )
{
  if( this != &other_view )
    View<T*>::operator=( other_view );

  return *this;
}

// Const view assignment operator
template<typename T>
template<typename T2>
ArrayView<T>& ArrayView<T>::operator=( const ArrayView<typename std::enable_if<std::is_const<T>::value,T2>::type>& other_view )
{
  if( this != &other_view )
    View<T*>::operator=( other_view );

  return *this;
}

// Return a sub-array view
template<typename T>
ArrayView<T> ArrayView<T>::operator( const size_type offset, const size_type size ) const
{
  return ArrayView<T>( &this->at( offset ), size );
}

// Return a const array view
template<typename T>
ArrayView<T>::ArrayView<const typename std::remove_const<T>::type> toConst() const
{
  return ArrayView<const typename std::remove_const<T>::type>( this->begin(), this->end() );
}

// Implicitly convert to a const array view
template<typename T>
ArrayView<T>::operator ArrayView<const typename std::remove_const<T>::type>() const
{
  return this->toConst();
}
  
} // end Utility namespace

#endif // end UTILITY_ARRAY_VIEW_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_ArrayView_def.hpp
//---------------------------------------------------------------------------//

