//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardFilledAdjointParticleGeometryModel_def.hpp
//! \author Alex Robinson
//! \brief  The standard filled adjoint particle geometry model class def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_FILLED_ADJOINT_PARTICLE_GEOMETRY_MODEL_DEF_HPP
#define MONTE_CARLO_STANDARD_FILLED_ADJOINT_PARTICLE_GEOMETRY_MODEL_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Get the total forward macroscopic cross section of a material
template<typename Material>
double StandardFilledAdjointParticleGeometryModel<Material>::getMacroscopicTotalForwardCrossSection(
                                const Geometry::Model::InternalCellHandle cell,
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
                                const Geometry::Model::InternalCellHandle cell,
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
                                const Geometry::Model::InternalCellHandle cell,
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
                                const Geometry::Model::InternalCellHandle cell,
                                const double energy ) const
{
  // Make sure that the cell is not void
  testPrecondition( !this->isCellVoid( cell ) );

  return this->getMaterial( cell )->getAdjointWeightFactor( energy );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_FILLED_ADJOINT_PARTICLE_GEOMETRY_MODEL_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardFilledAdjointParticleGeometryModel_def.hpp
//---------------------------------------------------------------------------//

