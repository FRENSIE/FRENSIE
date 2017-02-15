//---------------------------------------------------------------------------//
//!
//! \file   Utility_ArrayTraits.hpp
//! \author Alex Robinson
//! \brief  Array traits class specializations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ARRAY_TRAITS_HPP
#define UTILITY_ARRAY_TRAITS_HPP

// Std Lib Includes
#include <vector>
#include <cmath>

// Boost Includes
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/or.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_Tuple.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_TwoDArray.hpp>

// FRENSIE Includes
#include "Utility_ArrayTraitsDecl.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

namespace Details{

/*! The front/back array traits helper class
 *
 * This class will be used with all array types with a front, back, begin, 
 * and end member function.
 * \ingroup array_traits
 */
template<typename Array>
struct FrontBackArrayTraitsHelper
{
  //! The reference type of the array
  typedef typename Array::reference reference;
  //! The const reference type of the array
  typedef typename Array::const_reference const_reference;
  //! The iterator type of the array
  typedef typename Array::iterator iterator;
  // The const iterator type of the array
  typedef typename Array::const_iterator const_iterator;

  //! The front element of the array
  static inline reference front( Array& array )
  { return array.front(); }

  //! The front element of the array
  static inline const_reference front( const Array& array )
  { return array.front(); }

  //! The back element of the array
  static inline reference back( Array& array )
  { return array.back(); }

  //! The back element of the array
  static inline const_reference back( const Array& array )
  { return array.back(); }

  //! Return an iterator at the beginning of the array
  static inline iterator begin( Array& array )
  { return array.begin(); }

  //! Return an iterator at the beginning of the array
  static inline const_iterator begin( const Array& array )
  { return array.begin(); }

  //! Return an iterator at one past the end of the array
  static inline iterator end( Array& array )
  { return array.end(); }

  //! Return an iterator at one past the end of the array
  static inline const_iterator end( const Array& array )
  { return array.end(); }
};

/*! \brief The specialization of the front/back array traits helper class for
 * Teuchos::ArrayRCP
 * \ingroup array_traits
 */
template<typename T>
struct FrontBackArrayTraitsHelper<Teuchos::ArrayRCP<T> >
{
  //! The reference type of the array
  typedef typename Teuchos::ArrayRCP<T>::reference reference;
  //! The const reference type of the array
  typedef typename Teuchos::ArrayRCP<T>::const_reference const_reference;
  //! The iterator type of the array
  typedef typename Teuchos::ArrayRCP<T>::iterator iterator;
  // The const iterator type of the array
  typedef typename Teuchos::ArrayRCP<T>::const_iterator const_iterator;

  //! The front element of the array
  static inline reference front( Teuchos::ArrayRCP<T>& array )
  { return array[0]; }

  //! The front element of the array
  static inline const_reference front( const Teuchos::ArrayRCP<T>& array )
  { return array[0]; }

  //! The back element of the array
  static inline reference back( Teuchos::ArrayRCP<T>& array )
  { return array[array.size()-1]; }

  //! The back element of the array
  static inline const_reference back( const Teuchos::ArrayRCP<T>& array )
  { return array[array.size()-1]; }

  //! Return an iterator at the beginning of the array
  static inline iterator begin( Teuchos::ArrayRCP<T>& array )
  { return array.begin(); }

  //! Return an iterator at the beginning of the array
  static inline const_iterator begin( const Teuchos::ArrayRCP<T>& array )
  { return array.begin(); }

  //! Return an iterator at one past the end of the array
  static inline iterator end( Teuchos::ArrayRCP<T>& array )
  { return array.end(); }

