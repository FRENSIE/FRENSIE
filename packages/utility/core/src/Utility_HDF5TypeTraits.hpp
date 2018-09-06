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
#include <string>

// FRENSIE Includes
#include "Utility_HDF5TypeTraitsDecl.hpp"
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

  //! Check if the type uses a custom internal type
  typedef std::false_type UsesCustomInternalType;

  //! Initialize internal data
  static inline InternalType* initializeInternalData(
                                            const ExternalType* raw_data,
                                            const size_t size )
  { return const_cast<InternalType*>(raw_data); }

  //! Convert external type data to internal type data
  static inline void convertExternalDataToInternalData(
                                           const ExternalType* raw_data,
                                           const size_t size,
                                           InternalType* converted_data )
  {
    if( raw_data != converted_data )
      std::memcpy( converted_data, raw_data, SizeOfT*size );
  }
  
  //! Covert inner type to outer type
  static inline void convertInternalDataToExternalData(
                                           const InternalType* raw_data,
                                           const size_t size,
                                           ExternalType* converted_data )
  {
    if( raw_data != converted_data )
      std::memcpy( converted_data, raw_data, SizeOfT*size );
  }

  //! Calculate the size of an internal array of data
  static inline size_t calculateInternalDataSize( const size_t external_size )
  { return external_size; }

  //! Calculate the size of an external array of data
  static inline size_t calculateExternalDataSize( const size_t internal_size )
  { return internal_size; }

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

  //! Check if the type has a type traits specialization
  typedef std::true_type IsSpecialized;

  //! Check if the type has an opaque data type
  typedef std::true_type UsesOpaqueDataType;

  //! Check if the type uses a custom internal type
  typedef std::false_type UsesCustomInternalType;

  //! Returns the HDF5 data type object corresponding to opaque type T
  static inline HDF5_ENABLED_DISABLED_SWITCH(const H5::PredType&,int) dataType()
  { return HDF5_ENABLED_DISABLED_SWITCH(H5::PredType::NATIVE_OPAQUE,0); }

  //! Initialize internal data
  static inline InternalType* initializeInternalData(
                                            const ExternalType* raw_data,
                                            const size_t size )
  { return const_cast<InternalType*>((const InternalType*)raw_data); }

  //! Convert external type data to internal type data
  static inline void convertExternalDataToInternalData(
                                           const ExternalType* raw_data,
                                           const size_t size,
                                           InternalType* converted_data )
  {
    if( raw_data != converted_data )
      std::memcpy( converted_data, raw_data, sizeof(ExternalType)*size );
  }
  
  //! Convert inner type to outer type
  static inline void convertInternalDataToExternalData(
                                           const InternalType* raw_data,
                                           const size_t size,
                                           ExternalType* converted_data )
  {
    if( raw_data != converted_data )
      std::memcpy( converted_data, raw_data, sizeof(ExternalType)*size );
  }

  //! Calculate the size of an internal array of data
  static inline size_t calculateInternalDataSize( const size_t external_size )
  { return external_size*sizeof(ExternalType); }

  //! Calculate the size of an external array of data
  static inline size_t calculateExternalDataSize( const size_t internal_size )
  { return internal_size/sizeof(ExternalType); }

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

  //! Check if the type has a type traits specialization
  typedef std::true_type IsSpecialized;

  //! Check if the type has an opaque data type
  typedef std::false_type UsesOpaqueDataType;

  //! Check if the type uses a custom internal type
  typedef std::true_type UsesCustomInternalType;
  
  //! Returns the HDF5 data type object corresponding to bool
  static HDF5_ENABLED_DISABLED_SWITCH(const H5::EnumType&,int) dataType();

  //! Initialize internal data
  static InternalType* initializeInternalData( const ExternalType*,
                                               const size_t size );

  //! Convert external type data to internal type data
  static void convertExternalDataToInternalData(
                                          const ExternalType* raw_data,
                                          const size_t size,
                                          InternalType* converted_data );
  //! Covert inner type to outer type
  static void convertInternalDataToExternalData(
                                          const InternalType* raw_data,
                                          const size_t size,
                                          ExternalType* converted_data );

  //! Calculate the size of an internal array of data
  static size_t calculateInternalDataSize( const size_t external_size );

  //! Calculate the size of an external array of data
  static size_t calculateExternalDataSize( const size_t internal_size );
  
  //! Free the inner data created from outer data
  static void freeInternalData( InternalType*& data );

private:

  // The data type
  HDF5_ENABLED_LINE( static std::unique_ptr<H5::EnumType> s_data_type );
};

