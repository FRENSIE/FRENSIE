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
#include "DataGen_AdjointElectronCrossSectionEvaluator.hpp"
#include "Utility_TwoDGridGenerator.hpp"

namespace DataGen{

//! The adjoint electron grid generator
template<typename TwoDInterpPolicy>
class AdjointElectronGridGenerator : public Utility::TwoDGridGenerator<TwoDInterpPolicy>
{

public:

//  //! Advance Constructor
//  AdjointElectronGridGenerator(
//          const std::vector<double>& critical_energies,
//          const double max_energy = 20.0,
//          const double max_energy_nudge_value = 0.2,
//          const double energy_to_outgoing_energy_nudge_value = 1e-6,
//          const double convergence_tol = 0.001,
//          const double absolute_diff_tol = 1e-10,
//          const double distance_tol = 1e-8 );

  //! Basic Constructor
  AdjointElectronGridGenerator(
          const double max_energy = 20.0,
          const double max_energy_nudge_value = 0.2,
          const double energy_to_outgoing_energy_nudge_value = 1e-6,
          const double convergence_tol = 0.001,
          const double absolute_diff_tol = 1e-10,
          const double distance_tol = 1e-8 );

  //! Destructor
  virtual ~AdjointElectronGridGenerator()
  { /* ... */ }

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

  //! Set the critcal energies for the primary grid
  void setCriticalEnergies( const std::vector<double> critical_energies );
  
  //! Get the critcal energies for the primary grid
  std::vector<double> getCriticalEnergies() const;

  //! Create a cross section evaluator
  template< typename ElectroatomicReaction >
  static std::function<double (double,double)> createCrossSectionEvaluator(
    const std::shared_ptr<const DataGen::AdjointElectronCrossSectionEvaluator<ElectroatomicReaction> >& adjoint_diff_cross_section,
    const double cross_section_evaluation_tol );
                              

protected:

  //! Add critical energies to energy grid
  void addCriticalValuesToPrimaryGrid(std::deque<double>& energy_grid ) const;

  //! Initialize the outgoing energy grid at an energy grid point
  void initializeSecondaryGrid( std::vector<double>& outgoing_energy_grid,
                                const double energy ) const;
  
private:

  // The max table energy (highest energy grid point)
  double d_max_energy;

  // The max table energy nudge value 
  double d_nudged_max_energy;

  // The energy to outgoing energy nudge value
  double d_energy_to_outgoing_energy_nudge_value;

  // The critical enegies on the primary grid
  std::vector<double> d_critical_energies;
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
