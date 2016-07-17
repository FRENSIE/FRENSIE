//---------------------------------------------------------------------------//
//!
//! \file   Utility_HDF5TypeTraits.hpp
//! \author Alex Robinson
//! \brief  HDF5 Type Traits specializations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HDF5_TYPE_TRAITS_HPP
#define UTILITY_HDF5_TYPE_TRAITS_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_HDF5TypeTraitsDecl.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

namespace Utility{

/*! \brief The specialization of the Utility::HDF5TypeTraits for double
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<double>
{
  //! Returns the HDF5 data type object corresponding to double
  static inline H5::PredType dataType() 
  { return H5::PredType::NATIVE_DOUBLE; }
  
  //! Returns the name of this type
  static inline std::string name() 
  { return "double"; }
  
  //! Returns the zero value for this type
  static inline double zero() 
  { return Teuchos::ScalarTraits<double>::zero(); }

  //! Returns the unity value for this type
  static inline double one()
  { return Teuchos::ScalarTraits<double>::one(); }
};

/*! \brief The specialization of the Utility::HDF5TypeTraits for const double
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<const double> : public HDF5TypeTraits<double>
{ /* ... */ };

/*! \brief The specialization of the Utility::HDF5TypeTraits for float
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<float>
{
  //! Returns the HDF5 data type object corresponding to double
  static inline H5::PredType dataType() 
  { return H5::PredType::NATIVE_FLOAT; }
  
  //! Returns the name of this type
  static inline std::string name() 
  { return "double"; }
  
  //! Returns the zero value for this type
  static inline float zero() 
  { return Teuchos::ScalarTraits<float>::zero(); }

  //! Returns the unity value for this type
  static inline float one()
  { return Teuchos::ScalarTraits<float>::one(); }
};

/*! \brief The specialization of the Utility::HDF5TypeTraits for const float
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<const float> : public HDF5TypeTraits<float>
{ /* ... */ };

/*! \brief The specialization of the Utility::HDF5TypeTraits for int
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<int>
{
  //! Returns the HDF5 data type object corresponding to int
  static inline H5::PredType dataType() 
  { return H5::PredType::NATIVE_INT; }

  //! Returns the name of this type
  static inline std::string name() 
  { return "int"; }

  //! Returns the zero value for this type
  static inline int zero()
  { return Teuchos::ScalarTraits<int>::zero(); }

  //! Returns the unity value for this type
  static inline int one()
  { return Teuchos::ScalarTraits<int>::one(); }
};

/*! \brief The specialization of the Utility::HDF5TypeTraits for unsigned int
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<unsigned int>
{
  //! Returns the HDF5 data type object corresponding to unsigned int
  static inline H5::PredType dataType() 
  { return H5::PredType::NATIVE_UINT; }
  
  //! Returns the name of the type
  static inline std::string name() 
  { return "unsigned int"; }
  
  //! Returns the zero value for this type
  static inline unsigned zero()
  { return Teuchos::ScalarTraits<unsigned>::zero(); }

  //! Returns the unity value for this type
  static inline unsigned one()
  { return Teuchos::ScalarTraits<unsigned>::one(); }
};

/*! \brief The specialization of the Utility::HDF5TypeTraits for const int
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<const int> : public HDF5TypeTraits<int>
{ /* ... */ };

/*! \brief The specialization of the Utility::HDF5TypeTraits for long
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<long>
{
  //! Returns the HDF5 data type object corresponding to long
  static inline H5::PredType dataType() 
  { return H5::PredType::NATIVE_LONG; }
  
  //! Returns the name of the type
  static inline std::string name() 
  { return "long int"; }
  
  //! Returns the zero value for this type
  static inline unsigned zero()
  { return 0l; }

  //! Returns the unity value for this type
  static inline unsigned one()
  { return 1l; }
};

/*! \brief The specialization of the Utility::HDF5TypeTraits for const long
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<const long> : public HDF5TypeTraits<long>
{ /* ... */ };

/*! \brief The specialization of the Utility::HDF5TypeTraits for unsigned long
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<unsigned long>
{
  //! Returns the HDF5 data type object corresponding to unsigned int
  static inline H5::PredType dataType() 
  { return H5::PredType::NATIVE_ULONG; }
  
  //! Returns the name of the type
  static inline std::string name() 
  { return "unsigned long int"; }
  
  //! Returns the zero value for this type
  static inline unsigned zero()
  { return 0ul; }

  //! Returns the unity value for this type
  static inline unsigned one()
  { return 1ul; }
};

/*! \brief The specialization of the Utility::HDF5TypeTraits for const unsigned
 * long
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<const unsigned long> : public HDF5TypeTraits<unsigned long>
{ /* ... */ };

/*! \brief The specialization of the Utility::HDF5TypeTraits for long long
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<long long>
{
  //! Returns the HDF5 data type object corresponding to long long int
  static inline H5::PredType dataType() 
  { return H5::PredType::NATIVE_LLONG; }
  
  //! Returns the name of the type
  static inline std::string name() 
  { return "long long int"; }
  
  //! Returns the zero value for this type
  static inline unsigned zero()
  { return 0ll; }

  //! Returns the unity value for this type
  static inline unsigned one()
  { return 1ll; }
};

/*! \brief The specialization of the Utility::HDF5TypeTraits for const long 
 * long
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<const long long> : public HDF5TypeTraits<long long>
{ /* ... */ };

