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

// Boost Includes
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_constant.hpp>
#include <boost/type_traits/remove_const.hpp>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_HDF5TypeTraitsDecl.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_HDF5ExceptionCatchMacros.hpp"

namespace Utility{

/*! \brief the partial specialization of the Utility::HDF5TypeTraits for
 * all constant types
 * \ingroup hdf5_type_traits
 */
template<typename T>
struct HDF5TypeTraits<T,typename boost::enable_if<boost::is_const<T> >::type> : public HDF5TypeTraits<boost::remove_const<T>::type>
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

/*! \brief The partial specialization of the Utility::HDF5TypeTraits for the
 * Utility::Pair struct
 * \ingroup hdf5_type_traits
 */
template<typename T1, typename T2>
struct HDF5TypeTraits<Pair<T1,T2> >
{
  //! Typedef for the raw type
  typedef Pair<T1,T2> RawType;
  
  //! Returns the HDF5 data type object corresponding to Pair<T,T2>
  static H5::CompType dataType()
  {
    H5::CompType memtype( sizeof(RawType) );

    // the insertMember function can throw H5::DataTypeIException exceptions
    try
    {

      memtype.insertMember( "first",
			    HOFFSET( RawType, first ),
			    HDF5TypeTraits<T1>::dataType() );

      memtype.insertMember( "second",
			    HOFFSET( RawType, second ),
			    HDF5TypeTraits<T2>::dataType() );

    }

    HDF5_EXCEPTION_CATCH_RETHROW_AS( std::logic_error,
                                     "unable to create the HDF5 data type ("
                                     << name() << ")!" );

    return memtype;
  }

  //! Returns the name of this type
  static inline std::string name()
  {
    return "Utility::Pair<" + HDF5TypeTraits<T1>::name() + "," +
    HDF5TypeTraits<T2>::name() + ">";
  }

  //! Returns the zero value for this type
  static inline RawType zero()
  {
    return RawType(HDF5TypeTraits<T1>::zero(), HDF5TypeTraits<T2>::zero());
  }

  //! Returns the unity value for this type
  static inline RawType one()
  {
    return RawType( HDF5TypeTraits<T1>::one(), HDF5TypeTraits<T2>::one() );
  }
};

/*! \brief The partial specialization of the Utility::HDF5TypeTraits for the
 * std::pair struct
 * \ingroup hdf5_type_traits
 */
template<typename T1, typename T2>
struct HDF5TypeTraits<std::pair<T1,T2> >
{
  //! Typedef for the raw type
  typedef std::pair<T1,T2> RawType;
  
  //! Returns the HDF5 data type object corresponding to Pair<T,T2>
  static H5::CompType dataType()
  {
    H5::CompType memtype( sizeof(RawType) );

    // the insertMember function can throw H5::DataTypeIException exceptions
    try
    {

      memtype.insertMember( "first",
			    HOFFSET( RawType, first ),
			    HDF5TypeTraits<T1>::dataType() );

      memtype.insertMember( "second",
			    HOFFSET( RawType, second ),
			    HDF5TypeTraits<T2>::dataType() );

    }

    HDF5_EXCEPTION_CATCH_RETHROW_AS( std::logic_error,
                                     "unable to create the HDF5 data type ("
                                     << name() << ")!" );

    return memtype;
  }

  //! Returns the name of this type
  static inline std::string name()
  {
    return "std::pair<" + HDF5TypeTraits<T1>::name() + "," +
    HDF5TypeTraits<T2>::name() + ">";
  }

  //! Returns the zero value for this type
  static inline RawType zero()
  {
    return std::make_pair( HDF5TypeTraits<T1>::zero(),
                           HDF5TypeTraits<T2>::zero() );
  }

  //! Returns the unity value for this type
  static inline RawType one()
  {
    return std::make_pair( HDF5TypeTraits<T1>::one(),
                           HDF5TypeTraits<T2>::one() );
  }
};

/*! \brief The partial specialization of the Utility::HDF5TypeTraits for the
 * std::tuple<typename,typename> struct
 * \ingroup hdf5_type_traits
 */
template<typename T1, typename T2>
struct HDF5TypeTraits<std::tuple<T1,T2> >
{
  //! Typedef for the raw type
  typedef std::tuple<T1,T2> RawType;
  
  //! Returns the HDF5 data type object corresponding to Pair<T,T2>
  static H5::CompType dataType()
  {
    H5::CompType memtype( sizeof(RawType) );

    // the insertMember function can throw H5::DataTypeIException exceptions
    try
    {

      memtype.insertMember( "first",
			    HOFFSET( RawType, first ),
			    HDF5TypeTraits<T1>::dataType() );

      memtype.insertMember( "second",
			    HOFFSET( RawType, second ),
			    HDF5TypeTraits<T2>::dataType() );

    }

    HDF5_EXCEPTION_CATCH_RETHROW_AS( std::logic_error,
                                     "unable to create the HDF5 data type ("
                                     << name() << ")!" );

    return memtype;
  }

