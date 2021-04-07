//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointMaterial.hpp
//! \author Alex Robinson
//! \brief  Adjoint material base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_MATERIAL_HPP
#define MONTE_CARLO_ADJOINT_MATERIAL_HPP

// FRENSIE Includes
#include "MonteCarlo_Material.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

//! The adjoint material base class
template<typename ScatteringCenter>
class AdjointMaterial : public Material<ScatteringCenter>
{
  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

  // Typedef for the base type
  typedef Material<ScatteringCenter> BaseType;

  // Typedef for this type
  typedef AdjointMaterial<ScatteringCenter> ThisType;

public:

  //! The scattering center type
  typedef typename BaseType::ScatteringCenterType ScatteringCenterType;

  //! The reaction enum type
  typedef typename BaseType::ReactionEnumType ReactionEnumType;

  //! The particle state type
  typedef typename BaseType::ParticleStateType ParticleStateType;

  //! The material handle type
  typedef typename BaseType::MaterialId MaterialId;

  //! The scattering center name map
  typedef typename BaseType::ScatteringCenterNameMap ScatteringCenterNameMap;

  //! Destructor
  virtual ~AdjointMaterial()
  { /* ... */ }

  //! Return the critical line energies
  const std::vector<double>& getCriticalLineEnergies() const;

  //! Check if the energy corresponds to a line energy reaction
  bool doesEnergyHaveLineEnergyReaction( const double energy ) const;

  //! Return the macroscopic total cs at the desired line energy (1/cm)
  double getMacroscopicTotalLineEnergyCrossSection( const double energy) const;

  //! Return the macroscopic total forward cross section (1/cm)
  double getMacroscopicTotalForwardCrossSection( const double energy ) const;

  //! Return the adjoint weight factor
  double getAdjointWeightFactor( const double energy ) const;

  //! Return the adjoint line energy weight factor
  double getAdjointLineEnergyWeightFactor( const double energy ) const;

  //! Collide with a scattering center and survival bias
  void collideSurvivalBias( ParticleStateType& adjoint_particle,
                            ParticleBank& bank ) const final override;

  //! Collide with an adjoint photon at a line energy
  void collideAtLineEnergy( ParticleStateType& adjoint_particle,
                            ParticleBank& bank ) const;

protected:

  //! Constructor
  AdjointMaterial( const MaterialId id,
                   const double density,
                   const ScatteringCenterNameMap& scattering_center_name_map,
                   const std::vector<double>& scattering_center_fractions,
                   const std::vector<std::string>& scattering_center_names );

private:

  // Sample the atom that is collided with at a line energy
  size_t sampleCollisionAtomAtLineEnergy( const double energy ) const;

  // The ScatteringCenter::getTotalLineEnergyCrossSection function wrapper
  static typename BaseType::MicroscopicCrossSectionEvaluationFunctor
  s_total_line_energy_cs_evaluation_functor;

  // The ScatteringCenter::getTotalForwardCrossSection function wrapper
  static typename BaseType::MicroscopicCrossSectionEvaluationFunctor
  s_total_forward_cs_evaluation_functor;

  // The getMacroscopicTotalLineEnergyCrossSection function wrapper
  typename BaseType::MacroscopicCrossSectionEvaluationFunctor
  d_macroscopic_total_line_energy_cs_evaluation_functor;

  // The critical line energies
  std::vector<double> d_critical_line_energies;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_AdjointMaterial_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ADJOINT_MATERIAL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointMaterial.hpp
//---------------------------------------------------------------------------//