/*! \brief The specialization of the Utility::HDF5TypeTraits for unsigned long
 * long
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<unsigned long long>
{
  //! Returns the HDF5 data type object corresponding to unsigned int
  static inline H5::PredType dataType() 
  { return H5::PredType::NATIVE_ULLONG; }
  
  //! Returns the name of the type
  static inline std::string name() 
  { return "unsigned long long int"; }
  
  //! Returns the zero value for this type
  static inline unsigned zero()
  { return 0ull; }

  //! Returns the unity value for this type
  static inline unsigned one()
  { return 1ull; }
};

/*! \brief The specialization of the Utility::HDF5TypeTraits for const unsigned
 * long long
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<const unsigned long long> : public HDF5TypeTraits<unsigned long long>
{ /* ... */ };

/*! \brief The specialization of the Utility::HDF5TypeTraits for char
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<char>
{
  //! Returns the HDF5 data type object corresponding to bool
  static inline H5::PredType dataType()
  { return H5::PredType::NATIVE_CHAR; }

  //! Returns the zero value for this type
  static inline char zero()
  { return '0'; }

  //! Returns the unity value for this type
  static inline char one()
  { return '1'; }
};

/*! \brief The specialization of the Utility::HDF5TypeTraits for const char
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<const char> : public HDF5TypeTraits<char>
{ /* ... */ };

/*! \brief The specialization of the Utility::HDF5TypeTraits for signed char
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<signed char>
{
  //! Returns the HDF5 data type object corresponding to bool
  static inline H5::PredType dataType()
  { return H5::PredType::NATIVE_SCHAR; }

  //! Returns the zero value for this type
  static inline signed char zero()
  { return 0; }

  //! Returns the unity value for this type
  static inline signed char one()
  { return 1; }
};

/*! \brief The specialization of the Utility::HDF5TypeTraits for unsigned char
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<unsigned char>
{
  //! Returns the HDF5 data type object corresponding to bool
  static inline H5::PredType dataType()
  { return H5::PredType::NATIVE_UCHAR; }

  //! Returns the zero value for this type
  static inline unsigned char zero()
  { return 0; }

  //! Returns the unity value for this type
  static inline unsigned char one()
  { return 1; }
};

/*! \brief The specialization of the Utility::HDF5TypeTraits for const signed 
 * char
 * \ingroup hdf5_type_traits
 */
template<>
struct HDF5TypeTraits<const signed char> : public HDF5TypeTraits<signed char>
{ /* ... */ };

/*! \brief The partial specialization of the Utility::HDF5TypeTraits for the
 * Utility::Pair struct
 * \ingroup hdf5_type_traits
 */
template<typename T1, typename T2>
struct HDF5TypeTraits<Pair<T1,T2> >
{
  //! Returns the HDF5 data type object corresponding to Pair<T,T2>
  static H5::CompType dataType()
  {
    typedef Pair<T1,T2> Tuple;
    
    H5::CompType memtype( sizeof(Tuple) );
    
    // the insertMember function can throw H5::DataTypeIException exceptions
    try
    {
    
      memtype.insertMember( "first",
			    HOFFSET( Tuple, first ),
			    HDF5TypeTraits<T1>::dataType() );
      
      memtype.insertMember( "second",
			    HOFFSET( Tuple, second ),
			    HDF5TypeTraits<T2>::dataType() );
      
    }
    
    HDF5_EXCEPTION_CATCH_AND_EXIT();
    
    return memtype;
  }
  
  //! Returns the name of this type
  static inline std::string name() 
  {
    return "Pair<" + HDF5TypeTraits<T1>::name() + "," +
    HDF5TypeTraits<T2>::name() + ">";
  }

  //! Returns the zero value for this type
  static inline Pair<T1,T2> zero()
  { 
    return Pair<T1,T2>(HDF5TypeTraits<T1>::zero(), HDF5TypeTraits<T2>::zero());
  }

  //! Returns the unity value for this type
  static inline Pair<T1,T2> one()
  {
    return Pair<T1,T2>( HDF5TypeTraits<T1>::one(), HDF5TypeTraits<T2>::one() );
  }
};

/*! \brief The partial specialization of the Utility::HDF5TypeTraits for the
 * const Utility::Pair struct
 * \ingroup hdf5_type_traits
 */
template<typename T1, typename T2>
struct HDF5TypeTraits<const Pair<T1,T2> > : public HDF5TypeTraits<Pair<T1,T2> >
{ /* ... */ };

/*! \brief The partial specialization of the Utility::HDF5TypeTraits for the
 * Utility::Trip struct
 * \ingroup hdf5_type_traits
 */
