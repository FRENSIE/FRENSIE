//---------------------------------------------------------------------------//
//!
//! \file   Utility_Communicator.hpp
//! \author Alex Robinson
//! \brief  The communicator class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_COMMUNICATOR_HPP
#define UTILITY_COMMUNICATOR_HPP

// Std Lib Includes
#include <memory>
#include <stdexcept>

// FRENSIE Includes
#include "Utility_Timer.hpp"
#include "Utility_OStreamableObject.hpp"

namespace Utility{

/*! The communicator base class
 * \ingroup mpi
 */
class Communicator : public OStreamableObject
{

public:

  //! Default constructor
  Communicator()
  { /* ... */ }

  //! Destructor
  virtual ~Communicator()
  { /* ... */ }

  //! Create a default communicator
  static std::shared_ptr<const Communicator> getDefault();

  //! Create a null communicator
  static std::shared_ptr<const Communicator> getNull();

  //! Determine the rank of the executing process
  virtual int rank() const = 0;

  //! Determine the number of processes in a communicator
  virtual int size() const = 0;

  //! The any source value
  virtual int anySourceValue() const = 0;

  //! The any tag value
  virtual int anyTagValue() const = 0;

  //! Wait for all processes within the comm to reach the barrier
  virtual void barrier() const = 0;

  //! Check if this communicator can be used for communication
  virtual bool isValid() const = 0;

  //! Check if this communicator uses mpi
  virtual bool isMPIUsed() const = 0;
  
  //! Determine if this communicator is valid for communication
  operator bool() const;

  //! Check if this communicator is identical to another
  virtual bool isIdentical( const Communicator& comm ) const = 0;

  /*! \brief Split the communicator into multiple, disjoint communicators each
   * of which is based on a particular color
   */
  virtual std::shared_ptr<const Communicator> split( int color ) const = 0;

  /*! \brief Split the communicator into multiple, disjoint communicators each
   * of which is based on a particular color.
   */
  virtual std::shared_ptr<const Communicator> split( int color, int key ) const = 0;

  //! Create a timer
  virtual std::shared_ptr<Timer> createTimer() const = 0;
};

/*! Determine if two communicators are identical
 * \ingroup mpi
 */
bool operator==( const Communicator& comm_a, const Communicator& comm_b );

/*! Determine if two communicators are different
 * \ingroup mpi
 */
bool operator!=( const Communicator& comm_a, const Communicator& comm_b );

/*! The communicator status class
 * \ingroup mpi
 */
class CommunicatorStatus
{

public:

  //! Default constructor
  CommunicatorStatus()
  { /* ... */ }

  //! Destructor
  virtual ~CommunicatorStatus()
  { /* ... */ }

  //! Retrieve the source of the message
  virtual int source() const = 0;

  //! Retrieve the message tag
  virtual int tag() const = 0;

  //! Check if the communication was cancelled successfully
  virtual bool cancelled() const = 0;
};

/*! The communicator request class
 * \ingroup mpi
 */
class CommunicatorRequest
{

public:

  //! Default constructor
  CommunicatorRequest()
  { /* ... */ }

  //! Destructor
  virtual ~CommunicatorRequest()
  { /* ... */ }

  //! Wait until the communicator associated with this request has completed
  virtual std::shared_ptr<const CommunicatorStatus> wait() = 0;

  //! Cancel a pending communication
  virtual void cancel() = 0;
};

/*! The invalid communicator exception
 * \ingroup mpi
 */
class InvalidCommunicator : public std::logic_error
{
public:

  //! Constructor
  InvalidCommunicator( const std::string& details )
    : std::logic_error( details )
  { /* ... */ }

  //! Destructor
  ~InvalidCommunicator()
  { /* ... */ }
};

/*! The communication error exception
 * \ingroup mpi
 */
class CommunicationError : public std::runtime_error
{
public:

  //! Constructor
  CommunicationError( const std::string& details )
    : std::runtime_error( details )
  { /* ... */ }

  //! Destructor
  ~CommunicationError()
  { /* ... */ }
};
  
} // end Utility namespace

#endif // end UTILITY_COMMUNICATOR_HPP

//---------------------------------------------------------------------------//
// end Utility_Communicator.hpp
//---------------------------------------------------------------------------//
