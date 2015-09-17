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

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Data_EvaluatedElectronDataContainer.hpp"
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_TabularOneDDistribution.hpp"
#include "MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.hpp"
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
    const Data::EvaluatedElectronDataContainer& native_eedl_data,
    const double& cutoff_angle = 1.0e-6 );

  //! Destructor
  ~ElasticElectronMomentsEvaluator()
  { /* ... */ }

  //! Evaluate the Legnendre Polynomial expansion of the screened rutherford pdf
  double evaluateLegendreExpandedRutherford( const double scattering_angle,
                                        const double incoming_energy, 
                                        const int polynomial_order = 0) const;

  //! Evaluate the Legnendre Polynomial expansion of the differential hard elastic pdf
  double evaluateLegendreExpandedPDF( const double scattering_angle,
                                      const double incoming_energy, 
                                      const int polynomial_order = 0) const;

  //! Evaluate the Legnendre Polynomial expansion of the differential hard elastic pdf
  double evaluateLegendreExpandedPDFAtEnergyBin( 
                                const double scattering_angle,
                                const unsigned incoming_energy_bin, 
                                const int polynomial_order = 0) const;

  //! Return the moment of the elastic scattering distribution at a given energy and polynomial order
  void evaluateElasticMoment( 
            Teuchos::Array<Utility::long_float>& legendre_moments,
            const double energy,
            const int n,
            const double precision ) const;

  //! Return the moment of the elastic scattering distribution at a given energy and polynomial order
  void evaluateElasticMoment( 
            Teuchos::Array<Utility::long_float>& legendre_moments,
            const unsigned energy_bin,
            const int n,
            const double precision ) const;

  //! Evaluate the nth cross section moment of the screened Rutherford peak distribution 
  void evaluateScreenedRutherfordMoment( 
            Utility::long_float& rutherford_moments,
            const double energy,
            const int n ) const;

private:

  // The analog reaction
  Teuchos::RCP<MonteCarlo::ElectroatomicReaction> d_analog_reaction;

  // The screened Rutherford reaction
  Teuchos::RCP<MonteCarlo::ElectroatomicReaction> d_rutherford_reaction;

  // The analog distribution
  Teuchos::RCP<const MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution>
    d_rutherford_distribution;

  // The screened Rutherford distribution
  Teuchos::RCP<const MonteCarlo::AnalogElasticElectronScatteringDistribution>
    d_analog_distribution;

  // The raw ace electron data extractor
  Data::EvaluatedElectronDataContainer d_native_eedl_data;

  // The angle cutoff between hard and soft scattering
  double d_cutoff_angle;

  // The angle cosine cutoff between hard and soft scattering
  double d_cutoff_angle_cosine;

  // The angle cutoff between the distrubution and screened Rutherford scattering
  static double s_rutherford_cutoff_angle;

  // The angle cosine cutoff between the distrubution and screened Rutherford scattering
  static double s_rutherford_cutoff_angle_cosine;
};

} // end DataGen namespace

#endif // end DATA_GEN_ELASTIC_ELECTRON_MOMENTS_EVALUATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_ElasticElectronMomentsEvaluator.hpp
//---------------------------------------------------------------------------//
