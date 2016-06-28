//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AnalogElasticElectronScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The analog elastic electron scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ANALOG_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_ANALOG_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_TabularOneDDistribution.hpp"
#include "MonteCarlo_ElectronScatteringDistribution.hpp"
#include "MonteCarlo_AdjointElectronScatteringDistribution.hpp"
#include "Utility_InterpolationPolicy.hpp"

namespace MonteCarlo{

//! The scattering distribution base class
class AnalogElasticElectronScatteringDistribution : public ElectronScatteringDistribution,
    public AdjointElectronScatteringDistribution
{

public:

  //! Typedef for the elastic cutoff distribution
  typedef std::vector<Utility::Pair< double, Teuchos::RCP<const Utility::TabularOneDDistribution> > >
    CutoffDistribution;

  //! Constructor
  AnalogElasticElectronScatteringDistribution(
    const CutoffDistribution& elastic_cutoff_distribution,
    const int atomic_number );

  //! Destructor
  virtual ~AnalogElasticElectronScatteringDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
                   const double scattering_angle_cosine ) const;

  //! Evaluate the PDF
  double evaluatePDF( const double incoming_energy,
                      const double scattering_angle_cosine ) const;

  //! Evaluate the CDF
  double evaluateCDF( const double incoming_energy,
                      const double scattering_angle_cosine ) const;

  //! Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
               double& outgoing_energy,
               double& scattering_angle_cosine ) const;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
                              double& outgoing_energy,
                              double& scattering_angle_cosine,
                              unsigned& trials ) const;

  //! Randomly scatter the electron
  void scatterElectron( ElectronState& electron,
                        ParticleBank& bank,
                        Data::SubshellType& shell_of_interaction ) const;

  //! Randomly scatter the adjoint electron
  void scatterAdjointElectron( AdjointElectronState& adjoint_electron,
                               ParticleBank& bank,
                               Data::SubshellType& shell_of_interaction ) const;

  //! Evaluate Moliere's atomic screening constant at the given electron energy
  double evaluateMoliereScreeningConstant( const double energy ) const;

  //! Evaluate the distribution
  double evaluateScreenedRutherford(
            const double incoming_energy,
            const double scattering_angle_cosine,
            const double eta ) const;

  //! Evaluate the PDF
  double evaluateScreenedRutherfordPDF(
            const double incoming_energy,
            const double scattering_angle_cosine,
            const double eta ) const;

  //! Evaluate the CDF
  double evaluateScreenedRutherfordCDF(
            const double incoming_energy,
            const double scattering_angle_cosine,
            const double eta ) const;

protected:

   //! Sample an outgoing direction from the distribution
  void sampleIndependent(
            const CutoffDistribution::const_iterator& distribution_bin,
            double& scattering_angle_cosine ) const;

   //! Sample an outgoing direction from the distribution
  void sampleAndRecordTrialsImpl( const double incoming_energy,
                                  double& scattering_angle_cosine,
                                  unsigned& trials ) const;

private:

  // The change scattering angle cosine below which the screened Rutherford distribution is used
  static double s_cutoff_delta_mu;

  // The scattering angle cosine above which the screened Rutherford distribution is used
  static double s_cutoff_mu;

  // The fine structure constant (fsc) squared
  static double s_fine_structure_const_squared;

  // A parameter for moliere's screening factor  (1/2*(fsc/0.885)**2)
  static double s_screening_param1;

  // Atomic number (Z) of the target atom
  int d_atomic_number;

  // Atomic number (Z) of the target atom to the 2/3 power (Z^2/3)
  double d_Z_two_thirds_power;

  // A parameter for moliere's screening factor (3.76*fsc**2*Z**2)
  double d_screening_param2;

  // Cutoff elastic scattering distribution
  CutoffDistribution d_elastic_cutoff_distribution;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ANALOG_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AnalogElasticElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
