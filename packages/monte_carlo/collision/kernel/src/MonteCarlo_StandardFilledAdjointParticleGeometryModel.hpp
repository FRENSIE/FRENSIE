//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardFilledAdjointParticleGeometryModel.hpp
//! \author Alex Robinson
//! \brief  The standard filled adjoint particle geometry model class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_FILLED_ADJOINT_PARTICLE_GEOMETRY_MODEL_HPP
#define MONTE_CARLO_STANDARD_FILLED_ADJOINT_PARTICLE_GEOMETRY_MODEL_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardFilledParticleGeometryModel.hpp"

namespace MonteCarlo{

//! The standard filled adjoint particle geometry model class
template<typename Material>
class StandardFilledAdjointParticleGeometryModel : public StandardFilledParticleGeometryModel<Material>
{
  // Typedef for the base type
  typedef StandardFilledParticleGeometryModel<Material> BaseType;

  // Typedef for this type
  typedef StandardFilledParticleGeometryModel<Material> ThisType;

public:

  //! Typedef for the material type
  typedef typename BaseType::MaterialType MaterialType;

  //! Typedef for the scattering center name map
  typedef typename BaseType::ScatteringCenterNameMap ScatteringCenterNameMap;

  //! Typedef for the reaction enum type
  typedef typename BaseType::ReactionEnumType ReactionEnumType;

  //! Typedef for the particle type
  typedef typename BaseType::ParticleStateType ParticleStateType;

  //! Destructor
  ~StandardFilledAdjointParticleGeometryModel()
  { /* ... */ }

  //! Get the total forward macroscopic cross section of a material
  double getMacroscopicTotalForwardCrossSection(
                                const Geometry::Model::EntityId cell,
                                const double energy ) const final override;

  //! Get the total forward macroscopic cross section of a material
  double getMacroscopicTotalForwardCrossSectionQuick(
                                const Geometry::Model::EntityId cell,
                                const double energy ) const final override;

  //! Get the total forward macroscopic cross section of a material
  using BaseType::getMacroscopicTotalForwardCrossSection;

  //! Get the total forward macroscopic cross section of a material
  using BaseType::getMacroscopicTotalForwardCrossSectionQuick;

  //! Get the adjoint weight factor
  double getAdjointWeightFactor( const ParticleStateType& particle ) const;

  //! Get the adjoint weight factor
  double getAdjointWeightFactor(
                                const Geometry::Model::EntityId cell,
                                const double energy ) const;

  //! Get the adjoint weight factor
  double getAdjointWeightFactorQuick( const ParticleStateType& particle ) const;

  //! Get the adjoint weight factor
  double getAdjointWeightFactorQuick(
                                const Geometry::Model::EntityId cell,
                                const double energy ) const;

  //! Get the critical line energies
  const std::vector<double>& getCriticalLineEnergies() const;
  
protected:

  //! Constructor
  using StandardFilledParticleGeometryModel<Material>::StandardFilledParticleGeometryModel;

  //! Process the loaded scattering centers
  void processLoadedScatteringCenters( const ScatteringCenterNameMap& scattering_centers ) final override;

private:

  // The critical line energies
  std::vector<double> d_critical_line_energies;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardFilledAdjointParticleGeometryModel_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_FILLED_ADJOINT_PARTICLE_GEOMETRY_MODEL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardFilledAdjointParticleGeometryModel.hpp
//---------------------------------------------------------------------------//
