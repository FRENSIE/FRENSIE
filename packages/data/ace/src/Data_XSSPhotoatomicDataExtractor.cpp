//---------------------------------------------------------------------------//
//!
//! \file   Data_XSSPhotoatomicDataExtractor.cpp
//! \author Alex Robinson
//! \brief  XSS array (from ace table) photoatomic data extractor class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_XSSPhotoatomicDataExtractor.hpp"
#include "Utility_ContractException.hpp"

namespace Data{

// Constructor
/*! \details A copy of the jxs array will be made so that it can be modified.
 * All indices in the jxs array correspond to a starting index of 1 (1 is
 * subtracted from all indices so that the correct array location is accessed).
 */
XSSPhotoatomicDataExtractor::XSSPhotoatomicDataExtractor(
				  const Teuchos::ArrayView<const int>& nxs,
				  const Teuchos::ArrayView<const int>& jxs,
		                  const Teuchos::ArrayRCP<const double>& xss )
  : d_nxs( nxs ),
    d_jxs( jxs ),
    d_xss( xss )
{
  // Make sure the arrays have the correct size
  testPrecondition( nxs.size() == 16 );
  testPrecondition( jxs.size() == 32 );
  testPrecondition( xss.size() == nxs[0] );

  // Adjust the indices in the JXS array so that they correspond to a C-array
  for( unsigned i = 0; i < d_jxs.size(); ++i )
    d_jxs[i] -= 1;

  // Extract and cache the ESZG block
  d_eszg_block = d_xss( d_jxs[0], d_nxs[2]*5 );
}

// Check if fluorescence data is present
bool XSSPhotoatomicDataExtractor::hasFluorescenceData() const
{
  return d_nxs[3] != 0;
}

// Check if electron shell occupancy data is present
bool XSSPhotoatomicDataExtractor::hasElectronShellOccupancyData() const
{
  return d_nxs[4] != 0;
}

// Check if compton profile data is present
bool XSSPhotoatomicDataExtractor::hasComptonProfileData() const
{
  return d_nxs[4] != 0;
}

// Extract the ESZG block
Teuchos::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractESZGBlock() const
{
  return d_eszg_block;
}

// Extract the energy grid
/*! \details the values stored are the logarithms of the incoming energies.
 */
Teuchos::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractEnergyGrid() const
{
  return d_eszg_block( 0, d_nxs[2] );
}

// Extract the incoherent cross section
/*! \details the values stored are the logarithms of the incoherent cross sec.
 */
Teuchos::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractIncoherentCrossSection() const
{
  return d_eszg_block( d_nxs[2], d_nxs[2] );
}

// Extract the coherent cross section
/*! \details the values stored are the logarithms of the coherent cross sec.
 */
Teuchos::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractCoherentCrossSection() const
{
  return d_eszg_block( 2*d_nxs[2], d_nxs[2] );
}

// Extract the photoelectric cross section
/*! \details the values stored are the logarithms of the photoelectric cross
 * sec.
 */
Teuchos::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractPhotoelectricCrossSection() const
{
  return d_eszg_block( 3*d_nxs[2], d_nxs[2] );
}

// Extract the pair production cross section
/*! \details the values stored are the logarithms of the pair production cross
 * sec.
 */
Teuchos::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractPairProductionCrossSection() const
{
  return d_eszg_block( 4*d_nxs[2], d_nxs[2] );
}

// Extract the JINC block
Teuchos::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractJINCBlock() const
{
  return d_xss( d_jxs[1], 21 );
}

// Extract the JCOH block
Teuchos::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractJCOHBlock() const
{
  return d_xss( d_jxs[2], 110 );
}

// Extract the JFLO block
Teuchos::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractJFLOBlock() const
{
  if( hasFluorescenceData() )
    return d_xss( d_jxs[3], 4*d_nxs[3] );
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the LHNM block
Teuchos::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractLHNMBlock() const
{
  return d_xss( d_jxs[4], d_nxs[2] );
}

// Extract the LNEPS block
Teuchos::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractLNEPSBlock() const
{
  if( hasElectronShellOccupancyData() )
    return d_xss( d_jxs[5], d_nxs[4] );
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the LBEPS block
Teuchos::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractLBEPSBlock() const
{
  if( hasElectronShellOccupancyData() )
    return d_xss( d_jxs[6], d_nxs[4] );
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the LPIPS block
Teuchos::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractLPIPSBlock() const
{
  if( hasElectronShellOccupancyData() )
    return d_xss( d_jxs[7], d_nxs[4] );
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the LSWD block
Teuchos::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractLSWDBlock() const
{
  if( hasComptonProfileData() )
    return d_xss( d_jxs[8], d_nxs[4] );
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the SWD block
Teuchos::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractSWDBlock() const
{
  if( hasComptonProfileData() )
    return d_xss( d_jxs[9], d_nxs[0] - d_jxs[9] );
  else
    return Teuchos::ArrayView<const double>();
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_XSSPhotoatomicDataExtractor.cpp
//---------------------------------------------------------------------------//
