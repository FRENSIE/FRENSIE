//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ImportanceSampledDependentParticleSourceDimension.hpp
//! \author Alex Robinson
//! \brief  Importance sampled dependent particle source dimension class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_IMPORTANCE_SAMPLED_DEPENDENT_PARTICLE_SOURCE_DIMENSION_HPP
#define MONTE_CARLO_IMPORTANCE_SAMPLED_DEPENDENT_PARTICLE_SOURCE_DIMENSION_HPP

// FRENSIE Includes
#include "MonteCarlo_DependentParticleSourceDimension.hpp"

namespace MonteCarlo{

//! The importance sampled dependent particle source dimension class
template<ParticleSourceDimensionType indep_dimension,
         ParticleSourceDimensionType dep_dimension>
class ImportanceSampledDependentParticleSourceDimension : public DependentParticleSourceDimension<indep_dimension,dep_dimension>
{

public:

  //! Constructor
  ImportanceSampledDependentParticleSourceDimension(
            const std::shared_ptr<const Utility::FullyTabularTwoDDistribution>&
            dimension_distribution,
            const std::shared_ptr<const Utility::FullyTabularTwoDDistribution>&
            importance_distribution );

  //! Destructor
  ~ImportanceSampledDependentParticleSourceDimension()
  { /* ... */ }

protected:

  //! Sample a value for this dimension only
  void sampleDimension( ParticleSourcePhaseSpacePoint& phase_space_sample ) const override;

private:

  // The dimension importance distribution
  std::shared_ptr<const Utility::FullyTabularTwoDDistribution>
  d_dimension_importance_distribution;
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_ImportanceSampledDependentParticleSourceDimension_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_IMPORTANCE_SAMPLED_DEPENDENT_PARTICLE_SOURCE_DIMENSION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ImportanceSampledDependentParticleSourceDimension.hpp
//---------------------------------------------------------------------------//
