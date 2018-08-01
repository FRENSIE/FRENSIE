//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Material_def.hpp
//! \author Alex Robinson
//! \brief  Material base class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_MATERIAL_DEF_HPP
#define MONTE_CARLO_MATERIAL_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_MaterialHelpers.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Initialize static member data
template<typename ScatteringCenter>
typename Material<ScatteringCenter>::MicroscopicCrossSectionEvaluationFunctor
Material<ScatteringCenter>::s_total_cs_evaluation_functor(
                                  std::bind<double>( static_cast<double(ScatteringCenter::*)(const double) const>(&ScatteringCenter::getTotalCrossSection),
                                                     std::placeholders::_1,
                                                     std::placeholders::_2 ) );

template<typename ScatteringCenter>
typename Material<ScatteringCenter>::MicroscopicCrossSectionEvaluationFunctor
Material<ScatteringCenter>::s_absorption_cs_evaluation_functor(
                                std::bind<double>( static_cast<double(ScatteringCenter::*)(const double) const>(&ScatteringCenter::getAbsorptionCrossSection),
                                                   std::placeholders::_1,
                                                   std::placeholders::_2 ) );

// Constructor (without photonuclear data)
template<typename ScatteringCenter>
Material<ScatteringCenter>::Material(
		     const MaterialId id,
                     const double density,
                     const ScatteringCenterNameMap& scattering_center_name_map,
                     const std::vector<double>& scattering_center_fractions,
                     const std::vector<std::string>& scattering_center_names )
  : d_id( id ),
    d_number_density( density ),
    d_scattering_centers( scattering_center_fractions.size() ),
    d_scattering_center_names(),
    d_macroscopic_total_cs_evaluation_functor(
                 std::bind<double>( &ThisType::getMacroscopicTotalCrossSection,
                                    std::cref(*this),
                                    std::placeholders::_1 ) )
{
  // Make sure the id is valid
  testPrecondition( ThisType::isIdValid( id ) );
  // Make sure the density is valid
  testPrecondition( density != 0.0 );
  // Make sure the fraction values are valid (all positive or all negative)
  testPrecondition(
     MonteCarlo::areFractionValuesValid( scattering_center_fractions.begin(),
                                         scattering_center_fractions.end() ) );
  testPrecondition( scattering_center_fractions.size() ==
                    scattering_center_names.size() );

  // Copy (shallow) the scattering centers that make up this material
  for( size_t i = 0u; i < scattering_center_fractions.size(); ++i )
  {
    Utility::get<0>( d_scattering_centers[i] ) = scattering_center_fractions[i];

    typename ScatteringCenterNameMap::const_iterator scattering_center =
      scattering_center_name_map.find( scattering_center_names[i] );

    TEST_FOR_EXCEPTION( scattering_center == scattering_center_name_map.end(),
			std::runtime_error,
			"scattering center " << scattering_center_names[i] <<
			" has not been loaded!" );

    Utility::get<1>( d_scattering_centers[i] ) = scattering_center->second;

    TEST_FOR_EXCEPTION( d_scattering_center_names.find( scattering_center_names[i] ) != d_scattering_center_names.end(),
                        std::runtime_error,
                        "scattering center " << scattering_center_names[i] <<
                        " is already used by the material" << id << "!" );
    
    d_scattering_center_names[scattering_center_names[i]] = i;
  }

  // Convert weight fractions to atom fractions
  if( Utility::get<0>( d_scattering_centers.front() ) < 0.0 )
  {
    MonteCarlo::convertWeightFractionsToAtomFractions<0,1>(
					  d_scattering_centers.begin(),
                                          d_scattering_centers.end(),
                                          d_scattering_centers.begin(),
                                          d_scattering_centers.end(),
				          &ThisType::getAtomicWeightFromPair );
  }
  else // Normalize the atom fractions
  {
    MonteCarlo::normalizeFractionValues<0>( d_scattering_centers.begin(),
                                            d_scattering_centers.end() );
  }

  // Convert the mass density to a number density
  if( density < 0.0 )
  {
    d_number_density =
      MonteCarlo::convertMassDensityToNumberDensity<0,1>(
				          -1.0*density,
                                          d_scattering_centers.begin(),
                                          d_scattering_centers.end(),
                                          d_scattering_centers.begin(),
                                          d_scattering_centers.end(),
				          &ThisType::getAtomicWeightFromPair );
  }

  // Convert the atom fractions to isotopic number densities
  MonteCarlo::scaleAtomFractionsByNumberDensity<0>(
                                                  d_number_density,
                                                  d_scattering_centers.begin(),
                                                  d_scattering_centers.end() );
}

// Check if an id is valid
template<typename ScatteringCenter>
bool Material<ScatteringCenter>::isIdValid( const MaterialId id )
{
  return id < std::numeric_limits<MaterialId>::max();
}

