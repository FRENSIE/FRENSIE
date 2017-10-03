//---------------------------------------------------------------------------//
//!
//! \file   Utility_CommunicatorHelpers.hpp
//! \author Alex Robinson
//! \brief  The communicator helper method declarations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_COMMUNICATOR_HELPERS_HPP
#define UTILITY_COMMUNICATOR_HELPERS_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "Utility_Communicator.hpp"
#include "Utility_Vector.hpp"

namespace Utility{

//! Determine the number of elements that were contained in a message
template<typename T>
int count( const Communicator& comm, const CommunicatorStatus& status );

//! Send data to another process
template<typename T>
void send( const Communicator& comm,
           int destination_process,
           int tag,
           const T& value );

//! Send an array of data to another process
template<typename T>
void send( const Communicator& comm,
           int destination_process,
           int tag,
           const T* values,
           int number_of_values );

//! Receive data from another process
template<typename T>
std::shared_ptr<const CommunicatorStatus>
receive( const Communicator& comm,
         int source_process,
         int tag,
         T& value );

//! Receive an array of data from another process
template<typename T>
std::shared_ptr<const CommunicatorStatus>
receive( const Communicator& comm,
         int source_process,
         int tag,
         T* values,
         int number_of_values );

//! Send a data to another process without blocking
std::shared_ptr<CommunicatorRequest>
isend( const Communicator& comm,
       int destination_process,
       int tag,
       const T& value );

//! Send an array of data to another process without blocking
std::shared_ptr<CommunicatorRequest>
isend( const Communicator& comm,
       int destination_process,
       int tag, 
       const T* values,
       int number_of_values );

//! Prepare to receive data from another process
template<typename T>
std::shared_ptr<CommunicatorRequest>
ireceive( const Communicator& comm,
          int source_process,
          int tag,
          T& value );

//! Prepare to receive an array of data from another process
template<typename T>
std::shared_ptr<CommunicatorRequest>
ireceive( const Communicator& comm,
          int source_process,
          int tag,
          T* values,
          int number_of_values );

//! Wait until a message is available to be received
std::shared_ptr<const CommunicatorStatus>
probe( const Communicator& comm, int source_process, int tag );

//! Wait until a message is available to be received from any source
std::shared_ptr<const CommunicatorStatus>
probe( const Communicator& comm, int tag );

//! Wait until a message is available to be received from any source with any tag
std::shared_ptr<const CommunicatorStatus>
probe( const Communicator& comm );

//! Determine if a message is available to be received
std::shared_ptr<const CommunicatorStatus>
iprobe( const Communicator& comm, int source_process, int tag );

//! Determine if a message is available to be received from any source
std::shared_ptr<const CommunicatorStatus>
iprobe( const Communicator& comm, int tag );

//! Determine if a message is available to be received from any source with any tag
std::shared_ptr<const CommunicatorStatus>
iprobe( const Communicator& comm );

//! Wait for the request to finish
std::shared_ptr<const CommunicatorStatus>
wait( const Communicator& comm,
      const std::shared_ptr<CommunicatorRequest>& request );

//! Wait for the request to finish
void wait( const Communicator& comm,
           const std::shared_ptr<CommunicatorRequest>& request,
           std::shared_ptr<const CommunicatorStatus>& status );

//! Wait for the requests to finish
template<template<typename T,typename...> class STLCompliantInputSequenceContainer,
         template<typename T,typename...> class STLCompliantOutputSequenceContainer,
         typename T>
void wait( const Communicator& comm,
           const STLCompliantInputSequenceContainer<std::shared_ptr<CommunicatorRequest> >& requests,
           STLCompliantOutputSequenceContainer<std::shared_ptr<const CommunicatorStatus> >& statuses );

/*! \brief Gather the values stored at every process into vectors of values 
 * from each process.
 */
template<typename T>
void allGather( const Communicator& comm,
                const T& input_value,
                std::vector<T>& output_values );

/*! \brief Gather the values stored at every process into vectors of values 
 * from each process.
 */
template<typename T>
void allGather( const Communicator& comm,
                const T& input_value,
                T* output_values );

/*! \brief Gather the array of values stored at every process into vectors of
 * values from each process.
 */
template<typename T>
void allGather( const Communicator& comm,
                const T* input_values,
                int number_of_input_values,
                std::vector<T>& output_values );

/*! \brief Gather the array of values stored at every process into vectors of
 * values from each process.
 */
template<typename T>
void allGather( const Communicator& comm,
                const T* input_values,
                int number_of_input_values,
                T* output_values );

/*! \brief Combine the values stored by each process into a single value
 * available to all processes.
 */
template<typename T, typename ReduceOperation>
void allReduce( const Communicator& comm,
                const T* input_values,
                int number_of_input_values,
                T* output_values,
                ReduceOperation op );

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
                T* input_output_values,
                int number_of_values,
                ReduceOperation op );

/*! \brief Combine the values stored by each process into a single value
 * available to all processes.
 */
