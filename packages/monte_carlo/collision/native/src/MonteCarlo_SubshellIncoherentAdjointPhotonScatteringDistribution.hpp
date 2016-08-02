//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SubshellIncoherentAdjointPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The subshell adjoint incoherent photon scattering dist. decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SUBSHELL_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_SUBSHELL_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_AdjointPhotonKinematicHelpers.hpp"
#include "MonteCarlo_ComptonProfile.hpp"

namespace MonteCarlo{

//! The subshell incoherent adjoint photon scattering distribution class
class SubshellIncoherentAdjointPhotonScatteringDistribution : public IncoherentAdjointPhotonScatteringDistribution
{

public:

  //! This type
  typedef SubshellIncoherentAdjointPhotonScatteringDistribution ThisType;

  //! Constructor
  SubshellIncoherentAdjointPhotonScatteringDistribution(
      const double max_energy,
      const Data::SubshellType interaction_subshell,
      const double num_electrons_in_subshell,
      const double binding_energy,
      const Teuchos::RCP<const Utility::OneDDistribution>& occupation_number );

  //! Destructor
  virtual ~SubshellIncoherentAdjointPhotonScatteringDistribution()
  { /* ... */ }

  //! Return the subshell
  Data::SubshellType getSubshell() const;

  //! Return the number of electrons in the subshell
  double getSubshellOccupancy() const;

  //! Return the binding energy
  double getSubshellBindingEnergy() const;

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
                   const double max_energy,
                   const double scattering_angle_cosine ) const;

  //! Evaluate the integrated cross section (b)
  double evaluateIntegratedCrossSection( const double incoming_energy,
                                         const double max_energy,
                                         const double precision ) const;

  //! Sample an outgoing energy and direction from the distribution
  virtual void sample( const double incoming_energy,
                       double& outgoing_energy,
                       double& scattering_angle_cosine ) const;

  //! Sample an outgoing energy and direction and record the number of trials
  virtual void sampleAndRecordTrials( const double incoming_energy,
                                      double& outgoing_energy,
                                      double& scattering_angle_cosine,
                                      unsigned& trials ) const;

  //! Randomly scatter the photon and return the shell that was interacted with
  virtual void scatterAdjointPhoton(
                              AdjointPhotonState& adjoint_photon,
                              ParticleBank& bank,
                              Data::SubshellType& shell_of_interaction ) const;

protected:

  //! Check if an energy is above the scattering window
  bool isEnergyAboveScatteringWindow( const double energy_of_interest,
                                      const double initial_energy ) const;

  //! Evaluate the occupation number
  double evaluateOccupationNumber( const double pz ) const;

  //! Calculate the occupation number arguments
  double calculateOccupationNumberArguments(
                                  const double incoming_energy,
                                  const double max_energy,
                                  const double scattering_angle_cosine,
                                  double& pz_min,
                                  double& pz_max ) const;

  //! Evaluate the adjoint occupation number
  double evaluateAdjointOccupationNumber(
                                  const double incoming_energy,
                                  const double max_energy,
                                  const double scattering_angle_cosine ) const;
  
private:

  // Calculate the occupation number upper argument
  double calculateOccupationNumberUpperArgument(
                                  const double incoming_energy,
                                  const double scattering_angle_cosine ) const;

  // The interaction subshell
  Data::SubshellType d_subshell;

  // The number of electrons in the subshell
  double d_num_electrons_in_subshell;

  // The subshell binding energy
  double d_binding_energy;

  // The occupation number
  Teuchos::RCP<const Utility::OneDDistribution> d_occupation_number;
};

// Evaluate the occupation number
inline double SubshellIncoherentAdjointPhotonScatteringDistribution::evaluateOccupationNumber( const double pz ) const
{
  return d_occupation_number->evaluate( pz );
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SUBSHELL_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SubshellIncoherentAdjointPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
