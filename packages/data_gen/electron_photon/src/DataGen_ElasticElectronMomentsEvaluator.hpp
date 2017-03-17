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
#include <boost/multiprecision/cpp_dec_float.hpp>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"
#include "Utility_SloanRadauQuadrature.hpp"
#include "MonteCarlo_AnalogElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_AnalogElasticElectroatomicReaction.hpp"


namespace DataGen{

//! The elastic electron cross section moments class
class ElasticElectronMomentsEvaluator
{

public:

  //! Typedef for the elastic distribution
  typedef Utility::GaussKronrodIntegrator<Utility::long_float>
  Integrator;

  //! Constructor
  ElasticElectronMomentsEvaluator(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double tabular_evaluation_tol,
    const bool linlinlog_interpolation_mode_on,
    const bool correlated_sampling_mode_on );

  //! Constructor (without data container)
  ElasticElectronMomentsEvaluator(
    const std::map<double,std::vector<double> >& cutoff_elastic_angles,
    const Teuchos::ArrayRCP<double>& incoming_energy_grid,
    const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
    const Teuchos::ArrayRCP<double>& cutoff_cross_section,
    const Teuchos::ArrayRCP<double>& screened_rutherford_cross_section,
    const unsigned cutoff_threshold_energy_index,
    const unsigned screened_rutherford_threshold_energy_index,
    const std::shared_ptr<const MonteCarlo::AnalogElasticElectronScatteringDistribution>
        analog_distribution,
    const double cutoff_angle_cosine );

  //! Destructor
  ~ElasticElectronMomentsEvaluator()
  { /* ... */ }

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
            const double energy,
            const int n,
            const double tolerance = 1e-13,
            const unsigned number_of_iterations = 1000 ) const;

  /* Evaluate the nth PDF moment of the screened Rutherford peak distribution
   * at the energy using numerical integration
   */
  void evaluateScreenedRutherfordPDFMomentByNumericalIntegration(
            Utility::long_float& rutherford_moment,
            const Utility::long_float& eta,
            const double energy,
            const int n,
            const double tolerance = 1e-13,
            const unsigned number_of_iterations = 1000 ) const;

private:

  // Return the angular integration points
  void getAngularIntegrationPoints(
        std::vector<double>& angular_integration_points,
        const double energy ) const;

  // The electron energy grid
  Teuchos::ArrayRCP<double> d_incoming_energy_grid;

  // Grid searcher for the energy grid
  Teuchos::RCP<const Utility::HashBasedGridSearcher> d_grid_searcher;

  // The cutoff elastic cross section
  Teuchos::ArrayRCP<double> d_cutoff_cross_section;

  // The screened rutherford elastic cross section
  Teuchos::ArrayRCP<double> d_screened_rutherford_cross_section;

  // The cutoff elastic threshold_energy_index
  unsigned d_cutoff_threshold_energy_index;

  // The screened rutherford elastic threshold_energy_index
  unsigned d_screened_rutherford_threshold_energy_index;

  // The analog distribution
  std::shared_ptr<const MonteCarlo::AnalogElasticElectronScatteringDistribution>
    d_analog_distribution;

  // The cutoff reaction
  std::shared_ptr<const MonteCarlo::ElectroatomicReaction>
    d_cutoff_reaction;

  // The screened rutherford reaction
  std::shared_ptr<const MonteCarlo::ElectroatomicReaction>
    d_screened_rutherford_reaction;

  // The map of the cutoff angles
  std::map<double,std::vector<double> > d_cutoff_elastic_angles;

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
