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

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_TwoDArray.hpp>

// FRENSIE Includes
#include "Utility_ArrayTraitsDecl.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

namespace Traits{

/*! The partial specialization of the ArrayTraits struct for std::vector.
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<std::vector<T> >
{
  //! The size type of the array
  typedef typename std::vector<T>::size_type size_type;
  //! The type containted in the array
  typedef typename std::vector<T>::value_type value_type;
  //! The pointer type of the array
  typedef typename std::vector<T>::pointer pointer;
  //! The const pointer type of the array
  typedef typename std::vector<T>::const_pointer const_pointer;
  
  //! The head pointer of the array
  static inline pointer headPtr( std::vector<T> &array )
  { return &array[0]; }
  
  //! The head pointer of the const array
  static inline const_pointer headPtr( const std::vector<T> &array )
  { return &array[0]; }

  //! A view of the array
  static inline Teuchos::ArrayView<T> view( 
	  std::vector<T> &array,
	  const size_type offset = Teuchos::OrdinalTraits<size_type>::zero(),
	  const size_type size = Teuchos::OrdinalTraits<size_type>::invalid() )
  { 
    if( size == Teuchos::OrdinalTraits<size_type>::invalid() )
      return Teuchos::arrayViewFromVector( array ); 
    else
    {
      Teuchos::ArrayView<T> full_view = Teuchos::arrayViewFromVector( array );
      return full_view( offset, size );
    }
  }

  //! A view of the const array
  static inline Teuchos::ArrayView<const T> view( 
	  const std::vector<T> &array,
	  const size_type offset = Teuchos::OrdinalTraits<size_type>::zero(),
          const size_type size = Teuchos::OrdinalTraits<size_type>::invalid() )
  { 
    if( size == Teuchos::OrdinalTraits<size_type>::invalid() )
      return Teuchos::arrayViewFromVector( array ); 
    else
    {
      Teuchos::ArrayView<const T> full_view = 
	Teuchos::arrayViewFromVector( array );
      return full_view( offset, size );
    }
  }
  
  //! The size of the array
  static inline size_type size( const std::vector<T> &array )
  { return array.size(); }

  //! Resize the array
  static inline void resize( std::vector<T> &array, size_type n )
  { array.resize( n ); }

  //! Copy an ArrayView object
  static inline void copyView( std::vector<T> &array,
			       const Teuchos::ArrayView<T> &view )
  { array = Teuchos::createVector( view ); }

  //! Copy an ArrayView of const object
  static inline void copyView( std::vector<T> &array,
			       const Teuchos::ArrayView<const T> &view )
  { array = Teuchos::createVector( view ); }
};

/*! The partial specialization of the ArrayTraits struct for const std::vector.
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<const std::vector<T> >
{
  //! The size type of the array
  typedef typename std::vector<T>::size_type size_type;
  //! The type containted in the array
  typedef typename std::vector<T>::value_type value_type;
  //! The pointer type of the array
  typedef typename std::vector<T>::const_pointer pointer;
  //! The const pointer type of the array
  typedef typename std::vector<T>::const_pointer const_pointer;
  
  //! The head pointer of the array
  static inline const_pointer headPtr( const std::vector<T> &array )
  { return &array[0]; }

  //! A view of the const array
  static inline Teuchos::ArrayView<const T> view( 
	  const std::vector<T> &array,
	  const size_type offset = Teuchos::OrdinalTraits<size_type>::zero(),
	  const size_type size = Teuchos::OrdinalTraits<size_type>::invalid() )
  { 
    if( size == Teuchos::OrdinalTraits<size_type>::invalid() )
      return Teuchos::arrayViewFromVector( array ); 
    else
    {
      Teuchos::ArrayView<const T> full_view = 
	Teuchos::arrayViewFromVector( array );
      return full_view( offset, size );
    }
  }
  
  //! The size of the array
  static inline size_type size( const std::vector<T> &array )
  { return array.size(); }

  //! Resize the array
  static inline void resize( const std::vector<T> &array, size_type n )
  { testPrecondition( false ); } // cannot resize a const array

  //! Copy an ArrayView object
  static inline void copyView( const std::vector<T> &array,
			       const Teuchos::ArrayView<T> &view )
  { testPrecondition( false ); } // cannot change a const array

  //! Copy an ArrayView of const object
  static inline void copyView( std::vector<T> &array,
			       const Teuchos::ArrayView<const T> &view )
  { testPrecondition( false ); } // cannot change a const array
};

/*! The partial specialization of the ArrayTraits struct for Teuchos::Array.
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<Teuchos::Array<T> >
{
  //! The size type of the array
  typedef typename Teuchos::Array<T>::size_type size_type;
  //! The type contained in the array
  typedef typename Teuchos::Array<T>::value_type value_type;
  //! The pointer type of the array
  typedef typename Teuchos::Array<T>::pointer pointer;
  //! The const pointer type of the array
  typedef typename Teuchos::Array<T>::const_pointer const_pointer;
  
  //! The head pointer of the array
  static inline pointer headPtr( Teuchos::Array<T> &array )
  { return array.getRawPtr(); }
  
  //! The head pointer of the const array
  static inline const_pointer headPtr( const Teuchos::Array<T> &array )
  { return array.getRawPtr(); }

  //! A view of the array
  static inline Teuchos::ArrayView<T> view( 
	  Teuchos::Array<T> &array,
	  const size_type offset = Teuchos::OrdinalTraits<size_type>::zero(),
	  const size_type size = Teuchos::OrdinalTraits<size_type>::invalid() )
  { 
    if( size == Teuchos::OrdinalTraits<size_type>::invalid() )
      return array();
    else
      return array( offset, size );
  }

  //! A view of the const array
  static inline Teuchos::ArrayView<const T> view( 
	  const Teuchos::Array<T> &array,
	  const size_type offset = Teuchos::OrdinalTraits<size_type>::zero(),
	  const size_type size = Teuchos::OrdinalTraits<size_type>::invalid() )
  { 
    if( size == Teuchos::OrdinalTraits<size_type>::invalid() )
      return array();
    else
      return array( offset, size );
  }

  //! The size of the array
  static inline size_type size( const Teuchos::Array<T> &array )
  { return array.size(); }

  //! Resize the array
  static inline void resize( Teuchos::Array<T> &array, size_type n )
  { array.resize( n ); }

  //! Copy the ArrayView object
  static inline void copyView( Teuchos::Array<T> &array,
			       const Teuchos::ArrayView<T> &view )
  { Teuchos::Array<T> copy_array( view ); array = copy_array; }

  //! Copy the ArrayView of const object
  static inline void copyView( Teuchos::Array<T> &array,
			       const Teuchos::ArrayView<const T> &view )
  { Teuchos::Array<T> copy_array( view ); array = copy_array; }
};

/*! \brief The partial specialization of the ArrayTraits struct for const 
  Teuchos::Array.
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<const Teuchos::Array<T> >
{
  //! The size type of the array
  typedef typename Teuchos::Array<T>::size_type size_type;
  //! The type contained in the array
  typedef typename Teuchos::Array<T>::value_type value_type;
  //! The pointer type of the array
  typedef typename Teuchos::Array<T>::const_pointer pointer;
  //! The const pointer type of the array
  typedef typename Teuchos::Array<T>::const_pointer const_pointer;
  
  //! The head pointer of the array
  static inline const_pointer headPtr( const Teuchos::Array<T> &array )
  { return array.getRawPtr(); }

  //! A view of the const array
  static inline Teuchos::ArrayView<const T> view( 
	  const Teuchos::Array<T> &array,
	  const size_type offset = Teuchos::OrdinalTraits<size_type>::zero(),
	  const size_type size = Teuchos::OrdinalTraits<size_type>::invalid() )
  { 
    if( size == Teuchos::OrdinalTraits<size_type>::invalid() )
      return array();
    else
      return array( offset, size );
  }

  //! The size of the array
  static inline size_type size( const Teuchos::Array<T> &array )
  { return array.size(); }

  //! Resize the array
  static inline void resize( const Teuchos::Array<T> &array, size_type n )
  { testPrecondition( false ); } // cannot resize a const array

  //! Copy the ArrayView object
  static inline void copyView( const Teuchos::Array<T> &array,
			       const Teuchos::ArrayView<T> &view )
  { testPrecondition( false ); } // connot change a const array
  
  //! Copy the ArrayView of const object
  static inline void copyView( Teuchos::Array<T> &array,
			       const Teuchos::ArrayView<const T> &view )
  { testPrecondition( false ); } // cannot change a const array
};

/*! The partial specialization of the ArrayTraits struct for Teuchos::ArrayRCP.
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<Teuchos::ArrayRCP<T> >
{
  //! The size type of the array
  typedef typename Teuchos::ArrayRCP<T>::size_type size_type;
  //! The type contained in the array
  typedef typename Teuchos::ArrayRCP<T>::value_type value_type;
  //! The pointer type of the array
  typedef typename Teuchos::ArrayRCP<T>::pointer pointer;
  //! The const pointer type of the array
  typedef typename Teuchos::ArrayRCP<T>::const_pointer const_pointer;

  //! The head pointer of the array
  static inline pointer headPtr( Teuchos::ArrayRCP<T> &array )
  { return array.getRawPtr(); }
  
  //! The head pointer of the const array
  static inline const_pointer headPtr( const Teuchos::ArrayRCP<T> &array )
  { return array.getRawPtr(); }

  //! A view of the array
  static inline Teuchos::ArrayView<T> view( 
	  Teuchos::ArrayRCP<T> &array,
	  const size_type offset = Teuchos::OrdinalTraits<size_type>::zero(),
	  const size_type size = Teuchos::OrdinalTraits<size_type>::invalid() )
  { 
    if( size == Teuchos::OrdinalTraits<size_type>::invalid() )
      return array();
    else
      return array( offset, size );
  }

  //! A view of the const array
  static inline Teuchos::ArrayView<const T> view( 
	  const Teuchos::ArrayRCP<T> &array,
	  const size_type offset = Teuchos::OrdinalTraits<size_type>::zero(),
	  const size_type size = Teuchos::OrdinalTraits<size_type>::invalid() )
  { 
    if( size == Teuchos::OrdinalTraits<size_type>::invalid() )
      return array();
    else
      return array( offset, size );
  }
  
  //! The size of the array
  static inline size_type size( const Teuchos::ArrayRCP<T> &array )
  { return array.size(); }

  //! Resize the array
  static inline void resize( Teuchos::ArrayRCP<T> &array, size_type n )
  { array.resize( n ); }

  //! Copy the ArrayView object
  static inline void copyView( Teuchos::ArrayRCP<T> &array, 
			       const Teuchos::ArrayView<T> &view )
  { array = Teuchos::arcpClone( view.getConst() ); }

  //! Copy the ArrayView of const object
  static inline void copyView( Teuchos::ArrayRCP<T> &array,
			       const Teuchos::ArrayView<const T> &view )
  { array = Teuchos::arcpClone( view ); }
};

/*! \brief The partial specialization of the ArrayTraits struct for const
 * Teuchos::ArrayRCP.
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<const Teuchos::ArrayRCP<T> >
{
  //! The size type of the array
  typedef typename Teuchos::ArrayRCP<T>::size_type size_type;
  //! The type contained in the array
  typedef typename Teuchos::ArrayRCP<T>::value_type value_type;
  //! The pointer type of the array
  typedef typename Teuchos::ArrayRCP<T>::const_pointer pointer;
  //! The const pointer type of the array
  typedef typename Teuchos::ArrayRCP<T>::const_pointer const_pointer;

  //! The head pointer of the array
  static inline const_pointer headPtr( const Teuchos::ArrayRCP<T> &array )
  { return array.getRawPtr(); }

  //! A view of the array
  static inline Teuchos::ArrayView<const T> view( 
	  const Teuchos::ArrayRCP<T> &array,
	  const size_type offset = Teuchos::OrdinalTraits<size_type>::zero(),
	  const size_type size = Teuchos::OrdinalTraits<size_type>::invalid() )
  { 
    if( size == Teuchos::OrdinalTraits<size_type>::invalid() )
      return array();
    else
      return array( offset, size );
  }
  
  //! The size of the array
  static inline size_type size( const Teuchos::ArrayRCP<T> &array )
  { return array.size(); }

  //! Resize the array
  static inline void resize( const Teuchos::ArrayRCP<T> &array, size_type n )
  { testPrecondition( false ); } // cannot resize a const array

  //! Copy the ArrayView object
  static inline void copyView( const Teuchos::ArrayRCP<T> &array, 
			       const Teuchos::ArrayView<T> &view )
  { testPrecondition( false ); } // cannot change a const array

  //! Copy the ArrayView of const object
  static inline void copyView( const Teuchos::ArrayRCP<T> &array,
			       const Teuchos::ArrayView<const T> &view )
  { testPrecondition( false ); } // cannot change a const array
};

/*! \brief The partial specialization of the ArrayTraits struct for 
  Teuchos::ArrayView.
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<Teuchos::ArrayView<T> >
{
  //! The size type of the array
  typedef typename Teuchos::ArrayView<T>::size_type size_type;
  //! The type contained in the array
  typedef typename Teuchos::ArrayView<T>::value_type value_type;
  //! The pointer type of the array
  typedef typename Teuchos::ArrayView<T>::pointer pointer;
  //! The const pointer type of the array
  typedef typename Teuchos::ArrayView<T>::const_pointer const_pointer;

  //! The head pointer of the array
  static inline pointer headPtr( Teuchos::ArrayView<T> &array )
  { return array.getRawPtr(); }

  //! The head pointer of the const array
  static inline const_pointer headPtr( const Teuchos::ArrayView<T> &array )
  { return array.getRawPtr(); }

  //! A view of the array
  static inline Teuchos::ArrayView<T> view( Teuchos::ArrayView<T> &array )
  { return array(); }

  //! A view of the const array
  static inline Teuchos::ArrayView<const T> view( 
	  const Teuchos::ArrayView<T> &array,
	  const size_type offset = Teuchos::OrdinalTraits<size_type>::zero(),
	  const size_type size = Teuchos::OrdinalTraits<size_type>::invalid() )
  { 
    if( size == Teuchos::OrdinalTraits<size_type>::invalid() )
      return array();
    else
      return array( offset, size );
  }

  //! The size of the array
  static inline size_type size( const Teuchos::ArrayView<T> &array )
  { return array.size(); }

  //! Resize the array
  static inline void resize( Teuchos::ArrayView<T> &array, size_type n )
  { testPrecondition( false ); } // Can't resize an ArrayView 

  //! Copy the ArrayView object (shallow copy)
  static inline void copyView( Teuchos::ArrayView<T> &array,
			       const Teuchos::ArrayView<T> &view )
  { array = view; }

  //! Copy the ArrayView of const object (shallow copy)
  static inline void copyView( Teuchos::ArrayView<T> &array,
			       const Teuchos::ArrayView<const T> &view )
  { array = view; }
};

/*! \brief The partial specialization of the ArrayTraits struct for const
  Teuchos::ArrayView.
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<const Teuchos::ArrayView<T> >
{
  //! The size type of the array
  typedef typename Teuchos::ArrayView<T>::size_type size_type;
  //! The type contained in the array
  typedef typename Teuchos::ArrayView<T>::value_type value_type;
  //! The pointer type of the array
  typedef typename Teuchos::ArrayView<T>::const_pointer pointer;
  //! The const pointer type of the array
  typedef typename Teuchos::ArrayView<T>::const_pointer const_pointer;

  //! The head pointer of the array
  static inline const_pointer headPtr( const Teuchos::ArrayView<T> &array )
  { return array.getRawPtr(); }

  //! A view of the const array
  static inline Teuchos::ArrayView<const T> view( 
	  const Teuchos::ArrayView<T> &array,
	  const size_type offset = Teuchos::OrdinalTraits<size_type>::zero(),
	  const size_type size = Teuchos::OrdinalTraits<size_type>::invalid() )
  { 
    if( size == Teuchos::OrdinalTraits<size_type>::invalid() )
      return array();
    else
      return array( offset, size );
  }

  //! The size of the array
  static inline size_type size( const Teuchos::ArrayView<T> &array )
  { return array.size(); }

  //! Resize the array
  static inline void resize( const Teuchos::ArrayView<T> &array, size_type n )
  { testPrecondition( false ); } // Can't resize an ArrayView

  //! Copy the ArrayView object
  static inline void copyView( Teuchos::ArrayView<T> &array,
			       const Teuchos::ArrayView<T> &view )
  { testPrecondition( false ); } // Can't resize a const array

  //! Copy the ArrayView of const object
  static inline void copyView( Teuchos::ArrayView<T> &array,
			       const Teuchos::ArrayView<const T> &view )
  { testPrecondition( false ); } // Can't resize a const array
};

/*! \brief The partial specialization of the ArrayTraits struct for 
  Teuchos::ArrayView of const.
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<Teuchos::ArrayView<const T> >
{
  //! The size type of the array
  typedef typename Teuchos::ArrayView<const T>::size_type size_type;
  //! The type contained in the array
  typedef typename Teuchos::ArrayView<const T>::value_type value_type;
  //! The pointer type of the array
  typedef typename Teuchos::ArrayView<const T>::pointer pointer;
  //! The const pointer type of the array
  typedef typename Teuchos::ArrayView<const T>::const_pointer const_pointer;

  //! The head pointer of the array
  static inline pointer headPtr( Teuchos::ArrayView<const T> &array )
  { return array.getRawPtr(); }

  //! The head pointer of the const
  static inline const_pointer headPtr(const Teuchos::ArrayView<const T> &array)
  { return array.getRawPtr(); }

  //! A view of the array
  static inline Teuchos::ArrayView<const T> view(
	  Teuchos::ArrayView<const T> & array,
	  const size_type offset = Teuchos::OrdinalTraits<size_type>::zero(),
	  const size_type size = Teuchos::OrdinalTraits<size_type>::invalid() )
  { 
    if( size == Teuchos::OrdinalTraits<size_type>::invalid() )
      return array();
    else
      return array( offset, size );
  }

  //! A view of the const array
  static inline Teuchos::ArrayView<const T> view(
	  const Teuchos::ArrayView<const T> &array,
	  const size_type offset = Teuchos::OrdinalTraits<size_type>::zero(),
	  const size_type size = Teuchos::OrdinalTraits<size_type>::invalid() )
  { 
    if( size == Teuchos::OrdinalTraits<size_type>::invalid() )
      return array();
    else
      return array( offset, size );
  }
  
  //! The size of the array
  static inline size_type size( const Teuchos::ArrayView<const T> &array )
  { return array.size(); }

  //! Resize the array
  static inline void resize( Teuchos::ArrayView<const T> &array, size_type n )
  { testPrecondition( false ); } // Can't resize and ArrayView 

  //! Copy the ArrayView object
  static inline void copyView( Teuchos::ArrayView<const T> &array,
			       const Teuchos::ArrayView<T> &view )
  { testPrecondition( false ); } // Can't change an ArrayView of const
  
  //! Copy the ArrayView of const object
  static inline void copyView( Teuchos::ArrayView<const T> &array,
			       const Teuchos::ArrayView<const T> &view )
  { testPrecondition( false ); } // Can't change an ArrayView of const
};

/*! \brief The partial specialization of the ArrayTraits struct for const 
  Teuchos::ArrayView of const.
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<const Teuchos::ArrayView<const T> >
{
  //! The size type of the array
  typedef typename Teuchos::ArrayView<const T>::size_type size_type;
  //! The type contained in the array
  typedef typename Teuchos::ArrayView<const T>::value_type value_type;
  //! The pointer type of the array
  typedef typename Teuchos::ArrayView<const T>::const_pointer pointer;
  //! The const pointer type of the array
  typedef typename Teuchos::ArrayView<const T>::const_pointer const_pointer;

  //! The head pointer of the array
  static inline const_pointer 
  headPtr( const Teuchos::ArrayView<const T> &array )
  { return array.getRawPtr(); }
  
  //! A view of the const array
  static inline Teuchos::ArrayView<const T> view(
	  const Teuchos::ArrayView<const T> &array,
	  const size_type offset = Teuchos::OrdinalTraits<size_type>::zero(),
	  const size_type size = Teuchos::OrdinalTraits<size_type>::invalid() )
  { 
    if( size == Teuchos::OrdinalTraits<size_type>::invalid() )
      return array();
    else
      return array( offset, size );
  }
  
  //! The size of the array
  static inline size_type size( const Teuchos::ArrayView<const T> &array )
  { return array.size(); }

  //! Resize the array
  static inline void resize( const Teuchos::ArrayView<const T> &array, 
			     size_type n )
  { testPrecondition( false ); } // Can't resize and ArrayView 

  //! Copy the ArrayView object
  static inline void copyView( Teuchos::ArrayView<const T> &array,
			       const Teuchos::ArrayView<T> &view )
  { testPrecondition( false ); } // Can't change an ArrayView of const
  
  //! Copy the ArrayView of const object
  static inline void copyView( Teuchos::ArrayView<const T> &array,
			       const Teuchos::ArrayView<const T> &view )
  { testPrecondition( false ); } // Can't change an ArrayView of const
};

/*! \brief The partial specialization of the ArrayTraits struct for 
  Teuchos::TwoDArray
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<Teuchos::TwoDArray<T> >
{
  //! The size type of the array
  typedef typename Teuchos::Array<T>::size_type size_type;
  //! The type contained in the array
  typedef typename Teuchos::Array<T>::value_type value_type;
  //! The pointer type of the array
  typedef typename Teuchos::Array<T>::pointer pointer;
  //! The const pointer type of the array
  typedef typename Teuchos::Array<T>::const_pointer const_pointer;

  //! The head pointer of the array
  static inline pointer headPtr( Teuchos::TwoDArray<T> &array )
  { return array[0].getRawPtr(); }

  //! The head pointer of the const array
  static inline const_pointer headPtr( const Teuchos::TwoDArray<T> &array )
  { return array[0].getRawPtr(); }

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
      return array.getDataArray()();
    else
      return array.getDataArray()( offset, size );
  }

  //! The size of the array
  static inline size_type size( const Teuchos::TwoDArray<T> &array )
  { return array.getNumRows()*array.getNumCols(); }

  //! Resize the array (it will simply be linearized)
  static inline void resize( Teuchos::TwoDArray<T> &array, size_type n )
  { if( array.getNumCols() == 0 )
    {
      array.resizeRows( 1 );
      array.resizeCols( n );
    }
    else
    {
      double num_rows = 
	ceil( static_cast<double>( n )/array.getNumCols() );
      array.resizeRows( static_cast<size_type>( num_rows ) );
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

/*! \brief The partial specialization of the ArrayTraits struct for const
  Teuchos::TwoDArray
 * \ingroup array_traits
 */
template<typename T>
struct ArrayTraits<const Teuchos::TwoDArray<T> >
{
  //! The size type of the array
  typedef typename Teuchos::Array<T>::size_type size_type;
  //! The type contained in the array
  typedef typename Teuchos::Array<T>::value_type value_type;
  //! The pointer type of the array
  typedef typename Teuchos::Array<T>::const_pointer pointer;
  //! The const pointer type of the array
  typedef typename Teuchos::Array<T>::const_pointer const_pointer;

