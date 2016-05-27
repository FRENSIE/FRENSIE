//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardCompleteDopplerBroadenedPhotonEnergyDistribution.hpp
//! \author Alex Robinson
//! \brief  The standard complete Doppler broadened photon energy dist. decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP
#define MONTE_CARLO_STANDARD_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/scoped_ptr.hpp>
#include <boost/bimap.hpp>

// FRENSIE Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_CompleteDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "Data_SubshellType.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverter.hpp"
#include "MonteCarlo_ComptonProfilePolicy.hpp"
#include "Utility_TabularOneDDistribution.hpp"

namespace MonteCarlo{

//! The standard complete (all subshells) Doppler broadened photon energy dist.
template<typename ComptonProfilePolicy>
class StandardCompleteDopplerBroadenedPhotonEnergyDistribution : public CompleteDopplerBroadenedPhotonEnergyDistribution
{

public:

  //! The energy unit
  typedef CompleteDopplerBroadenedPhotonEnergyDistribution::EnergyUnit EnergyUnit;

  //! The momentum unit
  typedef CompleteDopplerBroadenedPhotonEnergyDistribution::MomentumUnit MomentumUnit;

  //! The area unit
  typedef CompleteDopplerBroadenedPhotonEnergyDistribution::BarnUnit AreaUnit;

  //! The area per energy unit
  typedef CompleteDopplerBroadenedPhotonEnergyDistribution::AreaPerEnergyUnit AreaPerEnergyUnit;

  //! The area per momentum unit
  typedef CompleteDopplerBroadenedPhotonEnergyDistribution::AreaPerMomentumUnit AreaPerMomentumUnit;

  //! The energy quantity type
  typedef CompleteDopplerBroadenedPhotonEnergyDistribution::EnergyQuantity EnergyQuantity;

  //! The inverse energy quantity type
  typedef CompleteDopplerBroadenedPhotonEnergyDistribution::InverseEnergyQuantity InverseEnergyQuantity;

  //! The momentum quantity type
  typedef CompleteDopplerBroadenedPhotonEnergyDistribution::MomentumQuantity MomentumQuantity;

  //! The inverse momentum quantity type
  typedef CompleteDopplerBroadenedPhotonEnergyDistribution::InverseMomentumQuantity InverseMomentumQuantity;

  //! The area quantity type
  typedef CompleteDopplerBroadenedPhotonEnergyDistribution::AreaQuantity AreaQuantity;

  //! The area per energy quantity type
  typedef CompleteDopplerBroadenedPhotonEnergyDistribution::AreaPerEnergyQuantity AreaPerEnergyQuantity;

  //! The area per momentum quantity type
  typedef CompleteDopplerBroadenedPhotonEnergyDistribution::AreaPerMomentumQuantity AreaPerMomentumQuantity;

  //! Constructor
  StandardCompleteDopplerBroadenedPhotonEnergyDistribution(
               const Teuchos::Array<double>& endf_subshell_occupancies,
               const Teuchos::Array<Data::SubshellType>& endf_subshell_order,
               const std::shared_ptr<const ComptonProfileSubshellConverter>&
               subshell_converter,
               const ComptonProfileArray& compton_profile_array );

  //! Destructor
  virtual ~StandardCompleteDopplerBroadenedPhotonEnergyDistribution()
  { /* .. */ }

  //! Check if the subshell is valid
  bool isValidSubshell( const Data::SubshellType subshell ) const;

  //! Return the occupancy of a subshell (default is the ENDF occupacy)
  virtual double getSubshellOccupancy( const Data::SubshellType subshell ) const;

  //! Evaluate the distribution with electron momentum projection
  virtual AreaPerMomentumQuantity evaluateWithElectronMomentumProjection(
                              const EnergyQuantity incoming_energy,
                              const MomentumQuantity electron_momentum_projection,
                              const double scattering_angle_cosine ) const;
  
  //! Evaluate the exact distribution
  virtual AreaPerEnergyQuantity evaluateExact(
                                  const EnergyQuantity incoming_energy,
                                  const EnergyQuantity outgoing_energy,
                                  const double scattering_angle_cosine ) const;

  //! Evaluate the subshell with the electron momentum projection
  AreaPerMomentumQuantity evaluateSubshellWithElectronMomentumProjection(
                           const EnergyQuantity incoming_energy,
                           const MomentumQuantity electron_momentum_projection,
                           const double scattering_angle_cosine,
                           const Data::SubshellType subshell ) const;
  
  //! Evaluate the exact subshell distribution
  AreaPerEnergyQuantity evaluateSubshellExact(
                                     const EnergyQuantity incoming_energy,
                                     const EnergyQuantity outgoing_energy,
                                     const double scattering_angle_cosine,
                                     const Data::SubshellType subshell ) const;

  //! Evaluate the PDF with electron momentum projection
  InverseMomentumQuantity evaluatePDFWithElectronMomentumProjection(
                           const EnergyQuantity incoming_energy,
                           const MomentumQuantity electron_momentum_projection,
                           const double scattering_angle_cosine,
                           const double precision ) const;
  
  //! Evaluate the exact PDF
  InverseEnergyQuantity evaluatePDFExact( const EnergyQuantity incoming_energy,
                                          const EnergyQuantity outgoing_energy,
                                          const double scattering_angle_cosine,
                                          const double precision ) const;

