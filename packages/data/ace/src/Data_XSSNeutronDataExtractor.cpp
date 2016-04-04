//---------------------------------------------------------------------------//
//!
//! \file   Data_XSSNeutronDataExtractor.cpp
//! \author Alex Robinson
//! \brief  XSS array (from ace table) neutron data extractor class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace Data{

// Constructor
/*! \details A copy of the jxs array will be made so that it can be modified. 
 * All indices in the jxs array correspond to a starting index of 1 (1 is 
 * subtracted from all indices so that the correct array location is accessed).
 */
XSSNeutronDataExtractor::XSSNeutronDataExtractor( 
				  const Teuchos::ArrayView<const int>& nxs,
				  const Teuchos::ArrayView<const int>& jxs,
		                  const Teuchos::ArrayRCP<const double>& xss )
  : d_nxs( nxs ),
    d_jxs( jxs ),
    d_xss( xss )
{
  // Make sure the array have the correct size
  testPrecondition( nxs.size() == 16 );
  testPrecondition( jxs.size() == 32 );
  testPrecondition( xss.size() == nxs[0] );

  // Adjust the indices in the JXS array so that they correspond to a C-array
  for( unsigned i = 0; i < d_jxs.size(); ++i )
    d_jxs[i] -= 1;

  // Extract and cache the ESZ block
  d_esz_block = d_xss( d_jxs[0], 5*d_nxs[2] );
}

// Check if the nuclide is fissionable
bool XSSNeutronDataExtractor::hasFissionData() const
{
  if( d_jxs[1] >= 0 )
    return true;
  else
    return false;
}

// check if the nuclide has delayed neutron data
bool XSSNeutronDataExtractor::hasDelayedNeutronData() const
{
  if( d_jxs[23] >= 0 )
    return true;
  else
    return false;
}

// Check if the nuclide has unresolved resonances
bool XSSNeutronDataExtractor::hasUnresolvedResonanceData() const
{
  if( d_jxs[22] >= 0 )
    return true;
  else
    return false;
}

// Extract the ESZ block from the XSS array
Teuchos::ArrayView<const double> 
XSSNeutronDataExtractor::extractESZBlock() const
{
  return d_esz_block;
}

// Extract the energy grid from the XSS array
Teuchos::ArrayView<const double>
XSSNeutronDataExtractor::extractEnergyGrid() const
{
  Teuchos::ArrayView<const double> energy_grid = d_esz_block( 0, d_nxs[2] );
  
  // Make sure the extracted energy grid is sorted
  testPostcondition( Utility::Sort::isSortedAscending( energy_grid.begin(), 
					      energy_grid.end() ) );
		    
  return energy_grid;
}

// Extract the total cross section from the XSS array
Teuchos::ArrayView<const double>
XSSNeutronDataExtractor::extractTotalCrossSection() const
{
  return d_esz_block( d_nxs[2], d_nxs[2] );
}

// Extract the total absorption cross section from the XSS array
Teuchos::ArrayView<const double>
XSSNeutronDataExtractor::extractTotalAbsorptionCrossSection() const
{
  return d_esz_block( 2*d_nxs[2], d_nxs[2] );
}

// Extract the elastic cross section from the XSS array
Teuchos::ArrayView<const double>
XSSNeutronDataExtractor::extractElasticCrossSection() const
{
  return d_esz_block( 3*d_nxs[2], d_nxs[2] );
}

// Extract the average heating numbers from the XSS array
Teuchos::ArrayView<const double>
XSSNeutronDataExtractor::extractAverageHeatingNumbers() const
{
  return d_esz_block( 4*d_nxs[2], d_nxs[2] );
}

