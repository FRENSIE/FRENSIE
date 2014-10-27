//---------------------------------------------------------------------------//
//!
//! \file   Data_XSSEPRDataExtractor.hpp
//! \author Alex Robinson
//! \brief  XSS array (from ace table) electron-photon-relaxation extractor dec
//!
//---------------------------------------------------------------------------//

#ifndef DATA_XSS_EPR_DATA_EXTRACTOR_HPP
#define DATA_XSS_EPR_DATA_EXTRACTOR_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_ArrayRCP.hpp>

namespace Data{

/*! \defgroup continuous_energy_epr_table Continuous Energy Electron-Photon-Relaxation Table
 * \ingroup ace_table
 * \todo Add reference for table layout.
 *
 * After a continuous energy EPR table has been read by the 
 * Data::ACEFileHandler the individual data blocks must be extracted from the
 * XSS array using the Data::XSSPhotoatomicDataExtractor. Both the NXS array
 * and the JXS array are required to successfully extract the blocks. The NXS
 * array elements have the following meanings:
 * <ul>
 *  <li> NXS[0] = length of XSS array</li>
 *  <li> NXS[1] = Z</li>
 *  <li> NXS[2] = number of photon energies in common grid (Ng)</li>
 *  <li> NXS[3] = length of obsolete fluorescence data divided by 4 (Nf)</li>
 *  <li> NXS[4] = number of shells for Compton Doppler broadening (Nd)</li>
 *  <li> NXS[5] = new format flag to identify new table format (always=1)</li>
 *  <li> NXS[6] = number of subshells for photoelectric and electron
 *                impact ionization (Ns)</li>
 *  <li> NXS[7] = number of electron energies in common grid (Ne)</li>
 *  <li> NXS[8] = length of {energy,energy-loss} table for electron 
 *                excitation (Nxl)</li>
 *  <li> NXS[9] = number of energies for which there are electron elastic
 *                angular tables (Na)</li>
 *  <li> NXS[10] = number of energies for which there are bremsstrahlung
 *                 photon energy tables (Nb)</li>
 *  <li> NXS[11] = length of {energy,energy-loss} table for electron
 *                 bremsstrahlung (Nbl)</li>
 * </ul>
 * The JXS array elements have the following meanings:
 * <ul>
 *  <li> JXS[0] = location of photon energy table (ESZG)</li>
 *  <li> JXS[1] = location of photon incoherent form factors (JINCE)
 *   <ul><li>Ninc = (JXS[2] - JXS[1])/2</li></ul> </li>
 *  <li> JXS[2] = location of photon coherent form factors (JCOHE)
 *   <ul><li>Ncoh = (JXS[3] - JXS[2])/3</li></ul> </li>
 *  <li> JXS[3] = location of obsolete fluorescence data (JFLO)
 *  <li> JXS[4] = location of heating numbers (LHNM)</li>
 *  <li> JXS[5] = location of number of electrons in each shell for
 *                Compton Doppler broadening (LNEPS)</li>
 *  <li> JXS[6] = location of shell binding energies for Compton Doppler
 *                broadening (LBEPS)</li>
 *  <li> JXS[7] = location of shell probabilities for Compton Doppler
 *                broadening (LPIPS)</li>
 *  <li> JXS[8] = location of relative locations of shell data for Compton
 *                Doppler broadening (LSWD)</li>
 *  <li> JXS[9] = location of shell data for Compton Doppler broadening 
 *                (SWD)</li>
 *  <li> JXS[10] = location of subshell designators in ENDF representation
 *                 (SUBSH)</li>
 *  <li> JXS[11] = location of number of electrons in each subshell 
 *                 (SPHEL)</li>
 *  <li> JXS[12] = location of binding energies for each subshell</li>
 *  <li> JXS[13] = location of probabilities for Compton-induced vacancies</li>
 *  <li> JXS[14] = location of number of transitions for fill a vacancy for
 *                 each subshell</li>
 *  <li> JXS[15] = location of subshell photoelectric cross sections
 *                 (SPHEL)</li>
 *  <li> JXS[16] = location of offsets to atomic relaxation transition 
 *                 data (RELO)</li>
 *  <li> JXS[17] = location of atomic relaxation transition data (XPROB)</li>
 *  <li> JXS[18] = location of electron energies (ESZE)</li>
 *  <li> JXS[19] = location of average energy-loss table for electron 
 *                 excitation (EXCIT)</li>
 *  <li> JXS[20] = location of electron elastic angular distribution info
 *                 (ELASI)</li>
 *  <li> JXS[21] = location of electron elastic angular distribution
 *                 tables (ELAS)</li>
 *  <li> JXS[22] = location of electroionization table info (EION)</li>
 *  <li> JXS[23] = location of bremsstrahlung table info (BREMI)</li>
 *  <li> JXS[24] = location of bremsstrahlung photon energy spectrum 
 *                 tables (BREME)</li>
 *  <li> JXS[25] = location of bremsstrahlung electron average energy-loss
 *                 table (BREML)</li>
 */

/*! The XSS electron-photon-relaxation data extractor class
 * \ingroup continuous_energy_epr_table
 */
class XSSEPRDataExtractor
{
  
public:

  //! Constructor
  XSSEPRDataExtractor( const Teuchos::ArrayView<const int>& nxs,
		       const Teuchos::ArrayView<const int>& jxs,
		       const Teuchos::ArrayRCP<const double>& xss );

  //! Destructor
  ~XSSEPRDataExtractor()
  { /* ... */ }

  //! Check if old fluorescence data is present
  bool hasOldFluorescenceData() const;

