//---------------------------------------------------------------------------//
//!
//! \file   DataGen_IncoherentCrossSectionEvaluator.hpp
//! \author Alex Robinson
//! \brief  Adjoint incoherent cross section evaluator declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_INCOHERENT_CROSS_SECTION_EVALUATOR_HPP
#define DATA_GEN_INCOHERENT_CROSS_SECTION_EVALUATOR_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_KleinNishinaDistribution.hpp"
#include "Utility_GaussKronrodQuadratureKernel.hpp"

namespace DataGen{

//! The incoherent cross section class
class IncoherentCrossSectionEvaluator
{

public:

  //! Default constructor (free electron)
  IncoherentCrossSectionEvaluator();

  //! Constructor (bound electrons)
  IncoherentCrossSectionEvaluator(
    const Teuchos::RCP<const Utility::OneDDistribution>& scattering_function );

  //! Destructor
  ~IncoherentCrossSectionEvaluator()
  { /* ... */ }

  //! Evaluate the differential incoherent cross section (dc/dx)
  double evaluateDifferentialCrossSection(
		 const double inverse_energy_loss_ratio,
		 const Utility::KleinNishinaDistribution& distribution ) const;

  //! Return the cross section valud at a given energy
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