template<typename T1, typename T2, typename T3>
struct HDF5TypeTraits<Trip<T1,T2,T3> >
{
  //! Returns the HDF5 data type object corresponding to Trip<T1,T2,T3>
  static H5::CompType dataType()
  {
    typedef Trip<T1,T2,T3> Tuple;
    
    H5::CompType memtype( sizeof(Tuple) );
    
    // the insertMember function can throw H5::DataTypeIException exceptions
    try
    {
      memtype.insertMember( "first",
			    HOFFSET( Tuple, first ),
			    HDF5TypeTraits<T1>::dataType() );
      
      memtype.insertMember( "second",
			    HOFFSET( Tuple, second ),
			    HDF5TypeTraits<T2>::dataType() );
      
      memtype.insertMember( "third",
			    HOFFSET( Tuple, third ),
			    HDF5TypeTraits<T3>::dataType() );
    }
    
    HDF5_EXCEPTION_CATCH_AND_EXIT();
    
    return memtype;
  }
  
  //! Returns the name of this type
  static inline std::string name() 
  { 
    return "Trip<" + HDF5TypeTraits<T1>::name() + "," +
    HDF5TypeTraits<T2>::name() + "," +
    HDF5TypeTraits<T3>::name() + ">";
  }

  //! Returns the zero value for this type
  static inline Trip<T1,T2,T3> zero()
  {
    return Trip<T1,T2,T3>( HDF5TypeTraits<T1>::zero(),
			   HDF5TypeTraits<T2>::zero(),
			   HDF5TypeTraits<T3>::zero() );
  }

  //! Returns the unity value for this type
  static inline Trip<T1,T2,T3> one()
  {
    return Trip<T1,T2,T3>( HDF5TypeTraits<T1>::one(),
			   HDF5TypeTraits<T2>::one(),
			   HDF5TypeTraits<T3>::one() );
  }
};

/*! \brief The partial specialization of the Utility::HDF5TypeTraits for the
 * const Utility::Trip struct
 * \ingroup hdf5_type_traits
 */
template<typename T1, typename T2, typename T3>
struct HDF5TypeTraits<const Trip<T1,T2,T3> > : public HDF5TypeTraits<Trip<T1,T2,T3> >
{ /* ... */ };

/*! \brief The partial specialization of the Utility::HDF5TypeTraits for the
 * Utility::Quad struct
 * \ingroup hdf5_type_traits
 */
template<typename T1, typename T2, typename T3, typename T4>
struct HDF5TypeTraits<Quad<T1,T2,T3,T4> >
{
  //! Returns the HDF5 data type object corresponding to Quad<T1,T2,T3,T4>
  static H5::CompType dataType()
  {
    typedef Quad<T1,T2,T3,T4> Tuple;
    
    H5::CompType memtype( sizeof(Tuple) );
    
    // the insertMember function can throw H5::DataTypeIException exceptions
    try
    {
      memtype.insertMember( "first",
			    HOFFSET( Tuple, first ),
			    HDF5TypeTraits<T1>::dataType() );
      
      memtype.insertMember( "second",
			    HOFFSET( Tuple, second ),
			    HDF5TypeTraits<T2>::dataType() );
      
      memtype.insertMember( "third",
			    HOFFSET( Tuple, third ),
			    HDF5TypeTraits<T3>::dataType() );
      
      memtype.insertMember( "fourth",
			    HOFFSET( Tuple, fourth ),
			    HDF5TypeTraits<T4>::dataType() );
    }
    
    HDF5_EXCEPTION_CATCH_AND_EXIT();
    
    return memtype;
  }
    
  //! Returns the name of this type
  static inline std::string name() 
  { 
    return "Quad<" + HDF5TypeTraits<T1>::name() + "," +
      HDF5TypeTraits<T2>::name() + "," +
      HDF5TypeTraits<T3>::name() + "," +
      HDF5TypeTraits<T4>::name() + ">";
  }
  
  //! Returns the zero value for this type
  static inline Quad<T1,T2,T3,T4> zero()
  {
    return Quad<T1,T2,T3,T4>( HDF5TypeTraits<T1>::zero(),
			      HDF5TypeTraits<T2>::zero(),
			      HDF5TypeTraits<T3>::zero(),
			      HDF5TypeTraits<T4>::zero() );
  }
  
  //! Returns the unity value for this type
  static inline Quad<T1,T2,T3,T4> one()
  {
    return Quad<T1,T2,T3,T4>( HDF5TypeTraits<T1>::one(),
			      HDF5TypeTraits<T2>::one(),
			      HDF5TypeTraits<T3>::one(),
			      HDF5TypeTraits<T4>::one() );
  }
};

/*! \brief The partial specialization of the Utility::HDF5TypeTraits for the
 * const Utility::Quad struct
 * \ingroup hdf5_type_traits
 */
template<typename T1, typename T2, typename T3, typename T4>
struct HDF5TypeTraits<const Quad<T1,T2,T3,T4> > : public HDF5TypeTraits<Quad<T1,T2,T3,T4> >
{ /* ... */ };

} // end Utility namespace

#endif // end UTILITY_HDF5_TYPE_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_HDF5TypeTraits.hpp
//---------------------------------------------------------------------------//
