//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The electron bremsstrahlung scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_BREMSSTRAHLUNG_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_BREMSSTRAHLUNG_ELECTRON_SCATTERING_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_ElectronScatteringDistribution.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_InterpolatedFullyTabularTwoDDistribution.hpp"

namespace MonteCarlo{

//! The scattering distribution base class
class BremsstrahlungElectronScatteringDistribution : public ElectronScatteringDistribution
{

public:

  //! Typedef for the two d distributions
  typedef Utility::FullyTabularTwoDDistribution TwoDDist;

  //! Constructor with simple dipole photon angular distribution
  BremsstrahlungElectronScatteringDistribution(
    const std::shared_ptr<TwoDDist>& bremsstrahlung_scattering_distribution,
    const bool use_weighted_sampling = true );

  //! Constructor with detailed 2BS photon angular distribution
  BremsstrahlungElectronScatteringDistribution(
    const std::shared_ptr<TwoDDist>& bremsstrahlung_scattering_distribution,
    const int atomic_number,
    const bool use_weighted_sampling );

  //! Destructor
  virtual ~BremsstrahlungElectronScatteringDistribution()
  { /* ... */ }

  //! Return the min incoming energy
  double getMinEnergy() const;

  //! Return the Max incoming energy
  double getMaxEnergy() const;

  //! Return if weighted sampling is on
  bool isWeightedSamplingOn() const;

  //! Evaluate the distribution for a given incoming and photon energy
  double evaluate( const double incoming_energy,
                   const double photon_energy ) const;

  //! Evaluate the PDF value for a given incoming and photon energy
  double evaluatePDF( const double incoming_energy,
                      const double photon_energy ) const;

  //! Evaluate the CDF
  double evaluateCDF( const double incoming_energy,
                      const double scattering_angle ) const;

  //! Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
               double& photon_energy,
               double& photon_angle_cosine ) const;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
                              double& photon_energy,
                              double& photon_angle_cosine,
                              unsigned& trials ) const;

  //! Randomly scatter the electron
  void scatterElectron( MonteCarlo::ElectronState& electron,
                        MonteCarlo::ParticleBank& bank,
                        Data::SubshellType& shell_of_interaction ) const;

private:

  //! Sample a secondary energy from the distribution
  double sampleWeighted( const double incoming_energy ) const;

  //! Sample a secondary energy from the distribution
  double sampleExact( const double incoming_energy ) const;

  // Sample the outgoing photon angle from a dipole distribution
  double SampleDipoleAngle(  const double incoming_electron_energy,
                             const double photon_energy ) const ;

  // Sample the outgoing photon angle using the 2BS sampling routine of Kock and Motz
  double Sample2BSAngle(  const double incoming_electron_energy,
                          const double photon_energy ) const ;

  // Calculate the rejection function for the 2BS sampling routine
  double Calculate2BSRejection( const double outgoing_electron_energy,
                                const double two_ratio,
                                const double parameter1,
                                const double x ) const;

  // atomic number (Z)
  double d_atomic_number;

  // bremsstrahlung scattering distribution
  std::shared_ptr<TwoDDist> d_bremsstrahlung_scattering_distribution;

  // upper cutoff energy for the condensed-history method
  double d_upper_cutoff_energy;

  // lower cutoff energy for the condensed-history method
  double d_lower_cutoff_energy;

  // Bool to use a weighted interpolation routine to sample the distribution
  bool d_use_weighted_sampling;

  // The outgoing angle function pointer
  std::function<double ( const double, const double )>
                                        d_angular_distribution_func;

  // The sample function pointer
  std::function<double ( const double )> d_sample_func;

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_BREMSSTRAHLUNG_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
