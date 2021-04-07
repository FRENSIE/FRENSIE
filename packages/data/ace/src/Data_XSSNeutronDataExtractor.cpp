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
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Data{

// Constructor
/*! \details A copy of the jxs array will be made so that it can be modified.
 * All indices in the jxs array correspond to a starting index of 1 (1 is
 * subtracted from all indices so that the correct array location is accessed).
 */
XSSNeutronDataExtractor::XSSNeutronDataExtractor(
		       const Utility::ArrayView<const int>& nxs,
                       const Utility::ArrayView<const int>& jxs,
		       const std::shared_ptr<const std::vector<double> >& xss )
  : d_nxs( nxs.begin(), nxs.end() ),
    d_jxs( jxs.begin(), jxs.end() ),
    d_xss( xss ),
    d_xss_view(),
    d_esz_block()
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

  // Extract and cache the ESZ block
  d_esz_block = d_xss_view( d_jxs[0], 5*d_nxs[2] );
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
Utility::ArrayView<const double>
XSSNeutronDataExtractor::extractESZBlock() const
{
  return d_esz_block;
}

// Extract the energy grid from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractEnergyGrid() const
{
  Utility::ArrayView<const double> energy_grid = d_esz_block( 0, d_nxs[2] );

  // Make sure the extracted energy grid is sorted
  TEST_FOR_EXCEPTION( !Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                         energy_grid.end() ),
                      std::runtime_error,
                      "An unsorted energy grid was encountered!" );

  return energy_grid;
}

// Extract the energy grid from the XSS array
auto XSSNeutronDataExtractor::extractEnergyGridInMeV() const -> Utility::ArrayView<const Energy>
{
  Utility::ArrayView<const Energy> energy_grid(
                  Utility::reinterpretAsQuantity<Energy>( d_esz_block.data() ),
                  Utility::ArrayView<const Energy>::size_type(d_nxs[2]) );

  // Make sure the extracted energy grid is sorted
  TEST_FOR_EXCEPTION( !Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                         energy_grid.end() ),
                      std::runtime_error,
                      "An unsorted energy grid was encountered!" );

  return energy_grid;
}

// Extract the total cross section from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractTotalCrossSection() const
{
  return d_esz_block( d_nxs[2], d_nxs[2] );
}

// Extract the total cross section from the XSS array
auto XSSNeutronDataExtractor::extractTotalCrossSectionInBarns() const -> Utility::ArrayView<const Area>
{
  return Utility::ArrayView<const Area>(
           Utility::reinterpretAsQuantity<Area>( d_esz_block.data()+d_nxs[2] ),
           Utility::ArrayView<const Area>::size_type(d_nxs[2]) );
}

// Extract the total absorption cross section from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractTotalAbsorptionCrossSection() const
{
  return d_esz_block( 2*d_nxs[2], d_nxs[2] );
}

// Extract the total absorption cross section from the XSS array
auto XSSNeutronDataExtractor::extractTotalAbsorptionCrossSectionInBarns() const -> Utility::ArrayView<const Area>
{
  return Utility::ArrayView<const Area>(
         Utility::reinterpretAsQuantity<Area>( d_esz_block.data()+2*d_nxs[2] ),
         Utility::ArrayView<const Area>::size_type(d_nxs[2]) );
}

// Extract the elastic cross section from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractElasticCrossSection() const
{
  return d_esz_block( 3*d_nxs[2], d_nxs[2] );
}

// Extract the elastic cross section from the XSS array
auto XSSNeutronDataExtractor::extractElasticCrossSectionInBarns() const -> Utility::ArrayView<const Area>
{
  return Utility::ArrayView<const Area>(
         Utility::reinterpretAsQuantity<Area>( d_esz_block.data()+3*d_nxs[2] ),
         Utility::ArrayView<const Area>::size_type(d_nxs[2]) );
}

// Extract the average heating numbers from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractAverageHeatingNumbers() const
{
  return d_esz_block( 4*d_nxs[2], d_nxs[2] );
}

// Extract the average heating numbers from the XSS array
auto XSSNeutronDataExtractor::extractAverageHeatingNumbersInMeV() const -> Utility::ArrayView<const Energy>
{
  return Utility::ArrayView<const Energy>(
       Utility::reinterpretAsQuantity<Energy>( d_esz_block.data()+4*d_nxs[2] ),
       Utility::ArrayView<const Energy>::size_type(d_nxs[2]) );
}

