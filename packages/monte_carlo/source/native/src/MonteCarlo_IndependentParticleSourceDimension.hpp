//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IndependentParticleSourceDimension.hpp
//! \author Alex Robinson
//! \brief  Independent particle source dimension class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INDEPENDENT_PARTICLE_SOURCE_DIMENSION_HPP
#define MONTE_CARLO_INDEPENDENT_PARTICLE_SOURCE_DIMENSION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ParticleSourceDimension.hpp"
#include "Utility_OneDDistribution.hpp"

namespace MonteCarlo{

//! The independent particle source dimension class
template<ParticleSourceDimensionType dimension>
class IndependentParticleSourceDimension : public ParticleSourceDimension
{

public:

  //! Constructor
  IndependentParticleSourceDimension(
                        const std::shared_ptr<const Utility::OneDDistribution>&
                        dimension_distribution );

  //! Destructor
  virtual ~IndependentParticleSourceDimension()
  { /* ... */ }

  //! Return the dimension type
  ParticleSourceDimensionType getDimensionType() const override;

  //! Return the dimension class type
  ParticleSourceDimensionClassType getDimensionClassType() const override;

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

  //! Evaluate the pdf of the dimension distribution
  double evaluateDimensionPDF( const double dimension_value ) const;

private:

  // The dimension distribution
  std::shared_ptr<const Utility::OneDDistribution> d_dimension_distribution;
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_IndependentParticleSourceDimension_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_INDEPENDENT_PARTICLE_SOURCE_DIMENSION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IndependentParticleSourceDimension.hpp
//---------------------------------------------------------------------------//
