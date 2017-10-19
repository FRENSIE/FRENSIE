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
#include <type_traits>

// FRENSIE Includes
#include "Utility_HDF5TypeTraitsDecl.hpp"
#include "Utility_HDF5ExceptionCatchMacros.hpp"
#include "Utility_Tuple.hpp"

namespace Utility{

namespace Details{

/*! Helper class for types that have the same internal and external types
 * \ingroup hdf5_type_traits
 */
template<typename T, size_t SizeOfT = sizeof(T)>
struct BasicHDF5TypeTraits
{
  //! Typedef for the type that will be used outside of HDF5 files
  typedef T ExternalType;

  //! Typedef for the type that will be stored in HDF5 files
  typedef ExternalType InternalType;

  //! Initialize internal data
  static inline InternalType* initializeInternalData(
                                            const ExternalType* const raw_data,
                                            const size_t size )
  { return raw_data; }

  //! Convert external type data to internal type data
  static inline void convertExternalDataToInternalData(
                                           const ExternalType* const raw_data,
                                           const size_t size,
                                           const InternalType* converted_data )
  {
    if( raw_data != converted_data )
      std::memcpy( converted_data, raw_data, SizeOfT*size );
  }
  
  //! Covert inner type to outer type
  static inline void convertInternalDataToExternalData(
                                           const InternalType* const raw_data,
                                           const size_t size,
                                           const ExternalType* converted_data )
  {
    if( raw_data != converted_data )
      std::memcpy( converted_data, raw_data, SizeOfT*size );
  }

  //! Calculate the size of an internal array of data
  static inline size_t calculateInternalDataSize( const size_t raw_size )
  { return raw_size; }

  //! Free the inner data created from outer data
  static inline void freeInternalData( InternalType*& )
  { /* ... */ }
};

/*! Helper class for types that use an opaque internal type
 * \ingroup hdf5_type_traits
 */
template<typename T>
struct OpaqueHDF5TypeTraits
{
  //! Typedef for the type that will be used outside of HDF5 files
  typedef T ExternalType;

  //! Typedef for the type that will be stored in HDF5 files
  typedef void InternalType;

  //! Returns the HDF5 data type object corresponding to opaque type T
  static inline H5::PredType dataType()
  { return H5::NATIVE_OPAQUE; }

  //! Initialize internal data
  static inline InternalType* initializeInternalData(
                                            const ExternalType* const raw_data,
                                            const size_t size )
  { return raw_data; }

  //! Convert external type data to internal type data
  static inline void convertExternalDataToInternalData(
                                           const ExternalType* const raw_data,
                                           const size_t size,
                                           const InternalType* converted_data )
  {
    if( raw_data != converted_data )
      std::memcpy( converted_data, raw_data, sizeof(ExternalType)*size );
  }
  
  //! Covert inner type to outer type
  static inline void convertInternalDataToExternalData(
                                           const InternalType* const raw_data,
                                           const size_t size,
                                           const ExternalType* converted_data )
  {
    if( raw_data != converted_data )
      std::memcpy( converted_data, raw_data, sizeof(ExternalType)*size );
  }

  //! Calculate the size of an internal array of data
  static inline size_t calculateInternalDataSize( const size_t raw_size )
  { return raw_size*sizeof(ExternalType); }

  //! Free the inner data created from outer data
  static inline void freeInternalData( InternalType*& )
  { /* ... */ }
};
  
} // end Details namespace

/*! \brief Partial specialization of Utility::HDF5TypeTraits for
 * all constant types
 * \ingroup hdf5_type_traits
 */
template<typename T>
struct HDF5TypeTraits<T,typename std::enable_if<std::is_const<T>::value>::type> : public HDF5TypeTraits<typename std::remove_const<T>::type>
{ /* ... */ };

/*! \brief Specialization of Utility::HDF5TypeTraits for bool
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<bool>
{
  //! Typedef for the type that will be used outside of HDF5 files
  typedef bool ExternalType;

  //! The enumeration type used to represent boolean values
  typedef enum { False = 0, True = 1 } BoolEnumType;
  
  //! Typedef for the type that will be stored in HDF5 files
  typedef BoolEnumType InternalType;
  
  //! Returns the HDF5 data type object corresponding to bool
  static H5::EnumType dataType();

  //! Initialize internal data
  static InternalType* initializeInternalData( const ExternalType* const,
                                               const size_t size );

  //! Convert external type data to internal type data
  static void convertExternalDataToInternalData(
                                          const ExternalType* const raw_data,
                                          const size_t size,
                                          const InternalType* converted_data );
  //! Covert inner type to outer type
  static void convertInternalDataToExternalData(
                                          const InternalType* const raw_data,
                                          const size_t size,
                                          const ExternalType* converted_data );
  //! Free the inner data created from outer data
  static void freeInternalData( InternalType*& data );

private:

  // The data type
  static std::unique_ptr<H5::EnumType> s_data_type;
};

/*! \brief Specialization of Utility::HDF5TypeTraits for char
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<char> : public Details::BasicHDF5TypeTraits<char>
{  
  //! Returns the HDF5 data type object corresponding tochar
  static inline H5::PredType dataType()
  { return H5::PredType::NATIVE_CHAR; }
};

/*! \brief Specialization of Utility::HDF5TypeTraits for signed char
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<signed char> : public Details::BasicHDF5TypeTraits<signed char>
{
  //! Returns the HDF5 data type object corresponding to signed char
  static inline H5::PredType dataType()
  { return H5::PredType::NATIVE_SCHAR; }
};

/*! \brief Specialization of Utility::HDF5TypeTraits for unsigned char
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<unsigned char> : public Details::BasicHDF5TypeTraits<unsigned char>
{
  //! Returns the HDF5 data type object corresponding to unsigned char
  static inline H5::PredType dataType()
  { return H5::PredType::NATIVE_UCHAR; }
};

/*! \brief Specialization of Utility::HDF5TypeTraits for wchar_t
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<wchar_t> : public Details::OpaqueHDF5TypeTraits<wchar_t>
{ /* ... */ };

