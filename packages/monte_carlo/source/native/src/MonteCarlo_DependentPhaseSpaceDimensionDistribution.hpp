//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DependentPhaseSpaceDimensionDistribution.hpp
//! \author Alex Robinson
//! \brief  Dependent phase space dimension distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP
#define MONTE_CARLO_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_PhaseSpaceDimension.hpp"

namespace MonteCarlo{

//! The dependent phase space dimension distribution class
template<PhaseSpaceDimension indep_dimension,PhaseSpaceDimension dep_dimension>
class DependentPhaseSpaceDimensionDistribution : public PhaseSpaceDimensionDistribution
{

public:

  //! Constructor
  DependentPhaseSpaceDimensionDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~DependentPhaseSpaceDimensionDistribution()
  { /* ... */ }

  //! Return the phase space dimension
  PhaseSpaceDimension getDimension() const override;

  //! Return the phase space dimension class
  PhaseSpaceDimensionClass getDimensionClass() const override;

  //! Return the independent phase space dimension
  PhaseSpaceDimension getIndepDimension() const;

  //! Return the independent phase space dimension class
  PhaseSpaceDimensionClass getIndepDimensionClass() const;

  //! Check if the dimension distribution is independent
  bool isIndependent() const override;

  //! Check if the dimension is dependent on the dimension of interest
  bool isDependentOnDimension(
                          const PhaseSpaceDimension dimension ) const override;
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_DependentPhaseSpaceDimensionDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_DEPENDENT_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DependentPhaseSpaceDimensionDistribution.hpp
//---------------------------------------------------------------------------//
