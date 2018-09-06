//---------------------------------------------------------------------------//
//!
//! \file   Data_XSSElectronDataExtractor.cpp
//! \author Luke Kersting
//! \brief  XSS array (from ace table) electron condensed history extractor def
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_XSSElectronDataExtractor.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Data{

// Constructor
/*! \details A copy of the jxs array will be made so that it can be modified.
 * All indices in the jxs array correspond to a starting index of 1 (1 is
 * subtracted from all indices so that the correct array location is accessed).
 */
XSSElectronDataExtractor::XSSElectronDataExtractor(
                       const Utility::ArrayView<const int>& nxs,
                       const Utility::ArrayView<const int>& jxs,
		       const std::shared_ptr<const std::vector<double> >& xss )
  : d_nxs( nxs.begin(), nxs.end() ),
    d_jxs( jxs.begin(), jxs.end() ),
    d_xss( xss ),
    d_xss_view()
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

  // Make sure the arrays were pulled from a table with the new el03 format
  TEST_FOR_EXCEPTION( nxs[15] != 3,
                      std::runtime_error,
                      "The data table format is not supported (only el03 "
                      "format is currently supported)!" );

  // Adjust the indices in the JXS array so that they correspond to a C-array
  for( size_t i = 0; i < d_jxs.size(); ++i )
    d_jxs[i] -= 1;

  // Create the XSS view
  d_xss_view = Utility::arrayViewOfConst( *d_xss );
}

// Extract the atomic number
unsigned XSSElectronDataExtractor::extractAtomicNumber() const
{
  return d_nxs[1];
}

// Extract the K edge below which no electron induced relaxation will occur (edg)
double XSSElectronDataExtractor::extractKEdge() const
{
  return d_xss_view[ d_jxs[0] ];
}

// Extract the Auger electron emission energy (eek) = (E_K - 2*E_L)
double XSSElectronDataExtractor::extractAugerEmissionEnergy() const
{
  return d_xss_view[ d_jxs[0]+1 ];
}

// Extract the radiation stopping power interpolation data block
Utility::ArrayView<const double>
XSSElectronDataExtractor::extractStoppingPowersBlock() const
{
  return d_xss_view( d_jxs[1], d_nxs[2]*3 );
}

// Extract the Mott scattering correction points data block
Utility::ArrayView<const double>
XSSElectronDataExtractor::extractMottScatteringCorrectionBlock() const
{
  return d_xss_view( d_jxs[2], d_nxs[3]*6 );
}

// Extract the Riley scattering cross section data block
Utility::ArrayView<const double>
XSSElectronDataExtractor::extractRileyBlock() const
{
  return d_xss_view( d_jxs[3], 14*9 );
}

// Extract the Bremsstrahlung interpolation data block
Utility::ArrayView<const double>
XSSElectronDataExtractor::extractBremsstrahlungInterpolationBlock() const
{
  return d_xss_view( d_jxs[4], d_nxs[4] + d_nxs[5] + ( d_nxs[4]*d_nxs[5] ) );
}

// Extract the photon to electron energy ratios for spectrum calculations (rkt)
Utility::ArrayView<const double>
XSSElectronDataExtractor::extractEnergySpectrumRatios() const
{
  return d_xss_view( d_jxs[8], d_nxs[8] );
}

// Extract the photon to electron energy ratios for angular distribution calculations (rka)
Utility::ArrayView<const double>
XSSElectronDataExtractor::extractEnergyAngularRatios() const
{
  return d_xss_view( d_jxs[9], d_nxs[9] );
}

// Extract the occupation number of electron for each level
Utility::ArrayView<const double>
XSSElectronDataExtractor::extractOccupationNumbers() const
{
  return d_xss_view( d_jxs[10], d_nxs[10] );
}

// Extract the oscillator strength or binding energy for each level
Utility::ArrayView<const double>
XSSElectronDataExtractor::extractBindingEnergy() const
{
  return d_xss_view( d_jxs[10] + d_nxs[10], d_nxs[10] );
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_XSSElectronDataExtractor.cpp
//---------------------------------------------------------------------------//
