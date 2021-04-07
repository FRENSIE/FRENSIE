//---------------------------------------------------------------------------//
//!
//! \file   rng_timer.cpp
//! \author Alex Robinon
//! \brief  Main function for timing custom random number generator
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <time.h>

// Boost Scoped Pointer
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Utility_RandomNumberGenerator.hpp"

// Time macro
#define TIME() (clock()/((double)CLOCKS_PER_SEC))

// Generator timing function
void timeGenerator( const int trial_size, const int histories = 1 )
{
  // Raw generator
  Utility::LinearCongruentialGenerator generator;

  double time1 = TIME();

  // Wrapped double generator timing
  for( int i = 0; i < histories; ++i )
  {
    Utility::RandomNumberGenerator::initialize( i );

    for( int j = 0; j < trial_size/histories; ++j )
      Utility::RandomNumberGenerator::getRandomNumber<double>();
  }
  std::cout << std::endl;

  double time2 = TIME();

  // Raw double generator timing
  for( int i = 0; i < histories; ++i )
  {
    for( int j = 0; j < trial_size/histories; ++j )
      generator.getRandomNumber();

    generator.nextHistory();
  }

  double time3 = TIME();

  // Check for valid time intervals
  if( time2 - time1 < 1.0e-15 || time3 - time2 < 1.0e-15 )
  {
    std::cerr << "Timing information not accurate enough for this generator."
	      << std::endl;
  }
  else
  {
    // Calculate the generation speed (Millions/sec)
    double mdbls_per_sec_wrapped = trial_size/(time2-time1)/1e6;
    double mdbls_per_sec_raw = trial_size/(time3-time2)/1e6;

    // Print the last double generated
    std::cout << "Last random number generated: "
	      << generator.getRandomNumber() << " "
	      << Utility::RandomNumberGenerator::getRandomNumber<double>()
	      << std::endl
	      << "Random numbers per history: " << trial_size/histories
	      << std::endl
	      << "User + System time information (NOTE: MRS = Million Random "
	      << "Numbers Per Second)\n" << std::endl
	      << "  Wrapped Double generator:\tTime = " << time2-time1
	      << " seconds " << "=> " << mdbls_per_sec_wrapped
	      << std::endl
	      << "  Raw Double generator:\t\tTime = " << time3-time2
	      << " seconds " << "=> " << mdbls_per_sec_raw
	      << std::endl << std::endl;
  }
}


// Main itming function
int main()
{
  Utility::RandomNumberGenerator::createStreams();

  Utility::RandomNumberGenerator::initialize();

  int trial_size = 10000000;

  std::cout << "Timing generator for single history" << std::endl;
  timeGenerator( trial_size );

  std::cout << "Timing generator for 10 histories" << std::endl;
  timeGenerator( trial_size, 10 );

  std::cout << "Timing generator for 100 histories" << std::endl;
  timeGenerator( trial_size, 100 );

  std::cout << "Timing generator for 1000 histories" << std::endl;
  timeGenerator( trial_size, 1000 );

  return 0;
}

//---------------------------------------------------------------------------//
// end rng_timer.cpp
//---------------------------------------------------------------------------//
