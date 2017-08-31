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

namespace DataGen{

//! The adjoint electron grid generator
template<typename ElectroatomicReaction, typename TwoDInterpPolicy>
class AdjointElectronGridGenerator : public Utility::TwoDGridGenerator<TwoDInterpPolicy>
{

public:

  //! Typedef for the const electroatomic reaction
  typedef const ElectroatomicReaction
    ConstElectroatomicReaction;

  //! Constructor
  AdjointElectronGridGenerator(
      const std::shared_ptr<const ElectroatomicReaction>& electroatomic_reaction,
      const std::vector<double>& primary_energy_grid,
      const double min_energy = 1e-5,
      const double max_energy = 20.0,
      const double max_energy_nudge_value = 0.2,
      const double energy_to_outgoing_energy_nudge_value = 1e-6,
      const double convergence_tol = 0.001,
      const double absolute_diff_tol = 1e-10,
      const double distance_tol = 1e-8 );

  //! Destructor
  virtual ~AdjointElectronGridGenerator()
  { /* ... */ }

  //! Get the min energy
  double getMinEnergy() const;

  //! Get the max energy
  double getMaxEnergy() const;

  //! Set the max energy nudge value
  void setMaxEnergyNudgeValue( const double max_energy_nudge_value );
  
  //! Get the nudged max energy
  double getNudgedMaxEnergy() const;

  //! Set the energy to outgoing energy nudge value
  void setEnergyToOutgoingEnergyNudgeValue(
            const double energy_to_outgoing_energy_nudge_value );

  //! Get the nudged energy
  double getNudgedEnergy( const double energy ) const;

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
    const std::vector<double> primary_energy_grid,
    const std::vector<double> adjoint_cross_sections,
    const unsigned threshold_index ) const;

protected:

  //! Initialize the outgoing energy grid at an energy grid point
  void initializeSecondaryGrid( std::vector<double>& outgoing_energy_grid,
                                const double energy ) const;
  
private:

  // The forward electroatomic reaction
  std::shared_ptr<const ElectroatomicReaction> d_electroatomic_reaction;

  // The primary incoming energy grid of the forward electronatomic reaction
  std::vector<double> d_primary_energy_grid;

  // The energies used as integration points
  std::vector<double> d_integration_points;

  // The min electron energy
  double d_min_energy;

  // The max table energy (highest energy grid point)
  double d_max_energy;

  // The max table energy nudge value 
  double d_nudged_max_energy;

  // The energy to outgoing energy nudge value
  double d_energy_to_outgoing_energy_nudge_value;
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
