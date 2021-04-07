//---------------------------------------------------------------------------//
//!
//! \file   Utility_Communicator.hpp
//! \author Alex Robinson
//! \brief  The communicator class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_COMMUNICATOR_HPP
#define UTILITY_COMMUNICATOR_HPP

// FRENSIE Includes
#include "Utility_CommunicatorDecl.hpp"
#include "Utility_SerialCommunicator.hpp"
#include "Utility_MPICommunicator.hpp"
#include "Utility_ArrayView.hpp"

/*! NOTE: Due to scatterv changes introduced in boost 1.72, 
 *  anything involving scatterv does not function properly 
 * at the moment and its tests are disabled. If you require
 * scatterv, please find the bug, fix it, and submit it for
 * a pull request.
 *  \ingroup mpi
 */

namespace Utility{

//! Send data to another process
template<typename T>
void send( const Communicator& comm,
           int destination_process,
           int tag,
           const T& value );

//! Send a std::initializer_list of data to another process
template<typename T>
void send( const Communicator& comm,
           int destination_process,
           int tag,
           std::initializer_list<T> values );

//! Send a Utility::ArrayView of data to another process
template<typename T>
void send( const Communicator& comm,
           int destination_process,
           int tag,
           const Utility::ArrayView<const T>& values );

//! Receive data from another process
template<typename T>
Communicator::Status receive( const Communicator& comm,
                              int source_process,
                              int tag,
                              T& value );

//! Receive an array of data from another process
template<typename T>
Communicator::Status receive( const Communicator& comm,
                              int source_process,
                              int tag,
                              const Utility::ArrayView<T>& values );

//! Send a data to another process without blocking
template<typename T>
Communicator::Request isend( const Communicator& comm,
                             int destination_process,
                             int tag,
                             const T& value );

//! Send an array of data to another process without blocking
template<typename T>
Communicator::Request isend( const Communicator& comm,
                             int destination_process,
                             int tag,
                             const ArrayView<const T>& values );

//! Prepare to receive data from another process
template<typename T>
Communicator::Request ireceive( const Communicator& comm,
                                int source_process,
                                int tag,
                                T& value );

//! Prepare to receive an array of data from another process
template<typename T>
Communicator::Request ireceive( const Communicator& comm,
                                int source_process,
                                int tag,
                                const ArrayView<T>& values );

//! Wait until a message is available to be received
template<typename T>
Communicator::Status probe( const Communicator& comm,
                            int source_process,
                            int tag );

//! Wait until a message is available to be received from any source
template<typename T>
Communicator::Status probe( const Communicator& comm, int tag );

//! Wait until a message is available to be received from any source with any tag
template<typename T>
Communicator::Status probe( const Communicator& comm );

//! Determine if a message is available to be received
template<typename T>
Communicator::Status iprobe( const Communicator& comm,
                             int source_process,
                             int tag );

//! Determine if a message is available to be received from any source
template<typename T>
Communicator::Status iprobe( const Communicator& comm, int tag );

//! Determine if a message is available to be received from any source with any tag
template<typename T>
Communicator::Status iprobe( const Communicator& comm );

//! Wait for the requests to finish
template<template<typename T,typename...> class STLCompliantInputSequenceContainer,
         template<typename T,typename...> class STLCompliantOutputSequenceContainer>
void wait( STLCompliantInputSequenceContainer<Communicator::Request>& requests,
           STLCompliantOutputSequenceContainer<Communicator::Status>& statuses );

/*! \brief Gather the values stored at every process into an array of values
 * from each process.
 */
template<typename T>
void allGather( const Communicator& comm,
                const T& input_value,
                std::vector<T>& output_values );

/*! \brief Gather the values stored at every process into an array of values
 * from each process.
 */
template<typename T>
void allGather( const Communicator& comm,
                const T& input_value,
                const Utility::ArrayView<T>& output_values );

/*! \brief Gather the values stored at every process into an array of values
 * from each process.
 */
template<typename T>
void allGather( const Communicator& comm,
                std::initializer_list<T> input_values,
                const std::vector<T>& output_values );

/*! \brief Gather the values stored at every process into an array of values
 * from each process.
 */
template<typename T>
void allGather( const Communicator& comm,
                std::initializer_list<T> input_values,
                const Utility::ArrayView<T>& output_values );

/*! \brief Gather the values stored at every process into an array of values
 * from each process.
 */
template<typename T>
void allGather( const Communicator& comm,
                const Utility::ArrayView<const T>& input_values,
                std::vector<T>& output_values );

/*! \brief Gather the values stored at every process into an array of values
 * from each process.
 */
template<typename T>
void allGather( const Communicator& comm,
                const Utility::ArrayView<const T>& input_values,
                const Utility::ArrayView<T>& output_values );

/*! \brief Combine the values stored by each process into a single value
 * available to all processes.
 */
template<typename T, typename ReduceOperation>
void allReduce( const Communicator& comm,
                const T& input_value,
                T& output_value,
                ReduceOperation op );

/*! \brief Combine the values stored by each process into a single value
 * available to all processes.
 */
template<typename T, typename ReduceOperation>
void allReduce( const Communicator& comm,
                T& input_output_value,
                ReduceOperation op );

/*! \brief Combine the values stored by each process into a single value
 * available to all processes.
 */
template<typename T, typename ReduceOperation>
void allReduce( const Communicator& comm,
                const Utility::ArrayView<const T>& input_values,
                const Utility::ArrayView<T>& output_values,
                ReduceOperation op );

/*! \brief Combine the values stored by each process into a single value
 * available to all processes.
 */
template<typename T, typename ReduceOperation>
void allReduce( const Communicator& comm,
                const Utility::ArrayView<T>& input_output_values,
                ReduceOperation op );

//! Send data from every process to every other process
template<typename T>
void allToAll( const Communicator& comm,
               const Utility::ArrayView<const T>& input_values,
               std::vector<T>& output_values );

//! Send data from every process to every other process
template<typename T>
void allToAll( const Communicator& comm,
               const Utility::ArrayView<const T>& input_values,
               const Utility::ArrayView<T>& output_values );

//! Broadcast a value from a root process to all other processes
template<typename T>
void broadcast( const Communicator& comm, T& value, int root_process );

//! Broadcast a value from a root process to all other processes
template<typename T>
void broadcast( const Communicator& comm,
                const Utility::ArrayView<T>& values,
                int root_process );

//! Gather the values stored at every process into a vector at the root process
template<typename T>
void gather( const Communicator& comm,
             const T& input_value,
             std::vector<T>& output_values,
             int root_process );

//! Gather the values stored at every process into a vector at the root process
template<typename T>
void gather( const Communicator& comm,
             const T& input_value,
             const Utility::ArrayView<T>& output_values,
             int root_process );

//! Gather the values stored at every process into a vector at the root process
template<typename T>
void gather( const Communicator& comm,
             const T& input_value,
             int root_process );

//! Gather the values stored at every process into a vector at the root process
template<typename T>
void gather( const Communicator& comm,
             std::initializer_list<T> input_values,
             std::vector<T>& output_values,
             int root_process );

//! Gather the values stored at every process into a vector at the root process
template<typename T>
void gather( const Communicator& comm,
             std::initializer_list<T> input_values,
             const Utility::ArrayView<T>& output_values,
             int root_process );

//! Gather the values stored at every process into a vector at the root process
template<typename T>
void gather( const Communicator& comm,
             std::initializer_list<T> input_values,
             int root_process );

//! Gather the values stored at every process into a vector at the root process
template<typename T>
void gather( const Communicator& comm,
             const Utility::ArrayView<const T>& input_values,
             std::vector<T>& output_values,
             int root_process );

//! Gather the values stored at every process into a vector at the root process
template<typename T>
void gather( const Communicator& comm,
             const Utility::ArrayView<const T>& input_values,
             const Utility::ArrayView<T>& output_values,
             int root_process );

//! Gather the values stored at every process into a vector at the root process
template<typename T>
void gather( const Communicator& comm,
             const Utility::ArrayView<const T>& input_values,
             int root_process );

//! Gather the values stored at every process into a vector at the root process
template<typename T>
void gatherv( const Communicator& comm,
              const T& input_value,
              std::vector<T>& output_values,
              int root_process );

//! Gather the values stored at every process into a vector at the root process
template<typename T>
void gatherv( const Communicator& comm,
              const T& input_value,
              const Utility::ArrayView<T>& output_values,
              int root_process );

//! Gather the values stored at every process into a vector at the root process
template<typename T>
void gatherv( const Communicator& comm,
              std::initializer_list<T> input_values,
              std::vector<T>& output_values,
              int root_process );

//! Gather the values stored at every process into a vector at the root process
template<typename T>
void gatherv( const Communicator& comm,
              std::initializer_list<T> input_values,
              const Utility::ArrayView<T>& output_values,
              int root_process );

//! Gather the values stored at every process into a vector at the root process
template<typename T>
void gatherv( const Communicator& comm,
              const Utility::ArrayView<const T>& input_values,
              std::vector<T>& output_values,
              int root_process );

//! Gather the values stored at every process into a vector at the root process
template<typename T>
void gatherv( const Communicator& comm,
              const Utility::ArrayView<const T>& input_values,
              const Utility::ArrayView<T>& output_values,
              int root_process );

//! Gather the values stored at every process into a vector at the root process
template<typename T>
void gatherv( const Communicator& comm,
              const T& input_value,
              int root_process );

//! Gather the values stored at every process into a vector at the root process
template<typename T>
void gatherv( const Communicator& comm,
              std::initializer_list<T> input_values,
              int root_process );

//! Gather the values stored at every process into a vector at the root process
template<typename T>
void gatherv( const Communicator& comm,
              const Utility::ArrayView<const T>& input_values,
              int root_process );

//! Scatter the values stored at the root process to all other processes
template<typename T>
void scatter( const Communicator& comm,
              std::initializer_list<T> input_values,
              T& output_value,
              int root_process );

//! Scatter the values stored at the root process to all other processes
template<typename T>
void scatter( const Communicator& comm,
              const Utility::ArrayView<const T>& input_values,
              T& output_value,
              int root_process );

//! Scatter the values stored at the root process to all other processes
template<typename T>
void scatter( const Communicator& comm,
              T& output_value,
              int root_process );

//! Scatter the values stored at the root process to all other processes
template<typename T>
void scatter( const Communicator& comm,
              std::initializer_list<T> input_values,
              const Utility::ArrayView<T>& output_values,
              int root_process );

//! Scatter the values stored at the root process to all other processes
template<typename T>
void scatter( const Communicator& comm,
              const Utility::ArrayView<const T>& input_values,
              const Utility::ArrayView<T>& output_values,
              int root_process );

//! Scatter the values stored at the root process to all other processes
template<typename T>
void scatter( const Communicator& comm,
              const Utility::ArrayView<T>& output_values,
              int root_process );

//! Scatter the values stored at the root process to all other processes
template<typename T>
void scatterv( const Communicator& comm,
               const Utility::ArrayView<const T>& input_values,
               const std::vector<int>& sizes,
               std::vector<T>& output_values,
               int root_process );

//! Scatter the values stored at the root process to all other processes
template<typename T>
void scatterv( const Communicator& comm,
               const Utility::ArrayView<const T>& input_values,
               const std::vector<int>& sizes,
               const Utility::ArrayView<T>& output_values,
               int root_process );

//! Scatter the values stored at the root process to all other processes
template<typename T>
void scatterv( const Communicator& comm,
               std::vector<T>& output_values,
               int root_process );

//! Scatter the values stored at the root process to all other processes
template<typename T>
void scatterv( const Communicator& comm,
               const Utility::ArrayView<T>& output_values,
               int root_process );

//! Combine the values stored by each process into a single value at the root
template<typename T, typename ReduceOperation>
void reduce( const Communicator& comm,
             const T& input_value,
             T& output_value,
             ReduceOperation op,
             int root_process );

//! Combine the values stored by each process into a single value at the root
template<typename T, typename ReduceOperation>
void reduce( const Communicator& comm,
             std::initializer_list<T> input_values,
             const Utility::ArrayView<T>& output_values,
             ReduceOperation op,
             int root_process );

//! Combine the values stored by each process into a single value at the root
template<typename T, typename ReduceOperation>
void reduce( const Communicator& comm,
             const Utility::ArrayView<const T>& input_values,
             const Utility::ArrayView<T>& output_values,
             ReduceOperation op,
             int root_process );

//! Combine the values stored by each process into a single value at the root
template<typename T, typename ReduceOperation>
void reduce( const Communicator& comm,
             const T& input_value,
             ReduceOperation op,
             int root_process );

//! Combine the values stored by each process into a single value at the root
template<typename T, typename ReduceOperation>
void reduce( const Communicator& comm,
             std::initializer_list<T> input_values,
             ReduceOperation op,
             int root_process );

//! Combine the values stored by each process into a single value at the root
template<typename T, typename ReduceOperation>
void reduce( const Communicator& comm,
             const Utility::ArrayView<const T>& input_values,
             ReduceOperation op,
             int root_process );

//! Compute a prefix reduction of values from all processes
template<typename T, typename ReduceOperation>
void scan( const Communicator& comm,
           const T& input_value,
           T& output_value,
           ReduceOperation op );

//! Compute a prefix reduction of values from all processes
template<typename T, typename ReduceOperation>
void scan( const Communicator& comm,
           const Utility::ArrayView<const T>& input_values,
           const Utility::ArrayView<T>& output_values,
           ReduceOperation op );

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "Utility_Communicator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_COMMUNICATOR_DECL_HPP

//---------------------------------------------------------------------------//
// end Utility_CommunicatorDecl.hpp
//---------------------------------------------------------------------------//
