//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ImportanceSampledIndependentParticleSourceDimension.hpp
//! \author Alex Robinson
//! \brief  Importance sampled independent particle source dimension class decl
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_IMPORTANCE_SAMPLED_INDEPENDENT_PARTICLE_SOURCE_DIMENSION_HPP
#define MONTE_CARLO_IMPORTANCE_SAMPLED_INDEPENDENT_PARTICLE_SOURCE_DIMENSION_HPP

// FRENSIE Includes
#include "MonteCarlo_IndependentParticleSourceDimension.hpp"

namespace MonteCarlo{

//! The importance sampled independent particle source dimension class
template<ParticleSourceDimensionType dimension>
class ImportanceSampledIndependentParticleSourceDimension : public IndependentParticleSourceDimension<dimension>
{
  
public:

  //! Constructor
  ImportanceSampledIndependentParticleSourceDimension(
                        const std::shared_ptr<const Utility::OneDDistribution>&
                        dimension_distribution,
                        const std::shared_ptr<const Utility::OneDDistribution>&
                        importance_distribution );

  //! Destructor
  ~ImportanceSampledIndependentParticleSourceDimension()
  { /* ... */ }

protected:

  //! Sample a value for this dimension only
  void sampleDimension( ParticleSourcePhaseSpacePoint& phase_space_sample ) const override;

private:

  // The dimension importance distribution
  std::shared_ptr<const Utility::OneDDistribution>
  d_dimension_importance_distribution;
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_ImportanceSampledIndependentParticleSourceDimension_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_IMPORTANCE_SAMPLED_INDEPENDENT_PARTICLE_SOURCE_DIMENSION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ImportanceSampledIndepedentParticleSourceDimension.hpp
//---------------------------------------------------------------------------//
