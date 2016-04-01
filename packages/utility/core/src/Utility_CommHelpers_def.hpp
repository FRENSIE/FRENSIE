//---------------------------------------------------------------------------//
//!
//! \file   Utility_CommHelpers_def.hpp
//! \author Alex Robinson
//! \brief  Comm helpers and estensions for the Teuchos comm helpers
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_COMM_HELPERS_DEF_HPP
#define UTILITY_COMM_HELPERS_DEF_HPP

// FRENSIE Includes
#include "Utility_MpiTypeTraits.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

#ifdef HAVE_FRENSIE_MPI

/*! Get MPI's error string corresponding to the error code
 * \details This method wouldn't be necessary if the Teuchos::getMpiErrorString
 * located in Teuchos_CommHelpers.cpp was not in an anonymous namespace.
 */
inline std::string getMpiErrorString( const int error_code )
{
  char error_string[MPI_MAX_ERROR_STRING+1];

  int error_string_length = MPI_MAX_ERROR_STRING;

  (void)::MPI_Error_string( error_code, error_string, &error_string_length );

  if( error_string[error_string_length-1] != '\0' )
    error_string[error_string_length] = '\0';

  return std::string( error_string );
}
  
//! The extended MPI Comm status
template<typename OrdinalType>
class ExtendedMpiCommStatus : public Teuchos::CommStatus<OrdinalType>
{
public:

  //! Constructor
  ExtendedMpiCommStatus( MPI_Status status )
    : d_status( status )
  { /* ... */ }

  //! Destructor
  virtual ~ExtendedMpiCommStatus()
  { /* ... */ }

  //! The source rank that sent the message.
  OrdinalType getSourceRank () { return d_status.MPI_SOURCE; }

  //! The tag of the received message.
  OrdinalType getTag () { return d_status.MPI_TAG; }

  //! The error code of the received message.
  OrdinalType getError () { return d_status.MPI_ERROR; }

  //! Get the message size
  template<typename T>
  int getMessageSize() const
  {
    T t;
    
    MPI_Datatype raw_mpi_type = Utility::MpiTypeTraits<T>::getType( t );

    int count = 0;

    int return_value = ::MPI_Get_count( &d_status, raw_mpi_type, &count );

    TEST_FOR_EXCEPTION( return_value != MPI_SUCCESS,
                        std::runtime_error,
                        "Error: could not get the size of the message from "
                        "the MPI_Status! Here is the error message: "
                        << Utility::getMpiErrorString( return_value ) );

    return count;
  }

private:

  //! Default constructor
  ExtendedMpiCommStatus();

  // The raw MPI_Status struct (we need access to this so we store it again)
  MPI_Status d_status;
};
  
#endif // end HAVE_FRENSIE_MPI

// Nonblocking test for a message from source with no status
/*! \details If a message is waiting the return value will be true.
 */
template<typename Ordinal>
bool iprobe( const Teuchos::Comm<Ordinal>& comm, const int source_rank )
{
  Teuchos::RCP<Teuchos::CommStatus<Ordinal> > dummy_status;

  return iprobe( comm, source_rank, dummy_status );
}

// Nonblocking test for a message from source with status
/*! \details If a message is waiting the return value will be true.
 */
template<typename Ordinal>
bool iprobe( const Teuchos::Comm<Ordinal>& comm,
             const int source_rank,
             Teuchos::RCP<Teuchos::CommStatus<Ordinal> >& status )
{
#ifdef HAVE_FRENSIE_MPI
  const Teuchos::MpiComm<Ordinal>* mpi_comm =
    dynamic_cast<const Teuchos::MpiComm<Ordinal>* >( &comm );

  if( mpi_comm == NULL )
  {
    const Teuchos::SerialComm<Ordinal>* serial_comm =
      dynamic_cast<const Teuchos::SerialComm<Ordinal>* >( &comm );

    TEST_FOR_EXCEPTION( serial_comm == NULL,
                        std::runtime_error,
                        "Error: The comm type is unknown! The nonblocking "
                        "probe could not be done." );

    THROW_EXCEPTION( std::logic_error,
                     "Error: you can not call iprobe(...) when you only have "
                     "one process!" );
    
    status.reset( new Teuchos::SerialCommStatus<Ordinal> );
  }
  else
  {
    int waiting_flag;
    MPI_Status raw_status;
    
    int return_value = ::MPI_Iprobe( source_rank,
                                     mpi_comm->getTag(),
                                     *mpi_comm->getRawMpiComm(),
                                     &waiting_flag,
                                     &raw_status );

    TEST_FOR_EXCEPTION( return_value != MPI_SUCCESS,
                        std::runtime_error,
                        "Error: MPI_IProbe failed! Here is the error "
                        "message: "
                        << Utility::getMpiErrorString( return_value ) );

    status.reset( new ExtendedMpiCommStatus<Ordinal>( raw_status ) );

    return waiting_flag;
  }
#else // MPI is not enabled - no messages can be sent
  THROW_EXCEPTION( std::logic_error,
                   "Error: you can not call iprobe(...) when you only have "
                   "one process!" );
#endif // end HAVE_FRENSIE_MPI
}

