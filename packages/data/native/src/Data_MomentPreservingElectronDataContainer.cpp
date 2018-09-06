//---------------------------------------------------------------------------//
//!
//! \file   Data_MomentPreservingElectronDataContainer.cpp
//! \author Luke Kersting
//! \brief  The native moment preserving electron data container class def.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>
#include <fstream>
#include <sstream>
#include <typeinfo>

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "Data_MomentPreservingElectronDataContainer.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_DesignByContract.hpp"

namespace Data{

// Initialize static member data
const std::string MomentPreservingElectronDataContainer::s_archive_name( "container" );

// Constructor (from saved archive)
MomentPreservingElectronDataContainer::MomentPreservingElectronDataContainer(
                           const boost::filesystem::path& file_name_with_path )
{
  // Import the data in the archive
  this->loadFromFile( file_name_with_path );
}

// The database name used in an archive
const char* MomentPreservingElectronDataContainer::getArchiveName() const
{
  return s_archive_name.c_str();
}

// Return the atomic number
unsigned MomentPreservingElectronDataContainer::getAtomicNumber() const
{
  return d_atomic_number;
}

// Return the elastic cutoff angle cosine
double MomentPreservingElectronDataContainer::getCutoffAngleCosine() const
{
  return d_cutoff_angle_cosine;
}

// Return the elastic angular energy grid
const std::vector<double>&
MomentPreservingElectronDataContainer::getElasticAngularEnergyGrid() const
{
  return d_angular_energy_grid;
}

// Return the number of discrete angles for an angular energy bin
unsigned MomentPreservingElectronDataContainer::getNumberOfDiscreteAngles(
                            const unsigned angular_energy_bin ) const
{
  // Make sure the angular energy bin is valid
  testPrecondition( angular_energy_bin >= 0 );
  testPrecondition( angular_energy_bin < d_angular_energy_grid.size() );

  return d_number_of_discrete_angles.find( angular_energy_bin )->second;
}

// Return the moment preserving discrete angles for an angular energy bin
const std::vector<double>&
MomentPreservingElectronDataContainer::getMomentPreservingDiscreteAngles(
					        const unsigned angular_energy_bin ) const
{
  // Make sure the angular energy bin is valid
  testPrecondition( angular_energy_bin >= 0 );
  testPrecondition( angular_energy_bin < d_angular_energy_grid.size() );

  return d_moment_preserving_elastic_discrete_angles.find( angular_energy_bin )->second;
}

// Return the moment preserving weights for an angular energy bin
const std::vector<double>&
MomentPreservingElectronDataContainer::getMomentPreservingWeights(
					        const unsigned angular_energy_bin ) const
{
  // Make sure the angular energy bin is valid
  testPrecondition( angular_energy_bin >= 0 );
  testPrecondition( angular_energy_bin < d_angular_energy_grid.size() );

  return d_moment_preserving_elastic_weights.find( angular_energy_bin )->second;
}

// Set the atomic number
void MomentPreservingElectronDataContainer::setAtomicNumber(
						 const unsigned atomic_number )
{
  // Make sure the atomic number is valid
  testPrecondition( atomic_number > 0 );
  testPrecondition( atomic_number <= 100 );

  d_atomic_number = atomic_number;
}

// Set the elastic cutoff angle cosine
void MomentPreservingElectronDataContainer::setCutoffAngleCosine(
                         const double cutoff_angle_cosine )
{
  // Make sure the elastic cutoff angle cosine is valid
  testPrecondition( cutoff_angle_cosine > -1.0 );
  testPrecondition( cutoff_angle_cosine <= 1.0 );

  d_cutoff_angle_cosine = cutoff_angle_cosine;
}

// Set the elastic angular energy grid
void MomentPreservingElectronDataContainer::setElasticAngularEnergyGrid(
				       const std::vector<double>& angular_energy_grid )
{
  // Make sure the angular energy grid is valid
  testPrecondition( angular_energy_grid.size() > 0 );
  testPrecondition(
        Utility::Sort::isSortedAscending( angular_energy_grid.begin(),
			                              angular_energy_grid.end() ) );

  testPrecondition( std::find_if( angular_energy_grid.begin(),
                                  angular_energy_grid.end(),
                                  isValueLessThanOrEqualToZero ) ==
                    angular_energy_grid.end() );

  d_angular_energy_grid = angular_energy_grid;
}

// Set the number of discrete angles for an angular energy bin
void MomentPreservingElectronDataContainer::setNumberOfDiscreteAngles(
             const unsigned angular_energy_bin,
             const unsigned number_of_discrete_angles )
{
  // Make sure the angular_energy_bin is valid
  testPrecondition( angular_energy_bin >= 0 );
  testPrecondition( angular_energy_bin < d_angular_energy_grid.size() );
  // Make sure the number of discrete angles is valid
  testPrecondition( number_of_discrete_angles > 0 );

  d_number_of_discrete_angles[angular_energy_bin] = number_of_discrete_angles;
}

// Set the moment preserving discrete angles for an angular energy bin
void MomentPreservingElectronDataContainer::setMomentPreservingDiscreteAngles(
         const unsigned angular_energy_bin,
         const std::vector<double>& moment_preserving_elastic_discrete_angles )
{
  // Make sure the angular_energy_bin is valid
  testPrecondition( angular_energy_bin >= 0 );
  testPrecondition( angular_energy_bin < d_angular_energy_grid.size() );
  // Make sure the moment preserving discrete angles are valid
  testPrecondition( moment_preserving_elastic_discrete_angles.size() ==
               d_number_of_discrete_angles.find( angular_energy_bin )->second );
  testPrecondition( std::find_if( moment_preserving_elastic_discrete_angles.begin(),
                                  moment_preserving_elastic_discrete_angles.end(),
                                  isValueLessThanMinusOne ) ==
                    moment_preserving_elastic_discrete_angles.end() );
  testPrecondition( std::find_if( moment_preserving_elastic_discrete_angles.begin(),
                                  moment_preserving_elastic_discrete_angles.end(),
                                  isValueGreaterThanOne ) ==
                    moment_preserving_elastic_discrete_angles.end() );

  d_moment_preserving_elastic_discrete_angles[angular_energy_bin] =
        moment_preserving_elastic_discrete_angles;
}

// Set the moment preserving weights for an angular energy bin
void MomentPreservingElectronDataContainer::setMomentPreservingWeights(
			 const unsigned angular_energy_bin,
			 const std::vector<double>& moment_preserving_elastic_weights )
{
  // Make sure the angular_energy_bin is valid
  testPrecondition( angular_energy_bin >= 0 );
  testPrecondition( angular_energy_bin < d_angular_energy_grid.size() );
  // Make sure the weight is valid
  testPrecondition( moment_preserving_elastic_weights.size() ==
               d_number_of_discrete_angles.find( angular_energy_bin )->second );
  testPrecondition( std::find_if( moment_preserving_elastic_weights.begin(),
                                  moment_preserving_elastic_weights.end(),
                                  isValueLessThanZero ) ==
                    moment_preserving_elastic_weights.end() );
  testPrecondition( std::find_if( moment_preserving_elastic_weights.begin(),
                                  moment_preserving_elastic_weights.end(),
                                  isValueGreaterThanOne ) ==
                    moment_preserving_elastic_weights.end() );

  d_moment_preserving_elastic_weights[angular_energy_bin] = moment_preserving_elastic_weights;
}

EXPLICIT_CLASS_SAVE_LOAD_INST( MomentPreservingElectronDataContainer );

} // end Data namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( MomentPreservingElectronDataContainer, Data );

//---------------------------------------------------------------------------//
// end Data_MomentPreservingElectronDataContainer.cpp
//---------------------------------------------------------------------------//
