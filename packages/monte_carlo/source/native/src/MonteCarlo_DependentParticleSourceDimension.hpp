//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DependentParticleSourceDimension.hpp
//! \author Alex Robinson
//! \brief  Dependent particle source dimension class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DEPENDENT_PARTICLE_SOURCE_DIMENSION_HPP
#define MONTE_CARLO_DEPENDENT_PARTICLE_SOURCE_DIMENSION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ParticleSourceDimension.hpp"
#include "Utility_FullyTabularTwoDDistribution.hpp"

namespace MonteCarlo{

//! The dependent particle source dimension class
template<ParticleSourceDimensionType indep_dimension,
         ParticleSourceDimensionType dep_dimension>
class DependentParticleSourceDimension : public ParticleSourceDimension
{

public:

  //! Constructor
  DependentParticleSourceDimension(
            const std::shared_ptr<const Utility::FullyTabularTwoDDistribution>&
            dimension_distribution );

  //! Destructor
  virtual ~DependentParticleSourceDimension()
  { /* ... */ }

  //! Return the dependent dimension type
  ParticleSourceDimensionType getDimensionType() const override;

  //! Return the dimension class type
  ParticleSourceDimensionClassType getDimensionClassType() const override;

  //! Return the independent dimension type
  ParticleSourceDimensionType getIndepDimensionType() const;

  //! Return the independent dimension class type
  ParticleSourceDimensionClassType getIndepDimensionClassType() const;

  //! Check if the dimension is independent
  bool isIndependent() const override;

  //! Check if the dimension is dependent on the dimension of interest
  bool isDependentOnDimension( const ParticleSourceDimensionType dimension ) const override;

protected:

  //! Sample a value for this dimension only
  virtual void sampleDimension( ParticleSourcePhaseSpacePoint& phase_space_sample ) const override;

  //! Set the value for this dimension only
  void setDimensionValue( ParticleSourcePhasePoint& phase_space_sample,
                          const double dimension_value ) const override;

  //! Evaluate the conditional pdf of the dimension distribution
  double evaluateDimensionConditionalPDF( const double indep_dimension_value,
                                          const double dimension_value ) const;

private:

  // The dimension distribution
  std::shared_ptr<const Utility::FullyTabularTwoDDistribution>
  d_dimension_distribution;
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_DependentParticleSourceDimension_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_DEPENDENT_PARTICLE_SOURCE_DIMENSION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DependentParticleSourceDimension.hpp
//---------------------------------------------------------------------------//
