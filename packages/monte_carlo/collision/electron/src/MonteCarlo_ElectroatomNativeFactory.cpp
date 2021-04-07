//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomNativeFactory.cpp
//! \author Luke Kersting
//! \brief  The electroatom native factory class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ElectroatomNativeFactory.hpp"
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Create a electroatom (using the provided atomic relaxation model)
/*! \details The provided atomic relaxation model will be used with this
 * atom. Special care must be taken to assure that the model corresponds to
 * the atom of interest. If the use of atomic relaxation data has been
 * requested, a electroionization reaction for each subshell will be created.
 * Otherwise a single total electroionization reaction will be created.
 */
void ElectroatomNativeFactory::createElectroatom(
       const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
       const std::string& electroatom_name,
       const double atomic_weight,
       const std::shared_ptr<const AtomicRelaxationModel>& atomic_relaxation_model,
       const SimulationElectronProperties& properties,
       std::shared_ptr<const Electroatom>& electroatom )
{
  // Make sure the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );
  // Make sure the atomic relaxation model is valid
  testPrecondition( atomic_relaxation_model.get() );

  std::shared_ptr<const ElectroatomCore> core;

  TwoDInterpolationType electron_interp = properties.getElectronTwoDInterpPolicy();

  TwoDGridType grid_policy = properties.getElectronTwoDGridPolicy();

  // Create the electroatom core
  /*! \todo Once testing for the proper 2D interp and sampling policies is
   * finished, these if else statements should be removed and replaced with the
   * default policies.
   */
  if( electron_interp == LOGLOGLOG_INTERPOLATION )
  {
    if( grid_policy == UNIT_BASE_CORRELATED_GRID )
    {
      ThisType::createElectroatomCore<Utility::LogLogLog,Utility::UnitBaseCorrelated>(
                              raw_electroatom_data,
                              atomic_relaxation_model,
                              properties,
                              core );
    }
    else if( grid_policy == CORRELATED_GRID )
    {
      ThisType::createElectroatomCore<Utility::LogLogLog,Utility::Correlated>(
                              raw_electroatom_data,
                              atomic_relaxation_model,
                              properties,
                              core );
    }
    else if( grid_policy == UNIT_BASE_GRID )
    {
      ThisType::createElectroatomCore<Utility::LogLogLog,Utility::UnitBase>(
                              raw_electroatom_data,
                              atomic_relaxation_model,
                              properties,
                              core );
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error, "the bivariate grid policy "
                       << grid_policy << " is not currently supported!" );
    }
  }
  else if( electron_interp == LINLINLIN_INTERPOLATION )
  {
    if( grid_policy == UNIT_BASE_CORRELATED_GRID )
    {
      ThisType::createElectroatomCore<Utility::LinLinLin,Utility::UnitBaseCorrelated>(
                              raw_electroatom_data,
                              atomic_relaxation_model,
                              properties,
                              core );
    }
    else if( grid_policy == CORRELATED_GRID )
    {
      ThisType::createElectroatomCore<Utility::LinLinLin,Utility::Correlated>(
                              raw_electroatom_data,
                              atomic_relaxation_model,
                              properties,
                              core );
    }
    else if( grid_policy == UNIT_BASE_GRID )
    {
      ThisType::createElectroatomCore<Utility::LinLinLin,Utility::UnitBase>(
                              raw_electroatom_data,
                              atomic_relaxation_model,
                              properties,
                              core );
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error, "the 2D sampling policy "
                       << grid_policy << " is not currently supported!" );
    }
  }
  else if( electron_interp == LINLINLOG_INTERPOLATION )
  {
    if( grid_policy == UNIT_BASE_CORRELATED_GRID )
    {
      ThisType::createElectroatomCore<Utility::LinLinLog,Utility::UnitBaseCorrelated>(
                              raw_electroatom_data,
                              atomic_relaxation_model,
                              properties,
                              core );
    }
    else if( grid_policy == CORRELATED_GRID )
    {
      ThisType::createElectroatomCore<Utility::LinLinLog,Utility::Correlated>(
                              raw_electroatom_data,
                              atomic_relaxation_model,
                              properties,
                              core );
    }
    else if( grid_policy == UNIT_BASE_GRID )
    {
      ThisType::createElectroatomCore<Utility::LinLinLog,Utility::UnitBase>(
                              raw_electroatom_data,
                              atomic_relaxation_model,
                              properties,
                              core );
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error, "the bivariate grid policy "
                       << grid_policy << " is not currently supported!" );
    }
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error, "the 2D interpolation policy "
                      << electron_interp << " is not currently supported!" );
  }



  // Create the electroatom
  electroatom.reset( new Electroatom( electroatom_name,
                                      raw_electroatom_data.getAtomicNumber(),
                                      atomic_weight,
                                      *core ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomNativeFactory.cpp
//---------------------------------------------------------------------------//
