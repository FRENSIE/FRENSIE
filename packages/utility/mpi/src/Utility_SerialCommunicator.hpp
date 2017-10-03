//---------------------------------------------------------------------------//
//!
//! \file   Utility_SerialCommunicator.hpp
//! \author Alex Robinson
//! \brief  The serial communicator class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SERIAL_COMMUNICATOR_HPP
#define UTILITY_SERIAL_COMMUNICATOR_HPP

// FRENSIE Includes
#include "Utility_Communicator.hpp"

namespace Utility{

/*! The serial communicator class
 * \ingroup mpi
 */
class SerialCommunicator : public Communicator
{

public:

  //! Default constructor
  SerialCommunicator();

  //! Destructor
  virtual ~SerialCommunicator();

  //! Determine the rank of the executing process
  int rank() const override;

  //! Determine the number of processes in a communicator
  int size() const override;

  //! The any source value
  int anySourceValue() const override;

  //! The any tag value
  int anyTagValue() const override;

  //! Wait for all processes within the comm to reach the barrier
  void barrier() const override;

  //! Check if this communicator is valid for communicator
  bool isValid() const override;

  //! Check if this communicator uses mpi
  bool isMPIUsed() const override;
  
  /*! \brief Split the communicator into multiple, disjoint communicators each
   * of which is based on a particular color
   */
  std::shared_ptr<const Communicator> split( int color ) const override;

  /*! \brief Split the communicator into multiple, disjoint communicators each
   * of which is based on a particular color.
   */
  std::shared_ptr<const Communicator> split( int color, int key ) const override;

  //! Create a timer
  std::shared_ptr<Timer> createTimer() const override;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const override;
};
  
} // end Utility namespace

#endif // end UTILITY_SERIAL_COMMUNICATOR_HPP

//---------------------------------------------------------------------------//
// end Utility_SerialCommunicator.hpp
//---------------------------------------------------------------------------//