/*! The specialization of Utility::HDF5TypeTraits for the std::string
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<std::string>
{
  //! Typedef for the type that will be used outside of HDF5 files
  typedef std::string ExternalType;

  //! Typedef for the type that will be stored in HDF5 files
  typedef const char* InternalType;

  //! Check if the type has a type traits specialization
  typedef std::true_type IsSpecialized;

  //! Check if the type has an opaque data type
  typedef std::false_type UsesOpaqueDataType;

  //! Check if the type uses a custom internal type
  typedef std::true_type UsesCustomInternalType;
  
  //! Returns the HDF5 data type object corresponding to std::string
  static HDF5_ENABLED_DISABLED_SWITCH(const H5::StrType&,int) dataType();

  //! Initialize internal data
  static InternalType* initializeInternalData( const ExternalType*,
                                               const size_t size );

  //! Convert external type data to internal type data
  static void convertExternalDataToInternalData(
                                          const ExternalType* raw_data,
                                          const size_t size,
                                          InternalType* converted_data );
  //! Covert inner type to outer type
  static void convertInternalDataToExternalData(
                                          const InternalType* raw_data,
                                          const size_t size,
                                          ExternalType* converted_data );

  //! Calculate the size of an internal array of data
  static size_t calculateInternalDataSize( const size_t external_size );

  //! Calculate the size of an external array of data
  static size_t calculateExternalDataSize( const size_t internal_size );
  
  //! Free the inner data created from outer data
  static void freeInternalData( InternalType*& data );

private:

  // The data type
  HDF5_ENABLED_LINE( static std::unique_ptr<H5::StrType> s_data_type );
};

/*! \brief Specialization of Utility::HDF5TypeTraits for char
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<char> : public Details::BasicHDF5TypeTraits<char>
{
  //! Check if the type has a type traits specialization
  typedef std::true_type IsSpecialized;
  
  //! Check if the type has an opaque data type
  typedef std::false_type UsesOpaqueDataType;
  
  //! Returns the HDF5 data type object corresponding tochar
  static inline HDF5_ENABLED_DISABLED_SWITCH(const H5::PredType&,int) dataType()
  { return HDF5_ENABLED_DISABLED_SWITCH(H5::PredType::NATIVE_CHAR,0); }
};

/*! \brief Specialization of Utility::HDF5TypeTraits for signed char
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<signed char> : public Details::BasicHDF5TypeTraits<signed char>
{
  //! Check if the type has a type traits specialization
  typedef std::true_type IsSpecialized;
  
  //! Check if the type has an opaque data type
  typedef std::false_type UsesOpaqueDataType;
  
  //! Returns the HDF5 data type object corresponding to signed char
  static inline HDF5_ENABLED_DISABLED_SWITCH(const H5::PredType&,int) dataType()
  { return HDF5_ENABLED_DISABLED_SWITCH(H5::PredType::NATIVE_SCHAR,0); }
};

/*! \brief Specialization of Utility::HDF5TypeTraits for unsigned char
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<unsigned char> : public Details::BasicHDF5TypeTraits<unsigned char>
{
  //! Check if the type has a type traits specialization
  typedef std::true_type IsSpecialized;
  
  //! Check if the type has an opaque data type
  typedef std::false_type UsesOpaqueDataType;
  
  //! Returns the HDF5 data type object corresponding to unsigned char
  static inline HDF5_ENABLED_DISABLED_SWITCH(const H5::PredType&,int) dataType()
  { return HDF5_ENABLED_DISABLED_SWITCH(H5::PredType::NATIVE_UCHAR,0); }
};

/* \brief Specialization of Utility::HDF5TypeTraits for wchar_t
 * \ingroup hdf5_type_traits
 */
// template<>
// struct HDF5TypeTraits<wchar_t> : public Details::OpaqueHDF5TypeTraits<wchar_t>
// { /* ... */ };