  //! Returns the name of this type
  static inline std::string name()
  {
    return "std::tuple<" + HDF5TypeTraits<T1>::name() + "," +
    HDF5TypeTraits<T2>::name() + ">";
  }

  //! Returns the zero value for this type
  static inline RawType zero()
  {
    return std::make_tuple( HDF5TypeTraits<T1>::zero(),
                            HDF5TypeTraits<T2>::zero() );
  }

  //! Returns the unity value for this type
  static inline RawType one()
  {
    return std::make_tuple( HDF5TypeTraits<T1>::one(),
                            HDF5TypeTraits<T2>::one() );
  }
};

/*! \brief The partial specialization of the Utility::HDF5TypeTraits for the
 * Utility::Trip struct
 * \ingroup hdf5_type_traits
 */
template<typename T1, typename T2, typename T3>
struct HDF5TypeTraits<Trip<T1,T2,T3> >
{
  //! Typedef for the raw type
  typedef Trip<T1,T2,T3> RawType;
  
  //! Returns the HDF5 data type object corresponding to Trip<T1,T2,T3>
  static H5::CompType dataType()
  {
    H5::CompType memtype( sizeof(RawType) );

    // the insertMember function can throw H5::DataTypeIException exceptions
    try
    {
      memtype.insertMember( "first",
			    HOFFSET( RawType, first ),
			    HDF5TypeTraits<T1>::dataType() );

      memtype.insertMember( "second",
			    HOFFSET( RawType, second ),
			    HDF5TypeTraits<T2>::dataType() );

      memtype.insertMember( "third",
			    HOFFSET( RawType, third ),
			    HDF5TypeTraits<T3>::dataType() );
    }

    HDF5_EXCEPTION_CATCH_RETHROW_AS( std::logic_error,
                                     "unable to create the HDF5 data type ("
                                     << name() << ")!" );

    return memtype;
  }

  //! Returns the name of this type
  static inline std::string name()
  {
    return "Utility::Trip<" + HDF5TypeTraits<T1>::name() + "," +
    HDF5TypeTraits<T2>::name() + "," +
    HDF5TypeTraits<T3>::name() + ">";
  }

  //! Returns the zero value for this type
  static inline RawType zero()
  {
    return RawType( HDF5TypeTraits<T1>::zero(),
                    HDF5TypeTraits<T2>::zero(),
                    HDF5TypeTraits<T3>::zero() );
  }

  //! Returns the unity value for this type
  static inline RawType one()
  {
    return RawType( HDF5TypeTraits<T1>::one(),
                    HDF5TypeTraits<T2>::one(),
                    HDF5TypeTraits<T3>::one() );
  }
};

/*! \brief The partial specialization of the Utility::HDF5TypeTraits for the
 * std::tuple<typename,typename,typename> struct
 * \ingroup hdf5_type_traits
 */
template<typename T1, typename T2, typename T3>
struct HDF5TypeTraits<std::tuple<T1,T2,T3> >
{
  //! Typedef for the raw type
  typedef std::tuple<T1,T2,T3> RawType;
  
  //! Returns the HDF5 data type object corresponding to Trip<T1,T2,T3>
  static H5::CompType dataType()
  {
    H5::CompType memtype( sizeof(RawType) );

    // the insertMember function can throw H5::DataTypeIException exceptions
    try
    {
      memtype.insertMember( "first",
			    HOFFSET( RawType, first ),
			    HDF5TypeTraits<T1>::dataType() );

      memtype.insertMember( "second",
			    HOFFSET( RawType, second ),
			    HDF5TypeTraits<T2>::dataType() );

      memtype.insertMember( "third",
			    HOFFSET( RawType, third ),
			    HDF5TypeTraits<T3>::dataType() );
    }

    HDF5_EXCEPTION_CATCH_RETHROW_AS( std::logic_error,
                                     "unable to create the HDF5 data type ("
                                     << name() << ")!" );

    return memtype;
  }

  //! Returns the name of this type
  static inline std::string name()
  {
    return "std::tuple<" + HDF5TypeTraits<T1>::name() + "," +
    HDF5TypeTraits<T2>::name() + "," +
    HDF5TypeTraits<T3>::name() + ">";
  }

  //! Returns the zero value for this type
  static inline RawType zero()
  {
    return std::make_tuple( HDF5TypeTraits<T1>::zero(),
                            HDF5TypeTraits<T2>::zero(),
                            HDF5TypeTraits<T3>::zero() );
  }