  //! Return an iterator at one past the end of the array
  static inline const_iterator end( const Teuchos::ArrayRCP<T>& array )
  { return array.end(); }
};

/*! The to string array traits helper class
 *
 * For all array types other than the Teuchos::Array, Teuchos::Tuple, 
 * Teuchos::ArrayView and the Teuchos::TwoDArray the array will be converted 
 * to a Teuchos::Array first and then the toString method will be used. 
 * Obviously the copy operation will incur an additional cost for all but the 
 * types listed above.
 * \ingroup array_traits
 */
template<typename Array>
struct ToStringArrayTraitsHelper
{
  //! Convert the array to a string
  static inline std::string toString( const Array& array )
  {
    Teuchos::Array<typename boost::remove_const<typename Array::value_type>::type>
      array_copy( array.begin(), array.end() );

    return Teuchos::toString( array_copy );
  }
};

/*! \brief The partial specialization of the ToStringArrayTraitsHelper for 
 * Teuchos::Array
 * \ingroup array_traits
 */
template<typename T>
struct ToStringArrayTraitsHelper<Teuchos::Array<T> >
{
  //! Convert the array to a string
  static inline std::string toString( const Teuchos::Array<T>& array )
  { return Teuchos::toString( array ); }
};

/*! \brief The partial specialization of the ToStringArrayTraitsHelper for 
 * Teuchos::ArrayView
 * \ingroup array_traits
 */
template<typename T>
struct ToStringArrayTraitsHelper<Teuchos::ArrayView<T> >
{
  //! Convert the array to a string
  static inline std::string toString( const Teuchos::ArrayView<T>& view )
  { return view.toString(); }
};

/*! The specialization of the ToStringArrayTraitsHelper for Teuchos::Tuple
 * \ingroup array_traits
 */
template<typename T, int N>
struct ToStringArrayTraitsHelper<Teuchos::Tuple<T,N> >
{
  //! Convert the array to a string
  static inline std::string toString( const Teuchos::Tuple<T,N>& tuple )
  { return tuple.toString(); }
};

/*! The from string array traits helper class
 *
 * For all array types other than the Teuchos::Array and the Teuchos::TwoDArray
 * a Teuchos::Array object will be created from the stream first and then
 * the desired array will be created from the Teuchos::Array object. 
 * Obviously the copy operation will incur an additional cost for all but
 * the types listed above.
 * \ingroup array_traits
 */
template<typename Array>
struct FromStringArrayTraitsHelper
{
  //! Create the array from a string
  static inline Array fromString( const std::string& array_string )
  {
    Teuchos::Array<typename Array::value_type> array_copy;
    try{
      array_copy = Teuchos::fromStringToArray<typename Array::value_type>(
                                                                array_string );
    }
    EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
                                std::runtime_error,
                                "Could not convert the string to an array!" );

    return Array( array_copy.begin(), array_copy.end() );
  }
};

/*! \brief The partial specialization of FromStringArrayTraitsHelper for
 * Teuchos::Array
 * \ingroup array_traits
 */
template<typename T>
struct FromStringArrayTraitsHelper<Teuchos::Array<T> >
{
  //! Create the array from a string
  static inline Teuchos::Array<T> fromString( const std::string& array_string )
  {
    try{
      return Teuchos::fromStringToArray<T>( array_string );
    }
    EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
                                std::runtime_error,
                                "Could not convert the string to an array!" );
  }
};

/*! \brief The partial specialization of FromStringArrayTraitsHelper for
 * Teuchos::ArrayRCP
 * \ingroup array_traits
 */
template<typename T>
struct FromStringArrayTraitsHelper<Teuchos::ArrayRCP<T> >
{
  //! Create the array from a string
  static inline Teuchos::ArrayRCP<T> fromString( const std::string& array_string )
  {
    Teuchos::Array<T> array_copy;
    
    try{
      array_copy = Teuchos::fromStringToArray<T>( array_string );
    }
    EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
                                std::runtime_error,
                                "Could not convert the string to an array!" );

    Teuchos::ArrayRCP<T> array;
    array.deepCopy( array_copy() );

    return array;
  }
};
  
/*! The 1D array traits helper class (statically sized array types)
 *
 * When dealing with an array of const type do not use the const when
 * inheriting from this helper.
 * \ingroup array_traits
 */
template<typename Array>
struct OneDStaticArrayTraitsHelper : public FrontBackArrayTraitsHelper<Array>, public ToStringArrayTraitsHelper<Array>
{
private:
  // Typedef for thi array traits type
  typedef OneDStaticArrayTraitsHelper<Array> TheseTraits;

public:
  //! The array type
  typedef Array ArrayType;
  //! The size type of the array
  typedef typename ArrayType::size_type size_type;
  //! The type containted in the array
  typedef typename ArrayType::value_type value_type;
  //! The pointer type of the array
  typedef typename ArrayType::pointer pointer;
  //! The const pointer type of the array
  typedef typename ArrayType::const_pointer const_pointer;
  //! The reference type of the array
  typedef typename FrontBackArrayTraitsHelper<Array>::reference reference;
  //! The const reference type of the array
  typedef typename FrontBackArrayTraitsHelper<Array>::const_reference const_reference;
  //! The iterator type of the array
  typedef typename FrontBackArrayTraitsHelper<Array>::iterator iterator;
  // The const iterator type of the array
  typedef typename FrontBackArrayTraitsHelper<Array>::const_iterator const_iterator;
  //! The array view type
  typedef Teuchos::ArrayView<value_type> ArrayViewType;
  //! The array const view type
  typedef Teuchos::ArrayView<const typename boost::remove_const<value_type>::type> ArrayConstViewType;
  //! Used to avoid ambiguous overloads
  typedef boost::mpl::true_ AvoidAmbiguousOverloads;