  //! Check if fluorescence data is present
  bool hasFluorescenceData() const;

  //! Extract the atomic number
  unsigned extractAtomicNumber() const;

  //! Extract the ESZG block
  Teuchos::ArrayView<const double> extractESZGBlock() const;

  //! Extract the incoming photon energy grid
  Teuchos::ArrayView<const double> extractPhotonEnergyGrid() const;
  
  //! Extract the incoherent cross section
  Teuchos::ArrayView<const double> extractIncoherentCrossSection() const;
  
  //! Extract the coherent cross section
  Teuchos::ArrayView<const double> extractCoherentCrossSection() const;
  
  //! Extract the photoelectric cross section
  Teuchos::ArrayView<const double> extractPhotoelectricCrossSection() const;

  //! Extract the pair production cross section 
  Teuchos::ArrayView<const double> extractPairProductionCrossSection() const;

  //! Extract the JINCE block
  Teuchos::ArrayView<const double> extractJINCEBlock() const;

  //! Extract the JCOHE block
  Teuchos::ArrayView<const double> extractJCOHEBlock() const;

  //! Extract the JFLO block
  Teuchos::ArrayView<const double> extractJFLOBlock() const;

  //! Extract the LHNM block
  Teuchos::ArrayView<const double> extractLHNMBlock() const;

  //! Extract the LNEPS block
  Teuchos::ArrayView<const double> extractLNEPSBlock() const;

  //! Extract the LBEPS block
  Teuchos::ArrayView<const double> extractLBEPSBlock() const;

  //! Extract the LPIPS block
  Teuchos::ArrayView<const double> extractLPIPSBlock() const;

  //! Extract the LSWD block
  Teuchos::ArrayView<const double> extractLSWDBlock() const;

  //! Extract the SWD block
  Teuchos::ArrayView<const double> extractSWDBlock() const;

  //! Extract the SUBSH block
  Teuchos::ArrayView<const double> extractSUBSHBlock() const;

  //! Extract the ENDF subshell designators
  Teuchos::ArrayView<const double> extractSubshellENDFDesignators() const;

  //! Extract the subshell occupancies
  Teuchos::ArrayView<const double> extractSubshellOccupancies() const;

  //! Extract the subshell binding energies
  Teuchos::ArrayView<const double> extractSubshellBindingEnergies() const;

  //! Extract the subshell Compton interaction cdf
  Teuchos::ArrayView<const double> extractSubshellComptonInteractionCDF() const;
  
  //! Extract the number of transitions to fill a vacancy in each subshell
  Teuchos::ArrayView<const double> extractSubshellVacancyTransitionPaths() const;

  //! Extract the SPHEL block
  Teuchos::ArrayView<const double> extractSPHELBlock() const;

  //! Extract the RELO block
  Teuchos::ArrayView<const double> extractRELOBlock() const;

  //! Extract the XPROB block
  Teuchos::ArrayView<const double> extractXPROBBlock() const;

  //! Extract the ESZE block
  Teuchos::ArrayView<const double> extractESZEBlock() const;

  //! Extract the incoming electron energy grid
  Teuchos::ArrayView<const double> extractElectronEnergyGrid() const;
  
  //! Extract the electron total cross section
  Teuchos::ArrayView<const double> extractElectronTotalCrossSection() const;

  //! Extract the electron elastic cross section
  Teuchos::ArrayView<const double> extractElasticCrossSection() const;

  //! Extract the bremsstrahlung cross section
  Teuchos::ArrayView<const double> extractBremsstrahlungCrossSection() const;

  //! Extract the excitation cross section
  Teuchos::ArrayView<const double> extractExcitationCrossSection() const;

  //! Extract the total electroionization cross section
  Teuchos::ArrayView<const double> extractElectroionizationCrossSection() const;
  
  //! Extract the electroionization subshell cross sections
  Teuchos::ArrayView<const double> extractElectroionizationSubshellCrossSections() const;

  //! Extract the EXCIT block
  Teuchos::ArrayView<const double> extractEXCITBlock() const;

  //! Extract the ELASI block
  Teuchos::ArrayView<const double> extractELASIBlock() const;

  //! Extract the ELAS block
  Teuchos::ArrayView<const double> extractELASBlock() const;

  //! Extract the EION block
  Teuchos::ArrayView<const double> extractEIONBlock() const;

  //! Extract the BREMI block
  Teuchos::ArrayView<const double> extractBREMIBlock() const;

  //! Extract the BREME block
  Teuchos::ArrayView<const double> extractBREMEBlock() const;

  //! Extract the BREML block
  Teuchos::ArrayView<const double> extractBREMLBlock() const;

private:

  // The nxs array (a copy will be stored)
  Teuchos::Array<int> d_nxs;

  // The jxs array (a copy will be stored so that modifications can be made)
  Teuchos::Array<int> d_jxs;

  // The xss array (data in this array should never be directly modified)
  Teuchos::ArrayRCP<const double> d_xss;

  // The ESZG block (cached for quick access to cross sections in this block)
  Teuchos::ArrayView<const double> d_eszg_block;

  // The SUBSH block (cached for quick access to subshell data in this block)
  Teuchos::ArrayView<const double> d_subsh_block;

  // The ESZE block (cached for quick access to cross sections in this block)
  Teuchos::ArrayView<const double> d_esze_block;
};

} // end Data namespace

#endif // end DATA_XSS_EPR_DATA_EXTRACTOR_HPP

//---------------------------------------------------------------------------//
// end Data_XSSEPRDataExtractor.hpp
//---------------------------------------------------------------------------//
