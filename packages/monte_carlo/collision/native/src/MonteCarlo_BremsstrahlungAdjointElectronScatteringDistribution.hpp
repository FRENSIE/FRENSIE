//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungAdjointElectronScatteringDistribuiton.hpp
//! \author Luke Kersting
//! \brief  The bremsstrahlung adjoint electron scattering distribution declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_BREMSSTRAHLUNG_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_BREMSSTRAHLUNG_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_AdjointElectronScatteringDistribution.hpp"
#include "Utility_InterpolatedFullyTabularTwoDDistribution.hpp"

namespace MonteCarlo{

//! The bremsstrahlung adjoint electron scattering distribution class
class BremsstrahlungAdjointElectronScatteringDistribution : public AdjointElectronScatteringDistribution
{

public:

  //! Typedef for the adjoint bremsstrahlung distribution
  typedef Utility::FullyTabularTwoDDistribution TwoDDist;

  //! Constructor
  BremsstrahlungAdjointElectronScatteringDistribution(
    const std::shared_ptr<TwoDDist>& adjoint_brem_scatter_dist );

  //! Destructor
  virtual ~BremsstrahlungAdjointElectronScatteringDistribution()
  { /* ... */ }

  //! Set the evaluation routines
  void setEvaluationRoutines( const bool unit_based_interpolation_mode_on );

  //! Return the min incoming energy
  double getMinEnergy() const;

  //! Return the Max incoming energy
  double getMaxEnergy() const;

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
                   const double outgoing_energy ) const;

  //! Evaluate the PDF
  double evaluatePDF( const double incoming_energy,
                      const double outgoing_energy ) const;

  //! Evaluate the PDF
  double evaluateCDF( const double incoming_energy,
                      const double outgoing_energy ) const;

  //! Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
               double& outgoing_energy,
               double& scattering_angle_cosine ) const;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
                              double& outgoing_energy,
                              double& scattering_angle_cosine,
                              unsigned& trials ) const;

  //! Randomly scatter the adjoint electron
  void scatterAdjointElectron( AdjointElectronState& electron,
                               ParticleBank& bank,
                               Data::SubshellType& shell_of_interaction ) const;

private:

  // bremsstrahlung scattering distribution
  std::shared_ptr<TwoDDist> d_adjoint_brem_scatter_dist;

  // The evaluate function pointer
  std::function<double ( const double, const double )> d_evaluate_function;

  // The evaluatePDF function pointer
  std::function<double ( const double, const double )> d_evaluate_pdf_function;

  // The evaluateCDF function pointer
  std::function<double ( const double, const double )> d_evaluate_cdf_function;

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_BREMSSTRAHLUNG_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungAdjointElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