  //! The number of dimensions in the array
  static inline size_type numberOfDimensions( const ArrayType& array )
  { return 1; }

  //! The size of each array dimension
  template<typename IntType,template<typename,typename...> class DimSizeArray>
  static inline void dimensionSizes( const ArrayType& array,
                                     DimSizeArray<IntType>& dim_size_array )
  {
    ArrayTraits<DimSizeArray<IntType> >::resize( dim_size_array, 1 );
    dim_size_array[0] = array.size();
  }
  
  //! The size of the array
  static inline size_type size( const ArrayType& array )
  { return array.size(); }

  //! The head pointer of the array
  static inline pointer headPtr( ArrayType& array )
  { return &array[0]; }

  //! The head pointer of the const array
  static inline const_pointer headPtr( const ArrayType& array )
  { return &array[0]; }

  //! Place the array in a stream
  static inline void toStream( std::ostream& os, const ArrayType& array )
  { os << TheseTraits::toString( array ); }

  //! A view of the array
  static inline ArrayViewType view(
	  ArrayType& array,
	  const size_type offset = Teuchos::OrdinalTraits<size_type>::zero(),
	  const size_type size = Teuchos::OrdinalTraits<size_type>::invalid() )
  {
    if( size == Teuchos::OrdinalTraits<size_type>::invalid() )
      return ArrayViewType( headPtr(array), TheseTraits::size(array) );
    else
      return ArrayViewType( headPtr(array)+offset, size + offset <= TheseTraits::size(array) ? size : TheseTraits::size(array) - offset );
  }

  //! A view of the const array
  static inline ArrayConstViewType view(
	  const ArrayType& array,
	  const size_type offset = Teuchos::OrdinalTraits<size_type>::zero(),
          const size_type size = Teuchos::OrdinalTraits<size_type>::invalid() )
  {
    if( size == Teuchos::OrdinalTraits<size_type>::invalid() )
      return ArrayConstViewType( headPtr(array), TheseTraits::size(array) );
    else
      return ArrayConstViewType( headPtr(array)+offset, size + offset <= TheseTraits::size(array) ? size : TheseTraits::size(array) - offset );
  }
};

/*! The 1D array helper class (dynamically sized array types)
 * \ingroup array_traits
 */
template<typename Array>
struct OneDDynamicArrayTraitsHelper: public OneDStaticArrayTraitsHelper<Array>, public FromStringArrayTraitsHelper<Array>
{
  //! The array type
  typedef typename OneDStaticArrayTraitsHelper<Array>::ArrayType ArrayType;
  //! The size type of the array
  typedef typename OneDStaticArrayTraitsHelper<Array>::size_type size_type;
  //! The type containted in the array
  typedef typename OneDStaticArrayTraitsHelper<Array>::value_type value_type;
  //! The pointer type of the array
  typedef typename OneDStaticArrayTraitsHelper<Array>::pointer pointer;
  //! The const pointer type of the array
  typedef typename OneDStaticArrayTraitsHelper<Array>::const_pointer const_pointer;
  //! The reference type of the array
  typedef typename OneDStaticArrayTraitsHelper<Array>::reference reference;
  //! The const reference type of the array
  typedef typename OneDStaticArrayTraitsHelper<Array>::const_reference const_reference;
  //! The iterator type of the array
  typedef typename OneDStaticArrayTraitsHelper<Array>::iterator iterator;
  // The const iterator type of the array
  typedef typename OneDStaticArrayTraitsHelper<Array>::const_iterator const_iterator;
  //! The array view type
  typedef typename OneDStaticArrayTraitsHelper<Array>::ArrayViewType ArrayViewType;
  //! The array const view type
  typedef typename OneDStaticArrayTraitsHelper<Array>::ArrayConstViewType ArrayConstViewType;
  //! Used to avoid ambiguous overloads
  typedef typename OneDStaticArrayTraitsHelper<Array>::AvoidAmbiguousOverloads AvoidAmbiguousOverloads;
  
  //! Resize the array
  static inline void resize( ArrayType& array, size_type n )
  { array.resize( n ); }

