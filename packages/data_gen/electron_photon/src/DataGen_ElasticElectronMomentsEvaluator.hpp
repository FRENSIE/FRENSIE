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
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_TabularOneDDistribution.hpp"
#include "MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.hpp"
#include "Utility_SloanRadauQuadrature.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"


namespace DataGen{

//! The elastic electron cross section moments class
class ElasticElectronMomentsEvaluator
{
  
public:

  //! Typedef for the elastic distribution
  typedef Teuchos::Array<Utility::Pair<double,
		       Teuchos::RCP<const Utility::TabularOneDDistribution> > >
  ElasticDistribution;

  //! Typedef for the elastic distribution
  typedef Utility::GaussKronrodIntegrator<Utility::long_float>
  Integrator;

  //! Constructor
  ElasticElectronMomentsEvaluator(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double& cutoff_angle_cosine = 0.999999 );

  //! Destructor
  ~ElasticElectronMomentsEvaluator()
  { /* ... */ }

  //! Evaluate the Legnendre Polynomial expansion of the screened rutherford pdf
  double evaluateLegendreExpandedRutherford(
            const double scattering_angle_cosine,
            const double incoming_energy,
            const int polynomial_order = 0 ) const;

  //! Evaluate the Legnendre Polynomial expansion of the screened rutherford pdf
  double evaluateLegendreExpandedRutherford(
            const double scattering_angle_cosine,
            const double incoming_energy,
            const double eta,
            const int polynomial_order = 0 ) const;

  //! Evaluate the Legnendre Polynomial expansion of the differential hard elastic pdf
  double evaluateLegendreExpandedPDF(
            const double scattering_angle_cosine,
            const double incoming_energy, 
            const int polynomial_order = 0) const;

  //! Evaluate the nth cross section moment of the elastic cutoff distribution at the energy
  void evaluateCutoffMoment( 
            Utility::long_float& cutoff_moment,
            const std::vector<double>& angular_grid,
            const Integrator& integrator,
            const double energy,
            const int n ) const;

  //! Evaluate the nth cross section moment of the screened Rutherford peak distribution at the energy
  void evaluateScreenedRutherfordMoment( 
            Utility::long_float& rutherford_moment,
            const double& energy,
            const int& n ) const;

  //! Evaluate the first n moments of the elastic scattering distribution at a given energy
  void evaluateElasticMoment( 
            std::vector<Utility::long_float>& legendre_moments,
            const double energy,
            const int n,
            const double precision ) const;

protected:

  // Evaluate the nth PDF moment of the cutoff distribution at the energy
  void evaluateCutoffPDFMoment(
            Utility::long_float& cutoff_moment,
            const std::vector<double>& angular_grid,
            const Integrator& integrator,
            const double energy,
            const int n ) const;

  // Evaluate the nth PDF moment of the screened Rutherford peak distribution at the energy
  void evaluateScreenedRutherfordPDFMoment( 
            Utility::long_float& rutherford_moment,
            const double& energy,
            const int& n ) const;

  /* Evaluate the nth PDF moment of the screened Rutherford peak distribution
   * at the eta using the recursion relationship
   */
  void evaluateScreenedRutherfordPDFMomentByRecursion(
            Utility::long_float& rutherford_moment,
            const Utility::long_float& eta,
            const int& n ) const;

  /* Evaluate the nth PDF moment of the screened Rutherford peak distribution
   * at the energy using numerical integration
   */
  void evaluateScreenedRutherfordPDFMomentByNumericalIntegration(
            Utility::long_float& rutherford_moment,
            const double& energy,
            const int& n ) const;

  /* Evaluate the nth PDF moment of the screened Rutherford peak distribution
   * at the energy using numerical integration
   */
  void evaluateScreenedRutherfordPDFMomentByNumericalIntegration(
            Utility::long_float& rutherford_moment,
            const Utility::long_float& eta,
            const double& energy,
            const int& n ) const;

private:

  // The cutoff reaction
  Teuchos::RCP<MonteCarlo::ElectroatomicReaction> d_cutoff_reaction;

  // The screened Rutherford reaction
  Teuchos::RCP<MonteCarlo::ElectroatomicReaction> d_rutherford_reaction;

  // The cutoff distribution
  Teuchos::RCP<const MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution>
    d_rutherford_distribution;

  // The screened Rutherford distribution
  Teuchos::RCP<const MonteCarlo::CutoffElasticElectronScatteringDistribution>
    d_cutoff_distribution;

  // The raw ace electron data extractor
  Data::ElectronPhotonRelaxationDataContainer d_data_container;

  // The change in angle cosine cutoff between hard and soft scattering
  double d_cutoff_delta_angle_cosine;

  // The angle cosine cutoff between hard and soft scattering
  double d_cutoff_angle_cosine;

  // The angle cutoff between the distrubution and screened Rutherford scattering
  static double s_rutherford_cutoff_delta_angle_cosine;

  // The angle cosine cutoff between the distrubution and screened Rutherford scattering
  static double s_rutherford_cutoff_angle_cosine;
};

} // end DataGen namespace

#endif // end DATA_GEN_ELASTIC_ELECTRON_MOMENTS_EVALUATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_ElasticElectronMomentsEvaluator.hpp
//---------------------------------------------------------------------------//
