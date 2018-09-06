//---------------------------------------------------------------------------//
//!
//! \file   Data_XSSEPRDataExtractor.cpp
//! \author Alex Robinson
//! \brief  XSS array (from ace table) electron-photon-relaxation extractor def
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Data{

// Constructor
/*! \details A copy of the jxs array will be made so that it can be modified.
 * All indices in the jxs array correspond to a starting index of 1 (1 is
 * subtracted from all indices so that the correct array location is accessed).
 */
XSSEPRDataExtractor::XSSEPRDataExtractor(
                       const Utility::ArrayView<const int>& nxs,
                       const Utility::ArrayView<const int>& jxs,
		       const std::shared_ptr<const std::vector<double> >& xss )
  : d_nxs( nxs.begin(), nxs.end() ),
    d_jxs( jxs.begin(), jxs.end() ),
    d_xss( xss ),
    d_xss_view(),
    d_eszg_block(),
    d_subsh_block(),
    d_esze_block()
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

  TEST_FOR_EXCEPTION( nxs[5] != 1 && nxs[5] != 3,
                      std::runtime_error,
                      "The data table format is not supported!" );

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

  // Extract and cache the SUBSH block
  d_subsh_block = d_xss_view( d_jxs[10], d_nxs[6]*5 );

  // Extract and cache the ESZE block
  d_esze_block = d_xss_view( d_jxs[18], d_nxs[7]*(6+d_nxs[6]) );

  if ( nxs[5] == 3 )
  {
    // Extract and cache the ESZE2 block
    d_esze2_block = d_xss_view( d_jxs[26], d_nxs[7]*2 );
  }
}

// Check if the file version is eprdata14
/*! \details Version eprdata14 has a ESZE2 block with additional
 * (total and transport) elastic cross section data.
 * Check this before attempting to extract the ESZE2 block.
 */
bool XSSEPRDataExtractor::isEPRVersion14() const
{
  return d_nxs[5] == 3;
}

// Check if old fluorescence data is present
/*! \details Check this before attempting to extract the JFLO block.
 */
bool XSSEPRDataExtractor::hasOldFluorescenceData() const
{
  return d_nxs[3] != 0;
}

// Check if fluorescence data is present
/*! \details Check this before attempting to extract the RELO or XPROB blocks.
 */
bool XSSEPRDataExtractor::hasFluorescenceData() const
{
  return d_subsh_block[4*d_nxs[6]] != 0;
}

// Extract the atomic number
unsigned XSSEPRDataExtractor::extractAtomicNumber() const
{
  return d_nxs[1];
}

// Extract the ESZG block
Utility::ArrayView<const double> XSSEPRDataExtractor::extractESZGBlock() const
{
  return d_eszg_block;
}

// Extract the incoming photon energy grid
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractPhotonEnergyGrid() const
{
  return d_eszg_block( 0, d_nxs[2] );
}

// Extract the incoherent cross section
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractIncoherentCrossSection() const
{
  return d_eszg_block( d_nxs[2], d_nxs[2] );
}

// Extract the coherent cross section
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractCoherentCrossSection() const
{
  return d_eszg_block( 2*d_nxs[2], d_nxs[2] );

}

// Extract the photoelectric cross section
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractPhotoelectricCrossSection() const
{
  return d_eszg_block( 3*d_nxs[2], d_nxs[2] );
}

// Extract the pair production cross section
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractPairProductionCrossSection() const
{
  return d_eszg_block( 4*d_nxs[2], d_nxs[2] );
}

// Extract the JINCE block
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractJINCEBlock() const
{
  return d_xss_view( d_jxs[1], d_jxs[2] - d_jxs[1] );
}

// Extract the JCOHE block
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractJCOHEBlock() const
{
  return d_xss_view( d_jxs[2], d_jxs[3] - d_jxs[2] );
}