// Return the material id
template<typename ScatteringCenter>
auto Material<ScatteringCenter>::getId() const -> MaterialId
{
  return d_id;
}

// Return the number density (atom/b-cm)
template<typename ScatteringCenter>
double Material<ScatteringCenter>::getNumberDensity() const
{
  return d_number_density;
}

// Return the scattering center at the desired index
template<typename ScatteringCenter>
const std::shared_ptr<const ScatteringCenter>&
Material<ScatteringCenter>::getScatteringCenter( const std::string& name ) const
{
  std::map<std::string,size_t>::const_iterator scattering_center_name_it =
    d_scattering_center_names.find( name );
    
  TEST_FOR_EXCEPTION( scattering_center_name_it == d_scattering_center_names.end(),
                      std::runtime_error,
                      "Material " << d_id << " does not have a scattering "
                      "center with the name " << name << "!" );

  const size_t index = scattering_center_name_it->second;

  return Utility::get<1>( d_scattering_centers[index] );
}

// Return the scattering center number density
template<typename ScatteringCenter>
double Material<ScatteringCenter>::getScatteringCenterNumberDensity( const std::string& name ) const
{
  std::map<std::string,size_t>::const_iterator scattering_center_name_it =
    d_scattering_center_names.find( name );
    
  TEST_FOR_EXCEPTION( scattering_center_name_it == d_scattering_center_names.end(),
                      std::runtime_error,
                      "Material " << d_id << " does not have a scattering "
                      "center with the name " << name << "!" );

  const size_t index = scattering_center_name_it->second;

  return Utility::get<0>( d_scattering_centers[index] );
}

// Return the macroscopic total cross section (1/cm)
template<typename ScatteringCenter>
double Material<ScatteringCenter>::getMacroscopicTotalCrossSection(
						    const double energy ) const
{
  return this->getMacroscopicCrossSection( energy,
                                           s_total_cs_evaluation_functor );
}

// Return the macroscopic absorption cross section (1/cm)
template<typename ScatteringCenter>
double Material<ScatteringCenter>::getMacroscopicAbsorptionCrossSection(
						    const double energy ) const
{
  return this->getMacroscopicCrossSection(
                                          energy,
                                          s_absorption_cs_evaluation_functor );
}

// Return the macroscopic cross section (1/cm) for a specific reaction
template<typename ScatteringCenter>
double Material<ScatteringCenter>::getMacroscopicReactionCrossSection(
	      const double energy,
	      const typename ScatteringCenter::ReactionEnumType reaction ) const
{
  // Note: We must cast the getReactionCrossSection method to the exact
  // function signature to avoid unresolved overloaded type errors due to the
  // ScatteringCenterType having a getReactionCrossSection overload

  return this->getMacroscopicCrossSection(
                              energy,
                              std::bind<double>( static_cast<double (ScatteringCenter::*)(const double, const typename ScatteringCenter::ReactionEnumType) const>(&ScatteringCenter::getReactionCrossSection),
                                                 std::placeholders::_1,
                                                 std::placeholders::_2,
                                                 reaction ) );
}

