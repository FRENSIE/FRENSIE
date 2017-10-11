//---------------------------------------------------------------------------//
//!
//! \file   Utility_CommunicatorDecl.hpp
//! \author Alex Robinson
//! \brief  The communicator class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_COMMUNICATOR_DECL_HPP
#define UTILITY_COMMUNICATOR_DECL_HPP

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

  // The communicator status class
  class Status;

  /*! The communicator request class
   * \ingroup mpi
   */
  class Request
  {

  public:
    
    // The communicator request implementation
    class Impl;
    
    //! Default constructor
    Request();
    
    //! Copy constructor
    Request( const Request& other_request );
    
    //! Assignment operator
    Request& operator=( const Request& other_request );
    
    //! Destructor
    ~Request()
    { /* ... */ }
    
    //! Wait until the operation associated with this request has completed
    Communicator::Status wait();
    
    //! Cancel the pending operation associated with this request
    void cancel();
    
  private:
    
    // The communicator class is a friend
    friend class Communicator;
    
    // Implementation constructor - only to be called by Utility::Communicator
    Request( const std::shared_ptr<Impl>& impl );
    
    // The request implementation
    std::shared_ptr<Impl> d_impl;
  };

  /*! The communicator status class
   * \ingroup mpi
   */
  class Status
  {

  public:
    
    // The communicator status implementation
    class Impl;

    //! Default constructor
    Status();
    
    //! Copy constructor
    Status( const Status& other_status );
    
    //! Assignment operator
    Status& operator=( const Status& other_status );
    
    //! Destructor
    ~Status()
    { /* ... */ }
    
    //! Check if there are message details
    bool hasMessageDetails() const;

    //! Check if there are message details
    operator bool() const;
    
    //! Check if the communication was cancelled successfully
    bool cancelled() const;
    
    //! Retrieve the source of the message
    int source() const;
    
    //! Retrieve the message tag
    int tag() const;
    
    //! Count the number of elements that were contained in the message
    int count() const;
    
  private:
    
    // The mpi communicator class is a friend
    friend class Communicator;
    
    // The mpi communicator request class is a friend
    friend class Communicator::Request;
    
    // Implementation constructor - only to be called by Utility::Communicator
    // or Utility::Communicator::Request
    Status( const std::shared_ptr<const Impl>& impl );

    // The implementation
    std::shared_ptr<const Impl> d_impl;
  };

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

protected:

  //! Create a new status object
  static Communicator::Status createStatus( const std::shared_ptr<const Communicator::Status::Impl>& impl );

  //! Create a new request object
  static Communicator::Request createRequest( const std::shared_ptr<Communicator::Request::Impl>& impl );
};

/*! The communicator status implementation class
 * \ingroup mpi
 */
class Communicator::Status::Impl
{
  
public:

  //! Constructor
  Impl()
  { /* ... */ }

  //! Destructor
  virtual ~Impl()
  { /* ... */ }

  //! Check if the communicator was cancelled successfully
  virtual bool cancelled() const = 0;

  //! Retrieve the source of the message
  virtual int source() const = 0;

  //! Retrieve the message tag
  virtual int tag() const = 0;

  //! The number of elements that were contained in the message
  virtual int count() const = 0;
};

/*! The communicator request implementation class
 * \ingroup mpi
 */
class Communicator::Request::Impl
{
  
public:

  //! Constructor
  Impl()
  { /* ... */ }

  //! Destructor
  virtual ~Impl()
  { /* ... */ }

  /*! Wait until the operation associated with this request has completed
   *
   * The returned pointer should be heap allocated (created using new).
   */
  virtual Communicator::Status::Impl* wait() = 0;

  //! Cancel the pending operation associated with this request
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

/*! The maximum operator
 * \ingroup mpi
 */
template<typename T>
struct maximum
{ 
  typedef T InputType;

  const T& operator()( const T&, const T& ) const;
};

/*! The minimum operator
 * \ingroup mpi
 */
template<typename T>
struct minimum
{
  typedef T InputType;

  const T& operator()( const T&, const T& ) const;
};

/*! The bitwise and operator
 * \ingroup mpi
 */
template<typename T>
struct bitwiseAnd
{
  typedef T InputType;

  T operator()( const T&, const T& ) const;
};

/*! The bitwise or operator
 * \ingroup mpi
 */
template<typename T>
struct bitwiseOr
{
  typedef T InputType;

  T operator()( const T&, const T& ) const;
};

/*! The bitwise exclusive or operator
 * \ingroup mpi
 */
template<typename T>
struct bitwiseXor
{
  typedef T InputType;

  T operator()( const T&, const T& ) const;
};

/*! The logical exclusive or operator
 * \ingroup mpi
 */
template<typename T>
struct logicalXor
{
  typedef T InputType;

  T operator()( const T&, const T& ) const;
};

/*! Determine if two communicators are identical
 * \ingroup mpi
 */
bool operator==( const Communicator& comm_a, const Communicator& comm_b );

/*! Determine if two communicators are different
 * \ingroup mpi
 */
bool operator!=( const Communicator& comm_a, const Communicator& comm_b );
  
} // end Utility namespace

#endif // end UTILITY_COMMUNICATOR_HPP

//---------------------------------------------------------------------------//
// end Utility_Communicator.hpp
//---------------------------------------------------------------------------//
