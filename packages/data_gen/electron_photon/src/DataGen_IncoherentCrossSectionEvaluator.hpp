//---------------------------------------------------------------------------//
//!
//! \file   DataGen_IncoherentCrossSectionEvaluator.hpp
//! \author Alex Robinson
//! \brief  Incoherent cross section evaluator declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_INCOHERENT_CROSS_SECTION_EVALUATOR_HPP
#define DATA_GEN_INCOHERENT_CROSS_SECTION_EVALUATOR_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_KleinNishinaDistribution.hpp"

namespace DataGen{

/*! The incoherent cross section evaluator class
 * \details This class generates the incoherent cross section using
 * Waller-Hartree theory.
 */
class IncoherentCrossSectionEvaluator
{

public:

  //! Default Constructor (free electron)
  IncoherentCrossSectionEvaluator();

  //! Constructor (bound electron)
  IncoherentCrossSectionEvaluator(
			   const Teuchos::RCP<const Utility::OneDDistribution>&
			   scattering_function );

  //! Destructor
  ~IncoherentCrossSectionEvaluator()
  { /* ... */ }

  //! Evaluate the differential incoherent cross section (dc/dx)
  double evaluateDifferentialCrossSection(
		 const double inverse_energy_loss_ratio,
		 const Utility::KleinNishinaDistribution& distribution ) const;

  //! Evaluate the incoherent cross section
  double evaluateCrossSection( const double energy,
			       const double precision = 1e-6 ) const;

private:

  // The scattering function
  Teuchos::RCP<const Utility::OneDDistribution> d_scattering_function;
};

} // end DataGen namespace

#endif // end DATA_GEN_INCOHERENT_CROSS_SECTION_EVALUATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_IncoherentCrossSectionEvaluator.hpp
//---------------------------------------------------------------------------//
