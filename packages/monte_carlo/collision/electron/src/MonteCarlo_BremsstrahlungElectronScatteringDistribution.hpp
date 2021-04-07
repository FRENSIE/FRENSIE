//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The electron bremsstrahlung scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_BREMSSTRAHLUNG_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_BREMSSTRAHLUNG_ELECTRON_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_ElectronScatteringDistribution.hpp"
#include "MonteCarlo_PositronScatteringDistribution.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "Utility_InterpolatedFullyTabularBasicBivariateDistribution.hpp"

namespace MonteCarlo{

//! The scattering distribution base class
class BremsstrahlungElectronScatteringDistribution : public ElectronScatteringDistribution,
                                                     public PositronScatteringDistribution
{

public:

  //! Typedef for this type
  typedef BremsstrahlungElectronScatteringDistribution ThisType;

  //! Typedef for the counter
  typedef ElectronScatteringDistribution::Counter Counter;

  //! Typedef for the two d distributions
  typedef Utility::FullyTabularBasicBivariateDistribution BasicBivariateDist;

  //! Constructor with simple dipole photon angular distribution
  BremsstrahlungElectronScatteringDistribution(
    const std::shared_ptr<const BasicBivariateDist>& bremsstrahlung_scattering_distribution,
    const bool bank_secondary_particles = true );

  //! Constructor with detailed 2BS photon angular distribution
  BremsstrahlungElectronScatteringDistribution(
    const int atomic_number,
    const std::shared_ptr<const BasicBivariateDist>& bremsstrahlung_scattering_distribution,
    const bool bank_secondary_particles = true );

  //! Destructor
  virtual ~BremsstrahlungElectronScatteringDistribution()
  { /* ... */ }

  //! Return the min incoming energy
  double getMinEnergy() const;

  //! Return the Max incoming energy
  double getMaxEnergy() const;

  //! Return the min outgoing photon energy
  double getMinPhotonEnergy( const double incoming_energy ) const;

  //! Return the Max outgoing photon energy
  double getMaxPhotonEnergy( const double incoming_energy ) const;

  //! Evaluate the distribution for a given incoming and photon energy
  double evaluate( const double incoming_energy,
                   const double photon_energy ) const override;

  //! Evaluate the PDF value for a given incoming and photon energy
  double evaluatePDF( const double incoming_energy,
                      const double photon_energy ) const override;

  //! Evaluate the CDF
  double evaluateCDF( const double incoming_energy,
                      const double scattering_angle ) const override;

  //! Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
               double& photon_energy,
               double& photon_angle_cosine ) const override;

  //! Sample an outgoing energy from the distribution with a random number
  double sampleWithRandomNumber( const double incoming_energy,
                                 const double random_number ) const;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
                              double& photon_energy,
                              double& photon_angle_cosine,
                              Counter& trials ) const override;

  //! Randomly scatter the electron
  void scatterElectron( MonteCarlo::ElectronState& electron,
                        MonteCarlo::ParticleBank& bank,
                        Data::SubshellType& shell_of_interaction ) const override;

  //! Randomly scatter the positron
  void scatterPositron( MonteCarlo::PositronState& positron,
                        MonteCarlo::ParticleBank& bank,
                        Data::SubshellType& shell_of_interaction ) const override;

private:

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
  std::shared_ptr<const BasicBivariateDist> d_bremsstrahlung_scattering_distribution;

  // The outgoing angle function pointer
  std::function<double ( const double, const double )>
                                        d_angular_distribution_func;

  // Turn secondary particle on/off
  bool d_bank_secondary_particles;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_BREMSSTRAHLUNG_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
