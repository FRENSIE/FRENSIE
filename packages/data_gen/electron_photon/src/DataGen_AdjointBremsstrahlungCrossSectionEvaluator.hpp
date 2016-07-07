//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointBremsstrahlungCrossSectionEvaluator.hpp
//! \author Luke Kersting
//! \brief  Adjoint bremsstrahlung cross section evaluator declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ADJOINT_BREMSSTRAHLUNG_CROSS_SECTION_EVALUATOR_HPP
#define DATA_GEN_ADJOINT_BREMSSTRAHLUNG_CROSS_SECTION_EVALUATOR_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardElectroatomicReaction.hpp"
#include "MonteCarlo_TwoDDistributionHelpers.hpp"
#include "Utility_OneDDistribution.hpp"
//#include "Utility_TabularOneDDistribution.hpp"


namespace DataGen{

//! The adjoint bremsstrahlung cross section class
class AdjointBremsstrahlungCrossSectionEvaluator
{

public:

  //! Typedef for the bremsstrahlung distribution
  typedef MonteCarlo::TwoDDistribution BremsstrahlungDistribution;

  //! Constructor
  AdjointBremsstrahlungCrossSectionEvaluator(
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    const Teuchos::ArrayRCP<const double>& electron_energy_grid,
    const Teuchos::ArrayRCP<const double>& bremsstrahlung_cross_section,
    const unsigned bremsstrahlung_threshold_energy_index,
    const BremsstrahlungDistribution& energy_loss_distribution );

  //! Destructor
  ~AdjointBremsstrahlungCrossSectionEvaluator()
  { /* ... */ }

  //! Evaluate the differential adjoint bremsstrahlung cross section (dc/dx)
  double evaluateDifferentialCrossSection(
        const double incoming_energy,
        const double outgoing_energy ) const;

  //! Return the cross section value at a given energy
  double evaluateAdjointCrossSection(
        const double energy,
        const double precision = 1e-6 ) const;

private:

  // The energy grid searcher
  Teuchos::RCP<Utility::HashBasedGridSearcher> d_grid_searcher;

  // The electron energy grid
  Teuchos::ArrayRCP<const double> d_electron_energy_grid;

  // The bremsstrahlung cross section
  Teuchos::ArrayRCP<const double> d_bremsstrahlung_cross_section;

  // The bremsstrahlung cross section threshold energy index
  unsigned d_bremsstrahlung_threshold_energy_index;

  // The bremsstrahlung energy loss distribution
  BremsstrahlungDistribution d_energy_loss_distribution;
};

} // end DataGen namespace

#endif // end DATA_GEN_ADJOINT_BREMSSTRAHLUNG_CROSS_SECTION_EVALUATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointBremsstrahlungCrossSectionEvaluator.hpp
//---------------------------------------------------------------------------//
