//---------------------------------------------------------------------------//
//!
//! \file   Utility_MPICommunicator.hpp
//! \author Alex Robinson
//! \brief  The mpi communicator class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_MPI_COMMUNICATOR_HPP
#define UTILITY_MPI_COMMUNICATOR_HPP

// FRENSIE Includes
#include "Utility_CommunicatorDecl.hpp"
#include "Utility_Vector.hpp"
#include "FRENSIE_config.hpp"

namespace Utility{

/*! The mpi communicator class
 *
 * This type of communicator cannot be constructed directly. Use the
 * Utility::Communicator::getDefault() method. If MPI has been
 * configured for use and has been initialized successfully, the MPI world
 * communicator will be returned.
 * NOTE: Due to scatterv changes introduced in boost 1.72, 
 *  anything involving scatterv does not function properly 
 * at the moment and its tests are disabled. If you require
 * scatterv, please find the bug, fix it, and submit it for
 * a pull request.
 *  \ingroup mpi
 */
 
class MPICommunicator : public Communicator
{

public:

  //! Destructor
  ~MPICommunicator()
  { /* ... */ }

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

  //! Send a message to another process (blocking)
  template<typename T>
  void send( int dest, int tag, const T* values, int number_of_values ) const;

  //! Receive a message from another process (blocking)
  template<typename T>
  Communicator::Status recv( int source, int tag, T* values, int number_of_values ) const;

  //! Send a message to another process (non-blocking)
  template<typename T>
  Communicator::Request isend( int dest, int tag, const T* values, int number_of_values ) const;

  //! Receive a message from another process (non-blocking)
  template<typename T>
  Communicator::Request irecv( int source, int tag, T* values, int number_of_values ) const;

  //! Wait until a message is available to be received
  template<typename T>
  Communicator::Status probe( int source, int tag ) const;

  //! Determine if a message is available to be received
  template<typename T>
  Communicator::Status iprobe( int source, int tag ) const;

  /*! \brief Gather the array of values stored at every process into vectors of
   * values from each process.
   */
  template<typename T>
  void allGather( const T* input_values,
                  int number_of_input_values,
                  T* output_values ) const;

  /*! \brief Combine the values stored by each process into a single value
   * available to all processes.
   */
  template<typename T, typename ReduceOperation>
  void allReduce( const T* input_values,
                  int number_of_input_values,
                  T* output_values,
                  ReduceOperation op ) const;

  /*! \brief Combine the values stored by each process into a single value
   * available to all processes.
   */
  template<typename T, typename ReduceOperation>
  void allReduce( T* input_output_values,
                  int number_of_values,
                  ReduceOperation op ) const;

  //! Send data from every process to every other process
  template<typename T>
  void allToAll( const T* input_values,
                 int number_of_input_values,
                 T* output_values ) const;

  //! Broadcast a value from a root process to all other processes
  template<typename T>
  void broadcast( T* values,
                  int number_of_values,
                  int root_process ) const;

  //! Gather the values stored at every process into a vector at the root process
  template<typename T>
  void gather( const T* input_values,
               int number_of_input_values,
               T* output_values,
               int root_process ) const;

  //! Gather the values stored at every process into a vector at the root process
  template<typename T>
  void gatherv( const T* input_values,
                int number_of_input_values,
                T* output_values,
                const std::vector<int>& sizes,
                const std::vector<int>& offsets,
                const int root_process ) const;

  //! Gather the values stored at every process into a vector at the root process
  template<typename T>
  void gatherv( const T* input_values,
                int number_of_input_values,
                T* output_values,
                const std::vector<int>& sizes,
                const int root_process ) const;

  //! Scatter the values stored at the root process to all other processes
  template<typename T>
  void scatter( const T* input_values,
                T* output_values,
                int number_of_values_per_proc,
                int root_process ) const;

  //! Scatter the values stored at the root process to all other processes
  template<typename T>
  void scatterv( const T* input_values,
                 const std::vector<int>& sizes,
                 const std::vector<int>& offsets,
                 T* output_values,
                 int number_of_output_values,
                 int root_process ) const;

  //! Scatter the values stored at the root process to all other processes
  template<typename T>
  void scatterv( const T* input_values,
                 const std::vector<int>& sizes,
                 T* output_values,
                 int number_of_output_values,
                 int root_process ) const;

  //! Combine the values stored by each process into a single value at the root
  template<typename T, typename ReduceOperation>
  void reduce( const T* input_values,
               int number_of_input_values,
               T* output_values,
               ReduceOperation op,
               int root_process ) const ;

  //! Compute a prefix reduction of values from all processes
  template<typename T, typename ReduceOperation>
  void scan( const T* input_values,
             int number_of_input_values,
             T* output_values,
             ReduceOperation op ) const;

private:

  //! The communicator base class is a friend
  friend class Communicator;

  // Constructor
  MPICommunicator();

#ifdef HAVE_FRENSIE_MPI
  // boost::communicator constructor
  MPICommunicator( const boost::mpi::communicator& comm );

  // The boost mpi communicator
  boost::mpi::communicator d_comm;
#endif // end HAVE_FRENSIE_MPI
};

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_MPICommunicator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_MPI_COMMUNICATOR_HPP

//---------------------------------------------------------------------------//
// end Utility_MPICommunicator.hpp
//---------------------------------------------------------------------------//
