//---------------------------------------------------------------------------//
//!
//! \file   Utility_CommHelpers.hpp
//! \author Alex Robinson
//! \brief  Comm helpers and extensions for the Teuchos comm helpers
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_COMM_HELPERS_HPP
#define UTILITY_COMM_HELPERS_HPP

// Trilinos Includes
#include <Teuchos_CommHelpers.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "FRENSIE_mpi_config.hpp"

// It is possible to build Trilinos with MPI and not FRENSIE. This section
// ensures that the mpi.h include still gets pulled in.
#ifdef HAVE_MPI
#ifndef HAVE_FRENSIE_MPI
#include <mpi.h>
#endif // end HAVE_FRENSIE_MPI
#endif // end HAVE_MPI

namespace Utility{
  
//! Nonblocking test for a message from source with no status
template<typename Ordinal>
bool iprobe( const Teuchos::Comm<Ordinal>& comm, const int source_rank );

//! Nonblocking test for a message from source with status
template<typename Ordinal>
bool iprobe( const Teuchos::Comm<Ordinal>& comm,
             const int source_rank,
             Teuchos::RCP<const Teuchos::CommStatus<Ordinal> >& status );

//! Nonblocking test for a message from any source with no status
template<typename Ordinal>
bool iprobe( const Teuchos::Comm<Ordinal>& comm );

//! Nonblocking test for a message from any source with status
template<typename Ordinal>
bool iprobe( const Teuchos::Comm<Ordinal>& comm,
             Teuchos::RCP<const Teuchos::CommStatus<Ordinal> >& status );

//! Blocking test for a message from source with status
template<typename Ordinal>
void probe( const Teuchos::Comm<Ordinal>& comm,
            const int source_rank,
            Teuchos::RCP<const Teuchos::CommStatus<Ordinal> >& status );

//! Blocking test for a message from any source with status
template<typename Ordinal>
void probe( const Teuchos::Comm<Ordinal>& comm,
            Teuchos::RCP<const Teuchos::CommStatus<Ordinal> >& status );

//! Get the size of a message
template<typename T, typename Ordinal>
int getMessageSize( const Teuchos::CommStatus<Ordinal>& status );

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "Utility_CommHelpers_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_COMM_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Utility_CommHelpers.hpp
//---------------------------------------------------------------------------//
