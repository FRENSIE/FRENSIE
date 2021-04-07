//---------------------------------------------------------------------------//
//!
//! \file   Data_XSSPhotoatomicDataExtractor.cpp
//! \author Alex Robinson
//! \brief  XSS array (from ace table) photoatomic data extractor class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_XSSPhotoatomicDataExtractor.hpp"
#include "Utility_DesignByContract.hpp"

namespace Data{

// Constructor
/*! \details A copy of the jxs array will be made so that it can be modified.
 * All indices in the jxs array correspond to a starting index of 1 (1 is
 * subtracted from all indices so that the correct array location is accessed).
 */
XSSPhotoatomicDataExtractor::XSSPhotoatomicDataExtractor(
                       const Utility::ArrayView<const int>& nxs,
                       const Utility::ArrayView<const int>& jxs,
		       const std::shared_ptr<const std::vector<double> >& xss )
  : d_nxs( nxs.begin(), nxs.end() ),
    d_jxs( jxs.begin(), jxs.end() ),
    d_xss( xss ),
    d_xss_view(),
    d_eszg_block()
{
  // Make sure that the xss array exists
  testPrecondition( xss.get() );
  
  // Make sure the arrays have the correct size
  TEST_FOR_EXCEPTION( nxs.size() != 16,
                      std::runtime_error,
                      "Invalid nxs array encountered!" );

  TEST_FOR_EXCEPTION( jxs.size() != 32,
                      std::runtime_error,
                      "Invalid jxs array encountered!" );

  TEST_FOR_EXCEPTION( xss->size() != nxs[0],
                      std::runtime_error,
                      "The nxs array expected the xss array to have size "
                      << nxs[0] << " but it was found to have size "
                      << xss->size() << "!" );

  // Adjust the indices in the JXS array so that they correspond to a C-array
  for( size_t i = 0; i < d_jxs.size(); ++i )
    d_jxs[i] -= 1;

  // Create the XSS view
  d_xss_view = Utility::arrayViewOfConst( *d_xss );
  
  // Extract and cache the ESZG block
  d_eszg_block = d_xss_view( d_jxs[0], d_nxs[2]*5 );
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
Utility::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractESZGBlock() const
{
  return d_eszg_block;
}

// Extract the energy grid
/*! \details the values stored are the logarithms of the incoming energies.
 */
Utility::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractEnergyGrid() const
{
  return d_eszg_block( 0, d_nxs[2] );
}

// Extract the incoherent cross section
/*! \details the values stored are the logarithms of the incoherent cross sec.
 */
Utility::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractIncoherentCrossSection() const
{
  return d_eszg_block( d_nxs[2], d_nxs[2] );
}

// Extract the coherent cross section
/*! \details the values stored are the logarithms of the coherent cross sec.
 */
Utility::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractCoherentCrossSection() const
{
  return d_eszg_block( 2*d_nxs[2], d_nxs[2] );
}

// Extract the photoelectric cross section
/*! \details the values stored are the logarithms of the photoelectric cross
 * sec.
 */
Utility::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractPhotoelectricCrossSection() const
{
  return d_eszg_block( 3*d_nxs[2], d_nxs[2] );
}

// Extract the pair production cross section
/*! \details the values stored are the logarithms of the pair production cross
 * sec.
 */
Utility::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractPairProductionCrossSection() const
{
  return d_eszg_block( 4*d_nxs[2], d_nxs[2] );
}

// Extract the JINC block
Utility::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractJINCBlock() const
{
  return d_xss_view( d_jxs[1], 21 );
}

// Extract the JCOH block
Utility::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractJCOHBlock() const
{
  return d_xss_view( d_jxs[2], 110 );
}

// Extract the JFLO block
Utility::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractJFLOBlock() const
{
  if( this->hasFluorescenceData() )
    return d_xss_view( d_jxs[3], 4*d_nxs[3] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the LHNM block
Utility::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractLHNMBlock() const
{
  return d_xss_view( d_jxs[4], d_nxs[2] );
}

// Extract the LNEPS block
Utility::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractLNEPSBlock() const
{
  if( this->hasElectronShellOccupancyData() )
    return d_xss_view( d_jxs[5], d_nxs[4] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the LBEPS block
Utility::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractLBEPSBlock() const
{
  if( this->hasElectronShellOccupancyData() )
    return d_xss_view( d_jxs[6], d_nxs[4] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the LPIPS block
Utility::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractLPIPSBlock() const
{
  if( this->hasElectronShellOccupancyData() )
    return d_xss_view( d_jxs[7], d_nxs[4] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the LSWD block
Utility::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractLSWDBlock() const
{
  if( this->hasComptonProfileData() )
    return d_xss_view( d_jxs[8], d_nxs[4] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the SWD block
Utility::ArrayView<const double>
XSSPhotoatomicDataExtractor::extractSWDBlock() const
{
  if( this->hasComptonProfileData() )
    return d_xss_view( d_jxs[9], d_nxs[0] - d_jxs[9] );
  else
    return Utility::ArrayView<const double>();
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_XSSPhotoatomicDataExtractor.cpp
//---------------------------------------------------------------------------//