  //! The head pointer of the array
  static inline const_pointer headPtr( const Teuchos::TwoDArray<T> &array )
  { return array.getRawPtr(); }

  //! A view of the const array
  static inline Teuchos::ArrayView<const T> view( 
	  const Teuchos::TwoDArray<T> &array,
	  const size_type offset = Teuchos::OrdinalTraits<size_type>::zero(),
	  const size_type size = Teuchos::OrdinalTraits<size_type>::invalid() )
  { 
    if( size == Teuchos::OrdinalTraits<size_type>::invalid() )
      return array.getDataArray()();
    else
      return array.getDataArray()( offset, size );
  }

  //! The size of the array
  static inline size_type size( const Teuchos::TwoDArray<T> &array )
  { return array.getnumRows()*array.getNumCols(); }

  //! Resize the array (it will simply be linearized)
  static inline void resize( const Teuchos::TwoDArray<T> &array, size_type n )
  { testPrecondition( false ); } // Cannot resize a const array

  //! Copy the ArrayView object (the TwoDArray will be linear)
  static inline void copyView( const Teuchos::TwoDArray<T> &array,
			       const Teuchos::ArrayView<T> &view )
  { testPrecondition( false ); } // Cannot change a const array

  //! Copy the ArrayView of const object (the TwoDArray will be linear)
  static inline void copyView( const Teuchos::TwoDArray<T> &array,
			       const Teuchos::ArrayView<const T> &view )
  { testPrecondition( false ); } // Cannot change a const array
};

} // end Traits namespace

} // end Utility namespace

#endif // end UTILITY_ARRAY_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_ArrayTraits.hpp
//---------------------------------------------------------------------------//
