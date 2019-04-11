//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SubshellIncoherentAdjointPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The subshell adjoint incoherent photon scattering dist. decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SUBSHELL_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_SUBSHELL_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_AdjointPhotonKinematicsHelpers.hpp"
#include "MonteCarlo_OccupationNumber.hpp"

namespace MonteCarlo{

//! The subshell incoherent adjoint photon scattering distribution class
class SubshellIncoherentAdjointPhotonScatteringDistribution : public IncoherentAdjointPhotonScatteringDistribution
{

public:

  //! This type
  typedef SubshellIncoherentAdjointPhotonScatteringDistribution ThisType;

  //! The trials counter type
  typedef IncoherentAdjointPhotonScatteringDistribution::Counter Counter;

  //! Constructor
  SubshellIncoherentAdjointPhotonScatteringDistribution(
      const double max_energy,
      const Data::SubshellType interaction_subshell,
      const double num_electrons_in_subshell,
      const double binding_energy,
      const std::shared_ptr<const OccupationNumber>& occupation_number,
      const AdjointKleinNishinaSamplingType sampling_type =
      TWO_BRANCH_REJECTION_ADJOINT_KN_SAMPLING );

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
                   const double scattering_angle_cosine ) const override;

  //! Evaluate the distribution (pull in hidden base class overloads)
  using IncoherentAdjointPhotonScatteringDistribution::evaluate;

  //! Sample an outgoing energy and direction from the distribution
  virtual void sample( const double incoming_energy,
                       double& outgoing_energy,
                       double& scattering_angle_cosine ) const override;

  //! Sample an outgoing energy and direction and record the number of trials
  virtual void sampleAndRecordTrials( const double incoming_energy,
                                      double& outgoing_energy,
                                      double& scattering_angle_cosine,
                                      Counter& trials ) const override;

  //! Randomly scatter the photon and return the shell that was interacted with
  virtual void scatterAdjointPhoton(
                              AdjointPhotonState& adjoint_photon,
                              ParticleBank& bank,
                              Data::SubshellType& shell_of_interaction ) const override;

protected:

  //! Evaluate the integrated cross section (b)
  double evaluateIntegratedCrossSectionImpl( const double incoming_energy,
                                             const double max_energy,
                                             const double precision ) const override;

  //! Check if an energy is above the scattering window
  bool isEnergyAboveScatteringWindow( const double energy_of_interest,
                                      const double initial_energy ) const override;

  //! Evaluate the occupation number
  double evaluateOccupationNumber( const double pz ) const;

  //! Check if the cross section is non-zero
  virtual bool isCrossSectionNonZero( const double incoming_energy,
                                      const double max_energy,
                                      const double scattering_angle_cosine ) const;

  //! Evaluate the adjoint occupation number
  virtual double evaluateAdjointOccupationNumber(
                                  const double incoming_energy,
                                  const double max_energy,
                                  const double scattering_angle_cosine ) const;

  //! Evaluate the max adjoint occupation number
  virtual double evaluateMaxAdjointOccupationNumber(
                                               const double incoming_energy,
                                               const double max_energy ) const;
  
private:

  // The interaction subshell
  Data::SubshellType d_subshell;

  // The number of electrons in the subshell
  double d_num_electrons_in_subshell;

  // The subshell binding energy
  double d_binding_energy;

  // The occupation number
  std::shared_ptr<const OccupationNumber> d_occupation_number;
};

// Evaluate the occupation number
inline double SubshellIncoherentAdjointPhotonScatteringDistribution::evaluateOccupationNumber( const double pz ) const
{
  OccupationNumber::MomentumQuantity momentum = pz*Utility::Units::mec_momentum;
  
  return d_occupation_number->evaluate( momentum );
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SUBSHELL_INCOHERENT_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SubshellIncoherentAdjointPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