/*! \brief Specialization of Utility::HDF5TypeTraits for short
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<short> : public Details::BasicHDF5TypeTraits<short>
{
  //! Check if the type has a type traits specialization
  typedef std::true_type IsSpecialized;
  
  //! Check if the type has an opaque data type
  typedef std::false_type UsesOpaqueDataType;
  
  //! Returns the HDF5 data type object corresponding to int
  static inline HDF5_ENABLED_DISABLED_SWITCH(const H5::PredType&,int) dataType()
  { return HDF5_ENABLED_DISABLED_SWITCH(H5::PredType::NATIVE_SHORT,0); }
};
  
/*! \brief Specialization of Utility::HDF5TypeTraits for unsigned short
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<unsigned short> : public Details::BasicHDF5TypeTraits<unsigned short>
{
  //! Check if the type has a type traits specialization
  typedef std::true_type IsSpecialized;
  
  //! Check if the type has an opaque data type
  typedef std::false_type UsesOpaqueDataType;
  
  //! Returns the HDF5 data type object corresponding to int
  static inline HDF5_ENABLED_DISABLED_SWITCH(const H5::PredType&,int) dataType()
  { return HDF5_ENABLED_DISABLED_SWITCH(H5::PredType::NATIVE_USHORT,0); }
};

/*! \brief Specialization of Utility::HDF5TypeTraits for int
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<int> : public Details::BasicHDF5TypeTraits<int>
{
  //! Check if the type has a type traits specialization
  typedef std::true_type IsSpecialized;
  
  //! Check if the type has an opaque data type
  typedef std::false_type UsesOpaqueDataType;
  
  //! Returns the HDF5 data type object corresponding to int
  static inline HDF5_ENABLED_DISABLED_SWITCH(const H5::PredType&,int) dataType()
  { return HDF5_ENABLED_DISABLED_SWITCH(H5::PredType::NATIVE_INT,0); }
};

/*! \brief Specialization of Utility::HDF5TypeTraits for unsigned int
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<unsigned int> : public Details::BasicHDF5TypeTraits<unsigned int>
{
  //! Check if the type has a type traits specialization
  typedef std::true_type IsSpecialized;
  
  //! Check if the type has an opaque data type
  typedef std::false_type UsesOpaqueDataType;
  
  //! Returns the HDF5 data type object corresponding to unsigned int
  static inline HDF5_ENABLED_DISABLED_SWITCH(const H5::PredType&,int) dataType()
  { return HDF5_ENABLED_DISABLED_SWITCH(H5::PredType::NATIVE_UINT,0); }
};

/*! \brief Specialization of Utility::HDF5TypeTraits for long
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<long> : public Details::BasicHDF5TypeTraits<long>
{
  //! Check if the type has a type traits specialization
  typedef std::true_type IsSpecialized;
  
  //! Check if the type has an opaque data type
  typedef std::false_type UsesOpaqueDataType;
  
  //! Returns the HDF5 data type object corresponding to long
  static inline HDF5_ENABLED_DISABLED_SWITCH(const H5::PredType&,int) dataType() 
  { return HDF5_ENABLED_DISABLED_SWITCH(H5::PredType::NATIVE_LONG,0); }
};

/*! \brief Specialization of Utility::HDF5TypeTraits for unsigned long
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<unsigned long> : public Details::BasicHDF5TypeTraits<unsigned long>
{
  //! Check if the type has a type traits specialization
  typedef std::true_type IsSpecialized;
  
  //! Check if the type has an opaque data type
  typedef std::false_type UsesOpaqueDataType;
  
  //! Returns the HDF5 data type object corresponding to unsigned long int
  static inline HDF5_ENABLED_DISABLED_SWITCH(const H5::PredType&,int) dataType()
  { return HDF5_ENABLED_DISABLED_SWITCH(H5::PredType::NATIVE_ULONG,0); }
};

/*! \brief Specialization of Utility::HDF5TypeTraits for long long
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<long long> : public Details::BasicHDF5TypeTraits<long long>
{
  //! Check if the type has a type traits specialization
  typedef std::true_type IsSpecialized;
  
  //! Check if the type has an opaque data type
  typedef std::false_type UsesOpaqueDataType;
  
  //! Returns the HDF5 data type object corresponding to long long int
  static inline HDF5_ENABLED_DISABLED_SWITCH(const H5::PredType&,int) dataType() 
  { return HDF5_ENABLED_DISABLED_SWITCH(H5::PredType::NATIVE_LLONG,0); }
};

/*! \brief Specialization of Utility::HDF5TypeTraits for unsigned long
 * long
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<unsigned long long> : public Details::BasicHDF5TypeTraits<unsigned long long>
{
  //! Check if the type has a type traits specialization
  typedef std::true_type IsSpecialized;
  
  //! Check if the type has an opaque data type
  typedef std::false_type UsesOpaqueDataType;
  
  //! Returns the HDF5 data type object corresponding to unsigned long long int
  static inline HDF5_ENABLED_DISABLED_SWITCH(const H5::PredType&,int) dataType()
  { return HDF5_ENABLED_DISABLED_SWITCH(H5::PredType::NATIVE_ULLONG,0); }
};

/*! \brief Specialization of Utility::HDF5TypeTraits for float
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<float> : public Details::BasicHDF5TypeTraits<float>
{
  //! Check if the type has a type traits specialization
  typedef std::true_type IsSpecialized;
  
  //! Check if the type has an opaque data type
  typedef std::false_type UsesOpaqueDataType;
  
  //! Returns the HDF5 data type object corresponding to float
  static inline HDF5_ENABLED_DISABLED_SWITCH(const H5::PredType&,int) dataType()
  { return HDF5_ENABLED_DISABLED_SWITCH(H5::PredType::NATIVE_FLOAT,0); }
};

/*! \brief Specialization of Utility::HDF5TypeTraits for double
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<double> : public Details::BasicHDF5TypeTraits<double>
{
  //! Check if the type has a type traits specialization
  typedef std::true_type IsSpecialized;
  
  //! Check if the type has an opaque data type
  typedef std::false_type UsesOpaqueDataType;
  
  //! Returns the HDF5 data type object corresponding to double
  static inline HDF5_ENABLED_DISABLED_SWITCH(const H5::PredType&,int) dataType()
  { return HDF5_ENABLED_DISABLED_SWITCH(H5::PredType::NATIVE_DOUBLE,0); }
};

/*! \brief Specialization of Utility::HDF5TypeTraits for long double
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<long double> : public Details::BasicHDF5TypeTraits<long double>
{
  //! Check if the type has a type traits specialization
  typedef std::true_type IsSpecialized;
  
  //! Check if the type has an opaque data type
  typedef std::false_type UsesOpaqueDataType;
  
  //! Returns the HDF5 data type object corresponding to long double
  static inline HDF5_ENABLED_DISABLED_SWITCH(const H5::PredType&,int) dataType()
  { return HDF5_ENABLED_DISABLED_SWITCH(H5::PredType::NATIVE_LDOUBLE,0); }
};

namespace Details{

#ifdef HAVE_FRENSIE_HDF5
  
/*! The hdf5 type traits helper for std::pair
 * \ingroup hdf5_type_traits
 */
  template<typename T1, typename T2, typename InternalT1 = T1, typename InternalT2 = T2>
