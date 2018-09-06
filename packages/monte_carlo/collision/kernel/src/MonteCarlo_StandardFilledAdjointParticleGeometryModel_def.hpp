//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardFilledAdjointParticleGeometryModel_def.hpp
//! \author Alex Robinson
//! \brief  The standard filled adjoint particle geometry model class def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_FILLED_ADJOINT_PARTICLE_GEOMETRY_MODEL_DEF_HPP
#define MONTE_CARLO_STANDARD_FILLED_ADJOINT_PARTICLE_GEOMETRY_MODEL_DEF_HPP

// Std Lib Includes
#include <algorithm>

// FRENSIE Includes
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Get the total forward macroscopic cross section of a material
template<typename Material>
double StandardFilledAdjointParticleGeometryModel<Material>::getMacroscopicTotalForwardCrossSection(
                                const Geometry::Model::EntityId cell,
                                const double energy ) const
{
  if( this->isCellVoid( cell ) )
    return 0.0;
  else
    return this->getMaterial( cell )->getMacroscopicTotalForwardCrossSection( energy );
}

// Get the total forward macroscopic cross section of a material
/*! \details Before calling this method you must first check if the cell
 * is void. Calling this method with a void cell is not allowed.
 */
template<typename Material>
double StandardFilledAdjointParticleGeometryModel<Material>::getMacroscopicTotalForwardCrossSectionQuick(
                                const Geometry::Model::EntityId cell,
                                const double energy ) const
{
  // Make sure that the cell is not void
  testPrecondition( !this->isCellVoid( cell ) );

  return this->getMaterial( cell )->getMacroscopicTotalForwardCrossSection( energy );
}

// Get the adjoint weight factor
template<typename Material>
double StandardFilledAdjointParticleGeometryModel<Material>::getAdjointWeightFactor( const ParticleStateType& particle ) const
{
  return this->getAdjointWeightFactor( particle.getCell(),
                                       particle.getEnergy() );
}

// Get the adjoint weight factor
template<typename Material>
double StandardFilledAdjointParticleGeometryModel<Material>::getAdjointWeightFactor(
                                const Geometry::Model::EntityId cell,
                                const double energy ) const
{
  // We don't want to modify the particle weight if the cell is void
  if( this->isCellVoid( cell ) )
    return 1.0; 
  else
    return this->getMaterial( cell )->getAdjointWeightFactor( energy );    
}

// Get the adjoint weight factor
/*! \details Before calling this method you must first check if the cell
 * is void. Calling this method with a void cell is not allowed.
 */
template<typename Material>
double StandardFilledAdjointParticleGeometryModel<Material>::getAdjointWeightFactorQuick( const ParticleStateType& particle ) const
{
  return this->getAdjointWeightFactorQuick( particle.getCell(),
                                            particle.getEnergy() );
}

// Get the adjoint weight factor
/*! \details Before calling this method you must first check if the cell
 * is void. Calling this method with a void cell is not allowed.
 */
template<typename Material>
double StandardFilledAdjointParticleGeometryModel<Material>::getAdjointWeightFactorQuick(
                                const Geometry::Model::EntityId cell,
                                const double energy ) const
{
  // Make sure that the cell is not void
  testPrecondition( !this->isCellVoid( cell ) );

  return this->getMaterial( cell )->getAdjointWeightFactor( energy );
}

// Process loaded scattering centers
template<typename Material>
void StandardFilledAdjointParticleGeometryModel<Material>::processLoadedScatteringCenters(
                            const ScatteringCenterNameMap& scattering_centers )
{
  // Get the critical line energies used by all scattering centers
  std::set<double> critical_line_energies;

  for( auto scattering_center : scattering_centers )
  {
    const std::vector<double>& scattering_center_critical_line_energies =
      scattering_center.second->getCriticalLineEnergies();

    critical_line_energies.insert( scattering_center_critical_line_energies.begin(),
                                   scattering_center_critical_line_energies.end() );
  }

  d_critical_line_energies.assign( critical_line_energies.begin(),
                                   critical_line_energies.end() );

  std::sort( d_critical_line_energies.begin(),
             d_critical_line_energies.end() );
}

// Get the critical line energies
template<typename Material>
const std::vector<double>& StandardFilledAdjointParticleGeometryModel<Material>::getCriticalLineEnergies() const
{
  return d_critical_line_energies;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_FILLED_ADJOINT_PARTICLE_GEOMETRY_MODEL_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardFilledAdjointParticleGeometryModel_def.hpp
//---------------------------------------------------------------------------//

