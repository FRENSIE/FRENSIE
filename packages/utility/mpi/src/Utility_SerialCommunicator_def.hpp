//---------------------------------------------------------------------------//
//!
//! \file   Utility_SerialCommunicator_def.hpp
//! \author Alex Robinson
//! \brief  The serial communicator template method definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SERIAL_COMMUNICATOR_DEF_HPP
#define UTILITY_SERIAL_COMMUNICATOR_DEF_HPP

// Std Lib Includes
#include <cstring>

// FRENSIE Includes
#include "Utility_LoggingMacros.hpp"

namespace Utility{

namespace Details{

/*! The serial communicator array copy helper
 * \ingroup mpi
 */
template<typename T, typename Enabled = void>
struct SerialCommunicatorArrayCopyHelper
{
  //! Copy from input array to output array using a element-by-element deep copy
  static inline void copyFromInputArrayToOutputArray(
                                                    const T* input_values,
                                                    int number_of_input_values,
                                                    T* output_values )
  {
    for( int i = 0; i < number_of_input_values; ++i )
      output_values[i] = input_values[i];
  }
};

/*! \brief Specialization of SerialCommunicatorArrayCopyHelper for arithmetic 
 * types
 * \ingroup mpi
 */
template<typename T>
struct SerialCommunicatorArrayCopyHelper<T,typename std::enable_if<std::is_arithmetic<T>::value>::type>
{
  //! Copy from input array to output array using memcpy
  static inline void copyFromInputArrayToOutputArray(
                                                    const T* input_values,
                                                    int number_of_input_values,
                                                    T* output_values )
  {
    std::memcpy( output_values,
                 input_values,
                 sizeof(T)*number_of_input_values );
  }
};
  
} // end Details namespace

// Gather the array of values stored at every process into vectors of
// values from each process.
/*! \details The values in the input array will simply be copied to the
 * output array
 */
template<typename T>
void SerialCommunicator::allGather( const T* input_values,
                                    int number_of_input_values,
                                    T* output_values )
{
  Details::SerialCommunicatorArrayCopyHelper<T>::copyFromInputArrayToOutputArray( input_values, number_of_input_values, output_values );
}

// Combine the values stored by each process into a single value
// available to all processes.
/*! \details The values in the input array will simply be copied to the
 * output array
 */
template<typename T, typename ReduceOperation>
void SerialCommunicator::allReduce( const T* input_values,
                                    int number_of_input_values,
                                    T* output_values,
                                    ReduceOperation )
{
  Details::SerialCommunicatorArrayCopyHelper<T>::copyFromInputArrayToOutputArray( input_values, number_of_input_values, output_values );
}

// Send data from every process to every other process
/*! \details The values in the input array will simply be copied to the
 * output array
 */
template<typename T>
void SerialCommunicator::allToAll( const T* input_values,
                                   int number_of_input_values,
                                   T* output_values )
{
  Details::SerialCommunicatorArrayCopyHelper<T>::copyFromInputArrayToOutputArray( input_values, number_of_input_values, output_values );
}

// Broadcast a value from a root process to all other processes
/*! \details The values in the input array will simply be copied to the
 * output array
 */
template<typename T>
void SerialCommunicator::broadcast( T*, int, int root_process )
{
  if( root_process != s_rank )
  {
    FRENSIE_LOG_TAGGED_WARNING( "Serial Comm",
                                "The only process available for the "
                                "broadcast operation is "
                                << s_rank << "! The requested root "
                                "process " << root_process <<
                                " will be ignored!" );
  }
}

// Gather the values stored at every process into a vector at the root process
/*! \details The values in the input array will simply be copied to the
 * output array
 */
template<typename T>
void SerialCommunicator::gather( const T* input_values,
                                 int number_of_input_values,
                                 T* output_values,
                                 int root_process )
{
  if( root_process != s_rank )
  {
    FRENSIE_LOG_TAGGED_WARNING( "Serial Comm",
                                "The only process available for the "
                                "gather operation is " << s_rank << "! "
                                "The requested root process "
                                << root_process <<
                                " will be ignored!" );
  }
  
  Details::SerialCommunicatorArrayCopyHelper<T>::copyFromInputArrayToOutputArray( input_values, number_of_input_values, output_values );
}

// The gatherv implementation
template<typename T>
void SerialCommunicator::gathervImpl(
                                  const T* input_values,
                                  int number_of_input_values,
                                  int requested_number_of_input_values_to_send,
                                  int input_values_offset,
                                  T* output_values )
{
  if( input_values_offset < number_of_input_values )
  {
    int number_to_send = requested_number_of_input_values_to_send;
      
    if( number_to_send + input_values_offset > number_of_input_values )
    {
      FRENSIE_LOG_TAGGED_WARNING( "Serial Comm",
                                  "There are only "
                                  << number_of_input_values << " input "
                                  "values but elements in the range ["
                                  << input_values_offset << ","
                                  << number_to_send + input_values_offset <<
                                  ") have been requested! Only elements "
                                  "in the range ["
                                  << input_values_offset << ","
                                  << number_of_input_values <<
                                  ") will be sent." );

      number_to_send = number_of_input_values - input_values_offset;
    }

    Details::SerialCommunicatorArrayCopyHelper<T>::copyFromInputArrayToOutputArray( input_values+input_values_offset, number_to_send, output_values );
  }
  else
  {
    FRENSIE_LOG_TAGGED_WARNING( "Serial Comm",
                                "The requested offset of "
                                << input_values_offset <<
                                " is beyone the input array bounds! No "
                                "elements will be sent." );
  }
}

// Gather the values stored at every process into a vector at the root process
/*! \details The values in the input array will simply be copied to the
 * output array
 */
template<typename T>
void SerialCommunicator::gatherv( const T* input_values,
                                  int number_of_input_values,
                                  T* output_values,
                                  const std::vector<int>& sizes,
                                  const std::vector<int>& offsets,
                                  const int root_process )
{
  if( root_process != s_rank )
  {
    FRENSIE_LOG_TAGGED_WARNING( "Serial Comm",
                                "The only process available for the "
                                "gatherv operation is " << s_rank << "!"
                                " The requested root process "
                                << root_process <<
                                " will be ignored!" );
  }
  
  if( !sizes.empty() )
  {
    int offset = 0;
    
    if( !offsets.empty() )
      offset = offsets.front();
    
    SerialCommunicator::gathervImpl( input_values,
                                     number_of_input_values,
                                     sizes.front(),
                                     offset,
                                     output_values );
  }
}

// Gather the values stored at every process into a vector at the root process
/*! \details The values in the input array will simply be copied to the
 * output array
 */
template<typename T>
void SerialCommunicator::gatherv( const T* input_values,
                                  int number_of_input_values,
                                  T* output_values,
                                  const std::vector<int>& sizes,
                                  const int root_process )
{
  if( root_process != s_rank )
  {
    FRENSIE_LOG_TAGGED_WARNING( "Serial Comm",
                                "The only process available for the "
                                "gatherv operation is " << s_rank << "!"
                                " The requested root process "
                                << root_process <<
                                " will be ignored!" );
  }

  if( !sizes.empty() )
  {
    SerialCommunicator::gathervImpl( input_values,
                                     number_of_input_values,
                                     sizes.front(),
                                     0, 
                                     output_values );
  }
}

// Scatter the values stored at the root process to all other processes
template<typename T>
void SerialCommunicator::scatter( const T* input_values,
                                  T* output_values,
                                  int number_of_values_per_proc,
                                  int root_process )
{
  if( root_process != s_rank )
  {
    FRENSIE_LOG_TAGGED_WARNING( "Serial Comm",
                                "The only process available for the "
                                "scatter operation is " << s_rank << "!"
                                " The requested root process "
                                << root_process <<
                                " will be ignored!" );
  }
  
  if( number_of_values_per_proc > 0 )
  {
    Details::SerialCommunicatorArrayCopyHelper<T>::copyFromInputArrayToOutputArray( input_values, number_of_values_per_proc, output_values );
  }
}

// The scatterv implementation
template<typename T>
void SerialCommunicator::scattervImpl(
                                  const T* input_values,
                                  int requested_number_of_input_values_to_send,
                                  int input_values_offset,
                                  T* output_values,
                                  int output_values_size )
{
  int number_to_send = requested_number_of_input_values_to_send;
    
  if( requested_number_of_input_values_to_send > output_values_size )
  {
    FRENSIE_LOG_TAGGED_WARNING( "Serial Comm",
                                requested_number_of_input_values_to_send <<
                                " have been requested but the output array "
                                "only has a size of " << output_values_size <<
                                "! Only " << output_values_size <<
                                " values will be sent." );
    
    number_to_send = output_values_size;
  }

  Details::SerialCommunicatorArrayCopyHelper<T>::copyFromInputArrayToOutputArray( input_values+input_values_offset, number_to_send, output_values );
}
  
// Scatter the values stored at the root process to all other processes
/*! \details The values in the input array will simply be copied to the
 * output array
 */
template<typename T>
void SerialCommunicator::scatterv( const T* input_values,
                                   const std::vector<int>& sizes,
                                   const std::vector<int>& offsets,
                                   T* output_values,
                                   int number_of_output_values,
                                   int root_process )
{
  if( root_process != s_rank )
  {
    FRENSIE_LOG_TAGGED_WARNING( "Serial Comm",
                                "The only process available for the "
                                "scatterv operation is " << s_rank <<
                                "! The requested root process "
                                << root_process <<
                                " will be ignored!" );
  }
  
  if( !sizes.empty() )
  {
    int offset = 0;
    
    if( !offsets.empty() )
      offset = offsets.front();
    
    SerialCommunicator::scattervImpl( input_values,
                                      sizes.front(),
                                      offset,
                                      output_values,
                                      number_of_output_values );
  }
}

// Scatter the values stored at the root process to all other processes
/*! \details The values in the input array will simply be copied to the
 * output array
 */
template<typename T>
void SerialCommunicator::scatterv( const T* input_values,
                                   const std::vector<int>& sizes,
                                   T* output_values,
                                   int number_of_output_values,
                                   int root_process )
{
  if( root_process != s_rank )
  {
    FRENSIE_LOG_TAGGED_WARNING( "Serial Comm",
                                "The only process available for the "
                                "scatterv operation is " << s_rank <<
                                "! The requested root process "
                                << root_process <<
                                " will be ignored!" );
  }
  
  if( !sizes.empty() )
  {
    SerialCommunicator::scattervImpl( input_values,
                                      sizes.front(),
                                      0,
                                      output_values,
                                      number_of_output_values );
  }
}

// Combine the values stored by each process intoa single value at the root
/*! \details The values in the input array will simply be copied to the
 * output array
 */
template<typename T, typename ReduceOperation>
void SerialCommunicator::reduce( const T* input_values,
                                 int number_of_input_values,
                                 T* output_values,
                                 ReduceOperation op,
                                 int root_process )
{
  if( root_process != s_rank )
  {
    FRENSIE_LOG_TAGGED_WARNING( "Serial Comm",
                                "The only process available for the "
                                "reduce operation is " << s_rank << "! "
                                "The requested root process "
                                << root_process <<
                                " will be ignored!" );
  }

  Details::SerialCommunicatorArrayCopyHelper<T>::copyFromInputArrayToOutputArray( input_values, number_of_input_values, output_values );
}

// Compute a prefix reduction of values from all processes
/*! \details The values in the input array will simply be copied to the
 * output array
 */ 
template<typename T, typename ReduceOperation>
void SerialCommunicator::scan( const T* input_values,
                               int number_of_input_values,
                               T* output_values,
                               ReduceOperation )
{
  Details::SerialCommunicatorArrayCopyHelper<T>::copyFromInputArrayToOutputArray( input_values, number_of_input_values, output_values );
}

} // end Utility namespace

#endif // end UTILITY_SERIAL_COMMUNICATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_SerialCommunicator_def.hpp
//---------------------------------------------------------------------------//