  //! Evaluate the subshell PDF with electron momentum projection
  InverseMomentumQuantity evaluateSubshellPDFWithElectronMomentumProjection(
                           const EnergyQuantity incoming_energy,
                           const MomentumQuantity electron_momentum_projection,
                           const double scattering_angle_cosine,
                           const Data::SubshellType subshell,
                           const double precision ) const;
  
  //! Evaluate the exact subshell PDF
  InverseEnergyQuantity evaluateSubshellPDFExact(
                                          const EnergyQuantity incoming_energy,
                                          const EnergyQuantity outgoing_energy,
                                          const double scattering_angle_cosine,
                                          const Data::SubshellType subshell,
                                          const double precision ) const;

  //! Evaluate the integrated cross section (b/mu)
  virtual AreaQuantity evaluateIntegratedCrossSection( 
                                          const EnergyQuantity incoming_energy,
                                          const double scattering_angle_cosine,
                                          const double precision ) const;

  //! Evaluate the exact integrated cross section (b/mu)
  virtual AreaQuantity evaluateIntegratedCrossSectionExact(
                                          const EnergyQuantity incoming_energy,
                                          const double scattering_angle_cosine,
                                          const double precision ) const;

  //! Evaluate the subshell integrated cross section (b/mu)
  AreaQuantity evaluateSubshellIntegratedCrossSection( 
				          const EnergyQuantity incoming_energy,
					  const double scattering_angle_cosine,
					  const Data::SubshellType subshell,
					  const double precision ) const;

  //! Evaluate the exact subshell integrated cross section (b/mu)
  AreaQuantity evaluateSubshellIntegratedCrossSectionExact(
                                          const EnergyQuantity incoming_energy,
					  const double scattering_angle_cosine,
					  const Data::SubshellType subshell,
					  const double precision ) const;

  //! Sample an outgoing energy from the distribution
  void sample( const EnergyQuantity incoming_energy,
	       const double scattering_angle_cosine,
	       EnergyQuantity& outgoing_energy,
	       Data::SubshellType& shell_of_interaction ) const;

  //! Sample an outgoing energy and record the number of trials
  void sampleAndRecordTrials( const EnergyQuantity incoming_energy,
			      const double scattering_angle_cosine,
			      EnergyQuantity& outgoing_energy,
			      Data::SubshellType& shell_of_interaction,
			      unsigned& trials ) const;

  //! Sample an electron momentum from the distribution
  void sampleMomentumAndRecordTrials( 
                                    const EnergyQuantity incoming_energy,
                                    const double scattering_angle_cosine,
                                    MomentumQuantity& electron_momentum,
                                    Data::SubshellType& shell_of_interaction,
                                    unsigned& trials ) const;

  //! Sample an electron momentum from the subshell distribution
  MomentumQuantity sampleSubshellMomentum(
                                     const EnergyQuantity incoming_energy,
                                     const double scattering_angle_cosine,
                                     const Data::SubshellType subshell ) const;

protected:

  //! Return the old subshell index corresponding to the subshell
  unsigned getOldSubshellIndex( const Data::SubshellType subshell ) const;

  //! Return the endf subshell index corresponding to the subshell
  unsigned getENDFSubshellIndex( const Data::SubshellType subshell ) const;

  //! Return the subshell corresponding to the endf subshell index
  Data::SubshellType getSubshell( const unsigned endf_subshell_index ) const;

  //! Return the Compton profile for a subshell
  const ComptonProfile& getComptonProfile(
                                     const Data::SubshellType& subshell) const;
  
  //! Return the Compton profile for an old subshell index 
  const ComptonProfile& getComptonProfile( 
                                    const unsigned& old_subshell_index ) const;

  //! Sample an ENDF subshell
  Data::SubshellType sampleENDFInteractionSubshell() const;

  //! Sample an interaction subshell
  virtual void sampleInteractionSubshell(
                                      unsigned& old_subshell_index,
                                      EnergyQuantity& subshell_binding_energy,
                                      Data::SubshellType& subshell ) const = 0;

private:

  // Sample an electron momentum from the subshell distribution
  MomentumQuantity sampleSubshellMomentum(
                                 const EnergyQuantity incoming_energy,
                                 const double scattering_angle_cosine,
                                 const EnergyQuantity subshell_binding_energy,
                                 const ComptonProfile& compton_profile ) const;

  // The ENDF subshell interaction probabilities
  boost::scoped_ptr<const Utility::TabularOneDDistribution>
  d_endf_subshell_occupancy_distribution;

  // The ENDF subshell order
  typedef boost::bimap<unsigned,Data::SubshellType> SubshellOrderMapType;
  boost::bimap<unsigned,Data::SubshellType> d_endf_subshell_order;

  // The ENDF subshell occupancies
  Teuchos::Array<double> d_endf_subshell_occupancies;

  // The Compton profile subshell converter
  std::shared_ptr<const ComptonProfileSubshellConverter> d_subshell_converter;

  // The electron momentum dist array
  ComptonProfileArray d_compton_profile_array;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardCompleteDopplerBroadenedPhotonEnergyDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardCompleteDopplerBroadenedPhotonEnergyDistribution.hpp
//---------------------------------------------------------------------------//
