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

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_TwoDArray.hpp>

// FRENSIE Includes
#include "Utility_ArrayTraitsDecl.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

namespace Details{

//! The 1D array helper class (statically sized array types)
template<typename T,
         template<typename,typename...> Array,
         bool is_statically_sized>
struct OneDArrayHelper
{
  //! The array type
  typedef Array<T> ArrayType;
  //! The array view type
  typedef Teuchos::ArrayView<T> ArrayViewType;
  //! The array const view type
  typedef Teuchos::ArrayView<const boost::remove_const<T>::type> ArrayConstViewType;
  //! The size type of the array
  typedef typename ArrayType::size_type size_type;
  //! The type containted in the array
  typedef typename ArrayType::value_type value_type;
  //! The pointer type of the array
  typedef typename ArrayType::pointer pointer;
  //! The const pointer type of the array
  typedef typename ArrayType::const_pointer const_pointer;

  //! The number of dimensions in the array
  static inline size_type numberOfDimensions( const ArrayType& array )
  { return 1; }

  //! The size of each array dimension
  template<typename IntType,template<typename,typename...> DimSizeArray>
  static inline void dimensionSizes( const ArrayType& array,
                                     DimSizeArray<IntType>& dim_size_array )
  {
    dim_size_array.resize( 1 );
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

  //! A view of the array
  static inline ArrayViewType view(
	  ArrayType& array,
	  const size_type offset = Teuchos::OrdinalTraits<size_type>::zero(),
	  const size_type size = Teuchos::OrdinalTraits<size_type>::invalid() )
  {
    if( size == Teuchos::OrdinalTraits<size_type>::invalid() )
      return ArrayViewType( headPtr(array), size(array) );
    else
      return ArrayViewType( headPtr(array)+offset, size );
  }

  //! A view of the const array
  static inline ArrayConstViewType view(
	  const ArrayType& array,
	  const size_type offset = Teuchos::OrdinalTraits<size_type>::zero(),
          const size_type size = Teuchos::OrdinalTraits<size_type>::invalid() )
  {
    if( size == Teuchos::OrdinalTraits<size_type>::invalid() )
      return ArrayConstViewType( headPtr(array), size(array) )
    else
      return ArrayViewConstType( headPtr(array)+offset, size(array) );
  }
};

//! The 1D array helper class (dynamically sized array types)
template<typename T,template<typename,typename...> Array>
struct OneDArrayHelper<T,Array,false> : public OneDArrayHelper<T,Array,true>
{
  //! Resize the array
  static inline void resize( ArrayType& array, size_type n )
  { array.resize( n ); }

  //! Reshape the array
  template<typename IntType, template<typename,typename... > DimSizeArray>
  static inline void reshape( ArrayType& array,
                              const DimSizeArray<IntType>& dim_size_array )
  {
    size_t number_of_dims =
      ArrayTraits<DimSizeArray<size_t> >::size( dim_size_array );

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
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<std::vector<T> > : public Details::OneDArrayHelper<T,std::vector,false>
{ /* ... */ };

/*! The partial specialization of the ArrayTraits struct for const std::vector
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<const std::vector<T> > : public Details::OneDArrayHelper<T,std::vector,true>
{ /* ... */ };

/*! The partial specialization of the ArrayTraits struct for Teuchos::Array.
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<Teuchos::Array<T> > : public Details::OneDArrayHelper<T,Teuchos::Array,false>
{ /* ... */ };

/*! \brief The partial specialization of the ArrayTraits struct for const 
 * Teuchos::Array.
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<const Teuchos::Array<T> > : public Details::OneDArrayHelper<T,Teuchos::Array,true>
{ /* ... */ };

/*! The partial specialization of the ArrayTraits struct for Teuchos::ArrayRCP.
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<Teuchos::ArrayRCP<T> > : public Details::OneDArrayHelper<T,Teuchos::ArrayRCP,false>
{ /* ... */ };

/*! \brief The partial specialization of the ArrayTraits struct for 
 * Teuchos::ArrayRCP of const.
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<Teuchos::ArrayRCP<const T> > : public Details::OneDArrayHelper<const T,Teuchos::ArrayRCP,true>
{ /* ... */ };

/*! \brief The partial specialization of the ArrayTraits struct for const 
 * Teuchos::ArrayRCP.
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<const Teuchos::ArrayRCP<T> > : public Details::OneDArrayHelper<T,Teuchos::ArrayRCP,true>
{ /* ... */ };

/*! \brief The partial specialization of the ArrayTraits struct for const 
 * Teuchos::ArrayRCP of const.
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<const Teuchos::ArrayRCP<const T> > : public Details::OneDArrayHelper<const T,Teuchos::ArrayRCP,true>
{ /* ... */ };

