//---------------------------------------------------------------------------//
//!
//! \file   Utility_View.hpp
//! \author Alex Robinson
//! \brief  The view class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_VIEW_HPP
#define UTILITY_VIEW_HPP

// Std Lib Includes
#include <iterator>
#include <type_traits>

// FRENSIE Includes
#include "Utility_IteratorTypeTraits.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_ComparisonTraits.hpp"

/*! \defgroup view View
 *
 * Methods and classes for working with slices (views) of containers. These
 * views are STL compliant containers.
 */

namespace Utility{

//! The view class 
template<typename Iterator>
class View
{

public:

  //! The value type of the view
  typedef typename std::iterator_traits<Iterator>::value_type value_type;

  //! The reference type of the view
  typedef typename std::iterator_traits<Iterator>::reference reference;

  //! The const reference type
  typedef typename std::add_const<reference> const_reference;

  //! The pointer type of the view
  typedef typename std::iterator_traits<Iterator>::pointer pointer;

  //! The const pointer type of the view
  typedef typename std::add_const<pointer>::type const_pointer;

  //! The iterator type of the view
  typedef Iterator iterator;

  //! The const iterator type of the view
  typedef typename Utility::ConstIterator<Iterator>::type const_iterator;

  //! The difference type of the view
  typedef typename std::iterator_traits<Iterator>::difference_type difference_type;

  //! The size type of the view
  typedef typename std::make_unsigned<difference_type>::type size_type;

  //! Default constructor
  View();

  //! Iterator constructor
  template<typename OtherIterator>
  View( const OtherIterator& start, const OtherIterator& end );

  //! Copy constructor
  View( const View<Iterator>& other_view );
  
  //! Const view copy constructor
  template<typename OtherIterator>
  View( const View<OtherIterator>& other_view );

  //! Assignment operator
  View<Iterator>& operator=( const View<Iterator>& other_view );

  //! Const view assignment operator
  template<typename OtherIterator>
  View<Iterator>& operator=( const View<OtherIterator>& other_view );

  //! Destructor
  virtual ~View();

  //! Get the size of the view
  size_type size() const;

  //! Check if the view is empty
  bool empty() const;

  //! Element access
  reference operator[]( const size_type index );

  //! Element access
  const_reference operator[]( const size_type index ) const;

  //! Element access
  reference at( const size_type index );

  //! Element access
  const_reference at( const size_type index ) const;

  //! Access first element
  reference front();

  //! Access first element
  const_reference front() const;

  //! Access last element
  reference back();

  //! Access last element
  const_reference back() const;

  //! Return iterator to beginning
  iterator begin();

  //! Return iterator to beginning
  const_iterator begin() const;

  //! return iterator to end
  iterator end();

  //! Return iterator to end
  const_iterator end() const;

  //! Return const iterator to beginning
  const_iterator cbegin() const;

  //! Return const iterator to end
  const_iterator cend() const;

  //! Return a const view
  View<const_iterator> toConst() const;

  //! Implicitly convert a view to a const view
  operator View<const_iterator>() const;

private:

  // The view start iterator
  iterator d_start_iterator;

  // The view end iterator
  iterator d_end_iterator;
};

/*! Create a view of a container
 * \ingroup view
 */
template<typename STLCompliantContainer>
inline View<typename STLCompliantContainer::iterator> view( STLCompliantContainer& container )
{
  return View<typename STLCompliantContainer::iterator>( container.begin(), container.end() );
}

/*! Create a const view of a container
 * \ingroup view
 */
template<typename STLCompliantContainer>
inline View<typename STLCompliantContainer::const_iterator> view( const STLCompliantContainer& container )
{
  return View<typename STLCompliantContainer::const_iterator>( container.begin(), container.end() );
}

/*! Create a const view of a container
 * \ingroup view
 */
template<typename STLCompliantContainer>
inline View<typename STLCompliantContainer::const_iterator> viewOfConst( const STLCompliantContainer& container )
{
  return View<typename STLCompliantContainer::const_iterator>( container.begin(), container.end() );
}

/*! Create a reverse view of a container
 * \ingroup view
 */
template<typename STLCompliantContainer>
inline View<typename STLCompliantContainer::reverse_iterator> reverseView( STLCompliantContainer& container )
{
  return View<typename STLCompliantContainer::reverse_iterator>( container.rbegin(), container.rend() );
}

/*! Create a const reverse view of a container
 * \ingroup view
 */
template<typename STLCompliantContainer>
inline View<typename STLCompliantContainer::const_reverse_iterator> reverseView( const STLCompliantContainer& container )
{
  return View<typename STLCompliantContainer::const_reverse_iterator>( container.rbegin(), container.rend() );
}

/*! Create a const reverse view of a container
 * \ingroup view
 */
template<typename STLCompliantContainer>
inline View<typename STLCompliantContainer::const_reverse_iterator> reverseViewOfConst( const STLCompliantContainer& container )
{
  return View<typename STLCompliantContainer::const_reverse_iterator>( container.rbegin(), container.rend() );
}

/*! Partial specialization of ToStringTraits for Utility::View
 * \ingroup view
 * \ingroup to_string_traits
 */
template<typename T>
struct ToStringTraits<Utility::View<T> > : public Details::ToStringTraitsIteratorHelper<Utility::View<T> >
{ /* ... */ };

/*! Specialization of ToStringTraits for Utility::View<std::string::const_iterator>
 * \ingroup view
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<Utility::View<std::string::const_iterator> >
{
  //! Return the string
  static inline std::string toString( const Utility::View<std::string::const_iterator>& string_view )
  {
    return std::string( string_view.begin(), string_view.end() );
  }

  //! Place the string view in a stream
  static inline void toStream( std::ostream& os, const Utility::View<std::string::const_iterator>& string_view )
  {
    os << ToStringTraits<Utility::View<std::string::const_iterator> >::toString( string_view );
  }
};

/*! \brief Partial specialization of ToStringTraits for 
 * Utility::View<std::string::iterator>
 * \ingroup view
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<Utility::View<std::string::iterator> > : public ToStringTraits<Utility::View<std::string::const_iterator> >
{ /* ... */ };

//! Place the view in a stream
template<typename T>
std::ostream& operator<<( std::ostream& os, const Utility::View<T>& view )
{
  Utility::toStream( os, view );

  return os;
}

/*! Partial specialization of ComparisonTraits for Utility::View
 * \ingroup view
 * \ingropu comparison_traits
 */
template<typename T>
struct ComparisonTraits<Utility::View<T> > : public Details::ComparisonTraitsSequenceContainerHelper<Utility::View,T>
{ /* ... */ };
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "Utility_View_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_VIEW_HPP

//---------------------------------------------------------------------------//
// end Utility_View.hpp
//---------------------------------------------------------------------------//