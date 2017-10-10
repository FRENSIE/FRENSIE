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

  /*! \brief Gather the array of values stored at every process into vectors of
   * values from each process.
   */
  template<typename T>
  static void allGather( const T* input_values,
                         int number_of_input_values,
                         T* output_values );

  /*! \brief Combine the values stored by each process into a single value
   * available to all processes.
   */
  template<typename T, typename ReduceOperation>
  static void allReduce( const T* input_values,
                         int number_of_input_values,
                         T* output_values,
                         ReduceOperation op );

  //! Send data from every process to every other process
  template<typename T>
  static void allToAll( const T* input_values,
                        int number_of_input_values,
                        T* output_values );

  //! Broadcast a value from a root process to all other processes
  template<typename T>
  static void broadcast( T* values,
                         int number_of_values,
                         int root_process );

  //! Gather the values stored at every process into a vector at the root process
  template<typename T>
  static void gather( const T* input_values,
                      int number_of_input_values,
                      T* output_values,
                      int root_process );

  //! Gather the values stored at every process into a vector at the root process
  template<typename T>
  static void gatherv( const T* input_values,
                       int number_of_input_values,
                       T* output_values,
                       const std::vector<int>& sizes,
                       const std::vector<int>& offsets,
                       const int root_process );

  //! Gather the values stored at every process into a vector at the root process
  template<typename T>
  static void gatherv( const T* input_values,
                       int number_of_input_values,
                       T* output_values,
                       const std::vector<int>& sizes,
                       const int root_process );

  //! Scatter the values stored at the root process to all other processes
  template<typename T>
  static void scatter( const T* input_values,
                       T* output_values,
                       int number_of_values_per_proc,
                       int root_process );

  //! Scatter the values stored at the root process to all other processes
  template<typename T>
  static void scatterv( const T* input_values,
                        const std::vector<int>& sizes,
                        const std::vector<int>& offsets,
                        T* output_values,
                        int number_of_output_values,
                        int root_process );

  //! Scatter the values stored at the root process to all other processes
  template<typename T>
  static void scatterv( const T* input_values,
                        const std::vector<int>& sizes,
                        T* output_values,
                        int number_of_output_values,
                        int root_process );

  //! Combine the values stored by each process intoa single value at the root
  template<typename T, typename ReduceOperation>
  static void reduce( const T* input_values,
                      int number_of_input_values,
                      T* output_values,
                      ReduceOperation op,
                      int root_process );

  //! Compute a prefix reduction of values from all processes
  template<typename T, typename ReduceOperation>
  static void scan( const T* input_values,
                    int number_of_input_values,
                    T* output_values,
                    ReduceOperation op );

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

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_SerialCommunicator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_SERIAL_COMMUNICATOR_HPP

//---------------------------------------------------------------------------//
// end Utility_SerialCommunicator.hpp
//---------------------------------------------------------------------------//
