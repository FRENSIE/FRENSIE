//---------------------------------------------------------------------------//
//!
//! \file   Data_XSSEPRDataExtractor.cpp
//! \author Alex Robinson
//! \brief  XSS array (from ace table) electron-photon-relaxation extractor def
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_ContractException.hpp"

namespace Data{

// Constructor
/*! \details A copy of the jxs array will be made so that it can be modified.
 * All indices in the jxs array correspond to a starting index of 1 (1 is
 * subtracted from all indices so that the correct array location is accessed).
 */
XSSEPRDataExtractor::XSSEPRDataExtractor(
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
  // Make sure the arrays were pulled from a table with the new format
  testPrecondition( nxs[5] == 1 || nxs[5] == 3);

  // Adjust the indices in the JXS array so that they correspond to a C-array
  for( unsigned i = 0; i < d_jxs.size(); ++i )
    d_jxs[i] -= 1;

  // Extract and cache the ESZG block
  d_eszg_block = d_xss( d_jxs[0], d_nxs[2]*5 );

  // Extract and cache the SUBSH block
  d_subsh_block = d_xss( d_jxs[10], d_nxs[6]*5 );

  // Extract and cache the ESZE block
  d_esze_block = d_xss( d_jxs[18], d_nxs[7]*(6+d_nxs[6]) );

  if ( nxs[5] == 3 )
  {
    // Extract and cache the ESZE2 block
    d_esze2_block = d_xss( d_jxs[26], d_nxs[7]*2 );
  }
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

// Check if additional (total and transport) elastic cross section data is present
/*! \details Check this before attempting to extract the ESZE2 block.
 */
  bool XSSEPRDataExtractor::hasAdditionalElasticCrossSectionData() const
{
  return d_nxs[5] == 3;
}

// Extract the atomic number
unsigned XSSEPRDataExtractor::extractAtomicNumber() const
{
  return d_nxs[1];
}

// Extract the ESZG block
Teuchos::ArrayView<const double> XSSEPRDataExtractor::extractESZGBlock() const
{
  return d_eszg_block;
}

// Extract the incoming photon energy grid
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractPhotonEnergyGrid() const
{
  return d_eszg_block( 0, d_nxs[2] );
}

// Extract the incoherent cross section
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractIncoherentCrossSection() const
{
  return d_eszg_block( d_nxs[2], d_nxs[2] );
}

// Extract the coherent cross section
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractCoherentCrossSection() const
{
  return d_eszg_block( 2*d_nxs[2], d_nxs[2] );
}

// Extract the photoelectric cross section
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractPhotoelectricCrossSection() const
{
  return d_eszg_block( 3*d_nxs[2], d_nxs[2] );
}

// Extract the pair production cross section
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractPairProductionCrossSection() const
{
  return d_eszg_block( 4*d_nxs[2], d_nxs[2] );
}

// Extract the JINCE block
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractJINCEBlock() const
{
  return d_xss( d_jxs[1], d_jxs[2] - d_jxs[1] );
}

// Extract the JCOHE block
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractJCOHEBlock() const
{
  return d_xss( d_jxs[2], d_jxs[3] - d_jxs[2] );
}

// Extract the JFLO block
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractJFLOBlock() const
{
  if( hasFluorescenceData() )
    return d_xss( d_jxs[3], 4*d_nxs[3] );
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the LHNM block
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractLHNMBlock() const
{
  return d_xss( d_jxs[4], d_nxs[2] );
}

// Extract the LNEPS block
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractLNEPSBlock() const
{
  return d_xss( d_jxs[5], d_nxs[4] );
}

// Extract the LBEPS block
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractLBEPSBlock() const
{
  return d_xss( d_jxs[6], d_nxs[4] );
}

// Extract the LPIPS block
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractLPIPSBlock() const
{
  return d_xss( d_jxs[7], d_nxs[4] );
}

// Extract the LSWD block
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractLSWDBlock() const
{
  return d_xss( d_jxs[8], d_nxs[4] );
}

// Extract the SWD block
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractSWDBlock() const
{
  return d_xss( d_jxs[9], d_jxs[10] - d_jxs[9] );
}

// Extract the SUBSH block
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractSUBSHBlock() const
{
  return d_subsh_block;
}

// Extract the ENDF subshell designators
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractSubshellENDFDesignators() const
{
  return d_subsh_block( 0, d_nxs[6] );
}

// Extract the subshell occupancies
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractSubshellOccupancies() const
{
  return d_subsh_block( d_nxs[6], d_nxs[6] );
}

// Extract the subshell binding energies
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractSubshellBindingEnergies() const
{
  return d_subsh_block( 2*d_nxs[6], d_nxs[6] );
}

// Extract the subshell Compton interaction cdf
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractSubshellComptonInteractionCDF() const
{
  return d_subsh_block( 3*d_nxs[6], d_nxs[6] );
}

// Extract the number of transitions to fill a vacancy in each subshell
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractSubshellVacancyTransitionPaths() const
{
  return d_subsh_block( 4*d_nxs[6], d_nxs[6] );
}

// Extract the SPHEL block
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractSPHELBlock() const
{
  return d_xss( d_jxs[15], d_nxs[6]*d_nxs[2] );
}

// Extract the RELO block
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractRELOBlock() const
{
  if( hasFluorescenceData() )
    return d_xss( d_jxs[16], d_nxs[6] );
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the XPROB block
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractXPROBBlock() const
{
  if( hasFluorescenceData() )
    return d_xss( d_jxs[17], d_jxs[18] - d_jxs[17] );
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the ESZE block
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractESZEBlock() const
{
  return d_esze_block();
}

// Extract the ESZE2 block
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractESZE2Block() const
{
  return d_esze2_block();
}

// Extract the incoming electron energy grid
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractElectronEnergyGrid() const
{
  return d_esze_block( 0, d_nxs[7] );
}

// Extract the electron total cross section
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractElectronTotalCrossSection() const
{
  return d_esze_block( d_nxs[7], d_nxs[7] );
}

// Extract the electron elastic transport cross section
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractElasticTransportCrossSection() const
{
  if( hasAdditionalElasticCrossSectionData() )
    return d_esze2_block( 0, d_nxs[7] );
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the electron elastic total cross section
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractElasticTotalCrossSection() const
{
  if( hasAdditionalElasticCrossSectionData() )
    return d_esze2_block( d_nxs[7], d_nxs[7] );
  else
    return Teuchos::ArrayView<const double>();
}

// Extract the electron elastic cutoff cross section ( mu = -1 to 0.999999 )
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractElasticCutoffCrossSection() const
{
  return d_esze_block( 2*d_nxs[7], d_nxs[7] );
}

// Extract the bremsstrahlung cross section
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractBremsstrahlungCrossSection() const
{
  return d_esze_block( 3*d_nxs[7], d_nxs[7] );
}

// Extract the excitation cross section
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractExcitationCrossSection() const
{
  return d_esze_block( 4*d_nxs[7], d_nxs[7] );
}

// Extract the total electroionization cross section
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractElectroionizationCrossSection() const
{
  return d_esze_block( 5*d_nxs[7], d_nxs[7] );
}

// Extract the electroionization subshell cross sections
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractElectroionizationSubshellCrossSections() const
{
  return d_esze_block( 6*d_nxs[7], d_nxs[7]*d_nxs[6] );
}

// Extract the EXCIT block
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractEXCITBlock() const
{
  return d_xss( d_jxs[19], 2*d_nxs[8] );
}

// Extract the ELASI block
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractELASIBlock() const
{
  return d_xss( d_jxs[20], 3*d_nxs[9] );
}

// Extract the ELAS block
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractELASBlock() const
{
  return d_xss( d_jxs[21], d_jxs[22] - d_jxs[21] );
}

// Extract the EION block
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractEIONBlock() const
{
  return d_xss( d_jxs[22], d_jxs[23] - d_jxs[22] );
}

// Return the EION data block location in xss array
unsigned
XSSEPRDataExtractor::returnEIONLoc() const
{
  return d_jxs[22];
}

// Extract the BREMI block
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractBREMIBlock() const
{
  return d_xss( d_jxs[23], 3*d_nxs[10] );
}

// Extract the BREME block
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractBREMEBlock() const
{
  return d_xss( d_jxs[24], d_jxs[25] - d_jxs[24] );
}

// Extract the BREML block
Teuchos::ArrayView<const double>
XSSEPRDataExtractor::extractBREMLBlock() const
{
  return d_xss( d_jxs[25], d_nxs[11]*2 );
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_XSSEPRDataExtractor.cpp
//---------------------------------------------------------------------------//
