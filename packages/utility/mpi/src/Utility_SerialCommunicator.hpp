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
#include "Utility_CommunicatorDecl.hpp"

namespace Utility{

/*! The serial communicator class
 * NOTE: Due to scatterv changes introduced in boost 1.72, 
 * anything involving scatterv does not function properly 
 * at the moment and its tests are disabled. If you require
 * scatterv, please find the bug, fix it, and submit it for
 * a pull request.
 * \ingroup mpi
 */

class SerialCommunicator : public Communicator
{

public:

  //! Get the serial communicator
  static std::shared_ptr<const SerialCommunicator> get();

  //! Destructor
  ~SerialCommunicator();

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

  //! Check if this communicator can be used for communication
  bool isValid() const override;

  //! Check if this communicator uses mpi
  bool isMPIUsed() const override;

  //! Check if this communicator is identical to another
  bool isIdentical( const Communicator& comm ) const override;
  
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

private:

  // Default constructor
  SerialCommunicator();

  // The gatherv implementation
  template<typename T>
  static void gathervImpl( const T* input_values,
                           int number_of_input_values,
                           int requested_number_of_input_values_to_send,
                           int input_values_offset,
                           T* output_values );

  // The scatterv implementation
  template<typename T>
  static void scattervImpl( const T* input_values,
                            int requested_number_of_input_values_to_send,
                            int input_values_offset,
                            T* output_values,
                            int output_values_size );

  // The rank of all serial communicators
  static const int s_rank = 0;

  // The size of all serial communicators
  static const int s_size = 1;

  // The serial communicator
  static std::shared_ptr<const SerialCommunicator> s_serial_comm;
};
  
} // end Utility namespace

#endif // end UTILITY_SERIAL_COMMUNICATOR_HPP

//---------------------------------------------------------------------------//
// end Utility_SerialCommunicator.hpp
//---------------------------------------------------------------------------//