struct HDF5TypeTraitsPairHelper
{
  //! Returns the HDF5 data type object
  static inline const H5::CompType& dataType()
  {
    if( !s_data_type )
    {
      typedef std::pair<InternalT1,InternalT2> Pair;
      
      s_data_type.reset( new H5::CompType( sizeof(Pair) ) );

      s_data_type->insertMember( "first", HOFFSET(Pair, first), HDF5TypeTraits<T1>::dataType() );
      s_data_type->insertMember( "second", HOFFSET(Pair, second), HDF5TypeTraits<T2>::dataType() );
    }

    return *s_data_type;
  }

private:

  // The data type
  static std::unique_ptr<H5::CompType> s_data_type;
};

// Initialize static member data
template<typename T1, typename T2, typename InternalT1, typename InternalT2>
std::unique_ptr<H5::CompType> HDF5TypeTraitsPairHelper<T1,T2,InternalT1,InternalT2>::s_data_type;

#endif // end HAVE_FRENSIE_HDF5
  
} // end Details namespace

/*! \brief Partial specialization of Utility::HDF5TypeTraits for std::pair
 *
 * This partial specialization is only for pairs consisting of types that
 * do not use a custom internal type.
 * \ingroup hdf5_type_traits
 */
template<typename T1, typename T2>
struct HDF5TypeTraits<std::pair<T1,T2>,typename std::enable_if<!HDF5TypeTraits<T1>::UsesCustomInternalType::value && !HDF5TypeTraits<T2>::UsesCustomInternalType::value>::type> : public Details::BasicHDF5TypeTraits<std::pair<T1,T2> >
{
  /*! \brief Check if the type has a type traits specialization (only true if
   * both T1 and T2 have specializations)
   */
  typedef typename std::conditional<HDF5TypeTraits<T1>::IsSpecialized::value && HDF5TypeTraits<T2>::IsSpecialized::value,std::true_type,std::false_type>::type IsSpecialized;
  
  //! Check if the type has an opaque data type
  typedef std::false_type UsesOpaqueDataType;
  
  //! Returns the HDF5 data type object corresponding to std::pair<T1,T2>
  static inline HDF5_ENABLED_DISABLED_SWITCH(const H5::CompType&,int) dataType()
  {
#ifdef HAVE_FRENSIE_HDF5
    return Details::HDF5TypeTraitsPairHelper<T1,T2>::dataType();
#else
    return 0;
#endif
  }
};

/*! \brief Partial specialization of Utility::HDF5TypeTraits for std::pair
 *
 * This partial specialization is for pairs consisting of at least one type 
 * that uses a custom internal type.
 * \ingroup hdf5_type_traits
 */