/*! \brief The partial specialization of the ArrayTraits struct for 
 *  Teuchos::ArrayView.
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<Teuchos::ArrayView<T> > : public Details::OneDArrayHelper<T,Teuchos::ArrayView,true>
{ /* ... */ };

/*! \brief The partial specialization of the ArrayTraits struct for
  Teuchos::ArrayView of const.
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<Teuchos::ArrayView<const T> > : public Details::OneDArrayHelper<const T,Teuchos::ArrayView,true>
{ /* ... */ };

/*! \brief The partial specialization of the ArrayTraits struct for const
  Teuchos::ArrayView of const.
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<const Teuchos::ArrayView<const T> > : public Details::OneDArrayHelper<const T,Teuchos::ArrayView,true>
{ /* ... */ };

/*! \brief The partial specialization of the ArrayTraits struct for const
  Teuchos::TwoDArray
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<const Teuchos::TwoDArray<T> >
{
  //! The array type
  typedef Teuchos::TwoDArray<T> ArrayType;
  //! The array view type
  typedef Teuchos::ArrayView<T> ArrayViewType;
  //! The array const view type
  typedef Teuchos::ArrayView<const T> ArrayConstViewType;
  //! The size type of the array
  typedef typename ArrayType::size_type size_type;
  //! The type contained in the array
  typedef typename ArrayType::value_type value_type;
  //! The pointer type of the array
  typedef typename ArrayType::pointer pointer;
  //! The const pointer type of the array
  typedef typename ArrayType::const_pointer const_pointer;

  //! The number of dimensions in the array
  static inline size_type numberOfDimensions( const ArrayType& array )
  { return 2; }

  //! The size of each array dimension
  template<typename IntType, template<typename,typename...> DimSizeArray>
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

  //! The head pointer of the array
  static inline pointer headPtr( Teuchos::TwoDArray<T> &array )
  { return array[0].getRawPtr(); }

  //! The head pointer of the const array
  static inline const_pointer headPtr( const Teuchos::TwoDArray<T> &array )
  { return const_cast<Teuchos::TwoDArray<T>& >( array )[0].getRawPtr(); }

  //! A view of the array
  static inline Teuchos::ArrayView<T> view(
	  Teuchos::TwoDArray<T> &array,
	  const size_type offset = Teuchos::OrdinalTraits<size_type>::zero(),
	  const size_type size = Teuchos::OrdinalTraits<size_type>::invalid() )
  {
    if( size == Teuchos::OrdinalTraits<size_type>::invalid() )
      return array.getDataArray()();
    else
      return array.getDataArray()( offset, size );
  }

  //! A view of the const array
  static inline Teuchos::ArrayView<const T> view(
	  const Teuchos::TwoDArray<T> &array,
	  const size_type offset = Teuchos::OrdinalTraits<size_type>::zero(),
	  const size_type size = Teuchos::OrdinalTraits<size_type>::invalid() )
  {
    if( size == Teuchos::OrdinalTraits<size_type>::invalid() )
      return array.getDataArray()().getConst();
    else
      return array.getDataArray()( offset, size ).getConst();
  }
};
  
/*! \brief The partial specialization of the ArrayTraits struct for
  Teuchos::TwoDArray
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<Teuchos::TwoDArray<T> > : public ArrayTraits<const Teuchos::TwoDArray<T> >
{
  //! Resize the array (it will simply be linearized)
  static inline void resize( ArrayType& array, size_type n )
  {
    array.resizeRows( 1 );
    array.resizeCols( n );
  }

  //! Reshape the array
  template<typename IntType, template<typename,typename... > DimSizeArray>
  static inline void reshape( ArrayType& array,
                              const DimSizeArray<IntType>& dim_size_array )
  {
    size_t number_of_dims =
      ArrayTraits<DimSizeArray<size_t> >::size( dim_size_array );
    
    if( number_of_dims == 0 )
      array.clear();
    else if( number_of_dimes == 1 )
      resize( array, dim_size_array[0] );
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

  //! Copy the ArrayView object (the TwoDArray will be linear)
  static inline void copyView( Teuchos::TwoDArray<T> &array,
			       const Teuchos::ArrayView<T> &view )
  {
    Teuchos::TwoDArray<T> copy_array( 1, view.size() );
    copy_array[0] = view;
    array = copy_array;
  }

  //! Copy the ArrayView of const object (the TwoDArray will be linear)
  static inline void copyView( Teuchos::TwoDArray<T> &array,
			       const Teuchos::ArrayView<const T> &view )
  {
    Teuchos::TwoDArray<T> copy_array( 1, view.size() );
    copy_array[0] = view;
    array = copy_array;
  }
};

} // end Utility namespace

#endif // end UTILITY_ARRAY_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_ArrayTraits.hpp
//---------------------------------------------------------------------------//
