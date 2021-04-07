//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointElectronGridGenerator.hpp
//! \author Luke Kersting
//! \brief  Adjoint electron grid generator declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ADJOINT_ELECTRON_GRID_GENERATOR_HPP
#define DATA_GEN_ADJOINT_ELECTRON_GRID_GENERATOR_HPP

// Std Lib Includes
#include <functional>
#include <memory>

// FRENSIE Includes
#include "Utility_TwoDGridGenerator.hpp"
#include "Utility_FullyTabularBasicBivariateDistribution.hpp"

namespace DataGen{

//! The adjoint electron grid generator
template<typename TwoDInterpPolicy>
class AdjointElectronGridGenerator : public Utility::TwoDGridGenerator<TwoDInterpPolicy>
{

public:

  //! Constructor
  AdjointElectronGridGenerator(
      const std::function<double(const double&)>& forward_cs_evaluator,
      const std::function<double(const double&, const double&)>& forward_pdf_evaluator,
      const std::function<double(const double&)>& min_energy_gain_function,
      const std::vector<double>& primary_energy_grid,
      const double min_energy = 1e-5,
      const double max_energy = 20.0,
      const double min_energy_nudge_value = 1e-9,
      const double max_energy_nudge_value = 1e-2,
      const double convergence_tol = 0.001,
      const double absolute_diff_tol = 1e-10,
      const double distance_tol = 1e-8,
      const bool electron_scatter_above_max_energy_mode = true );

  //! Destructor
  virtual ~AdjointElectronGridGenerator()
  { /* ... */ }

  //! Get the min energy
  double getMinIncomingEnergy() const;

  //! Get the max incoming energy
  double getMaxIncomingEnergy() const;

  //! Get the min outgoing energy
  double getMinOutgoingEnergy() const;

  //! Get the max outgoing energy
  double getMaxOutgoingEnergy() const;

  //! Return the min energy nudge value
  double getMinEnergyNudgeValue() const;

  //! Return the max energy nudge value
  double getMaxEnergyNudgeValue() const;

  //! Get the nudged minimum outgoing adjoint energy
  double getNudgedMinEnergy( const double energy ) const;

  //! Evaluate the adjoint PDF value
  double evaluateAdjointPDF(
        const double incoming_adjoint_energy,
        const double outgoing_adjoint_energy,
        const double precision = 1e-6 ) const;

  //! Evaluate the adjoint PDF value
  double evaluateAdjointPDF(
        const double adjoint_cross_section,
        const double incoming_adjoint_energy,
        const double outgoing_adjoint_energy,
        const double precision ) const;

  //! Return the differential cross section value at a given energy
  double evaluateAdjointDifferentialCrossSection(
      const double adjoint_incoming_energy,
      const double adjoint_outgoing_energy ) const;

  //! Return the cross section value at a given energy
  double evaluateAdjointCrossSection(
        const double adjoint_energy,
        const double precision = 1e-6 ) const;

  //! Create a cross section evaluator
  std::function<double (double)> createAdjointCrossSectionFunction(
    const double cross_section_evaluation_tol ) const;

  //! Generate and evaluate the distribution grid in place
  void generateAndEvaluateDistribution(
    std::vector<double>& outgoing_energy_grid,
    std::vector<double>& evaluated_pdf,
    const double evaluation_tol,
    const double incoming_adjoint_energy,
    const double adjoint_cross_section ) const;

  //! Generate and evaluate the distribution grid in place on a primary energy grid
  void generateAndEvaluateDistributionOnPrimaryEnergyGrid(
    std::map<double,std::vector<double> >& outgoing_energy_grid,
    std::map<double,std::vector<double> >& evaluated_pdf,
    const double evaluation_tol,
    const std::vector<double>& primary_energy_grid,
    const std::vector<double>& adjoint_cross_sections,
    const unsigned threshold_index ) const;

protected:

  //! Initialize the outgoing energy grid at an energy grid point
  void initializeSecondaryGrid( std::vector<double>& outgoing_energy_grid,
                                const double energy ) const;

private:

  // Function for evaluating the forward cross section
  std::function<double(const double&)> d_forward_cs_evaluator;

  // Function for evaluating the forward pdf
  std::function<double(const double&, const double&)> d_forward_pdf_evaluator;

  // Functor to calculate the min adjoint energy gain
  std::function<double(const double&)> d_min_energy_gain_function;

  // The primary incoming energy grid of the forward electronatomic reaction
  std::vector<double> d_primary_energy_grid;

  // The energies used as integration points
  std::vector<double> d_integration_points;

  // The min table incoming energy
  double d_min_incoming_energy;

  // The max table incoming energy
  double d_max_incoming_energy;

  // The min table outgoing energy
  double d_min_outgoing_energy;

  // The max table outgoing energy
  double d_max_outgoing_energy;

  // The max table energy nudge value
  double d_nudged_max_energy;

  // The min energy nudge value
  double d_min_energy_nudge_value;

  // The max energy nudge value
  double d_max_energy_nudge_value;

  // The electron scatter above max energy mode
  bool d_electron_scatter_above_max_energy_mode;
};

} // end DataGen namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "DataGen_AdjointElectronGridGenerator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_GEN_ADJOINT_ELECTRON_GRID_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointElectronGridGenerator.hpp
//---------------------------------------------------------------------------//
