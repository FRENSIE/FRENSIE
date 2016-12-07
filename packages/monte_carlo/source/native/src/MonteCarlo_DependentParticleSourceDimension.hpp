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
  ~DependentParticleSourceDimension()
  { /* ... */ }

  //! Return the dependent dimension type
  ParticleSourceDimensionType getDimensionType() const override;

  //! Return the independent dimension type
  ParticleSourceDimensionType getIndepDimensionType() const;

  //! Check if the dimension is independent
  bool isIndependent() const override;

  //! Check if the dimension is dependent on the dimension of interest
  bool isDependentOnDimension( const ParticleSourceDimensionType dimension ) const override;

  //! Set the dimension importance distribution
  void setImportanceDistribution(
            const std::shared_ptr<const Utility::FullyTabularTwoDDistribution>&
            importance_distribution ); 

protected:

  //! Sample a value for this dimension only
  void sampleDimension( ParticleSourcePhaseSpacePoint& phase_space_sample ) const override;

  //! Set the value for this dimension only
  void setDimensionValue( ParticleSourcePhasePoint& phase_space_sample,
                          const double dimension_value ) const override;

private:

  // The dimension distribution
  std::shared_ptr<const Utility::FullyTabularTwoDDistribution>
  d_dimension_distribution;

  // The dimension importance distribution
  std::shared_ptr<const Utility::FullyTabularTwoDDistribution>
  d_dimension_importance_distribution;
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
