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

// FACEMC Includes
#include <LinearCongruentialGenerator.hpp>

// Time macro
#define TIME() (clock()/((double)CLOCKS_PER_SEC))

// Generator timing function
void timeGenerator( const int trial_size, const int histories = 1 )
{
  // Timing info
  double time1, time2, time3;
  
  boost::scoped_ptr<FACEMC::LinearCongruentialGenerator>
    generator( new FACEMC::LinearCongruentialGenerator );

  time1 = TIME();

  // Float generator timing
  for( int i = 0; i < histories; ++i )
  {
    for( int j = 0; j < trial_size/histories; ++j )
      generator->rnd<float>();

    generator->changeHistory( i+1 );
  }

  time2 = TIME();

  //Double generator timing
  for( int i = 0; i < histories; ++i )
  {
    for( int j = 0; j < trial_size/histories; ++j )
      generator->rnd<double>();

    generator->changeHistory( i+1 );
  }
  
  time3 = TIME();

  // Check for valid time intervals
  if( time2 - time1 < 1.0e-15 || time3 - time2 < 1.0e-15 )
  {
    std::cerr << "Timing information not accurate enough for this generator."
	      << std::endl;
  }
  else
  {
    // Calculate the generation speed (Millions/sec)
    double mflts_per_sec = trial_size/(time2-time1)/1e6;
    double mdbls_per_sec = trial_size/(time3-time2)/1e6;

    // Print the last double generated
    std::cout << "Last random number generated: " << generator->rnd<double>()
	      << std::endl
	      << "Random numbers per history: " << trial_size/histories
	      << std::endl
	      << "User + System time information (NOTE: MRS = Million Random "
	      << "Numbers Per Second)\n" << std::endl
	      << "  Float generator:\tTime = " << time2-time1 << " seconds "
	      << "=> " << mflts_per_sec << std::endl
	      << "  Double generator:\tTime = " << time3-time2 << " seconds "
	      << "=> " << mdbls_per_sec << std::endl << std::endl;
  }

  //delete generator;
}
      

// Main itming function
int main()
{
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