// Extract the NU block form the XSS array
Utility::ArrayView<const double>
XSSNeutronDataExtractor::extractNUBlock() const
{
  if( d_jxs[1] >= 0 )
    return d_xss_view( d_jxs[1], d_jxs[2]-d_jxs[1] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the MTR block from the XSS array
Utility::ArrayView<const double>
XSSNeutronDataExtractor::extractMTRBlock() const
{
  if( d_nxs[3] != 0 )
    return d_xss_view( d_jxs[2], d_nxs[3] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the MTRP block from the XSS array
Utility::ArrayView<const double>
XSSNeutronDataExtractor::extractMTRPBlock() const
{
  if( d_nxs[5] != 0 )
    return d_xss_view( d_jxs[12], d_nxs[5] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the LQR block from the XSS array
Utility::ArrayView<const double>
XSSNeutronDataExtractor::extractLQRBlock() const
{
  if( d_nxs[3] != 0 )
    return d_xss_view( d_jxs[3], d_nxs[3] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the TYR block from the XSS array
Utility::ArrayView<const double>
XSSNeutronDataExtractor::extractTYRBlock() const
{
  if( d_nxs[3] != 0 )
    return d_xss_view( d_jxs[4], d_nxs[3] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the LSIG block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */
Utility::ArrayView<const double>
XSSNeutronDataExtractor::extractLSIGBlock() const
{
  if( d_nxs[3] != 0 )
    return d_xss_view( d_jxs[5], d_nxs[3] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the LSIGP block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */
Utility::ArrayView<const double>
XSSNeutronDataExtractor::extractLSIGPBlock() const
{
  if( d_nxs[5] != 0 )
    return d_xss_view( d_jxs[13], d_nxs[5] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the SIG block from the XSS array
Utility::ArrayView<const double>
XSSNeutronDataExtractor::extractSIGBlock() const
{
  if( d_nxs[3] != 0 )
    return d_xss_view( d_jxs[6], d_jxs[7]-d_jxs[6] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the LAND block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */
Utility::ArrayView<const double>
XSSNeutronDataExtractor::extractLANDBlock() const
{
  return d_xss_view( d_jxs[7], d_nxs[4]+1 );
}

// Extract the AND block from the XSS array
Utility::ArrayView<const double>
XSSNeutronDataExtractor::extractANDBlock() const
{
  return d_xss_view( d_jxs[8], d_jxs[9]-d_jxs[8] );
}

// Extract the LDLW block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */
Utility::ArrayView<const double>
XSSNeutronDataExtractor::extractLDLWBlock() const
{
  if( d_nxs[4] != 0 )
    return d_xss_view( d_jxs[9], d_nxs[4] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the LDLWP block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */
Utility::ArrayView<const double>
XSSNeutronDataExtractor::extractLDLWPBlock() const
{
  if( d_nxs[5] != 0 )
    return d_xss_view( d_jxs[17], d_nxs[5] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the DLW block from the XSS array
Utility::ArrayView<const double>
XSSNeutronDataExtractor::extractDLWBlock() const
{
  if( d_nxs[4] != 0 )
    return d_xss_view( d_jxs[10], d_jxs[11]-d_jxs[10] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the DLWP block from the XSS array
Utility::ArrayView<const double>
XSSNeutronDataExtractor::extractDLWPBlock() const
{
  if( d_nxs[5] != 0 )
    return d_xss_view( d_jxs[18], d_jxs[19]-d_jxs[18] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the GPD block from the XSS array
/*! \details For newer evaluations the GPD block only contains the total
 * photon production cross section (size=nxs[2]). For older evaluations, the
 * block also contains the 30*20 matrix of secondary photon energies.
 */
Utility::ArrayView<const double>
XSSNeutronDataExtractor::extractGPDBlock() const
{
  if( d_jxs[11] >= 0 )
    return d_xss_view( d_jxs[11], d_jxs[12]-d_jxs[11] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the SIGP block from the XSS array
Utility::ArrayView<const double>
XSSNeutronDataExtractor::extractSIGPBlock() const
{
  if( d_nxs[5] != 0 )
    return d_xss_view( d_jxs[14], d_jxs[15]-d_jxs[14] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the LANDP block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */
Utility::ArrayView<const double>
XSSNeutronDataExtractor::extractLANDPBlock() const
{
  if( d_nxs[5] != 0 )
    return d_xss_view( d_jxs[15], d_nxs[5] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the ANDP block from the XSS array
/*! \details Even if photon production interactions are present (nxs[5] != 0 ),
 * it is possible that there will be no ANDP block. This can occur if every
 * entry in the LANDP block is 0 (indicating that the outgoing photon angle is
 * isotropic in the lab frame).
 */
Utility::ArrayView<const double>
XSSNeutronDataExtractor::extractANDPBlock() const
{
  if( d_nxs[5] != 0 )
    return d_xss_view( d_jxs[16], d_jxs[17]-d_jxs[16] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the YP block from the XSS array
Utility::ArrayView<const double>
XSSNeutronDataExtractor::extractYPBlock() const
{
  if( d_nxs[5] != 0 )
  {
    int size = (int)d_xss_view[d_jxs[19]] + 1;

    return d_xss_view( d_jxs[19], size );
  }
  else
    return Utility::ArrayView<const double>();
}

// Extract the FIS block from the XSS array
Utility::ArrayView<const double>
XSSNeutronDataExtractor::extractFISBlock() const
{
  if( d_jxs[20] >= 0 )
  {
    int size = (int)d_xss_view[d_jxs[20]+1] + 2;

    return d_xss_view( d_jxs[20], size );
  }
  else
    return Utility::ArrayView<const double>();
}

// Extract the UNR block from the XSS array
Utility::ArrayView<const double>
XSSNeutronDataExtractor::extractUNRBlock() const
{
  if( d_jxs[22] >= 0 )
    return d_xss_view( d_jxs[22], d_jxs[23]-d_jxs[22] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the DNU (delayed NU) block from the XSS array
Utility::ArrayView<const double>
XSSNeutronDataExtractor::extractDNUBlock() const
{
  if( this->hasDelayedNeutronData() )
    return d_xss_view( d_jxs[23], d_jxs[24]-d_jxs[23] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the BDD (basic delayed data) block from the XSS array
Utility::ArrayView<const double>
XSSNeutronDataExtractor::extractBDDBlock() const
{
  if( this->hasDelayedNeutronData() )
    return d_xss_view( d_jxs[24], d_jxs[25] - d_jxs[24] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the DNEDL (delayed neutron LDLW) block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */
Utility::ArrayView<const double>
XSSNeutronDataExtractor::extractDNEDLBlock() const
{
  if( d_nxs[7] != 0 )
    return d_xss_view( d_jxs[25], d_nxs[7] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the delayed neutron DLW block from the XSS array
Utility::ArrayView<const double>
XSSNeutronDataExtractor::extractDNEDBlock() const
{
  if( d_nxs[7] != 0 )
    return d_xss_view( d_jxs[26], d_jxs[11] - d_jxs[26] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the Ace Laws from the XSS array
std::vector<double> XSSNeutronDataExtractor::extractAceLaws() const
{
  std::vector<double> ace_laws;

  if( d_nxs[4] != 0 )
  {
    Utility::ArrayView<const double> ldlw_block =
      XSSNeutronDataExtractor::extractLDLWBlock();

    Utility::ArrayView<const double> mtr_block =
      XSSNeutronDataExtractor::extractMTRBlock();

    ace_laws.resize( ldlw_block.size() );

    for( size_t i = 0; i < ldlw_block.size(); ++i )
    {
      if( d_xss_view[int(ldlw_block[i]) + int(d_jxs[10]) -1] == 0 )
        ace_laws[i] = d_xss_view[int(ldlw_block[i]) + int(d_jxs[10])];
      
      else
      {
        FRENSIE_LOG_TAGGED_WARNING( "XSSNeutronDataExtractor",
                                    "More than one ACE Law found for MT "
                                    "number " << int(mtr_block[i]) << ". "
                                    "This is not currently supported!" );
      }
    }
  }
  
  return ace_laws;
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_XSSNeutronDataExtractor.cpp
//---------------------------------------------------------------------------//

