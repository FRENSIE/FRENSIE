//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_TransportKernel.cpp
//! \author Alex Robinson
//! \brief  Transport kernel class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_TransportKernel.hpp"
#include "MonteCarlo_ContractException.hpp"

namespace MonteCarlo{

// Constructor
TransportKernel::TransportKernel(
                      const std::shared_ptr<const FilledGeometryModel>& model )
  : d_model( model )
{
  // Make sure that the model is valid
  testPrecondition( model.get() );
}

// Sample the optical path length traveled by a particle before a collision
double TransportKernel::sampleOpticalPathLengthToNextCollisionSite() const
{
  return -std::log( Utility::RandomNumberGenerator::getRandomNumber<double>() );
}

// Check if the transport kernel is defined on the model of interest
bool TransportKernel::isDefinedOnModel( const FilledGeometryModel& model ) const
{
  return d_model.get() == &model;
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_TransportKernel.cpp
//---------------------------------------------------------------------------//
