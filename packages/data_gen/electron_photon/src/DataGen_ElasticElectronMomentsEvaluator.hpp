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

// FRENSIE Includes
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"
#include "Utility_SloanRadauQuadrature.hpp"
#include "MonteCarlo_CoupledElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_CoupledElasticElectroatomicReaction.hpp"
#include "MonteCarlo_TwoDInterpolationType.hpp"
#include "MonteCarlo_TwoDGridType.hpp"


namespace DataGen{

//! The elastic electron cross section moments class
class ElasticElectronMomentsEvaluator
{

public:

  //! Typedef for the elastic distribution
  typedef Utility::GaussKronrodIntegrator<Utility::long_float>
  Integrator;

  // Typedef for elastic electron traits
  typedef MonteCarlo::ElasticElectronTraits ElasticTraits;

  //! Constructor
  ElasticElectronMomentsEvaluator(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const MonteCarlo::TwoDInterpolationType two_d_interp,
    const MonteCarlo::TwoDGridType two_d_grid,
    const double cutoff_angle_cosine,
    const double tabular_evaluation_tol );

  //! Constructor (without data container)
  ElasticElectronMomentsEvaluator(
    const std::map<double,std::vector<double> >& cutoff_elastic_angles,
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
     grid_searcher,
    const std::shared_ptr<const std::vector<double> >& cutoff_cross_section,
    const std::shared_ptr<const std::vector<double> >& total_elastic_cross_section,
    const unsigned screened_rutherford_threshold_energy_index,
    const std::shared_ptr<const MonteCarlo::CoupledElasticElectronScatteringDistribution>
        coupled_distribution,
    const std::shared_ptr<const ElasticTraits>& elastic_traits,
    const double cutoff_angle_cosine );

  //! Destructor
  ~ElasticElectronMomentsEvaluator()
  { /* ... */ }

  //! Evaluate the Legendre Polynomial expansion of the screened rutherford pdf
  double evaluateLegendreExpandedRutherford(
            const double scattering_angle_cosine,
            const double incoming_energy,
            const int polynomial_order = 0 ) const;

  //! Evaluate the Legendre Polynomial expansion of the screened rutherford pdf
  double evaluateLegendreExpandedRutherford(
            const double scattering_angle_cosine,
            const double incoming_energy,
            const double eta,
            const int polynomial_order = 0 ) const;

  //! Evaluate the Legendre Polynomial expansion of the differential hard elastic pdf
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


  // Grid searcher for the energy grid
  std::shared_ptr<const Utility::HashBasedGridSearcher<double> > d_grid_searcher;

  // The screened rutherford elastic threshold_energy_index
  unsigned d_screened_rutherford_threshold_energy_index;

  // The coupled distribution
  std::shared_ptr<const MonteCarlo::CoupledElasticElectronScatteringDistribution>
    d_coupled_distribution;

  // The cutoff elastic reaction
  std::shared_ptr<const MonteCarlo::ElectroatomicReaction>
    d_cutoff_reaction;

  // The total elastic reaction
  std::shared_ptr<const MonteCarlo::ElectroatomicReaction>
    d_total_reaction;

  // The map of the cutoff angles
  std::map<double,std::vector<double> > d_cutoff_elastic_angles;

  // The angle cosine cutoff between hard and soft scattering
  double d_cutoff_angle_cosine;

  // Elastic electron traits
  std::shared_ptr<const ElasticTraits> d_elastic_traits;
};

} // end DataGen namespace

#endif // end DATA_GEN_ELASTIC_ELECTRON_MOMENTS_EVALUATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_ElasticElectronMomentsEvaluator.hpp
//---------------------------------------------------------------------------//