template<typename T1, typename T2>
struct HDF5TypeTraits<std::pair<T1,T2>,typename std::enable_if<HDF5TypeTraits<T1>::UsesCustomInternalType::value || HDF5TypeTraits<T2>::UsesCustomInternalType::value>::type>
{
 private:

  // Internal T1
  typedef typename std::remove_const<typename std::conditional<HDF5TypeTraits<T1>::UsesCustomInternalType::value,typename HDF5TypeTraits<T1>::InternalType,T1>::type>::type InternalT1;

  // Internal T2
  typedef typename std::conditional<HDF5TypeTraits<T2>::UsesCustomInternalType::value,typename HDF5TypeTraits<T2>::InternalType,T2>::type InternalT2;

 public:
  
  //! Typedef for the type that will be used outside of HDF5 files
  typedef std::pair<T1,T2> ExternalType;

  //! Typedef for the type that will be stored in HDF5 files
  typedef std::pair<InternalT1,InternalT2> InternalType;

  /*! \brief Check if the type has a type traits specialization (only true if
   * both T1 and T2 have specializations)
   */
  typedef typename std::conditional<HDF5TypeTraits<T1>::IsSpecialized::value && HDF5TypeTraits<T2>::IsSpecialized::value,std::true_type,std::false_type>::type IsSpecialized;
  
  //! Check if the type has an opaque data type
  typedef std::false_type UsesOpaqueDataType;

  //! Check if the type uses a custom internal type
  typedef std::true_type UsesCustomInternalType;
  
  //! Returns the HDF5 data type object corresponding to bool
  static inline HDF5_ENABLED_DISABLED_SWITCH(const H5::CompType&,int) dataType()
  {
#ifdef HAVE_FRENSIE_HDF5
    return Details::HDF5TypeTraitsPairHelper<T1,T2,InternalT1,InternalT2>::dataType();
#else
    return 0;
#endif
  }

  //! Initialize internal data
  static inline InternalType* initializeInternalData(
                                                  const ExternalType* raw_data,
                                                  const size_t size )
  { return new InternalType[size]; }

  //! Convert external type data to internal type data
  static inline void convertExternalDataToInternalData(
                                           const ExternalType* raw_data,
                                           const size_t size,
                                           InternalType* converted_data )
  {
    for( size_t i = 0; i < size; ++i )
    {
      HDF5TypeTraits<T1>::convertExternalDataToInternalData( &raw_data[i].first, 1, &converted_data[i].first );
      HDF5TypeTraits<T2>::convertExternalDataToInternalData( &raw_data[i].second, 1, &converted_data[i].second );
    }
  }
  
  //! Convert internal type data to external type data
  static inline void convertInternalDataToExternalData(
                                              const InternalType* raw_data,
                                              const size_t size,
                                              ExternalType* converted_data )
  {
    typedef typename std::remove_const<T1>::type NonConstT1;
    
    for( size_t i = 0; i < size; ++i )
    {
      // When loading map::value_type arrays the first pair element will be
      // const qualified - we must remove this to set the data
      HDF5TypeTraits<NonConstT1>::convertInternalDataToExternalData( &raw_data[i].first, 1, const_cast<NonConstT1*>(&converted_data[i].first) );
      HDF5TypeTraits<T2>::convertInternalDataToExternalData( &raw_data[i].second, 1, &converted_data[i].second );
    }
  }

  //! Calculate the size of an internal array of data
  static inline size_t calculateInternalDataSize( const size_t external_size )
  { return external_size; }

  //! Calculate the size of an external array of data
  static inline size_t calculateExternalDataSize( const size_t internal_size )
  { return internal_size; }

  //! Free the inner data created from outer data
  static inline void freeInternalData( InternalType*& data )
  {
    delete[] data;
    data = NULL;
  }
};