// Extract the JFLO block
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractJFLOBlock() const
{
  if( this->hasFluorescenceData() )
    return d_xss_view( d_jxs[3], 4*d_nxs[3] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the LHNM block
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractLHNMBlock() const
{
  return d_xss_view( d_jxs[4], d_nxs[2] );
}

// Extract the LNEPS block
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractLNEPSBlock() const
{
  return d_xss_view( d_jxs[5], d_nxs[4] );
}

// Extract the LBEPS block
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractLBEPSBlock() const
{
  return d_xss_view( d_jxs[6], d_nxs[4] );
}

// Extract the LPIPS block
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractLPIPSBlock() const
{
  return d_xss_view( d_jxs[7], d_nxs[4] );
}

// Extract the LSWD block
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractLSWDBlock() const
{
  return d_xss_view( d_jxs[8], d_nxs[4] );
}

// Extract the SWD block
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractSWDBlock() const
{
  return d_xss_view( d_jxs[9], d_jxs[10] - d_jxs[9] );
}

// Extract the SUBSH block
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractSUBSHBlock() const
{
  return d_subsh_block;
}

// Extract the ENDF subshell designators
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractSubshellENDFDesignators() const
{
  return d_subsh_block( 0, d_nxs[6] );
}

// Extract the subshell occupancies
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractSubshellOccupancies() const
{
  return d_subsh_block( d_nxs[6], d_nxs[6] );
}

// Extract the subshell binding energies
Utility::ArrayView<const double> XSSEPRDataExtractor::extractSubshellBindingEnergies() const
{
  return d_subsh_block( 2*d_nxs[6], d_nxs[6] );
}

// Extract the subshell binding energies
auto XSSEPRDataExtractor::extractSubshellBindingEnergiesInMeV() const -> Utility::ArrayView<const Energy>
{
  return Utility::ArrayView<const Energy>(
     Utility::reinterpretAsQuantity<Energy>( d_subsh_block.data()+2*d_nxs[6] ),
     Utility::ArrayView<const Energy>::size_type(d_nxs[6]) );
}

// Extract the subshell Compton interaction cdf
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractSubshellComptonInteractionCDF() const
{
  return d_subsh_block( 3*d_nxs[6], d_nxs[6] );
}

// Extract the number of transitions to fill a vacancy in each subshell
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractSubshellVacancyTransitionPaths() const
{
  return d_subsh_block( 4*d_nxs[6], d_nxs[6] );
}

// Extract the SPHEL block
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractSPHELBlock() const
{
  return d_xss_view( d_jxs[15], d_nxs[6]*d_nxs[2] );
}

// Extract the RELO block
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractRELOBlock() const
{
  if( this->hasFluorescenceData() )
    return d_xss_view( d_jxs[16], d_nxs[6] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the XPROB block
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractXPROBBlock() const
{
  if( this->hasFluorescenceData() )
    return d_xss_view( d_jxs[17], d_jxs[18] - d_jxs[17] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the ESZE block
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractESZEBlock() const
{
  return d_esze_block;
}

// Extract the ESZE2 block
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractESZE2Block() const
{
  return d_esze2_block;
}

// Extract the incoming electron energy grid
Utility::ArrayView<const double> XSSEPRDataExtractor::extractElectronEnergyGrid() const
{
  return d_esze_block( 0, d_nxs[7] );
}

// Extract the incoming electron energy grid
auto XSSEPRDataExtractor::extractElectronEnergyGridInMeV() const -> Utility::ArrayView<const Energy>
{
  return Utility::ArrayView<const Energy>(
                 Utility::reinterpretAsQuantity<Energy>( d_esze_block.data() ),
                 Utility::ArrayView<const Energy>::size_type(d_nxs[7]) );
}

// Extract the electron total cross section
Utility::ArrayView<const double> XSSEPRDataExtractor::extractElectronTotalCrossSection() const
{
  return d_esze_block( d_nxs[7], d_nxs[7] );
}

// Extract the electron total cross section
auto XSSEPRDataExtractor::extractElectronTotalCrossSectionInBarns() const -> Utility::ArrayView<const Area>
{
  return Utility::ArrayView<const Area>(
          Utility::reinterpretAsQuantity<Area>( d_esze_block.data()+d_nxs[7] ),
          Utility::ArrayView<const Area>::size_type(d_nxs[7]) );
}

// Extract the electron elastic total cross section
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractElasticTotalCrossSection() const
{
  if( this->isEPRVersion14() )
    return d_esze2_block( d_nxs[7], d_nxs[7] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the electron elastic total cross section
auto XSSEPRDataExtractor::extractElasticTotalCrossSectionInBarns() const
  -> Utility::ArrayView<const Area>
{
  return Utility::ArrayView<const Area>(
        Utility::reinterpretAsQuantity<Area>( d_esze2_block.data()+d_nxs[7] ),
        Utility::ArrayView<const Area>::size_type(d_nxs[7]) );
}

// Extract the electron elastic cutoff cross section ( mu = -1 to 0.999999 )
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractElasticCutoffCrossSection() const
{
  return d_esze_block( 2*d_nxs[7], d_nxs[7] );
}

// Extract the electron elastic cutoff cross section ( mu = -1 to 0.999999 )
auto XSSEPRDataExtractor::extractElasticCutoffCrossSectionInBarns() const
  -> Utility::ArrayView<const Area>
{
  return Utility::ArrayView<const Area>(
        Utility::reinterpretAsQuantity<Area>( d_esze_block.data()+2*d_nxs[7] ),
        Utility::ArrayView<const Area>::size_type(d_nxs[7]) );
}

// Extract the electron elastic transport cross section
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractElasticTransportCrossSection() const
{
  if( this->isEPRVersion14() )
    return d_esze2_block( 0, d_nxs[7] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the electron elastic transport cross section
auto XSSEPRDataExtractor::extractElasticTransportCrossSectionInBarns() const
  -> Utility::ArrayView<const Area>
{
  if( this->isEPRVersion14() )
  {
    return Utility::ArrayView<const Area>(
                  Utility::reinterpretAsQuantity<Area>( d_esze2_block.data() ),
                  Utility::ArrayView<const Area>::size_type(d_nxs[7]) );
  }
  else
    return Utility::ArrayView<const Area>();
}

// Extract the bremsstrahlung cross section
Utility::ArrayView<const double> XSSEPRDataExtractor::extractBremsstrahlungCrossSection() const
{
  return d_esze_block( 3*d_nxs[7], d_nxs[7] );
}

// Extract the bremsstrahlung cross section
auto XSSEPRDataExtractor::extractBremsstrahlungCrossSectionInBarns() const -> Utility::ArrayView<const Area>
{
  return Utility::ArrayView<const Area>(
        Utility::reinterpretAsQuantity<Area>( d_esze_block.data()+3*d_nxs[7] ),
        Utility::ArrayView<const Area>::size_type(d_nxs[7]) );
}

// Extract the excitation cross section
Utility::ArrayView<const double> XSSEPRDataExtractor::extractExcitationCrossSection() const
{
  return d_esze_block( 4*d_nxs[7], d_nxs[7] );
}

// Extract the excitation cross section
auto XSSEPRDataExtractor::extractExcitationCrossSectionInBarns() const -> Utility::ArrayView<const Area>
{
  return Utility::ArrayView<const Area>(
        Utility::reinterpretAsQuantity<Area>( d_esze_block.data()+4*d_nxs[7] ),
        Utility::ArrayView<const Area>::size_type(d_nxs[7]) );
}

// Extract the total electroionization cross section
Utility::ArrayView<const double> XSSEPRDataExtractor::extractElectroionizationCrossSection() const
{
  return d_esze_block( 5*d_nxs[7], d_nxs[7] );
}

// Extract the total electroionization cross section
auto XSSEPRDataExtractor::extractElectroionizationCrossSectionInBarns() const -> Utility::ArrayView<const Area>
{
  return Utility::ArrayView<const Area>(
        Utility::reinterpretAsQuantity<Area>( d_esze_block.data()+5*d_nxs[7] ),
        Utility::ArrayView<const Area>::size_type(d_nxs[7]) );
}

// Extract the electroionization subshell cross sections
Utility::ArrayView<const double> XSSEPRDataExtractor::extractElectroionizationSubshellCrossSections() const
{
  return d_esze_block( 6*d_nxs[7], d_nxs[7]*d_nxs[6] );
}

// Extract the electroionization subshell cross sections
auto XSSEPRDataExtractor::extractElectroionizationSubshellCrossSectionsInBarns() const -> Utility::ArrayView<const Area>
{
  return Utility::ArrayView<const Area>(
        Utility::reinterpretAsQuantity<Area>( d_esze_block.data()+6*d_nxs[7] ),
        Utility::ArrayView<const Area>::size_type(d_nxs[7]*d_nxs[6]) );
}

// Extract the EXCIT block
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractEXCITBlock() const
{
  return d_xss_view( d_jxs[19], 2*d_nxs[8] );
}

// Extract the ELASI block
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractELASIBlock() const
{
  return d_xss_view( d_jxs[20], 3*d_nxs[9] );
}

// Extract the ELAS block
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractELASBlock() const
{
  return d_xss_view( d_jxs[21], d_jxs[22] - d_jxs[21] );
}

// Extract the EION block
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractEIONBlock() const
{
  return d_xss_view( d_jxs[22], d_jxs[23] - d_jxs[22] );
}

// Return the EION data block location in xss array
unsigned
XSSEPRDataExtractor::returnEIONLoc() const
{
  return d_jxs[22];
}

// Extract the BREMI block
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractBREMIBlock() const
{
  return d_xss_view( d_jxs[23], 3*d_nxs[10] );
}

// Extract the BREME block
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractBREMEBlock() const
{
  return d_xss_view( d_jxs[24], d_jxs[25] - d_jxs[24] );
}

// Extract the BREML block
Utility::ArrayView<const double>
XSSEPRDataExtractor::extractBREMLBlock() const
{
  return d_xss_view( d_jxs[25], d_nxs[11]*2 );
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_XSSEPRDataExtractor.cpp
//---------------------------------------------------------------------------//
