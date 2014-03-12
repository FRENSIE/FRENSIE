//---------------------------------------------------------------------------//
//!
//! \file   EnergySpaceResponseFunction.hpp
//! \author Alex Robinson
//! \brief  Energy space dependent (only) response function declaration
//!
//---------------------------------------------------------------------------//

#ifndef ENERGY_SPACE_RESPONSE_FUNCTION_HPP
#define ENERGY_SPACE_RESPONSE_FUNCTION_HPP

// FACEMC Includes
#include "ResponseFunction.hpp"
#include "OneDDistribution.hpp"

namespace FACEMC{

//! The energy space response function
class EnergySpaceResponseFunction : public ResponseFunction
{

public:
  
  //! Constructor
  EnergySpaceResponseFunction( 
		    const std::string& name,
		    const Teuchos::RCP<OneDDistribution> energy_distribution );

  //! Destructor
  ~EnergySpaceResponseFunction()
  { /* ... */ }

  //! Evaluate the response function at the desired energy
  double evaluate( const BasicParticleState& particle ) const;

  //! Check if the response function is spatially uniform
  bool isSpatiallyUniform() const;

private:

  // The energy distribution
  Teuchos::RCP<OneDDistribution> d_energy_distribution;
}

} // end FACEMC namespace

#endif // end ENERGY_SPACE_RESPONSE_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end EnergySpaceResponseFunction.hpp
//---------------------------------------------------------------------------//
