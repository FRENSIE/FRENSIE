//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ElasticElectronMomentsEvaluator.hpp
//! \author Luke Kersting
//! \brief  Elastic electron cross section moments evaluator declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ELASTIC_ELECTRON_MOMENTS_EVALUATOR_HPP
#define DATA_GEN_ELASTIC_ELECTRON_MOMENTS_EVALUATOR_HPP

// Boost Includes
#include <boost/scoped_ptr.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
/*
// Std Lib Includes
#include <limits>

// Boost Includes
#include <boost/distribution.hpp>
#include <boost/bind.hpp>
*/
// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_TabularOneDDistribution.hpp"
#include "MonteCarlo_HardElasticElectronScatteringDistribution.hpp"
#include "Utility_SloanRadauQuadrature.hpp"


namespace DataGen{

//! The elastic electron cross section moments class
class ElasticElectronMomentsEvaluator
{
  
public:

  //! Typedef for the elastic distribution
  typedef Teuchos::Array<Utility::Pair<double,
		       Teuchos::RCP<const Utility::TabularOneDDistribution> > >
  ElasticDistribution;

  //! Constructor
  ElasticElectronMomentsEvaluator(
    const Data::XSSEPRDataExtractor& raw_ace_data,
    const Teuchos::RCP<const MonteCarlo::HardElasticElectronScatteringDistribution>&
                               elastic_distribution,
    const double& cutoff_angle_cosine = 0.9 );

  //! Destructor
  ~ElasticElectronMomentsEvaluator()
  { /* ... */ }

  //! Evaluate the Legnendre Polynomial expansion of the differential hard elastic cross section (dc/dx)
  double evaluateLegendreExpandedPDF( const double scattering_angle_cosine,
                                      const double incoming_energy, 
                                      const int polynomial_order = 0) const;

  //! Evaluate the Legnendre Polynomial expansion of the screened rutherford
  double evaluateLegendreExpandedScreenedRutherford(
            const double scattering_angle_cosine,
            const double incoming_energy, 
            const int polynomial_order = 0 ) const;

  //! Return the moment of the elastic scattering distribution at a given energy and polynomial order
  double evaluateElasticMoment( const double energy, 
                                const int polynomial_order,
                                const double precision ) const;

  //! Evaluate the first n screened Rutherford cross section moments above the cutoff mu
  void evaluateNormalizedScreenedRutherfordMoments( 
            Teuchos::Array<Utility::long_float>& rutherford_moments,
            const double energy,
            const int n ) const;

private:

  // The forward reaction data
  Teuchos::RCP<MonteCarlo::ElectroatomicReaction> d_elastic_reaction;

  // The knock on energy distribution
  Teuchos::RCP<const MonteCarlo::HardElasticElectronScatteringDistribution>
                                         d_elastic_distribution;

  // The raw ace electron data extractor
  Data::XSSEPRDataExtractor d_raw_ace_data;

  // The angle cosine cutoff between hard and soft scattering
  double d_cutoff_angle_cosine;

  // The angle cosine cutoff between the distrubution and screened Rutherford scattering
  static double s_rutherford_cutoff;

  // Difference btw cutoff angle cosine for analytical peak and foward peak (mu=1)
  static double s_delta_rutherford;
};

} // end DataGen namespace

#endif // end DATA_GEN_ELASTIC_ELECTRON_MOMENTS_EVALUATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_ElasticElectronMomentsEvaluator.hpp
//---------------------------------------------------------------------------//