  //! Reshape the array
  template<typename IntType,
           template<typename,typename... > class DimSizeArray>
  static inline void reshape( ArrayType& array,
                              const DimSizeArray<IntType>& dim_size_array )
  {
    size_t number_of_dims =
      ArrayTraits<DimSizeArray<IntType> >::size(dim_size_array);

    if( number_of_dims > 0 )
    {
      size_t total_size = dim_size_array[0];
    
      for( size_t i = 1; i < number_of_dims; ++i )
        total_size *= dim_size_array[i];

      array.resize( total_size );
    }
    else
      array.clear();
  }

  //! Copy an ArrayView object
  static inline void copyView( ArrayType& array, const ArrayViewType& view )
  { array.assign( view.begin(), view.end() ); }

  //! Copy an ArrayConstView object
  static inline void copyView( ArrayType& array,
                               const ArrayConstViewType& view )
  { array.assign( view.begin(), view.end() ); }
};
  
} // end Details namespace

/*! The partial specialization of the ArrayTraits struct for std::vector.
 * \details Template parameter T cannot be const qualified.
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<std::vector<T>,typename boost::enable_if<typename boost::mpl::not_<boost::is_const<T> >::type>::type> : public Details::OneDDynamicArrayTraitsHelper<std::vector<T> >
{ /* ... */ };

/*! The partial specialization of the ArrayTraits struct for const std::vector.
 * \details Template parameter T cannot be const qualified.
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<const std::vector<T>,typename boost::enable_if<typename boost::mpl::not_<boost::is_const<T> >::type>::type> : public Details::OneDStaticArrayTraitsHelper<std::vector<T> >
{ /* ... */ };

/*! The partial specialization of the ArrayTraits struct for Teuchos::Array.
 * \details Template parameter T cannot be const qualified.
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<Teuchos::Array<T>,typename boost::enable_if<typename boost::mpl::not_<boost::is_const<T> >::type>::type> : public Details::OneDDynamicArrayTraitsHelper<Teuchos::Array<T> >
{ /* ... */ };

/*! \brief The partial specialization of the ArrayTraits struct for const 
 * \details Template parameter T cannot be const qualified.
 * Teuchos::Array.
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<const Teuchos::Array<T>,typename boost::enable_if<typename boost::mpl::not_<boost::is_const<T> >::type>::type> : public Details::OneDStaticArrayTraitsHelper<Teuchos::Array<T> >
{ /* ... */ };  

/*! The partial specialization of the ArrayTraits struct for Teuchos::ArrayRCP.
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<Teuchos::ArrayRCP<T> > : public Details::OneDDynamicArrayTraitsHelper<Teuchos::ArrayRCP<T> >
{ /* ... */ };

/*! \brief The partial specialization of the ArrayTraits struct for 
 * Teuchos::ArrayRCP of const.
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<Teuchos::ArrayRCP<const T> > : public Details::OneDStaticArrayTraitsHelper<Teuchos::ArrayRCP<const T> >
{ /* ... */ };

/*! \brief The partial specialization of the ArrayTraits struct for const
 * Teuchos::ArrayRCP and const Teuchos::ArrayRCP const.
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<const Teuchos::ArrayRCP<T> > : public Details::OneDStaticArrayTraitsHelper<Teuchos::ArrayRCP<T> >
{ /* ... */ };

/*! \brief The partial specialization of the ArrayTraits struct for
 * Teuchos::Tuple<N>
 * \details Template parameter T cannot be const qualified.
 * \ingroup array_traits
 */
template<typename T, int N>
struct ArrayTraits<Teuchos::Tuple<T,N>,typename boost::enable_if<typename boost::mpl::not_<boost::is_const<T> >::type>::type> : public Details::OneDStaticArrayTraitsHelper<Teuchos::Tuple<T,N> >
{ /* ... */ };

/*! \brief The partial specialization of the ArrayTraits struct for const
 * Teuchos::Tuple<N>
 * \details Template parameter T cannot be const qualified.
 * \ingroup array_traits
 */
template<typename T, int N>
struct ArrayTraits<const Teuchos::Tuple<T,N>,typename boost::enable_if<typename boost::mpl::not_<boost::is_const<T> >::type>::type> : public Details::OneDStaticArrayTraitsHelper<Teuchos::Tuple<T,N> >
{ /* ... */ };

/*! \brief The partial specialization of the ArrayTraits struct for 
 *  Teuchos::ArrayView and Teuchos::ArrayView of const.
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<Teuchos::ArrayView<T> > : public Details::OneDStaticArrayTraitsHelper<Teuchos::ArrayView<T> >
{ /* ... */ };

