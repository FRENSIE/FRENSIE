//---------------------------------------------------------------------------//
//!
//! \file   Facemc_FissionNeutronMultiplicityDistribution.hpp
//! \author Alex Robinson
//! \brief  The fission neutron multiplicity distribution base class decl
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_FISSION_NEUTRON_MULTIPLICITY_DISTRIBUTION_HPP
#define FACEMC_FISSION_NEUTRON_MULTIPLICITY_DISTRIBUTION_HPP

namespace Facemc{

//! The fission neutron multiplicity distribution base class
class FissionNeutronMultiplicityDistribution
{
  
public:

  //! Constructor
  FissionNeutronMultiplicityDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~FissionNeutronMultiplicityDistribution()
  { /* ... */ }

  //! Return the average number of neutrons emitted 
  virtual double getAverageNumberOfEmittedNeutrons( 
					       const double energy ) const = 0;

  //! Return the average number of prompt neutrons emitted
  virtual double getAverageNumberOfPromptNeutrons( 
					       const double energy ) const = 0;

  //! Return the average number of delayed neutrons emitted
  virtual double getAverageNumberOfDelayedNeutrons( 
					       const double energy ) const = 0;
};

} // end Facemc namespace

#endif // end FACEMC_FISSION_NEUTRON_MULTIPLICITY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Facemc_FissionNeutronMultiplicityDistribution.hpp
//---------------------------------------------------------------------------//
