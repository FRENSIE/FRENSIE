//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointMaterial_def.hpp
//! \author Alex Robinson
//! \brief  Adjoint material base class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_MATERIAL_DEF_HPP
#define MONTE_CARLO_ADJOINT_MATERIAL_DEF_HPP

// Std Lib Includes
#include <algorithm>

namespace MonteCarlo{

// Initialize static member data
template<typename ScatteringCenter>
typename Material<ScatteringCenter>::MicroscopicCrossSectionEvaluationFunctor
AdjointMaterial<ScatteringCenter>::s_total_line_energy_cs_evaluation_functor(
          std::bind<double>( &ScatteringCenter::getTotalLineEnergyCrossSection,
                             std::placeholders::_1,
                             std::placeholders::_2 ) );

template<typename ScatteringCenter>
typename Material<ScatteringCenter>::MicroscopicCrossSectionEvaluationFunctor
AdjointMaterial<ScatteringCenter>::s_total_forward_cs_evaluation_functor(
          std::bind<double>( &ScatteringCenter::getTotalForwardCrossSection,
                             std::placeholders::_1,
                             std::placeholders::_2 ) );

// Constructor
template<typename ScatteringCenter>
AdjointMaterial<ScatteringCenter>::AdjointMaterial(
                     const MaterialId id,
                     const double density,
                     const ScatteringCenterNameMap& scattering_center_name_map,
                     const std::vector<double>& scattering_center_fractions,
                     const std::vector<std::string>& scattering_center_names )
  : BaseType( id,
              density,
              scattering_center_name_map,
              scattering_center_fractions,
              scattering_center_names ),
    d_macroscopic_total_line_energy_cs_evaluation_functor(
       std::bind<double>( &ThisType::getMacroscopicTotalLineEnergyCrossSection,
                          std::cref(*this),
                          std::placeholders::_1 ) ),
    d_critical_line_energies()
{
  // Get the critical line energies used by all scattering centers
  std::set<double> critical_line_energies;

  for( size_t i = 0; i < this->getNumberOfScatteringCenters(); ++i )
  {
    const std::vector<double>& scattering_center_critical_line_energies =
      this->getScatteringCenter( i ).getCriticalLineEnergies();

    critical_line_energies.insert( scattering_center_critical_line_energies.begin(),
                                   scattering_center_critical_line_energies.end() );
  }

  d_critical_line_energies.assign( critical_line_energies.begin(),
                                   critical_line_energies.end() );

  std::sort( d_critical_line_energies.begin(),
             d_critical_line_energies.end() );
}

// Return the critical line energies
template<typename ScatteringCenter>
const std::vector<double>& AdjointMaterial<ScatteringCenter>::getCriticalLineEnergies() const
{
  return d_critical_line_energies;
}

// Check if the energy corresponds to a line energy reaction
template<typename ScatteringCenter>
bool AdjointMaterial<ScatteringCenter>::doesEnergyHaveLineEnergyReaction( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !QT::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  for( size_t i = 0; i < this->getNumberOfScatteringCenters(); ++i )
  {
    if( this->getScatteringCenter( i ).doesEnergyHaveLineEnergyReaction( energy ) )
      return true;
  }

  return false;
}

// Return the macroscopic total cs at the desired line energy (1/cm)
template<typename ScatteringCenter>
double AdjointMaterial<ScatteringCenter>::getMacroscopicTotalLineEnergyCrossSection( const double energy) const
{
  return this->getMacroscopicCrossSection(
                                   energy,
                                   s_total_line_energy_cs_evaluation_functor );
}

// Return the macroscopic total forward cross section (1/cm)
template<typename ScatteringCenter>
double AdjointMaterial<ScatteringCenter>::getMacroscopicTotalForwardCrossSection( const double energy ) const
{
  return this->getMacroscopicCrossSection(
                                       energy,
                                       s_total_forward_cs_evaluation_functor );
}

// Return the adjoint weight factor
template<typename ScatteringCenter>
double AdjointMaterial<ScatteringCenter>::getAdjointWeightFactor( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !QT::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double macroscopic_total_forward_cross_section =
    this->getMacroscopicTotalForwardCrossSection( energy );

  if( macroscopic_total_forward_cross_section > 0.0 )
  {
    return this->getMacroscopicTotalCrossSection( energy )/
      macroscopic_total_forward_cross_section;
  }
  else
    return 1.0;
}

// Return the adjoint line energy weight factor
template<typename ScatteringCenter>
double AdjointMaterial<ScatteringCenter>::getAdjointLineEnergyWeightFactor( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !QT::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double macroscopic_total_forward_cross_section =
    this->getMacroscopicTotalForwardCrossSection( energy );

  if( macroscopic_total_forward_cross_section > 0.0 )
  {
    return this->getMacroscopicTotalLineEnergyCrossSection( energy )/
      macroscopic_total_forward_cross_section;
  }
  else
    return 1.0;
}

// Collide with a scattering center and survival bias
/*! \details There are no absorption reactions associated with adjoint
 * particles so this method is identical to the analogue method.
 */
template<typename ScatteringCenter>
inline void AdjointMaterial<ScatteringCenter>::collideSurvivalBias(
                                           ParticleStateType& adjoint_particle,
                                           ParticleBank& bank ) const
{
  this->collideAnalogue( adjoint_particle, bank );
}

// Collide with an adjoint photon at a line energy
/*! \details This method should only be called with an adjoint particle that
 * is a probe. You must also check that a line energy reaction exists at the
 * particle's energy.
 */
template<typename ScatteringCenter>
void AdjointMaterial<ScatteringCenter>::collideAtLineEnergy(
                                           ParticleStateType& adjoint_particle,
                                           ParticleBank& bank ) const
{
  // Make sure that the particle is a probe
  testPrecondition( adjoint_particle.isProbe() );
  // Make sure that there are line energy reactions at the particle's energy
  testPrecondition( this->doesEnergyHaveLineEnergyReaction( adjoint_particle.getEnergy() ) );

  size_t sampled_index =
    this->sampleCollisionAtomAtLineEnergy( adjoint_particle.getEnergy() );

  this->getScatteringCenter( sampled_index ).collideAtLineEnergy( adjoint_particle, bank );
}

// Sample the atom that is collided with at a line energy
template<typename ScatteringCenter>
size_t AdjointMaterial<ScatteringCenter>::sampleCollisionAtomAtLineEnergy( const double energy ) const
{
  return this->sampleCollisionScatteringCenterImpl(
                 energy,
                 d_macroscopic_total_line_energy_cs_evaluation_functor,
                 s_total_line_energy_cs_evaluation_functor );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_MATERIAL_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointMaterial_def.hpp
//---------------------------------------------------------------------------//