/*! \brief The partial specialization of the ArrayTraits struct for const
 *  Teuchos::ArrayView and const Teuchos::ArrayView of const.
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<const Teuchos::ArrayView<T> > : public Details::OneDStaticArrayTraitsHelper<Teuchos::ArrayView<T> >
{ /* ... */ };

/*! \brief The partial specialization of the ArrayTraits struct for const
  Teuchos::TwoDArray
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<const Teuchos::TwoDArray<T> >
{
private:
  // Typedef for this array traits type
  typedef ArrayTraits<const Teuchos::TwoDArray<T> > TheseTraits;

public:
  //! The array type
  typedef Teuchos::TwoDArray<T> ArrayType;
  //! The size type of the array
  typedef typename ArrayType::size_type size_type;
  //! The type contained in the array
  typedef typename Teuchos::Array<T>::value_type value_type;
  //! The pointer type of the array
  typedef typename Teuchos::Array<T>::pointer pointer;
  //! The const pointer type of the array
  typedef typename Teuchos::Array<T>::const_pointer const_pointer;
  //! The reference type of the array
  typedef typename Teuchos::Array<T>::reference reference;
  //! The const reference type of the array
  typedef typename Teuchos::Array<T>::const_reference const_reference;
  //! The iterator type of the array
  typedef typename Teuchos::Array<T>::iterator iterator;
  // The const iterator type of the array
  typedef typename Teuchos::Array<T>::const_iterator const_iterator;
  //! The array view type
  typedef Teuchos::ArrayView<T> ArrayViewType;
  //! The array const view type
  typedef Teuchos::ArrayView<const T> ArrayConstViewType;
  //! Used to avoid ambiguous overloads
  typedef boost::mpl::true_ AvoidAmbiguousOverloads;

  //! The number of dimensions in the array
  static inline size_type numberOfDimensions( const ArrayType& array )
  { return 2; }

  //! The size of each array dimension
  template<typename IntType, template<typename,typename...> class DimSizeArray>
  static inline void dimensionSizes( const ArrayType& array,
                                     DimSizeArray<IntType>& dim_size_array)
  {
    dim_size_array.resize( 2 );
    dim_size_array[0] = array.getNumRows();
    dim_size_array[1] = array.getNumCols();
  }

  //! The size of the array
  static inline size_type size( const ArrayType& array )
  { return array.getNumRows()*array.getNumCols(); }

  //! The front element of the array
  static inline reference front( ArrayType& array )
  { return array( 0, 0 ); }

  //! The front element of the array
  static inline const_reference front( const ArrayType& array )
  { return array( 0, 0 ); }

  //! The back element of the array
  static inline reference back( ArrayType& array )
  { return array( array.getNumRows()-1, array.getNumCols()-1 ); }

  //! The back element of the array
  static inline const_reference back( const ArrayType& array )
  { return array( array.getNumRows()-1, array.getNumCols()-1 ); }

  //! Return an iterator at the beginning of the array
  static inline iterator begin( ArrayType& array )
  { return const_cast<Teuchos::Array<T>&>(array.getDataArray()).begin(); }

  //! Return an iterator at the beginning of the array
  static inline const_iterator begin( const ArrayType& array )
  { return array.getDataArray().begin(); }

  //! Return an iterator at one past the end of the array
  static inline iterator end( ArrayType& array )
  { return const_cast<Teuchos::Array<T>&>(array.getDataArray()).end(); }

  //! Return an iterator at one past the end of the array
  static inline const_iterator end( const ArrayType& array )
  { return array.getDataArray().end(); }

  //! The head pointer of the array
  static inline pointer headPtr( ArrayType& array )
  { return array[0].getRawPtr(); }

  //! The head pointer of the const array
  static inline const_pointer headPtr( const ArrayType& array )
  { return const_cast<Teuchos::TwoDArray<T>& >( array )[0].getRawPtr(); }

  //! Convert the array to a string
  static inline std::string toString( const Teuchos::TwoDArray<T>& array )
  { return Teuchos::TwoDArray<T>::toString( array ); }    

  //! Place the array in a stream
  static inline void toStream( std::ostream& os, const ArrayType& array )
  { os << TheseTraits::toString( array ); }

  //! A view of the array
  static inline ArrayViewType view(
	  ArrayType& array,
	  const size_type offset = Teuchos::OrdinalTraits<size_type>::zero(),
	  const size_type size = Teuchos::OrdinalTraits<size_type>::invalid() )
  {
    if( size == Teuchos::OrdinalTraits<size_type>::invalid() )
      return const_cast<Teuchos::Array<T>&>( array.getDataArray() )();
    else
      return const_cast<Teuchos::Array<T>&>( array.getDataArray() )( offset, size + offset <= TheseTraits::size(array) ? size : TheseTraits::size(array) - offset );
  }

  //! A view of the const array
  static inline ArrayConstViewType view(
	  const ArrayType& array,
	  const size_type offset = Teuchos::OrdinalTraits<size_type>::zero(),
	  const size_type size = Teuchos::OrdinalTraits<size_type>::invalid() )
  {
    if( size == Teuchos::OrdinalTraits<size_type>::invalid() )
      return array.getDataArray()();
    else
      return array.getDataArray()( offset, size + offset <= TheseTraits::size(array) ? size : TheseTraits::size(array) - offset );
  }
};
  
/*! \brief The partial specialization of the ArrayTraits struct for
  Teuchos::TwoDArray
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<Teuchos::TwoDArray<T> > : public ArrayTraits<const Teuchos::TwoDArray<T> >
{
private:
  // Typedef for this array traits type
  typedef ArrayTraits<Teuchos::TwoDArray<T> > TheseTraits;

public:
  //! The array type
  typedef Teuchos::TwoDArray<T> ArrayType;
  //! The size type of the array
  typedef typename ArrayType::size_type size_type;
  //! The type contained in the array
  typedef typename Teuchos::Array<T>::value_type value_type;
  //! The pointer type of the array
  typedef typename Teuchos::Array<T>::pointer pointer;
  //! The const pointer type of the array
  typedef typename Teuchos::Array<T>::const_pointer const_pointer;
  //! The array view type
  typedef Teuchos::ArrayView<T> ArrayViewType;
  //! The array const view type
  typedef Teuchos::ArrayView<const T> ArrayConstViewType;
  //! Used to avoid ambiguous overloads
  typedef boost::mpl::true_ AvoidAmbiguousOverloads;
  
  //! Resize the array (it will simply be linearized)
  static inline void resize( ArrayType& array, size_type n )
  {
    array.resizeRows( 1 );
    array.resizeCols( n );
  }

  //! Reshape the array
  template<typename IntType,
           template<typename,typename... > class DimSizeArray>
  static inline void reshape( ArrayType& array,
                              const DimSizeArray<IntType>& dim_size_array )
  {
    size_t number_of_dims =
      ArrayTraits<DimSizeArray<IntType> >::size( dim_size_array );
    
    if( number_of_dims == 0 )
      array.clear();
    else if( number_of_dims == 1 )
      TheseTraits::resize( array, dim_size_array[0] );
    else if( number_of_dims == 2 )
    {
      array.resizeRows( dim_size_array[0] );
      array.resizeCols( dim_size_array[1] );
    }
    // The number of columns will be preserved (dim_size_array[1]). The
    // number of rows will be scaled based on the size of the higher order
    // dimension sizes
    else
    {
      // Calculate the number of rows
      size_t rows = dim_size_array[0];

      for( size_t i = 2; i < dim_size_array.size(); ++i )
        rows *= dim_size_array[i];

      array.resizeRows( rows );
      array.resizeCols( dim_size_array[1] );
    }
  }

  //! Create the array from a string
  static inline Teuchos::TwoDArray<T> fromString( const std::string& array_string )
  {
    try{
      return Teuchos::TwoDArray<T>::fromString( array_string );
    }
    EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
                                std::runtime_error,
                                "Could not convert the string to a 2D "
                                "array!" );
  }

  //! Copy the ArrayView object (the TwoDArray will be linear)
  static inline void copyView( ArrayType& array,
			       const ArrayViewType& view )
  {
    array.resizeRows( 1 );
    array.resizeCols( view.size() );
    
    const_cast<Teuchos::Array<T>&>( array.getDataArray() ).assign( view.begin(), view.end() );
  }

  //! Copy the ArrayView of const object (the TwoDArray will be linear)
  static inline void copyView( ArrayType& array,
			       const ArrayConstViewType& view )
  {
    array.resizeRows( 1 );
    array.resizeCols( view.size() );
    
    const_cast<Teuchos::Array<T>&>( array.getDataArray() ).assign( view.begin(), view.end() );
  }
};

} // end Utility namespace

#endif // end UTILITY_ARRAY_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_ArrayTraits.hpp
//---------------------------------------------------------------------------//
