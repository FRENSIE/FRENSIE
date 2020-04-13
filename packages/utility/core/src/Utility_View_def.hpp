//---------------------------------------------------------------------------//
//!
//! \file   Utility_View_def.hpp
//! \author Alex Robinson
//! \brief  The view class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_VIEW_DEF_HPP
#define UTILITY_VIEW_DEF_HPP

// Std Lib Includes
#include <iterator>
#include <type_traits>

namespace Utility{

namespace Details{

// The iterator helper class used to adapt all iterator types to the
// RandomAccessIterator concept.
template<typename Iterator, typename Enabled = void>
struct IteratorHelper
{ 
  static inline typename std::iterator_traits<Iterator>::reference offsetValue( Iterator start_iterator, typename std::iterator_traits<Iterator>::difference_type n )
  {
    Iterator offset_iterator = start_iterator;
    std::advance( offset_iterator, n );

    return *offset_iterator;
  }

  static inline typename std::add_const<typename std::iterator_traits<Iterator>::reference>::type constOffsetValue( Iterator start_iterator, typename std::iterator_traits<Iterator>::difference_type n )
  {
    Iterator offset_iterator = start_iterator;
    std::advance( offset_iterator, n );

    return *offset_iterator;
  }
};

// The iterator helper class partial specialization for random access iterators
template<typename Iterator>
struct IteratorHelper<Iterator,typename std::enable_if<std::is_same<typename std::iterator_traits<Iterator>::iterator_category,std::random_access_iterator_tag>::value>::type>
{
  static inline typename std::iterator_traits<Iterator>::reference offsetValue( Iterator start_iterator, typename std::iterator_traits<Iterator>::difference_type n )
  { return start_iterator[n]; }

  static inline typename std::add_const<typename std::iterator_traits<Iterator>::reference>::type constOffsetValue( Iterator start_iterator, typename std::iterator_traits<Iterator>::difference_type n )
  { return start_iterator[n]; }
};
  
} // end Details namespace

// Default constructor
template<typename Iterator>
View<Iterator>::View()
  : d_start_iterator(),
    d_end_iterator( d_start_iterator )
{ /* ... */ }

// Iterator constructor
/*! \details The OtherIterator type must be implicitly convertable to
 * the Iterator type (e.g. std::iterator to std::const_iterator).
 */
template<typename Iterator>
template<typename OtherIterator>
View<Iterator>::View( const OtherIterator& start, const OtherIterator& end )
  : d_start_iterator( start ),
    d_end_iterator( end )
{ /* ... */ }

// Copy constructor
template<typename Iterator>
View<Iterator>::View( const View<Iterator>& other_view )
  : d_start_iterator( other_view.d_start_iterator ),
    d_end_iterator( other_view.d_end_iterator )
{ /* ... */ }

// Copy constructor
/*! \details This constructor will only be defined if Iterator is a const
 * iterator type. The OtherIterator type must be implicitly convertable to
 * the Iterator type (e.g. std::iterator to std::const_iterator).
 */
template<typename Iterator>
template<typename OtherIterator>
View<Iterator>::View( const View<OtherIterator>& other_view )
  : d_start_iterator( other_view.begin() ),
    d_end_iterator( other_view.end() )
{ /* ... */ }

// Assignment operator
template<typename Iterator>
View<Iterator>& View<Iterator>::operator=( const View<Iterator>& other_view )
{
  if( this != &other_view )
  {
    d_start_iterator = other_view.d_start_iterator;
    d_end_iterator = other_view.d_end_iterator;
  }

  return *this;
}

// Assignment operator
/*! \details This operator will only be defined if Iterator is a const
 * iterator type. The OtherIterator type must be implicitly convertable to
 * the Iterator type (e.g. std::iterator to std::const_iterator).
 */
template<typename Iterator>
template<typename OtherIterator>
View<Iterator>& View<Iterator>::operator=( const View<OtherIterator>& other_view )
{
  d_start_iterator = other_view.begin();
  d_end_iterator = other_view.end();

  return *this;
}

// Destructor
template<typename Iterator>
View<Iterator>::~View()
{ /* ... */ }

// Get the size of the view
template<typename Iterator>
auto View<Iterator>::size() const -> size_type
{
  if( d_start_iterator != d_end_iterator )
    return std::distance( d_start_iterator, d_end_iterator );
  else
    return 0;
}

// Check if the view is empty
template<typename Iterator>
bool View<Iterator>::empty() const
{
  return d_start_iterator == d_end_iterator;
}

// Element access
template<typename Iterator>
auto View<Iterator>::operator[]( const size_type index ) const -> reference
{
  return Details::IteratorHelper<Iterator>::offsetValue( d_start_iterator, index );
}

// Element access
template<typename Iterator>
auto View<Iterator>::at( const size_type index ) const -> reference
{
  return Details::IteratorHelper<Iterator>::offsetValue( d_start_iterator, index );
}

// Access first element
template<typename Iterator>
auto View<Iterator>::front() const -> reference
{
  return *d_start_iterator;
}

// Access last element
template<typename Iterator>
auto View<Iterator>::back() const -> reference
{
  return Details::IteratorHelper<Iterator>::offsetValue( d_start_iterator, this->size()-1 );
}

// Return iterator to beginning
template<typename Iterator>
auto View<Iterator>::begin() const -> iterator
{
  return d_start_iterator;
}

// return iterator to end
template<typename Iterator>
auto View<Iterator>::end() const -> iterator
{
  return d_end_iterator;
}

// Return const iterator to beginning
template<typename Iterator>
auto View<Iterator>::cbegin() const -> const_iterator
{
  return d_start_iterator;
}

// Return const iterator to end
template<typename Iterator>
auto View<Iterator>::cend() const -> const_iterator
{
  return d_end_iterator;
}

// Swap with another view
template<typename Iterator>
void View<Iterator>::swap( View<Iterator>& other_view )
{
  Iterator cached_start_iterator = d_start_iterator;
  Iterator cached_end_iterator = d_end_iterator;

  d_start_iterator = other_view.d_start_iterator;
  d_end_iterator = other_view.d_end_iterator;

  other_view.d_start_iterator = cached_start_iterator;
  other_view.d_end_iterator = cached_end_iterator;
}

// Return a const view
template<typename Iterator>
auto View<Iterator>::toConst() const -> View<const_iterator>
{
  return View<const_iterator>( d_start_iterator, d_end_iterator );
}

// Implicitly convert a view to a const view
template<typename Iterator>
View<Iterator>::operator View<const_iterator>() const
{
  return this->toConst();
}

} // end Utility namespace

#endif // end UTILITY_VIEW_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_View_def.hpp
//---------------------------------------------------------------------------//
