//---------------------------------------------------------------------------//
//!
//! \file   dagfacemc_demo.cpp
//! \author Alex Robinson
//! \brief  This file is for demonstrating the ray tracing capabilities of 
//!         DAG-FACEMC.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>

// Trilinos Includes
#include <Teuchos_CommandLineProcessor.hpp>

// FACEMC Includes
#include "GeometryHandlerTraits.hpp"
#include "DagMCHelpers.hpp"
#include "ParticleState.hpp"
#include "RandomNumberGenerator.hpp"

template<typename ParticleState>
void initializeParticleState( ParticleState& particle )
{
  particle.setPosition( -40.0, -40.0, 59.0 );
  
  typedef FACEMC::RandomNumberGenerator RNG;

  // Sample the particle direction uniformly
  double rn1 = RNG::getRandomNumber<double>();
  double z_dir = -1.0 + 2.0*rn1;
  
  double rn2 = RNG::getRandomNumber<double>();
  double sin_theta = sqrt( 1.0 - z_dir*z_dir );
  double pi = acos( -1.0 );
  double x_dir = sin_theta*cos( 2.0*pi*rn2 );
  double y_dir = sin_theta*sin( 2.0*pi*rn2 );

  particle.setDirection( x_dir, y_dir, z_dir );
}

// Print out the ray history
template<typename ParticleState>
void printRayHistory( std::ostream& os, 
		      const std::vector<ParticleState>& ray_history,
		      const long int ray_history_number )
{  
  // Create the first vertex
  os << "create vertex x "  << ray_history[0].getXPosition()
     << " y " << ray_history[0].getYPosition()
     << " z " << ray_history[0].getZPosition()
     << std::endl;
  os << "vertex {Id('vertex')} rename 'vertex" << ray_history_number 
     << ".0'" << std::endl;
  
  // Create all remaining vertices
  for( unsigned i = 1; i < ray_history.size(); ++i )
  {
    // Create the vertex
    os << "create vertex x "  << ray_history[i].getXPosition()
     << " y " << ray_history[i].getYPosition()
     << " z " << ray_history[i].getZPosition()
     << std::endl;
    os << "vertex {Id('vertex')} rename 'vertex" << ray_history_number 
       << "." << i << "'" << std::endl;

    // Connect the previous vertex with this vertex
    os << "create curve vertex" << ray_history_number << "." << i-1 << ", "
       << "vertex" << ray_history_number << "." << i << std::endl;
  }
}

int main( int argc, char** argv )
{
  // The sat file name
  std::string sat_file_name;

  // The number of rays to fire
  long int num_rays_to_fire = 5;
  
  // Create the Teuchos command line processor
  Teuchos::CommandLineProcessor clp( false );
  clp.setOption( "sat_file_name", 
		 &sat_file_name, 
		 "File name of the CAD geometry (sat file)",
		 true );
  clp.setOption( "num_rays_to_fire",
		 &num_rays_to_fire,
		 "Number of random rays to fire." );
  
  // Parse the command line
  Teuchos::CommandLineProcessor::EParseCommandLineReturn
    parse_return = clp.parse( argc, argv );
  if( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL )
  {
    std::cout << "Parse error... ending" << std::endl;
    
    return parse_return;
  }

  // Open the journal file for visualizing particle tracks
  std::ofstream journal_file( "rays.jou" );

  // Set up the valid property names
  std::vector<std::string> property_names( 6 );
  property_names[0] = "graveyard";
  property_names[1] = "mat";
  property_names[2] = "rho";
  property_names[3] = "tally";
  property_names[4] = "cell.flux";
  property_names[5] = "surf.flux";

  // Initialize DagMC
  FACEMC::initializeDagMC( sat_file_name, property_names, 1e-3 );

  // The geometry handler traits class for DagMC
  typedef FACEMC::Traits::GeometryHandlerTraits<moab::DagMC> GHT;

  // The particle state that will be used for ray firing
  FACEMC::ParticleState<typename GHT::CellHandle> particle( 1ull );
  particle.setParticleType( FACEMC::PHOTON );
  
  // Initialize the random number generator
  FACEMC::RandomNumberGenerator::initialize();

  // Trace the number of rays requested
  for( long int i = 0; i < num_rays_to_fire; ++i )
  {						       
    // Initialize the particle state
    initializeParticleState( particle );

    // Store the ray history
    std::vector<FACEMC::ParticleState<typename GHT::CellHandle> > ray_history;

    // Find the starting cell of the particle
    GHT::updateCellContainingParticle( particle );

    ray_history.push_back( particle );

    // Trace the particle (ray) until it exits the geometry
    while( !GHT::isTerminationCell( particle.getCell() ) )
    {
      typename GHT::SurfaceHandle surface_hit;
      double distance_to_surface_hit;

      // Fire a ray through the geometry
      GHT::fireRay( particle, surface_hit, distance_to_surface_hit );
      
      // Move the particle to the intersection point
      particle.advance( distance_to_surface_hit );

      ray_history.push_back( particle );

      // Find the cell that the particle enters
      GHT::updateCellContainingParticle( surface_hit, particle );
    }

    // Print out the ray history
    printRayHistory( journal_file, ray_history, i );
  }
  
  return 0;
}
