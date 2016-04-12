//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The screened Rutherford elastic electronscattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SCREENED_RUTHERFORD_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_SCREENED_RUTHERFORD_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_TabularOneDDistribution.hpp"
#include "MonteCarlo_ElectronScatteringDistribution.hpp"
#include "MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp"

namespace MonteCarlo{

//! The scattering distribution base class
class ScreenedRutherfordElasticElectronScatteringDistribution : public ElectronScatteringDistribution
{

public:

  //! Typedef for the array of energy dependent screened rutherford paramters
  //! (first = energy, second = Moliere screening constant, 
  //!  third = normalization constant
  typedef Teuchos::Array<Utility::Trip<double,double,double> > ParameterArray;

  typedef Teuchos::RCP<const CutoffElasticElectronScatteringDistribution>
            ElasticDistribution;    

  //! Constructor from ACE table data
  ScreenedRutherfordElasticElectronScatteringDistribution(
    const ElasticDistribution& elastic_cutoff_distribution,
    const int atomic_number,
    const double lower_cutoff_angle_cosine = 0.999999 );

  //! Constructor from ENDL table data
  ScreenedRutherfordElasticElectronScatteringDistribution(
    const ParameterArray& screened_rutherford_parameters,
    const double lower_cutoff_angle_cosine = 0.999999 );

  //! Destructor 
  virtual ~ScreenedRutherfordElasticElectronScatteringDistribution()
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
                        
protected:

   //! Sample an outgoing direction from the distribution
  void sampleAndRecordTrialsImpl( const double incoming_energy,
                                  double& scattering_angle_cosine,
                                  unsigned& trials ) const;

  //! Evaluate Moliere's atomic screening constant at the given electron energy
  double evaluateMoliereScreeningConstant( const double energy ) const;

private:

  //! Evaluate the integrated PDF
  double evaluateIntegratedPDF( const double incoming_energy) const;

  // evaluate the pdf integrated from 0 to angle
  double evaluateIntegratedPDF( 
        const double& scattering_angle, 
        const ParameterArray::const_iterator& lower_bin_boundary, 
        const ParameterArray::const_iterator& upper_bin_boundary,
        const double& interpolation_fraction ) const;

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

  // The scattering angle below which the screened Rutherford distribution is used
  double d_upper_cutoff_delta_mu;

  // The scattering angle cosine above which the screened Rutherford distribution is used
  double d_lower_cutoff_angle_cosine;

  // Flag to indicate that tabulated screened rutherford parameters are used
  bool d_using_endl_tables;

  // Cutoff elastic scattering distribution
  ElasticDistribution d_elastic_cutoff_distribution;

  // Screened Rutherford energy depended paramters: Moliere's screening constant and normalization constant
  ParameterArray d_screened_rutherford_parameters;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SCREENED_RUTHERFORD_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
