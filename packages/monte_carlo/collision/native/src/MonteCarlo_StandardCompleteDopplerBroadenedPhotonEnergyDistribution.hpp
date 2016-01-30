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
#include "MonteCarlo_SubshellType.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverter.hpp"
#include "MonteCarlo_ComptonProfilePolicy.hpp"
#include "Utility_TabularOneDDistribution.hpp"

namespace MonteCarlo{

//! The standard complete (all subshells) Doppler broadened photon energy dist.
template<typename ComptonProfilePolicy>
class StandardCompleteDopplerBroadenedPhotonEnergyDistribution : public CompleteDopplerBroadenedPhotonEnergyDistribution
{

public:

  //! Constructor
  StandardCompleteDopplerBroadenedPhotonEnergyDistribution(
               const Teuchos::Array<double>& endf_subshell_occupancies,
               const Teuchos::Array<SubshellType>& endf_subshell_order,
               const std::shared_ptr<const ComptonProfileSubshellConverter>&
               subshell_converter,
               const ElectronMomentumDistArray& electron_momentum_dist_array );

  //! Destructor
  virtual ~StandardCompleteDopplerBroadenedPhotonEnergyDistribution()
  { /* .. */ }

  //! Check if the subshell is valid
  bool isValidSubshell( const SubshellType subshell ) const;

  //! Return the occupancy of a subshell (default is the ENDF occupacy)
  virtual double getSubshellOccupancy( const SubshellType subshell ) const;

  //! Evaluate the distribution
  virtual double evaluate( const double incoming_energy,
                           const double outgoing_energy,
                           const double scattering_angle_cosine ) const;

  //! Evaluate the subshell distribution
  double evaluateSubshell( const double incoming_energy,
                           const double outgoing_energy,
                           const double scattering_angle_cosine,
                           const SubshellType subshell ) const;

  //! Evaluate the PDF
  double evaluatePDF( const double incoming_energy,
		      const double outgoing_energy,
		      const double scattering_angle_cosine ) const;

  //! Evaluate the PDF
  double evaluateSubshellPDF( const double incoming_energy,
                              const double outgoing_energy,
                              const double scattering_angle_cosine,
                              const SubshellType subshell ) const;

  //! Evaluate the integrated cross section (b/mu)
  virtual double evaluateIntegratedCrossSection( 
                                          const double incoming_energy,
                                          const double scattering_angle_cosine,
                                          const double precision ) const;

  //! Evaluate the integrated cross section (b/mu)
  double evaluateSubshellIntegratedCrossSection( 
				          const double incoming_energy,
					  const double scattering_angle_cosine,
					  const SubshellType subshell,
					  const double precision ) const;

  //! Sample an outgoing energy from the distribution
  void sample( const double incoming_energy,
	       const double scattering_angle_cosine,
	       double& outgoing_energy,
	       SubshellType& shell_of_interaction ) const;

  //! Sample an outgoing energy and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
			      const double scattering_angle_cosine,
			      double& outgoing_energy,
			      SubshellType& shell_of_interaction,
			      unsigned& trials ) const;

  //! Sample an electron momentum from the distribution
  void sampleMomentumAndRecordTrials( 
                                    const double incoming_energy,
                                    const double scattering_angle_cosine,
                                    double& electron_momentum,
                                    SubshellType& shell_of_interaction,
                                    unsigned& trials ) const;

  //! Sample an electron momentum from the subshell distribution
  double sampleSubshellMomentum( const double incoming_energy,
                                 const double scattering_angle_cosine,
                                 const SubshellType subshell ) const;

protected:

  //! Return the old subshell index corresponding to the subshell
  unsigned getOldSubshellIndex( const SubshellType subshell ) const;

  //! Return the endf subshell index corresponding to the subshell
  unsigned getENDFSubshellIndex( const SubshellType subshell ) const;

  //! Return the subshell corresponding to the endf subshell index
  SubshellType getSubshell( const unsigned endf_subshell_index ) const;

  //! Return the Compton profile for a subshell
  const ComptonProfile& getComptonProfile( const SubshellType& subshell) const;
  
  //! Return the Compton profile for an old subshell index 
  const ComptonProfile& getComptonProfile( 
                                    const unsigned& old_subshell_index ) const;

  //! Sample an ENDF subshell
  SubshellType sampleENDFInteractionSubshell() const;

  //! Sample an interaction subshell
  virtual void sampleInteractionSubshell( unsigned& old_subshell_index,
                                          double& subshell_binding_energy,
                                          SubshellType& subshell ) const = 0;

private:

  // Sample an electron momentum from the subshell distribution
  double sampleSubshellMomentum( const double incoming_energy,
                                 const double scattering_angle_cosine,
                                 const double subshell_binding_energy,
                                 const ComptonProfile& compton_profile ) const;

  // The ENDF subshell interaction probabilities
  boost::scoped_ptr<const Utility::TabularOneDDistribution>
  d_endf_subshell_occupancy_distribution;

  // The ENDF subshell order
  typedef boost::bimap<unsigned,SubshellType> SubshellOrderMapType;
  boost::bimap<unsigned,SubshellType> d_endf_subshell_order;

  // The ENDF subshell occupancies
  Teuchos::Array<double> d_endf_subshell_occupancies;

  // The Compton profile subshell converter
  std::shared_ptr<const ComptonProfileSubshellConverter> d_subshell_converter;

  // The electron momentum dist array
  ElectronMomentumDistArray d_electron_momentum_distribution;
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