template<typename T, typename ReduceOperation>
void allReduce( const Communicator& comm,
                T& input_output_value,
                ReduceOperation op );

//! Send data from every process to every other process
template<typename T>
void allToAll( const Communicator& comm,
               const std::vector<T>& input_values,
               std::vector<T>& output_values );

//! Send data from every process to every other process
template<typename T>
void allToAll( const Communicator& comm,
               const std::vector<T>& input_values,
               int number_of_input_values,
               std::vector<T>& output_values );

//! Send data from every process to every other process
template<typename T>
void allToAll( const Communicator& comm,
               const T* input_values,
               int number_of_input_values,
               T* output_values );

//! Broadcast a value from a root process to all other processes
template<typename T>
void broadcast( const Communicator& comm, T& value, int root_process );

//! Broadcast a value from a root process to all other processes
template<typename T>
void broadcast( const Communicator& comm,
                T* values,
                int number_of_values,
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
             T* output_values,
             int root_process );

//! Gather the values stored at every process into a vector at the root process
template<typename T>
void gather( const Communicator& comm,
             const T* input_values,
             int number_of_input_values,
             std::vector<T>& output_values,
             int root_process );

//! Gather the values stored at every process into a vector at the root process
template<typename T>
void gather( const Communicator& comm,
             const T* input_values,
             int number_of_input_values,
             T* output_values,
             int root_process );

//! Gather the values stored at every process into a vector at the root process
template<typename T>
void gatherv( const Communicator& comm,
              const std::vector<T>& input_values,
              T* output_values,
              const std::vector<int>& sizes,
              const std::vector<int>& offsets,
              const int root_process );

//! Gather the values stored at every process into a vector at the root process
template<typename T>
void gatherv( const Communicator& comm,
              const T* input_values,
              int number_of_input_values,
              T* output_values,
              const std::vector<int>& sizes,
              const std::vector<int>& offsets,
              const int root_process );

//! Gather the values stored at every process into a vector at the root process
template<typename T>
void gatherv( const Communicator& comm,
              const std::vector<T>& input_values,
              T* output_values,
              const std::vector<int>& sizes,
              const int root_process );

//! Gather the values stored at every process into a vector at the root process
template<typename T>
void gatherv( const Communicator& comm,
              const T* input_values,
              int number_of_input_values,
              T* output_values,
              const std::vector<int>& sizes,
              const int root_process );

//! Scatter the values stored at the root process to all other processes
template<typename T>
void scatter( const Communicator& comm,
              const std::vector<T>& input_values,
              T& output_value,
              int root_process );

//! Scatter the values stored at the root process to all other processes
template<typename T>
void scatter( const Communicator& comm,
              const T* input_values,
              T& output_value,
              int root_process );

//! Scatter the values stored at the root process to all other processes
template<typename T>
void scatter( const Communicator& comm,
              const std::vector<T>& input_values,
              T* output_values,
              int number_of_values_per_proc,
              int root_process );

//! Scatter the values stored at the root process to all other processes
template<typename T>
void scatter( const Communicator& comm,
              const T* input_values,
              T* output_values,
              int number_of_values_per_proc,
              int root_process );

//! Scatter the values stored at the root process to all other processes
template<typename T>
void scatterv( const Communicator& comm,
               const std::vector<T>& input_values,
               const std::vector<int>& sizes,
               const std::vector<int>& offsets,
               T* output_values,
               int number_of_output_values,
               int root_process );

//! Scatter the values stored at the root process to all other processes
template<typename T>
void scatterv( const Communicator& comm,
               const T* input_values,
               const std::vector<int>& sizes,
               const std::vector<int>& offsets,
               T* output_values,
               int number_of_output_values,
               int root_process );

//! Scatter the values stored at the root process to all other processes
template<typename T>
void scatterv( const Communicator& comm,
               const std::vector<T>& input_values,
               const std::vector<int>& sizes,
               T* output_values,
               int number_of_output_values,
               int root_process );

//! Scatter the values stored at the root process to all other processes
template<typename T>
void scatterv( const Communicator& comm,
               const T* input_values,
               const std::vector<int>& sizes,
               T* output_values,
               int number_of_output_values,
               int root_process );

//! Combine the values stored by each process intoa single value at the root
template<typename T, typename ReduceOperation>
void reduce( const Communicator& comm,
             const T& input_value,
             T& output_value,
             ReduceOperation op,
             int root_process );

//! Combine the values stored by each process intoa single value at the root
template<typename T, typename ReduceOperation>
void reduce( const Communicator& comm,
             const T* input_values,
             int number_of_input_values,
             T* output_values,
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
           const T* input_values,
           int number_of_input_values,
           T* output_value,
           ReduceOperation op );
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_CommunicatorHelpers_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_COMMUNICATOR_HELPERS_HPP

//---------------------------------------------------------------------------//
// end Utility_CommunicatorHelpers.hpp
//---------------------------------------------------------------------------//