/*! \brief Specialization of Utility::HDF5TypeTraits for short
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<short> : public Details::BasicHDF5TypeTraits<short>
{
  //! Returns the HDF5 data type object corresponding to int
  static inline H5::PredType dataType()
  { return H5::PredType::NATIVE_SHORT; }
};
  
/*! \brief Specialization of Utility::HDF5TypeTraits for unsigned short
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<unsigned short> : public Details::BasicHDF5TypeTraits<unsigned short>
{
  //! Returns the HDF5 data type object corresponding to int
  static inline H5::PredType dataType()
  { return H5::PredType::NATIVE_USHORT; }
};

/*! \brief Specialization of Utility::HDF5TypeTraits for int
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<int> : public Details::BasicHDF5TypeTraits<int>
{
  //! Returns the HDF5 data type object corresponding to int
  static inline H5::PredType dataType()
  { return H5::PredType::NATIVE_INT; }
};

/*! \brief Specialization of Utility::HDF5TypeTraits for unsigned int
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<unsigned int> : public Details::BasicHDF5TypeTraits<unsigned int>
{
  //! Returns the HDF5 data type object corresponding to unsigned int
  static inline H5::PredType dataType()
  { return H5::PredType::NATIVE_UINT; }
};

/*! \brief Specialization of Utility::HDF5TypeTraits for long
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<long> : public Details::BasicHDF5TypeTraits<long>
{
  //! Returns the HDF5 data type object corresponding to long
  static inline H5::PredType dataType() 
  { return H5::PredType::NATIVE_LONG; }
};

/*! \brief Specialization of Utility::HDF5TypeTraits for unsigned long
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<unsigned long> : public Details::BasicHDF5TypeTraits<unsigned long>
{
  //! Returns the HDF5 data type object corresponding to unsigned int
  static inline H5::PredType dataType()
  { return H5::PredType::NATIVE_ULONG; }
};

/*! \brief Specialization of Utility::HDF5TypeTraits for long long
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<long long> : public Details::BasicHDF5TypeTraits<long long>
{
  //! Returns the HDF5 data type object corresponding to long long int
  static inline H5::PredType dataType() 
  { return H5::PredType::NATIVE_LLONG; }
};

/*! \brief Specialization of Utility::HDF5TypeTraits for unsigned long
 * long
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<unsigned long long> : public Details::BasicHDF5TypeTraits<unsigned long long>
{
  //! Returns the HDF5 data type object corresponding to unsigned int
  static inline H5::PredType dataType()
  { return H5::PredType::NATIVE_ULLONG; }
};

/*! \brief Specialization of Utility::HDF5TypeTraits for float
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<float> : public Details::BasicHDF5TypeTraits<double>
{
  //! Returns the HDF5 data type object corresponding to double
  static inline H5::PredType dataType()
  { return H5::PredType::NATIVE_FLOAT; }
};

/*! \brief Specialization of Utility::HDF5TypeTraits for double
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<double> : public Details::BasicHDF5TypeTraits<double>
{
  //! Returns the HDF5 data type object corresponding to double
  static inline H5::PredType dataType()
  { return H5::PredType::NATIVE_DOUBLE; }
};

/*! \brief Specialization of Utility::HDF5TypeTraits for long double
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<long double> : public Details::BasicHDF5TypeTraits<long double>
{
  //! Returns the HDF5 data type object corresponding to double
  static inline H5::PredType dataType()
  { return H5::PredType::NATIVE_LDOUBLE; }
};

/*! \brief Partial specialization of Utility::HDF5TypeTraits for std::pair
 * \ingroup hdf5_type_traits
 */
template<typename T1, typename T2>
struct HDF5TypeTraits<std::pair<T1,T2> > : public Details::BasicHDF5TypeTraits<std::pair<T1,T2> >
{
  //! Returns the HDF5 data type object corresponding to bool
  static inline H5::CompType dataType()
  {
    if( !s_data_type )
    {
      s_data_type.reset( new H5::CompType( sizeof(std::pair<T1,T2>) ) );
      
      s_data_type.insertMember( "first", HOFFSET(std::pair<T1,T2>, first), HDF5TypeTraits<T1>::dataType() );
      s_data_type.insertMember( "second", HOFFSET(std::pair<T1,T2>, second), HDF5TypeTraits<T2>::dataType() );
    }

    return *s_data_type;
  }

private:

  // The data type
  static std::unique_ptr<H5::CompType> s_data_type;
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

/*! \brief The partial specialization of Utility::HDF5TypeTraits for the
 * Utility::Tuple struct
 * \ingroup hdf5_type_traits
 */
template<typename... Types>
struct HDF5TypeTraits<Tuple<Types...> > : public Details::BasicHDF5TypeTraits<Tuple<Types...> >
{
  //! Returns the HDF5 data type object corresponding to Utility::Tuple
  static inline H5::CompType dataType()
  {
    if( !s_data_type )
    {
      s_data_type.reset( new H5::CompType( sizeof(Tuple<Types...>) ) );
      
      Details::HDF5TupleTypeHelper<0,RawType>::addElementTypes( *s_data_type, Tuple<Types...>() );
    }

    return *s_data_type;
  }

private:

  // The data type
  std::unique_ptr<H5::CompType> s_data_type
};

} // end Utility namespace

#endif // end UTILITY_HDF5_TYPE_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_HDF5TypeTraits.hpp
//---------------------------------------------------------------------------//
