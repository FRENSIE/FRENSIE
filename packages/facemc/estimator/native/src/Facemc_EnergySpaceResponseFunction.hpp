//---------------------------------------------------------------------------//
//!
//! \file   Facemc_EnergySpaceResponseFunction.hpp
//! \author Alex Robinson
//! \brief  Energy space dependent (only) response function declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_ENERGY_SPACE_RESPONSE_FUNCTION_HPP
#define FACEMC_ENERGY_SPACE_RESPONSE_FUNCTION_HPP

// FRENSIE Includes
#include "Facemc_ResponseFunction.hpp"
#include "Utility_OneDDistribution.hpp"

namespace Facemc{

//! The energy space response function
class EnergySpaceResponseFunction : public ResponseFunction
{

public:
  
  //! Constructor
  EnergySpaceResponseFunction( 
	   const std::string& name,
	   const Teuchos::RCP<Utility::OneDDistribution> energy_distribution );

  //! Destructor
  ~EnergySpaceResponseFunction()
  { /* ... */ }

  //! Evaluate the response function at the desired energy
  double evaluate( const ParticleState& particle ) const;

  //! Check if the response function is spatially uniform
  bool isSpatiallyUniform() const;

private:

  // The energy distribution
  Teuchos::RCP<Utility::OneDDistribution> d_energy_distribution;
};

} // end Facemc namespace

#endif // end FACEMC_ENERGY_SPACE_RESPONSE_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end Facemc_EnergySpaceResponseFunction.hpp
//---------------------------------------------------------------------------//