namespace Details{

/*! The hdf5 tuple serializer intermediate tuple helper class
 * \ingroup hdf5
 */
template<typename... Types>
struct HDF5TupleSerializerIntermediateTupleHelper
{
  typedef std::tuple<typename std::conditional<HDF5TypeTraits<Types>::UsesCustomInternalType::value,typename HDF5TypeTraits<Types>::InternalType,typename HDF5TypeTraits<Types>::ExternalType>::type...> type;
};

/*! \brief Partial specialization of HDF5TupleSerializerIntermediateTupleHelper
 * for std::tuple
 * \ingroup hdf5
 */
template<typename... Types>
struct HDF5TupleSerializerIntermediateTupleHelper<std::tuple<Types...> > : public HDF5TupleSerializerIntermediateTupleHelper<Types...>
{ /* ... */ };

/*! \brief The helper class that gets the offset of the tuple element in a
 * serialized array
 * \ingroup hdf5
 */
template<size_t I, typename ExternalTuple, typename Enabled = void>
struct HDF5TupleSerializerElementOffsetHelper
{
  //! Return the offset of tuple element I
  static inline size_t offset()
  {
    typedef typename Utility::TupleElement<I-1,ExternalTuple>::type RawPreviousElementType;
    typedef typename std::conditional<HDF5TypeTraits<RawPreviousElementType>::UsesCustomInternalType::value,typename HDF5TypeTraits<RawPreviousElementType>::InternalType,RawPreviousElementType>::type PreviousElementType;
    
    return HDF5TupleSerializerElementOffsetHelper<I-1,ExternalTuple>::offset() + sizeof(PreviousElementType);
  }
};

/*! \brief Partial specialization of HDF5TupleSerializerElementOffsetHelper for
 * I==0
 * \ingroup hdf5
 */
template<size_t I, typename ExternalTuple>
struct HDF5TupleSerializerElementOffsetHelper<I,ExternalTuple,typename std::enable_if<I==0>::type>
{
  //! Return the offset of tuple element I
  static inline size_t offset()
  { return 0; }
};

#ifdef HAVE_FRENSIE_HDF5
  
/*! The helper class that constructs a tuple HDF5 data type
 * \ingroup hdf5
 */
template<size_t I, typename ExternalTuple, typename Enabled = void>
struct HDF5TupleSerializerDataTypeHelper
{
  static inline void addElementTypes( H5::CompType& type )
  {
    std::ostringstream oss;
    oss << "element_" << I;

    const size_t offset =
      HDF5TupleSerializerElementOffsetHelper<I,ExternalTuple>::offset();

    const H5::DataType& element_type =
      HDF5TypeTraits<typename TupleElement<I,ExternalTuple>::type>::dataType();
    
    type.insertMember( oss.str(), offset, element_type );

    // Add the remaining tuple elements
    HDF5TupleSerializerDataTypeHelper<I+1,ExternalTuple>::addElementTypes( type );
  }
};

/*! \brief Partial specialization of HDF5TupleSerializerDataTypeHelper for
 * I==tuple size
 * \ingroup hdf5
 */
template<size_t I, typename ExternalTuple>
struct HDF5TupleSerializerDataTypeHelper<I,ExternalTuple,typename std::enable_if<(I>=TupleSize<ExternalTuple>::value)>::type>
{
  static inline void addElementTypes( H5::CompType& )
  { /* ... */ }
};

#endif // end HAVE_FRENSIE_HDF5

/*! The next element hdf5 type traits helper class
 * \ingroup hfd5
 */
template<size_t I, typename ExternalTuple, typename Enabled = void>
struct NextElementHDF5TypeTraits
{
  typedef HDF5TypeTraits<typename Utility::TupleElement<I+1,ExternalTuple>::type> type;
};

/*! \brief Partial specialization of NextElementHDF5TypeTraits for 
 * I==TupleSize-1
 * \ingroup hdf5
 */
template<size_t I, typename ExternalTuple>
struct NextElementHDF5TypeTraits<I,ExternalTuple,typename std::enable_if<(I==Utility::TupleSize<ExternalTuple>::value-1)>::type>
{
  typedef HDF5TypeTraits<typename Utility::TupleElement<I,ExternalTuple>::type> type;
};

/*! \brief The helper class that serializes tuple data in a portable way (by
 * ignoring platform specific tuple memory layout details).
 * \ingroup hdf5
 */
template<size_t I, typename ExternalTuple, typename Enabled = void>
struct HDF5TupleSerializerHelper
{
  typedef HDF5TypeTraits<typename Utility::TupleElement<I,ExternalTuple>::type> CurrentElementHDF5TypeTraits;
  typedef typename NextElementHDF5TypeTraits<I,ExternalTuple>::type NextElementHDF5TypeTraits;

  //! Serialize an element that has a custom internal type
  static inline void serialize( const ExternalTuple& tuple,
                                void* serialized_data,
                                std::true_type )
  {
    typename CurrentElementHDF5TypeTraits::InternalType intermediate_element;
    CurrentElementHDF5TypeTraits::convertExternalDataToInternalData( &Utility::get<I>(tuple), 1, &intermediate_element );
    
    std::memcpy( (uint8_t*)serialized_data+HDF5TupleSerializerElementOffsetHelper<I,ExternalTuple>::offset(),
                 &intermediate_element,
                 sizeof(typename CurrentElementHDF5TypeTraits::InternalType) );

    HDF5TupleSerializerHelper<I+1,ExternalTuple>::serialize( tuple, serialized_data, typename NextElementHDF5TypeTraits::UsesCustomInternalType() );
  }

