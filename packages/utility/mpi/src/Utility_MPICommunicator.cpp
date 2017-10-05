//---------------------------------------------------------------------------//
//!
//! \file   Utility_MPICommunicator.cpp
//! \author Alex Robinson
//! \brief  The mpi communicator class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_MPICommunicator.hpp"
#include "Utility_GlobalMPISession.hpp"

namespace Utility{

// Constructor
MPICommunicator::MPICommunicator()
{ /* ... */ }

#ifdef HAVE_FRENSIE_MPI
// boost::communicator constructor
MPICommunicator::MPICommunicator( const boost::mpi::communicator& comm )
  : d_comm( comm )
{ /* ... */ }
#endif // end HAVE_FRENSIE_MPI

// Determine the rank of the executing process
int MPICommunicator::rank() const
{
#ifdef HAVE_FRENSIE_MPI
  return d_comm.rank();
#else
  return -1;
#endif // end HAVE_FRENSIE_MPI  
}

// Determine the number of processes in a communicator
int MPICommunicator::size() const
{
#ifdef HAVE_FRENSIE_MPI
  return d_comm.size();
#else
  return 0;
#endif // end HAVE_FRENSIE_MPI
}

// The any source value
int MPICommunicator::anySourceValue() const
{
#ifdef HAVE_FRENSIE_MPI
  return boost::mpi::any_source;
#else
  return -1;
#endif // end HAVE_FRENSIE_MPI
}

// The any tag value
int MPICommunicator::anyTagValue() const
{
#ifdef HAVE_FRENSIE_MPI
  return boost::mpi::any_tag;
#else
  return -1;
#endif // end HAVE_FRENSIE_MPI
}

//! Wait for all processes within the comm to reach the barrier
void MPICommunicator::barrier() const
{
#ifdef HAVE_FRENSIE_MPI
  d_comm.barrier();
#endif // end HAVE_FRENSIE_MPI
}

// Check if this communicator is valid for communicator
bool MPICommunicator::isValid() const
{
#ifdef HAVE_FRENSIE_MPI
  return d_comm;
#else
  return false;
#endif // end HAVE_FRENSIE_MPI
}

// Check if this communicator uses mpi
bool MPICommunicator::isMPIUsed() const
{
#ifdef HAVE_FRENSIE_MPI
  return true;
#else
  return false;
#endif // end HAVE_FRENSIE_MPI
}

// Check if this communicator is this communicator is identical to another
bool MPICommunicator::isIdentical( const Communicator& comm ) const
{
  // Attempt to cast the comm to a mpi comm
  const MPICommunicator* const mpi_comm =
    static_cast<const MPICommunicator* const>( &comm );

  if( mpi_comm )
  {
#ifdef HAVE_FRENSIE_MPI
    return d_comm == mpi_comm->d_comm;
#else // HAVE_FRENSIE_MPI
    return true;
#endif // end HAVE_FRENSIE_MPI
  }
  else
    return false;
}
  
// Split the communicator into multiple, disjoint communicators each
// of which is based on a particular color
std::shared_ptr<const Communicator>
MPICommunicator::split( int MPI_ENABLED_PARAMETER(color) ) const
{
#ifdef HAVE_FRENSIE_MPI
  boost::mpi::communicator sub_comm = d_comm.split( color );

  return std::shared_ptr<const Communicator>( new MPICommunicator( sub_comm ) );
#else
  return Communicator::getNull();
#endif // end HAVE_FRENSIE_MPI
}

// Split the communicator into multiple, disjoint communicators each
// of which is based on a particular color.
std::shared_ptr<const Communicator>
MPICommunicator::split( int MPI_ENABLED_PARAMETER(color),
                        int MPI_ENABLED_PARAMETER(key) ) const
{
#ifdef HAVE_FRENSIE_MPI
  boost::mpi::communicator sub_comm = d_comm.split( color, key );

  return std::shared_ptr<const Communicator>( new MPICommunicator( sub_comm ) );
#else
  return Communicator::getNull();
#endif // end HAVE_FRENSIE_MPI
}

// Create a communicator that is the union of this communicator and
// another communicator
std::shared_ptr<const Communicator> MPICommunicator::combine(
                                               const Communicator& comm ) const
{
  // Attempt to cast the comm to a mpi comm
  const MPICommunicator* const mpi_comm =
    static_cast<const MPICommunicator* const>( &comm );

  if( mpi_comm )
  {
#ifdef HAVE_FRENSIE_MPI
    boost::mpi::intercommunicator
      inter_comm( d_comm, 0, mpi_comm->d_comm, 0 );
    
    boost::mpi::communicator union_comm = inter_comm.merge( false );
    
    return std::shared_ptr<const Communicator>( new MPICommunicator( union_comm ) );
#else // HAVE_FRENSIE_MPI
    return Communicator::getNull();
#endif // end HAVE_FRENSIE_MPI
  }
  else
    return Communicator::getNull();
}

// Create a communicator that is the intersection of this 
// communicator and another communicator
std::shared_ptr<const Communicator> MPICommunicator::intersect(
                                               const Communicator& comm ) const
{
  // Attempt to cast the comm to a mpi comm
  const MPICommunicator* const mpi_comm =
    static_cast<const MPICommunicator* const>( &comm );

  if( mpi_comm )
  {
#ifdef HAVE_FRENSIE_MPI
    boost::mpi::intercommunicator
      inter_comm( d_comm, 0, mpi_comm->d_comm, 0 );

    boost::mpi::communicator union_comm = inter_comm.merge( false );

    std::vector<int> local_ranks_in_union_comm;

    inter_comm.local_group().translate_ranks( 
    
    boost::mpi::communicator
      intersection_comm( union_comm, inter_comm.local_group() & inter_comm.remote_group() );

    return std::shared_ptr<const Communicator>( new MPICommunicator( intersection_comm ) );
#else // HAVE_FRENSIE_MPI
    return Communicator::getNull();
#endif // end HAVE_FRENSIE_MPI
  }
  else
    return Communicator::getNull();
}

// Create a communicator that is the difference of this
// communicator and another communicator
std::shared_ptr<const Communicator> MPICommunicator::subtract(
                                               const Communicator& comm ) const
{
  // Attempt to cast the comm to a mpi comm
  const MPICommunicator* const mpi_comm =
    static_cast<const MPICommunicator* const>( &comm );

  if( mpi_comm )
  {
#ifdef HAVE_FRENSIE_MPI
    boost::mpi::communicator
      difference_comm( d_comm.group() - mpi_comm->d_comm.group() );

    return std::shared_ptr<const Communicator>( new MPICommunicator( difference_comm ) );
#else // HAVE_FRENSIE_MPI
    return Communicator::getNull();
#endif // end HAVE_FRENSIE_MPI
  }
  else
    return Communicator::getNull();
}

// Create a timer
std::shared_ptr<Timer> MPICommunicator::createTimer() const
{
  return GlobalMPISession::createTimer();
}

// Method for placing the object in an output stream
void MPICommunicator::toStream( std::ostream& os ) const
{
  os << "MPI Communicator (rank=" << this->rank() << ", "
       << "size=" << this->size() << ")";
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_MPICommunicator.cpp
//---------------------------------------------------------------------------//