// Extract the NU block form the XSS array
Teuchos::ArrayView<const double> 
XSSNeutronDataExtractor::extractNUBlock() const
{
  if( d_jxs[1] >= 0 )
    return d_xss( d_jxs[1], d_jxs[2]-d_jxs[1] );
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the MTR block from the XSS array
Teuchos::ArrayView<const double> 
XSSNeutronDataExtractor::extractMTRBlock() const
{
  if( d_nxs[3] != 0 )
    return d_xss( d_jxs[2], d_nxs[3] );
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the MTRP block from the XSS array
Teuchos::ArrayView<const double> 
XSSNeutronDataExtractor::extractMTRPBlock() const
{
  if( d_nxs[5] != 0 )
    return d_xss( d_jxs[12], d_nxs[5] );
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the LQR block from the XSS array
Teuchos::ArrayView<const double> 
XSSNeutronDataExtractor::extractLQRBlock() const
{
  if( d_nxs[3] != 0 )
    return d_xss( d_jxs[3], d_nxs[3] );
  else 
    return Teuchos::ArrayView<const double>();
}

// Extract the TYR block from the XSS array
Teuchos::ArrayView<const double> 
XSSNeutronDataExtractor::extractTYRBlock() const
{
  if( d_nxs[3] != 0 )
    return d_xss( d_jxs[4], d_nxs[3] );
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the LSIG block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */ 
Teuchos::ArrayView<const double> 
XSSNeutronDataExtractor::extractLSIGBlock() const
{
  if( d_nxs[3] != 0 )
    return d_xss( d_jxs[5], d_nxs[3] );
  else
    return Teuchos::ArrayView<const double>();
}
  
// Extract the LSIGP block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */
Teuchos::ArrayView<const double> 
XSSNeutronDataExtractor::extractLSIGPBlock() const
{
  if( d_nxs[5] != 0 )
    return d_xss( d_jxs[13], d_nxs[5] );
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the SIG block from the XSS array
Teuchos::ArrayView<const double> 
XSSNeutronDataExtractor::extractSIGBlock() const
{
  if( d_nxs[3] != 0 )
    return d_xss( d_jxs[6], d_jxs[7]-d_jxs[6] );
  else 
    return Teuchos::ArrayView<const double>();
}

// Extract the LAND block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */
Teuchos::ArrayView<const double> 
XSSNeutronDataExtractor::extractLANDBlock() const
{
  return d_xss( d_jxs[7], d_nxs[4]+1 );
}

// Extract the AND block from the XSS array
Teuchos::ArrayView<const double> 
XSSNeutronDataExtractor::extractANDBlock() const
{
  return d_xss( d_jxs[8], d_jxs[9]-d_jxs[8] );
}

// Extract the LDLW block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */
Teuchos::ArrayView<const double> 
XSSNeutronDataExtractor::extractLDLWBlock() const
{
  if( d_nxs[4] != 0 )
    return d_xss( d_jxs[9], d_nxs[4] );
  else 
    return Teuchos::ArrayView<const double>();
}

// Extract the LDLWP block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */
Teuchos::ArrayView<const double> 
XSSNeutronDataExtractor::extractLDLWPBlock() const
{
  if( d_nxs[5] != 0 )
    return d_xss( d_jxs[17], d_nxs[5] );
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the DLW block from the XSS array
Teuchos::ArrayView<const double> 
XSSNeutronDataExtractor::extractDLWBlock() const
{
  if( d_nxs[4] != 0 )
    return d_xss( d_jxs[10], d_jxs[11]-d_jxs[10] );
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the DLWP block from the XSS array
Teuchos::ArrayView<const double> 
XSSNeutronDataExtractor::extractDLWPBlock() const
{
  if( d_nxs[5] != 0 )
    return d_xss( d_jxs[18], d_jxs[19]-d_jxs[18] );
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the GPD block from the XSS array
/*! \details For newer evaluations the GPD block only contains the total
 * photon production cross section (size=nxs[2]). For older evaluations, the
 * block also contains the 30*20 matrix of secondary photon energies.
 */
Teuchos::ArrayView<const double>
XSSNeutronDataExtractor::extractGPDBlock() const
{
  if( d_jxs[11] >= 0 )
    return d_xss( d_jxs[11], d_jxs[12]-d_jxs[11] );
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the SIGP block from the XSS array
Teuchos::ArrayView<const double> 
XSSNeutronDataExtractor::extractSIGPBlock() const
{
  if( d_nxs[5] != 0 )
    return d_xss( d_jxs[14], d_jxs[15]-d_jxs[14] );
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the LANDP block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */
Teuchos::ArrayView<const double> 
XSSNeutronDataExtractor::extractLANDPBlock() const
{
  if( d_nxs[5] != 0 )
    return d_xss( d_jxs[15], d_nxs[5] );
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the ANDP block from the XSS array
/*! \details Even if photon production interactions are present (nxs[5] != 0 ),
 * it is possible that there will be no ANDP block. This can occur if every
 * entry in the LANDP block is 0 (indicating that the outgoing photon angle is
 * isotropic in the lab frame).
 */
Teuchos::ArrayView<const double> 
XSSNeutronDataExtractor::extractANDPBlock() const
{
  if( d_nxs[5] != 0 )
    return d_xss( d_jxs[16], d_jxs[17]-d_jxs[16] );
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the YP block from the XSS array
Teuchos::ArrayView<const double> 
XSSNeutronDataExtractor::extractYPBlock() const
{
  if( d_nxs[5] != 0 )
  {
    int size = (int)d_xss[d_jxs[19]] + 1;
    
    return d_xss( d_jxs[19], size );
  }
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the FIS block from the XSS array
Teuchos::ArrayView<const double> 
XSSNeutronDataExtractor::extractFISBlock() const
{
  if( d_jxs[20] >= 0 )
  {
    int size = (int)d_xss[d_jxs[20]+1] + 2;
    
    return d_xss( d_jxs[20], size );
  }
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the UNR block from the XSS array
Teuchos::ArrayView<const double> 
XSSNeutronDataExtractor::extractUNRBlock() const
{
  if( d_jxs[22] >= 0 )
    return d_xss( d_jxs[22], d_jxs[23]-d_jxs[22] );
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the DNU (delayed NU) block from the XSS array
Teuchos::ArrayView<const double> 
XSSNeutronDataExtractor::extractDNUBlock() const
{
  if( hasDelayedNeutronData() )
    return d_xss( d_jxs[23], d_jxs[24]-d_jxs[23] );
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the BDD (basic delayed data) block from the XSS array
Teuchos::ArrayView<const double>
XSSNeutronDataExtractor::extractBDDBlock() const
{
  if( hasDelayedNeutronData() )
    return d_xss( d_jxs[24], d_jxs[25] - d_jxs[24] );
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the DNEDL (delayed neutron LDLW) block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */
Teuchos::ArrayView<const double>
XSSNeutronDataExtractor::extractDNEDLBlock() const
{
  if( d_nxs[7] != 0 )
    return d_xss( d_jxs[25], d_nxs[7] );
  else 
    return Teuchos::ArrayView<const double>();
}

// Extract the delayed neutron DLW block from the XSS array
Teuchos::ArrayView<const double>
XSSNeutronDataExtractor::extractDNEDBlock() const
{
  if( d_nxs[7] != 0 )
    return d_xss( d_jxs[26], d_jxs[11] - d_jxs[26] );
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the Ace Laws from the XSS array
Teuchos::ArrayRCP<double>
XSSNeutronDataExtractor::extractAceLaws() const
{
	Teuchos::ArrayRCP<double> AceLaws;
		
  if( d_nxs[4] != 0 )
  {
		Teuchos::ArrayView<const double> LDLWBlock = 
		                               XSSNeutronDataExtractor::extractLDLWBlock();
		                               
		Teuchos::ArrayView<const double> MTRBlock = 
		                               XSSNeutronDataExtractor::extractMTRBlock();
		                                 
		AceLaws.resize( LDLWBlock.size() );
		                              
		for ( int i = 0; i < LDLWBlock.size(); ++i )
		{
		  if (d_xss[ int(LDLWBlock[i]) + int(d_jxs[10]) -1] == 0)
		  {
		    AceLaws[i] = d_xss[ int(LDLWBlock[i]) + int(d_jxs[10]) ];
		  }
		  else
		  {
		    std::cerr << "Error: More than one ACE Law found for MT number " <<
		    int(MTRBlock[i]) << ". This is not currently supported!" << std::endl;
		  }
		}
		
		return AceLaws;
  }
  else
  {
    return AceLaws;
  }
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_XSSNeutronDataExtractor.cpp
//---------------------------------------------------------------------------//

