//---------------------------------------------------------------------------//
//!
//! \file   Utility_MpiTypeTraits.hpp
//! \author Alex Robinson
//! \brief  Mpi Type Traits specializations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_MPI_TYPE_TRAITS_HPP
#define UTILITY_MPI_TYPE_TRAITS_HPP

// FRENSIE Includes
#include "Utility_MpiTypeTraitsDecl.hpp"

#ifdef HAVE_FRENSIE_MPI

namespace Utility{

/*! Specialization of Utility::MpiTypeTraits for double
 * \ingroup mpi_type_traits
 */
template<>
struct MpiTypeTraits<double>
{
  //! The MPI_Datatype corresponding to double
  static inline MPI_Datatype getType( const double& )
  { return MPI_DOUBLE; }
};

/*! Specialization of Utility::MpiTypeTraits for float
 * \ingroup mpi_type_traits
 */
template<>
struct MpiTypeTraits<float>
{
  //! The MPI_DataType corresponding to float
  static inline MPI_Datatype getType( const float& )
  { return MPI_FLOAT; }
};

/*! Specialization of Utility::MpiTypeTraits for long long
 * \ingroup mpi_type_traits
 */
template<>
struct MpiTypeTraits<long long>
{
  //! The MPI_DataType corresponding to long long
  static inline MPI_Datatype getType( const long long& )
  { return MPI_LONG_LONG; }
};

/*! Specialization of Utility::MpiTypeTraits for unsigned long long
 * \ingroup mpi_type_traits
 */
template<>
struct MpiTypeTraits<unsigned long long>
{
  //! The MPI_DataType corresponding to unsigned long long
  static inline MPI_Datatype getType( const unsigned long long& )
  { return MPI_UNSIGNED_LONG_LONG; }
};

/*! Specialization of Utility::MpiTypeTraits for long
 * \ingroup mpi_type_traits
 */
template<>
struct MpiTypeTraits<long>
{
  //! The MPI_DataType corresponding to long
  static inline MPI_Datatype getType( const long& )
  { return MPI_LONG; }
};

/*! Specialization of Utility::MpiTypeTraits for unsigned long
 * \ingroup mpi_type_traits
 */
template<>
struct MpiTypeTraits<unsigned long>
{
  //! The MPI_DataType corresponding to unsigned long
  static inline MPI_Datatype getType( const unsigned long& )
  { return MPI_UNSIGNED_LONG; }
};

/*! Specialization of Utility::MpiTypeTraits for int
 * \ingroup mpi_type_traits
 */
template<>
struct MpiTypeTraits<int>
{
  //! The MPI_DataType corresponding to long
  static inline MPI_Datatype getType( const int& )
  { return MPI_INT; }
};

/*! Specialization of Utility::MpiTypeTraits for unsigned
 * \ingroup mpi_type_traits
 */
template<>
struct MpiTypeTraits<unsigned>
{
  //! The MPI_DataType corresponding to long
  static inline MPI_Datatype getType( const unsigned& )
  { return MPI_UNSIGNED; }
};

/*! Specialization of Utility::MpiTypeTraits for short
 * \ingroup mpi_type_traits
 */
template<>
struct MpiTypeTraits<short>
{
  //! The MPI_DataType corresponding to long
  static inline MPI_Datatype getType( const short& )
  { return MPI_SHORT; }
};

/*! Specialization of Utility::MpiTypeTraits for unsigned short
 * \ingroup mpi_type_traits
 */
template<>
struct MpiTypeTraits<unsigned short>
{
  //! The MPI_DataType corresponding to long
  static inline MPI_Datatype getType( const unsigned short& )
  { return MPI_UNSIGNED_SHORT; }
};

/*! Specialization of Utility::MpiTypeTraits for char
 * \ingroup mpi_type_traits
 */
template<>
struct MpiTypeTraits<char>
{
  //! The MPI_DataType corresponding to long
  static inline MPI_Datatype getType( const char& )
  { return MPI_CHAR; }
};
  
} // end Utility namespace

#endif // end HAVE_FRENSIE_MPI

#endif // end UTILITY_MPI_TYPE_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_MpiTypeTraits.hpp
//---------------------------------------------------------------------------//
