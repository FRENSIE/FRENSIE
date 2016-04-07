//---------------------------------------------------------------------------//
//!
//! \file   Utility_MpiTypeTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  Mpi Type Traits declaration. Note: This class wouldn't be necessary
//!         if the Teuchos::MpiTypeTraits class (found in
//!         Teuchos_CommHelpers.cpp) was not in an Anonymous namespace!!!
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_MPI_TYPE_TRAITS_DECL_HPP
#define UTILITY_MPI_TYPE_TRAITS_DECL_HPP

// FRENSIE Includes
#include "FRENSIE_mpi_config.hpp"
#include "Utility_UndefinedTraits.hpp"

/*! \defgroup mpi_type_traits MPI Type Traits
 * \ingroup traits
 *
 * Attempting to use the class without a specialization will result in a 
 * compile time error.
 */

#ifdef HAVE_FRENSIE_MPI

namespace Utility{

//! This structure defines the traits needed by the Comm Helpers
template<typename T>
struct MpiTypeTraits
{
  //! The MPI_Datatype corresponding to T
  static MPI_Datatype getType( const T& )
  { (void)UndefinedTraits<T>::notDefined(); return 0; }
};
  
} // end Utility namespace

#endif // end HAVE_FRENSIE_MPI

#endif // end UTILITY_MPI_TYPE_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_MpiTypeTraitsDecl.hpp
//---------------------------------------------------------------------------//