  //! Returns the unity value for this type
  static inline RawType one()
  {
    return std::make_tuple( HDF5TypeTraits<T1>::one(),
                            HDF5TypeTraits<T2>::one(),
                            HDF5TypeTraits<T3>::one() );
  }
};

/*! \brief The partial specialization of the Utility::HDF5TypeTraits for the
 * Utility::Quad struct
 * \ingroup hdf5_type_traits
 */
template<typename T1, typename T2, typename T3, typename T4>
struct HDF5TypeTraits<Quad<T1,T2,T3,T4> >
{
  //! Typedef for the raw type
  typedef Utility::Quad<T1,T2,T3,T4> RawType;
  
  //! Returns the HDF5 data type object corresponding to Quad<T1,T2,T3,T4>
  static H5::CompType dataType()
  {
    H5::CompType memtype( sizeof(RawType) );

    // the insertMember function can throw H5::DataTypeIException exceptions
    try
    {
      memtype.insertMember( "first",
			    HOFFSET( RawType, first ),
			    HDF5TypeTraits<T1>::dataType() );

      memtype.insertMember( "second",
			    HOFFSET( RawType, second ),
			    HDF5TypeTraits<T2>::dataType() );

      memtype.insertMember( "third",
			    HOFFSET( RawType, third ),
			    HDF5TypeTraits<T3>::dataType() );

      memtype.insertMember( "fourth",
			    HOFFSET( RawType, fourth ),
			    HDF5TypeTraits<T4>::dataType() );
    }

    HDF5_EXCEPTION_CATCH_RETHROW_AS( std::logic_error,
                                     "unable to crete the HDF5 data type ("
                                     << name() << ")!" );

    return memtype;
  }

  //! Returns the name of this type
  static inline std::string name()
  {
    return "Utility::Quad<" + HDF5TypeTraits<T1>::name() + "," +
      HDF5TypeTraits<T2>::name() + "," +
      HDF5TypeTraits<T3>::name() + "," +
      HDF5TypeTraits<T4>::name() + ">";
  }

  //! Returns the zero value for this type
  static inline RawType zero()
  {
    return RawType( HDF5TypeTraits<T1>::zero(),
                    HDF5TypeTraits<T2>::zero(),
                    HDF5TypeTraits<T3>::zero(),
                    HDF5TypeTraits<T4>::zero() );
  }

  //! Returns the unity value for this type
  static inline RawType one()
  {
    return RawType( HDF5TypeTraits<T1>::one(),
                    HDF5TypeTraits<T2>::one(),
                    HDF5TypeTraits<T3>::one(),
                    HDF5TypeTraits<T4>::one() );
  }
};

/*! \brief The partial specialization of the Utility::HDF5TypeTraits for the
 * std::tuple<typename,typename,typename,typename> struct
 * \ingroup hdf5_type_traits
 */
template<typename T1, typename T2, typename T3, typename T4>
struct HDF5TypeTraits<std::tuple<T1,T2,T3,T4> >
{
  //! Typedef for the raw type
  typedef std::tuple<T1,T2,T3,T4> RawType;
  
  //! Returns the HDF5 data type object corresponding to Quad<T1,T2,T3,T4>
  static H5::CompType dataType()
  {
    H5::CompType memtype( sizeof(RawType) );

    // the insertMember function can throw H5::DataTypeIException exceptions
    try
    {
      memtype.insertMember( "first",
			    HOFFSET( RawType, first ),
			    HDF5TypeTraits<T1>::dataType() );

      memtype.insertMember( "second",
			    HOFFSET( RawType, second ),
			    HDF5TypeTraits<T2>::dataType() );

      memtype.insertMember( "third",
			    HOFFSET( RawType, third ),
			    HDF5TypeTraits<T3>::dataType() );

      memtype.insertMember( "fourth",
			    HOFFSET( RawType, fourth ),
			    HDF5TypeTraits<T4>::dataType() );
    }

    HDF5_EXCEPTION_CATCH_RETHROW_AS( std::logic_error,
                                     "unable to crete the HDF5 data type ("
                                     << name() << ")!" );

    return memtype;
  }

  //! Returns the name of this type
  static inline std::string name()
  {
    return "std::tuple<" + HDF5TypeTraits<T1>::name() + "," +
      HDF5TypeTraits<T2>::name() + "," +
      HDF5TypeTraits<T3>::name() + "," +
      HDF5TypeTraits<T4>::name() + ">";
  }

  //! Returns the zero value for this type
  static inline RawType zero()
  {
    return std::make_tuple( HDF5TypeTraits<T1>::zero(),
                            HDF5TypeTraits<T2>::zero(),
                            HDF5TypeTraits<T3>::zero(),
                            HDF5TypeTraits<T4>::zero() );
  }

  //! Returns the unity value for this type
  static inline RawType one()
  {
    return std::make_tuple( HDF5TypeTraits<T1>::one(),
                            HDF5TypeTraits<T2>::one(),
                            HDF5TypeTraits<T3>::one(),
                            HDF5TypeTraits<T4>::one() );
  }
};

} // end Utility namespace

#endif // end UTILITY_HDF5_TYPE_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_HDF5TypeTraits.hpp
//---------------------------------------------------------------------------//