// Return the macroscopic cross section
template<typename ScatteringCenter>
double Material<ScatteringCenter>::getMacroscopicCrossSection(
  const double energy,
  const MicroscopicCrossSectionEvaluationFunctor& cs_evaluation_functor ) const
{
  // Make sure the energy is valid
  testPrecondition( !QT::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double cross_section = 0.0;

  for( size_t i = 0u; i < d_scattering_centers.size(); ++i )
  {
    cross_section += Utility::get<0>( d_scattering_centers[i] )*
      cs_evaluation_functor( *Utility::get<1>( d_scattering_centers[i] ),
                             energy );
  }

  return cross_section;
}

// Return the survival probability
template<typename ScatteringCenter>
double Material<ScatteringCenter>::getSurvivalProbability( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !QT::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double survival_prob;
  double total_cross_sec = this->getMacroscopicTotalCrossSection( energy );

  if( total_cross_sec > 0.0 )
  {
    survival_prob = 1.0 -
      this->getMacroscopicAbsorptionCrossSection( energy )/total_cross_sec;
  }
  else
    survival_prob = 1.0;

  // Make sure the survival probability is valid
  testPostcondition( !QT::isnaninf( survival_prob ) );
  testPostcondition( survival_prob >= 0.0 );
  testPostcondition( survival_prob <= 1.0 );

  return survival_prob;
}

// Get the absorption reaction types
template<typename ScatteringCenter>
void Material<ScatteringCenter>::getAbsorptionReactionTypes( ReactionEnumTypeSet& reaction_types ) const
{
  for( size_t i = 0; i < d_scattering_centers.size(); ++i )
  {
    Utility::get<1>(d_scattering_centers[i])->getAbsorptionReactionTypes(
                                                              reaction_types );
  }
}

// Get the scattering reaction types
template<typename ScatteringCenter>
void Material<ScatteringCenter>::getScatteringReactionTypes( ReactionEnumTypeSet& reaction_types ) const
{
  for( size_t i = 0; i < d_scattering_centers.size(); ++i )
  {
    Utility::get<1>(d_scattering_centers[i])->getScatteringReactionTypes(
                                                              reaction_types );
  }
}

// Get the miscellaneous reaction types
template<typename ScatteringCenter>
void Material<ScatteringCenter>::getMiscReactionTypes( ReactionEnumTypeSet& reaction_types ) const
{
  for( size_t i = 0; i < d_scattering_centers.size(); ++i )
  {
    Utility::get<1>(d_scattering_centers[i])->getMiscReactionTypes(
                                                              reaction_types );
  }
}

// Get the reaction types
template<typename ScatteringCenter>
void Material<ScatteringCenter>::getReactionTypes( ReactionEnumTypeSet& reaction_types ) const
{
  for( size_t i = 0; i < d_scattering_centers.size(); ++i )
  {
    Utility::get<1>(d_scattering_centers[i])->getReactionTypes(
                                                              reaction_types );
  }
}

// Collide with a photon
template<typename ScatteringCenter>
void Material<ScatteringCenter>::collideAnalogue( ParticleStateType& particle,
                                                  ParticleBank& bank ) const
{
  size_t atom_index =
    this->sampleCollisionScatteringCenter( particle.getEnergy() );

  Utility::get<1>(d_scattering_centers[atom_index])->collideAnalogue(
                                                              particle, bank );
}

// Collide with a photon and survival bias
/*! \details The method of survival biasing that has been implemented is to
 * first select the nuclide that is collided with. The particle weight is
 * then multiplied by the survival probability associated with the
 * microscopic cross sections for the collision nuclide. An alternative method
 * would be to multiply the weight of the particle by the macroscopic
 * survival probability associated with the material and then sample a
 * collision nuclide. The latter method appears to be more involved than the
 * former, which is why the former was chosen.
 */
template<typename ScatteringCenter>
void Material<ScatteringCenter>::collideSurvivalBias(
                                                   ParticleStateType& particle,
                                                   ParticleBank& bank ) const
{
  size_t atom_index =
    this->sampleCollisionScatteringCenter( particle.getEnergy() );

  Utility::get<1>(d_scattering_centers[atom_index])->collideSurvivalBias(
                                                              particle, bank );
}

// Return the number of scattering centers
template<typename ScatteringCenter>
size_t Material<ScatteringCenter>::getNumberOfScatteringCenters() const
{
  return d_scattering_centers.size();
}

// Return the scattering center at the desired index
template<typename ScatteringCenter>
const ScatteringCenter& Material<ScatteringCenter>::getScatteringCenter( const size_t index ) const
{
  testPrecondition( index < d_scattering_centers.size() );

  return *Utility::get<1>( d_scattering_centers[index] );
}

// Get the atomic weight from an atom pointer
template<typename ScatteringCenter>
double Material<ScatteringCenter>::getAtomicWeightFromPair(
       const std::pair<double,std::shared_ptr<const ScatteringCenter> >& pair )
{
  return Utility::get<1>(pair)->getAtomicWeight();
}

// Sample the collision atom
template<typename ScatteringCenter>
size_t Material<ScatteringCenter>::sampleCollisionScatteringCenterImpl(
                           const double energy,
                           const MacroscopicCrossSectionEvaluationFunctor&
                           macroscopic_total_cs_evaluation_functor,
                           const MicroscopicCrossSectionEvaluationFunctor&
                           total_cs_evaluation_functor ) const
{
  double scaled_random_number =
    Utility::RandomNumberGenerator::getRandomNumber<double>()*
    macroscopic_total_cs_evaluation_functor( energy );

  double partial_total_cs = 0.0;

  size_t collision_scattering_center_index =
    std::numeric_limits<size_t>::max();

  for( size_t i = 0u; i < d_scattering_centers.size(); ++i )
  {
    partial_total_cs +=
      Utility::get<0>( d_scattering_centers[i] )*
      total_cs_evaluation_functor( *Utility::get<1>( d_scattering_centers[i] ),
                                   energy );

    if( scaled_random_number < partial_total_cs )
    {
      collision_scattering_center_index = i;

      break;
    }
  }

  // Make sure a collision index was found
  testPostcondition( collision_scattering_center_index !=
		     std::numeric_limits<size_t>::max() );

  return collision_scattering_center_index;
}

// Sample the atom that is collided with
template<typename ScatteringCenter>
size_t Material<ScatteringCenter>::sampleCollisionScatteringCenter( const double energy ) const
{
  return this->sampleCollisionScatteringCenterImpl(
                                     energy,
                                     d_macroscopic_total_cs_evaluation_functor,
                                     s_total_cs_evaluation_functor );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_MATERIAL_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_Material_def.hpp
//---------------------------------------------------------------------------//
