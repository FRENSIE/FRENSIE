//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointIncoherentGridGenerator.hpp
//! \author Alex Robinson
//! \brief  Adjoint incoherent grid generator declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ADJOINT_INCOHERENT_GRID_GENERATOR_HPP
#define DATA_GEN_ADJOINT_INCOHERENT_GRID_GENERATOR_HPP

// Std Lib Includes
#include <functional>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistribution.hpp"
#include "Utility_TwoDGridGenerator.hpp"

namespace DataGen{

//! The adjoint incoherent cross section grid generator
template<typename TwoDInterpPolicy>
class AdjointIncoherentGridGenerator : public Utility::TwoDGridGenerator<TwoDInterpPolicy>
{

public:

  //! Constructor
  AdjointIncoherentGridGenerator(
                          const double max_energy = 20.0,
                          const double max_energy_nudge_value = 0.2,
                          const double energy_to_max_energy_nudge_value = 1e-6,
                          const double convergence_tol = 0.001,
                          const double absolute_diff_tol = 1e-12,
                          const double distance_tol = 1e-14 );

  //! Destructor
  virtual ~AdjointIncoherentGridGenerator()
  { /* ... */ }

  //! Get the max energy
  double getMaxEnergy() const;

  //! Set the max energy nudge value
  void setMaxEnergyNudgeValue( const double max_energy_nudge_value );

  //! Get the nudged max energy
  double getNudgedMaxEnergy() const;

  //! Set the energy to max energy nudge value
  void setEnergyToMaxEnergyNudgeValue(
                               const double energy_to_max_energy_nudge_value );

  //! Get the nudged energy
  double getNudgedEnergy( const double energy ) const;

  //! Create a cross section evaluator
  static std::function<double (double,double)>
  createCrossSectionEvaluator(
     const std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>& adjoint_incoherent_cross_section,
     const double cross_section_evaluation_tol );


protected:

  //! Add critical energies to energy grid
  void addCriticalValuesToPrimaryGrid(std::deque<double>& energy_grid ) const;

  //! Initialize the max energy grid at an energy grid point
  void initializeSecondaryGrid( std::vector<double>& max_energy_grid,
                                const double energy ) const;

private:

  // The max table energy (highest energy grid point)
  double d_max_energy;

  // The max table energy nudge value
  double d_nudged_max_energy;

  // The energy to max energy nudge value
  double d_energy_to_max_energy_nudge_value;
};

} // end DataGen namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "DataGen_AdjointIncoherentGridGenerator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_GEN_ADJOINT_INCOHERENT_GRID_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointIncoherentGridGenerator.hpp
//---------------------------------------------------------------------------//
