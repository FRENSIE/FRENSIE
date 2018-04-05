//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointMaterial_def.hpp
//! \author Alex Robinson
//! \brief  Adjoint material base class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_MATERIAL_DEF_HPP
#define MONTE_CARLO_ADJOINT_MATERIAL_DEF_HPP

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
                     const InternalMaterialHandle id,
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
                          std::placeholders::_1 ) )
{ /* ... */ }

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

  double weight_factor;

  double macroscopic_total_forward_cross_section =
    this->getMacroscopicTotalForwardCrossSection( energy );

  if( macroscopic_total_forward_cross_section > 0.0 )
  {
    weight_factor = this->getMacroscopicTotalCrossSection( energy )/
      this->getMacroscopicTotalForwardCrossSection( energy );
  }
  else
    weight_factor = 1.0;

  // Make sure that the weight factor is valid
  testPrecondition( weight_factor > 0.0 );

  return weight_factor;
}

// Return the adjoint line energy weight factor
template<typename ScatteringCenter>
double AdjointMaterial<ScatteringCenter>::getAdjointLineEnergyWeightFactor( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !QT::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double weight_factor;

  double macroscopic_total_forward_cross_section =
    this->getMacroscopicTotalForwardCrossSection( energy );

  if( macroscopic_total_forward_cross_section > 0.0 )
  {
    weight_factor = this->getMacroscopicTotalLineEnergyCrossSection( energy )/
      this->getMacroscopicTotalForwardCrossSection( energy );
  }
  else
    weight_factor = 1.0;

  // Make sure the weight factor is valid
  testPostcondition( weight_factor >= 0.0 );

  return weight_factor;
}

// Collide with an adjoint photon at a line energy
template<typename ScatteringCenter>
void AdjointMaterial<ScatteringCenter>::collideAtLineEnergy( 
                   typename ScatteringCenter::ParticleStateType& adjoint_photon,
                   ParticleBank& bank ) const
{
  // Make sure that the particle is a probe
  testPrecondition( adjoint_photon.isProbe() );
  // Make sure that there are line energy reactions at the particle's energy
  testPrecondition( this->doesEnergyHaveLineEnergyReaction( adjoint_photon.getEnergy() ) );
  
  size_t sampled_index =
    this->sampleCollisionAtomAtLineEnergy( adjoint_photon.getEnergy() );

  this->getScatteringCenter( sampled_index ).collideAtLineEnergy( adjoint_photon, bank );
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
