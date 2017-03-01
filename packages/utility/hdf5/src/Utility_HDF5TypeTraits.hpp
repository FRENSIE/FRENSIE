//---------------------------------------------------------------------------//
//!
//! \file   Utility_HDF5TypeTraits.hpp
//! \author Alex Robinson
//! \brief  HDF5 Type Traits specializations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HDF5_TYPE_TRAITS_HPP
#define UTILITY_HDF5_TYPE_TRAITS_HPP

// Std Lib Includes
#include <utility>
#include <tuple>
#include <type_traits>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_HDF5TypeTraitsDecl.hpp"
#include "Utility_HDF5ExceptionCatchMacros.hpp"
#include "Utility_Tuple.hpp"

namespace Utility{

/*! \brief the partial specialization of the Utility::HDF5TypeTraits for
 * all constant types
 * \ingroup hdf5_type_traits
 */
template<typename T>
struct HDF5TypeTraits<T,typename std::enable_if<std::is_const<T>::value>::type> : public HDF5TypeTraits<typename std::remove_const<T>::type>
{ /* ... */ };

/*! \brief The specialization of the Utility::HDF5TypeTraits for double
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<double>
{
  //! Typedef for the raw type
  typedef double RawType;
  
  //! Returns the HDF5 data type object corresponding to double
  static inline H5::PredType dataType()
  { return H5::PredType::NATIVE_DOUBLE; }

  //! Returns the name of this type
  static inline std::string name()
  { return "double"; }

  //! Returns the zero value for this type
  static inline RawType zero()
  { return 0.0; }

  //! Returns the unity value for this type
  static inline RawType one()
  { return 1.0; }
};

/*! \brief The specialization of the Utility::HDF5TypeTraits for float
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<float>
{
  //! Typedef for the raw type
  typedef float RawType;
  
  //! Returns the HDF5 data type object corresponding to double
  static inline H5::PredType dataType()
  { return H5::PredType::NATIVE_FLOAT; }

  //! Returns the name of this type
  static inline std::string name()
  { return "float"; }

  //! Returns the zero value for this type
  static inline RawType zero()
  { return 0.0f; }

  //! Returns the unity value for this type
  static inline RawType one()
  { return 1.0f; }
};

/*! \brief The specialization of the Utility::HDF5TypeTraits for int
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<int>
{
  //! Typedef for the raw type
  typedef int RawType;
  
  //! Returns the HDF5 data type object corresponding to int
  static inline H5::PredType dataType()
  { return H5::PredType::NATIVE_INT; }

  //! Returns the name of this type
  static inline std::string name()
  { return "int"; }

  //! Returns the zero value for this type
  static inline RawType zero()
  { return 0; }

  //! Returns the unity value for this type
  static inline RawType one()
  { return 1; }
};

/*! \brief The specialization of the Utility::HDF5TypeTraits for unsigned int
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<unsigned int>
{
  //! Typedef for the raw type
  typedef unsigned int RawType;
  
  //! Returns the HDF5 data type object corresponding to unsigned int
  static inline H5::PredType dataType()
  { return H5::PredType::NATIVE_UINT; }

  //! Returns the name of the type
  static inline std::string name()
  { return "unsigned int"; }

  //! Returns the zero value for this type
  static inline RawType zero()
  { return 0u; }

  //! Returns the unity value for this type
  static inline RawType one()
  { return 1u; }
};

/*! \brief The specialization of the Utility::HDF5TypeTraits for long
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<long>
{
  //! Typedef for the raw type
  typedef long RawType;
  
  //! Returns the HDF5 data type object corresponding to long
  static inline H5::PredType dataType() 
  { return H5::PredType::NATIVE_LONG; }
  
  //! Returns the name of the type
  static inline std::string name() 
  { return "long int"; }
  
  //! Returns the zero value for this type
  static inline RawType zero()
  { return 0l; }

  //! Returns the unity value for this type
  static inline RawType one()
  { return 1l; }
};

/*! \brief The specialization of the Utility::HDF5TypeTraits for unsigned long
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<unsigned long>
{
  //! Typedef for the raw type
  typedef unsigned long RawType;
  
  //! Returns the HDF5 data type object corresponding to unsigned int
  static inline H5::PredType dataType()
  { return H5::PredType::NATIVE_ULONG; }

  //! Returns the name of the type
  static inline std::string name()
  { return "unsigned long int"; }

  //! Returns the zero value for this type
  static inline RawType zero()
  { return 0ul; }

  //! Returns the unity value for this type
  static inline RawType one()
  { return 1ul; }
};


/*! \brief The specialization of the Utility::HDF5TypeTraits for long long
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<long long>
{
  //! Typedef for the raw type
  typedef long long RawType;
  
  //! Returns the HDF5 data type object corresponding to long long int
  static inline H5::PredType dataType() 
  { return H5::PredType::NATIVE_LLONG; }
  
  //! Returns the name of the type
  static inline std::string name() 
  { return "long long int"; }
  
  //! Returns the zero value for this type
  static inline RawType zero()
  { return 0ll; }

  //! Returns the unity value for this type
  static inline RawType one()
  { return 1ll; }
};

/*! \brief The specialization of the Utility::HDF5TypeTraits for unsigned long
 * long
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<unsigned long long>
{
  //! Typedef for the raw type
  typedef unsigned long long RawType;
  
  //! Returns the HDF5 data type object corresponding to unsigned int
  static inline H5::PredType dataType()
  { return H5::PredType::NATIVE_ULLONG; }

  //! Returns the name of the type
  static inline std::string name()
  { return "unsigned long long int"; }

  //! Returns the zero value for this type
  static inline RawType zero()
  { return 0ull; }

  //! Returns the unity value for this type
  static inline RawType one()
  { return 1ull; }
};

/*! \brief The specialization of the Utility::HDF5TypeTraits for char
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<char>
{
  //! Typedef for the raw type
  typedef char RawType;
  
  //! Returns the HDF5 data type object corresponding to bool
  static inline H5::PredType dataType()
  { return H5::PredType::NATIVE_CHAR; }

  //! Returns the name of the type
  static inline std::string name()
  { return "char"; }

  //! Returns the zero value for this type
  static inline RawType zero()
  { return '0'; }

  //! Returns the unity value for this type
  static inline RawType one()
  { return '1'; }
};

/*! \brief The specialization of the Utility::HDF5TypeTraits for signed char
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<signed char>
{
  //! Typedef for the raw type
  typedef signed char RawType;
  
  //! Returns the HDF5 data type object corresponding to bool
  static inline H5::PredType dataType()
  { return H5::PredType::NATIVE_SCHAR; }

  //! Returns the name of the type
  static inline std::string name()
  { return "signed char"; }

  //! Returns the zero value for this type
  static inline RawType zero()
  { return 0; }

  //! Returns the unity value for this type
  static inline RawType one()
  { return 1; }
};

/*! \brief The specialization of the Utility::HDF5TypeTraits for unsigned char
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<unsigned char>
{
  //! Typedef for the raw type
  typedef unsigned char RawType;
  
  //! Returns the HDF5 data type object corresponding to bool
  static inline H5::PredType dataType()
  { return H5::PredType::NATIVE_UCHAR; }

  //! Returns the name of the type
  static inline std::string name()
  { return "unsigned char"; }

  //! Returns the zero value for this type
  static inline unsigned char zero()
  { return 0u; }

  //! Returns the unity value for this type
  static inline unsigned char one()
  { return 1u; }
};

namespace Details{

// The helper class that constructs a tuple HDF5 data type
template<size_t I, typename TupleType, typename Enabled = void>
struct HDF5TupleTypeHelper
{
  static inline void addElementTypes( H5::CompType& type,
                                      const TupleType& layout_tuple )
  {
    std::ostringstream oss;
    oss << "element_" << I;

    const size_t offset =
      reinterpret_cast<const uint8_t*>(&Utility::get<I>( layout_tuple )) -
      reinterpret_cast<const uint8_t*>(&layout_tuple);

    H5::DataType element_type =
      HDF5TypeTraits<typename TupleElement<I,TupleType>::type>::dataType();
    
    type.insertMember( oss.str(), offset, element_type );

    // Add the remaining tuple elements
    HDF5TupleTypeHelper<I+1,TupleType>::addElementTypes( type, layout_tuple );
  }

  static inline void addElementNames( std::string& type_name )
  {
    type_name += HDF5TypeTraits<typename TupleElement<I,TupleType>::type>::name();
    type_name += ",";

    // Add the remaining tuple element names
    HDF5TupleTypeHelper<I+1,TupleType>::addElementNames( type_name );
  }

  static inline void zeroElements( TupleType& tuple )
  {
    Utility::get<I>( tuple ) =
      HDF5TypeTraits<typename TupleElement<I,TupleType>::type>::zero();

    // Zero the remaining elements
    HDF5TupleTypeHelper<I+1,TupleType>::zeroElements( tuple );
  }

  static inline void oneElements( TupleType& tuple )
  {
    Utility::get<I>( tuple ) =
      HDF5TypeTraits<typename TupleElement<I,TupleType>::type>::one();

    // Set the remaining elements to one
    HDF5TupleTypeHelper<I+1,TupleType>::oneElements( tuple );
  }
};

// The helper class that constructs a tuple HDF5 data type (specialization for
// I = TupleSize-1, which is for the last element)
template<size_t I, typename TupleType>
struct HDF5TupleTypeHelper<I,TupleType,typename std::enable_if<I==TupleSize<TupleType>::value-1>::type>
{
  static inline void addElementTypes( H5::CompType& type,
                                      const TupleType& layout_tuple )
  {
    std::ostringstream oss;
    oss << "element_" << I;

    const size_t offset =
      reinterpret_cast<const uint8_t*>(&Utility::get<I>( layout_tuple )) -
      reinterpret_cast<const uint8_t*>(&layout_tuple);


    H5::DataType element_type =
      HDF5TypeTraits<typename TupleElement<I,TupleType>::type>::dataType();
    
    type.insertMember( oss.str(), offset, element_type );
  }

  static inline void addElementNames( std::string& type_name )
  { 
    type_name += HDF5TypeTraits<typename TupleElement<I,TupleType>::type>::name();
  }

  static inline void zeroElements( TupleType& tuple )
  {
    Utility::get<I>( tuple ) =
      HDF5TypeTraits<typename TupleElement<I,TupleType>::type>::zero();
  }

  static inline void oneElements( TupleType& tuple )
  {
    Utility::get<I>( tuple ) =
      HDF5TypeTraits<typename TupleElement<I,TupleType>::type>::one();
  }
};
  
} // end Details namespace

/*! \brief The partial specialization of the Utility::HDF5TypeTraits for the
 * Utility::Tuple struct
 * \ingroup hdf5_type_traits
 */
template<typename... Types>
struct HDF5TypeTraits<Tuple<Types...> >
{
  //! Typedef for the raw type
  typedef Tuple<Types...> RawType;
  
