//---------------------------------------------------------------------------//
//!
//! \file   Data_XSSElectronDataExtractor.cpp
//! \author Luke Kersting
//! \brief  XSS array (from ace table) electron condensed history extractor def
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_XSSElectronDataExtractor.hpp"
#include "Utility_ContractException.hpp"

namespace Data{

// Constructor
/*! \details A copy of the jxs array will be made so that it can be modified.
 * All indices in the jxs array correspond to a starting index of 1 (1 is
 * subtracted from all indices so that the correct array location is accessed).
 */ 
XSSElectronDataExtractor::XSSElectronDataExtractor(
				  const Teuchos::ArrayView<const int>& nxs,
				  const Teuchos::ArrayView<const int>& jxs,
				  const Teuchos::ArrayRCP<const double>& xss )
  : d_nxs( nxs ),
    d_jxs( jxs ),
    d_xss( xss )
{
  // Make sure the arrays have the correct size
  testPrecondition( nxs.size() == 16 );
  testPrecondition( jxs.size() == 11 );
  testPrecondition( xss.size() == nxs[0] );
  // Make sure the arrays were pulled from a table with the new el03 format
  testPrecondition( nxs[15] == 3 );

  // Adjust the indices in the JXS array so that they correspond to a C-array
  for( unsigned i = 0; i < d_jxs.size(); ++i )
    d_jxs[i] -= 1;
}

// Extract the atomic number
unsigned XSSElectronDataExtractor::extractAtomicNumber() const
{
  return d_nxs[0];
}

// Extract the K edge below which no electron induced relaxation will occur (edg)
double XSSElectronDataExtractor::extractKEdge() const
{
  return d_xss( d_jxs[0], 1 );
}

// Extract the Auger electron emission energy (eek) = (E_K - 2*E_L)
double XSSElectronDataExtractor::extractAugerEmissionEnergy() const
{
  return d_xss( d_jxs[0]+1, 1 );
}

// Extract the energy points for radiation stopping power interpolation
Teuchos::ArrayView<const double> 
XSSElectronDataExtractor::extractStoppingPowersBlock() const
{
  return d_xss( d_jxs[1], d_jxs[2] - d_jxs[1] );
}
  
// Extract the Mott scattering correction points data block
Teuchos::ArrayView<const double> 
XSSElectronDataExtractor::extractMottScatteringCorrectionBlock() const
{
  return d_xss( d_jxs[2], d_jxs[3] - d_jxs[2] );
}
  
// Extract the Riley scattering cross section data block
Teuchos::ArrayView<const double> 
XSSElectronDataExtractor::extractRileyBlock() const
{
  return d_xss( d_jxs[3], d_jxs[4] - d_jxs[3] );
}

// Extract the Bremsstrahlung interpolation data block
Teuchos::ArrayView<const double> 
XSSElectronDataExtractor::extractBremsstrahlungInterpolationBlock() const
{
  return d_xss( d_jxs[4], d_jxs[5] - d_jxs[4] );
}

// Extract the parameter used for riley cross section evaluation
double XSSElectronDataExtractor::extractRileyOffset() const
{
  return d_xss( d_jxs[6], d_jxs[7] - d_jxs[6] );
}

// Extract the atomic number (Z) to the power of 1/3
double XSSElectronDataExtractor::extractAtomicNumberToOneThirdPower() const
{
  return d_xss( d_jxs[7], 1 );
}

// Extract the log of the atomic number (Z)
double XSSElectronDataExtractor::extractAtomicNumberLog() const
{
  return d_xss( d_jxs[7] + 1, 1 );
}

// Extract a parameter dependent on the atomic number (Z) and atomic mass number (A)
Teuchos::ArrayView<const double> 
XSSElectronDataExtractor::extractAtomicNumberParameter() const
{
  return d_xss( d_jxs[7] + 2, 1 );
}

// Extract the photon to electron energy ratios for spectrum calculations (rkt)
Teuchos::ArrayView<const double> 
XSSElectronDataExtractor::extractRKTBlock() const
{
  return d_xss( d_jxs[8], d_nxs[8] );
}

// Extract the photon to electron energy ratios for angular distribution calculations (rka)
Teuchos::ArrayView<const double> 
XSSElectronDataExtractor::extractRKABlock() const
{
  return d_xss( d_jxs[9], d_nxs[9] );
}

// Extract the occupation number of electron for each level
Teuchos::ArrayView<const double> 
XSSElectronDataExtractor::extractOccupationNumbers() const
{
  return d_xss( d_jxs[10], d_nxs[10] );
}

// Extract the oscillator strength or binding energy for each level
Teuchos::ArrayView<const double> 
XSSElectronDataExtractor::extractBindingEnergy() const
{
  return d_xss( d_jxs[10] + d_nxs[10], d_nxs[10] );
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_XSSElectronDataExtractor.cpp
//---------------------------------------------------------------------------//