  //! Serialize an element with a standard internal type
  static inline void serialize( const ExternalTuple& tuple,
                                void* serialized_data,
                                std::false_type )
  {
    std::memcpy( (uint8_t*)serialized_data+HDF5TupleSerializerElementOffsetHelper<I,ExternalTuple>::offset(),
                 &Utility::get<I>( tuple ),
                 sizeof(typename Utility::TupleElement<I,ExternalTuple>::type) );

    HDF5TupleSerializerHelper<I+1,ExternalTuple>::serialize( tuple, serialized_data, typename NextElementHDF5TypeTraits::UsesCustomInternalType() );
  }

  //! Deserialize an element with a custom internal type
  static inline void deserialize( ExternalTuple& tuple,
                                  const void* serialized_data,
                                  std::true_type )
  {
    typename CurrentElementHDF5TypeTraits::InternalType intermediate_element;

    std::memcpy( &intermediate_element,
                 (const uint8_t*)serialized_data+HDF5TupleSerializerElementOffsetHelper<I,ExternalTuple>::offset(),
                 sizeof(typename CurrentElementHDF5TypeTraits::InternalType) );

    CurrentElementHDF5TypeTraits::convertInternalDataToExternalData( &intermediate_element, 1, &Utility::get<I>(tuple) );

    HDF5TupleSerializerHelper<I+1,ExternalTuple>::deserialize( tuple, serialized_data, typename NextElementHDF5TypeTraits::UsesCustomInternalType() );
  }

  //! Deserialize an element with a standard internal type
  static inline void deserialize( ExternalTuple& tuple,
                                  const void* serialized_data,
                                  std::false_type )
  {
    std::memcpy( &Utility::get<I>( tuple ),
                 (const uint8_t*)serialized_data+HDF5TupleSerializerElementOffsetHelper<I,ExternalTuple>::offset(),
                 sizeof(typename Utility::TupleElement<I,ExternalTuple>::type) );

    HDF5TupleSerializerHelper<I+1,ExternalTuple>::deserialize( tuple, serialized_data, typename NextElementHDF5TypeTraits::UsesCustomInternalType() );
  }
};

/*! \brief Partial specialization of HDF5TupleSerializerHelper for I==TupleSize
 * \ingroup hdf5
 */
template<size_t I, typename ExternalTuple>
struct HDF5TupleSerializerHelper<I,ExternalTuple,typename std::enable_if<(I>=Utility::TupleSize<ExternalTuple>::value)>::type>
{
  template<typename Tag>
  static inline void serialize( const ExternalTuple&, void*, Tag )
  { /* ... */ }

  template<typename Tag>
  static inline void deserialize( ExternalTuple&, const void*, Tag )
  { /* ... */ }
};
  
/*! The hdf5 tuple serializer class
 *
 * This class ensures that our HDF5 files will remain portable by providing an 
 * intermediate serialization method that consistently orders the tuple 
 * elements before sending the tuple to the hdf5 file (the C++ standard does
 * not require that tuple elements be in any particular order).
 * \ingroup hdf5
 */
template<typename ExternalType>
struct HDF5TupleSerializer
{
public:

  //! The intermediate tuple type
  typedef typename HDF5TupleSerializerIntermediateTupleHelper<ExternalType>::type IntermediateType;

  //! Constructor
  explicit HDF5TupleSerializer( void* serialized_data )
    : d_serialized_data( serialized_data )
  { /* ... */ }

  //! Destructor
  ~HDF5TupleSerializer()
  { /* ... */ }

#ifdef HAVE_FRENSIE_HDF5
  //! Return the HDF5 data type
  static inline const H5::CompType& getDataType()
  {
    if( !s_data_type )
    {
      s_data_type.reset( new H5::CompType( sizeof(IntermediateType) ) );
      
      HDF5TupleSerializerDataTypeHelper<0,ExternalType>::addElementTypes( *s_data_type );
    }

    return *s_data_type;
  }
#endif //end HAVE_FRENSIE_HDF5

  //! Return the size of serialized data (in bytes)
  static inline size_t getSerializedDataSize()
  { return sizeof(IntermediateType); }

  //! Return the offset for a tuple element
  template<size_t I>
  static size_t getOffset()
  { return HDF5TupleSerializerElementOffsetHelper<I,ExternalType>::offset(); }

  //! Set the data
  void serialize( const ExternalType& tuple )
  {
    HDF5TupleSerializerHelper<0,ExternalType>::serialize( tuple, d_serialized_data, typename HDF5TypeTraits<typename Utility::TupleElement<0,ExternalType>::type>::UsesCustomInternalType() );
  }