  //! Returns the HDF5 data type object corresponding to Utility::Tuple
  static H5::CompType dataType()
  {
    H5::CompType memtype( sizeof(RawType) );

    // the insertMember function can throw H5::DataTypeIException exceptions
    try
    {
      Details::HDF5TupleTypeHelper<0,RawType>::addElementTypes( memtype, RawType() );
    }

    HDF5_EXCEPTION_CATCH_RETHROW_AS( std::logic_error,
                                     "unable to create the HDF5 data type ("
                                     << name() << ")!" );

    return memtype;
  }

  //! Returns the name of this type
  static inline std::string name()
  {
    std::string type_name = "Utility::Tuple<";
    Details::HDF5TupleTypeHelper<0,RawType>::addElementNames( type_name );
    type_name += ">";

    return type_name;
  }

  //! Returns the zero value for this type
  static inline RawType zero()
  {
    RawType tuple;

    Details::HDF5TupleTypeHelper<0,RawType>::zeroElements( tuple );
    
    return tuple;
  }

  //! Returns the unity value for this type
  static inline RawType one()
  {
    RawType tuple;

    Details::HDF5TupleTypeHelper<0,RawType>::oneElements( tuple );
    
    return tuple;
  }
};

} // end Utility namespace

#endif // end UTILITY_HDF5_TYPE_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_HDF5TypeTraits.hpp
//---------------------------------------------------------------------------//