// Nonblocking test for a message from any source with no status
/*! \details If a message is waiting the return value will be true.
 */
template<typename Ordinal>
bool iprobe( const Teuchos::Comm<Ordinal>& comm )
{
  Teuchos::RCP<Teuchos::CommStatus<Ordinal> > dummy_status;
  
  return iprobe( comm, dummy_status );
}

// Nonblocking test for a message from any source with status
/*! \details If a message is waiting the return value will be true.
 */
template<typename Ordinal>
bool iprobe( const Teuchos::Comm<Ordinal>& comm,
             Teuchos::RCP<Teuchos::CommStatus<Ordinal> >& status )
{
#ifdef HAVE_FRENSIE_MPI
  return iprobe( comm, MPI_ANY_SOURCE, status );
#else // MPI is not enabled - the source will always be 0
  return iprobe( comm, 0, status );
#endif // end HAVE_FRENSIE_MPI
}

// Blocking test for a message from source with status
template<typename Ordinal>
void probe( const Teuchos::Comm<Ordinal>& comm,
            const int source_rank,
            Teuchos::RCP<Teuchos::CommStatus<Ordinal> >& status )
{
#ifdef HAVE_FRENSIE_MPI
  const Teuchos::MpiComm<Ordinal>* mpi_comm =
    dynamic_cast<const Teuchos::MpiComm<Ordinal>* >( &comm );

  if( mpi_comm == NULL )
  {
    const Teuchos::SerialComm<Ordinal>* serial_comm =
      dynamic_cast<const Teuchos::SerialComm<Ordinal>* >( &comm );

    TEST_FOR_EXCEPTION( serial_comm == NULL,
                        std::runtime_error,
                        "Error: The comm type is unknown! The nonblocking "
                        "probe could not be done." );

    THROW_EXCEPTION( std::logic_error,
                     "Error: you can not call probe(...) when you only have "
                     "one process!" );
  }
  else
  {
    MPI_Status raw_status;

    int return_value = ::MPI_Probe( source_rank,
                                    mpi_comm->getTag(),
                                    *mpi_comm->getRawMpiComm(),
                                    &raw_status );

    TEST_FOR_EXCEPTION( return_value != MPI_SUCCESS,
                        std::runtime_error,
                        "Error: MPI_Probe failed! Here is the error "
                        "message: "
                        << Utility::getMpiErrorString( return_value ) );

    status.reset( new ExtendedMpiCommStatus<Ordinal>( raw_status ) );
  }
#else // MPI is not enabled - no messages can be sent
  THROW_EXCEPTION( std::logic_error,
                   "Error: you can not call probe(...) when you only have "
                   "one process!" );
#endif // end HAVE_FRENSIE_MPI
}

// Blocking test for a message from any source with status
template<typename Ordinal>
void probe( const Teuchos::Comm<Ordinal>& comm,
            Teuchos::RCP<Teuchos::CommStatus<Ordinal> >& status )
{
#ifdef HAVE_FRENSIE_MPI
  return probe( comm, MPI_ANY_SOURCE, status );
#else // MPI is not enabled - the source will always be 0
  return probe( comm, 0, status );
#endif // end HAVE_FRENSIE_MPI
}

// Get the size of a message
/*! \details The message size can only be retrieved from a status that
 * that has been returned from a probe or iprobe call (currently).
 */
template<typename T, typename Ordinal>
int getMessageSize( const Teuchos::CommStatus<Ordinal>& status )
{
#ifdef HAVE_FRENSIE_MPI
  const ExtendedMpiCommStatus<Ordinal>* extended_mpi_comm_status =
    dynamic_cast<const ExtendedMpiCommStatus<Ordinal>* >( &status );

  if( extended_mpi_comm_status == NULL )
  {
    const Teuchos::SerialCommStatus<Ordinal>* serial_comm_status =
      dynamic_cast<const Teuchos::SerialCommStatus<Ordinal>* >( &status );

    TEST_FOR_EXCEPTION( serial_comm_status == NULL,
                        std::runtime_error,
                        "Error: The size of the message could not be "
                        "determined! \n\tNote: The message size can only be "
                        "determined after a call to probe or iprobe." );

    return 0;
  }
  else
    return extended_mpi_comm_status->getMessageSize<T>();
#else // MPI is not enabled - all "messages" will be empty
  return 0;
#endif // end HAVE_FRENSIE_MPI
}

} // end Utility namespace

#endif // end UTILITY_COMM_HELPERS_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_CommHelpers_def.hpp
//---------------------------------------------------------------------------//