  //! Initialize a tuple
  void deserialize( ExternalType& tuple ) const
  {
    HDF5TupleSerializerHelper<0,ExternalType>::deserialize( tuple, d_serialized_data, typename HDF5TypeTraits<typename Utility::TupleElement<0,ExternalType>::type>::UsesCustomInternalType() );
  }
  
private:

  // The data type
  HDF5_ENABLED_LINE( static std::unique_ptr<H5::CompType> s_data_type );

  // The tuple element serialized data
  void* d_serialized_data;
};

// Initialize static member data
#ifdef HAVE_FRENSIE_HDF5
template<typename ExternalType>
std::unique_ptr<H5::CompType> HDF5TupleSerializer<ExternalType>::s_data_type;
#endif // end HAVE_FRENSIE_HDF5

/*! IsSpecialized helper for tuples
 * \ingroup hdf5
 */
template<typename... Types>
struct IsSpecializedHelper;

/*! \brief Partial specialization of IsSpecializedHelper for parameter packs 
 * with at least two elements
 */
template<typename T, typename... Types>
struct IsSpecializedHelper<T,Types...>
{
  typedef typename std::conditional<HDF5TypeTraits<T>::IsSpecialized::value && IsSpecializedHelper<Types...>::type::value,std::true_type,std::false_type>::type type;
};

/*! \brief Partial specialization of IsSpecializedHelper for parameter packs 
 * with a single element
 */
template<typename T>
struct IsSpecializedHelper<T>
{
  typedef typename std::conditional<HDF5TypeTraits<T>::IsSpecialized::value,std::true_type,std::false_type>::type type;
};
  
} // end Details namespace

/*! \brief The partial specialization of Utility::HDF5TypeTraits for the
 * Utility::Tuple struct
 * \ingroup hdf5_type_traits
 */
template<typename... Types>
struct HDF5TypeTraits<std::tuple<Types...> >
{  
  //! Typedef for the type that will be used outside of HDF5 files
  typedef std::tuple<Types...> ExternalType;

  //! Typedef for the type that will be stored in HDF5 files
  typedef void InternalType;

  //! Check if the type has a type traits specialization
  typedef typename Details::IsSpecializedHelper<Types...>::type IsSpecialized;
  
  //! Check if the type has an opaque data type
  typedef std::false_type UsesOpaqueDataType;

  //! Check if the type uses a custom internal type
  typedef std::true_type UsesCustomInternalType;
  
  //! Returns the HDF5 data type object corresponding to Utility::Tuple
  static inline HDF5_ENABLED_DISABLED_SWITCH(const H5::CompType&,int) dataType()
  {
#ifdef HAVE_FRENSIE_HDF5
    return Details::HDF5TupleSerializer<ExternalType>::getDataType();
#else
    return 0;
#endif
  }

  //! Initialize internal data
  static inline InternalType* initializeInternalData(
                                            const ExternalType*,
                                            const size_t size )
  {
    return malloc( size*Details::HDF5TupleSerializer<ExternalType>::getSerializedDataSize() );
  }

  //! Convert external type data to internal type data
  static inline void convertExternalDataToInternalData(
                                           const ExternalType* raw_data,
                                           const size_t size,
                                           InternalType* converted_data )
  {
    for( size_t i = 0; i < size; ++i )
    {
      Details::HDF5TupleSerializer<ExternalType>
        serializer( (uint8_t*)converted_data + Details::HDF5TupleSerializer<ExternalType>::getSerializedDataSize()*i );
      
      serializer.serialize( raw_data[i] );
    }
  }
  
  //! Convert internal type data to external type data
  static inline void convertInternalDataToExternalData(
                                              const InternalType* raw_data,
                                              const size_t size,
                                              ExternalType* converted_data )
  {
    for( size_t i = 0; i < size; ++i )
    {
      Details::HDF5TupleSerializer<ExternalType>
        serializer( (uint8_t*)const_cast<void*>(raw_data) + Details::HDF5TupleSerializer<ExternalType>::getSerializedDataSize()*i );
      
      serializer.deserialize( converted_data[i] );
    }
  }

  //! Calculate the size of an internal array of data
  static inline size_t calculateInternalDataSize( const size_t external_size )
  { return external_size; }

  //! Calculate the size of an external array of data
  static inline size_t calculateExternalDataSize( const size_t internal_size )
  { return internal_size; }

  //! Free the inner data created from outer data
  static inline void freeInternalData( InternalType*& data )
  {
    free(data);
    data = NULL;
  }
};

} // end Utility namespace

#endif // end UTILITY_HDF5_TYPE_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_HDF5TypeTraits.hpp
//---------------------------------------------------------------------------//
