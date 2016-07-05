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
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "MonteCarlo_TwoDDistributionHelpers.hpp"
#include "Utility_TabularOneDDistribution.hpp"


namespace DataGen{

//! The adjoint bremsstrahlung cross section class
class AdjointBremsstrahlungCrossSectionEvaluator
{

public:

  //! Typedef for the bremsstrahlung distribution
  typedef MonteCarlo::TwoDDistribution BremsstrahlungDistribution;

  //! Constructor
  AdjointBremsstrahlungCrossSectionEvaluator(
    const Teuchos::RCP<MonteCarlo::ElectroatomicReaction>& bremsstrahlung_reaction,
    const BremsstrahlungDistribution& energy_loss_distribution );

  //! Destructor
  ~AdjointBremsstrahlungCrossSectionEvaluator()
  { /* ... */ }

  //! Evaluate the differential adjoint bremsstrahlung cross section (dc/dx)
  double evaluateDifferentialCrossSection(
	  const double incoming_energy,
          const double outgoing_energy ) const;

  //! Return the cross section value at a given energy
  double evaluateCrossSection( const double energy,
			       const double precision = 1e-6 ) const;

private:

  // The forward reaction data
  Teuchos::RCP<MonteCarlo::ElectroatomicReaction> d_bremsstrahlung_reaction;

  // The energy loss distribution
  BremsstrahlungDistribution d_energy_loss_distribution;
};

} // end DataGen namespace

#endif // end DATA_GEN_ADJOINT_BREMSSTRAHLUNG_CROSS_SECTION_EVALUATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointBremsstrahlungCrossSectionEvaluator.hpp
//---------------------------------------------------------------------------//
