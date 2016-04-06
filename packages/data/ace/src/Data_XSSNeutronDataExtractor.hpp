//---------------------------------------------------------------------------//
//!
//! \file   Data_XSSNeutronDataExtractor.hpp
//! \author Alex Robinson
//! \brief  XSS array (from ace table) neutron data extractor class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_XSS_NEUTRON_DATA_EXTRACTOR_HPP
#define DATA_XSS_NEUTRON_DATA_EXTRACTOR_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayView.hpp>

namespace Data{

/*! \defgroup continuous_energy_neutron_table Continuous Energy Neutron Table
 * \ingroup ace_table
 *
 * After a continuous energy neutron table has been read by the 
 * Data::ACEFileHandler the individual data blocks must be extracted from 
 * the XSS array using the Data::XSSNeutronDataExtractor. Both the NXS array 
 * and the JXS array are required to successfully extract the blocks. The NXS 
 * array elements have the following meanings:
 * <ul>
 *  <li> NXS[0]  = length of XSS array
 *  <li> NXS[1]  = 1000*Z+A (ZA)
 *  <li> NXS[2]  = number of energies (NES)
 *  <li> NXS[3]  = number of reactions excluding elastic (NTR)
 *  <li> NXS[4]  = number of reactions having secondary neutrons excluding 
 *                 elastic (NR)
 *  <li> NXS[5]  = number of photon production reactions (NTRP)
 *  <li> NXS[6]  = N/A
 *  <li> NXS[7]  = number of delayed neutron precursor families (NPCR)
 *  <li> NXS[8]  = N/A
 *  <li> NXS[9]  = N/A
 *  <li> NXS[10] = N/A
 *  <li> NXS[11] = N/A
 *  <li> NXS[12] = N/A
 *  <li> NXS[13] = N/A
 *  <li> NXS[14] = number of PIKMT reactions (NT)
 *  <li> NXS[15] = 0 (normal photon production) or -1 (do not produce photons)
 * </ul>
 * The JXS array elements have the following meanings:
 * <ul>
 *  <li> JXS[0]  = location of energy table (ESZ)
 *  <li> JXS[1]  = location of fission nu data (NU)
 *  <li> JXS[2]  = location of MT array (MTR)
 *  <li> JXS[3]  = location of Q-value array (LQR)
 *  <li> JXS[4]  = location of reaction multiplicity array (TYR)
 *  <li> JXS[5]  = location of table of cross section locators (LSIG)
 *  <li> JXS[6]  =  location of cross sections (SIG)
 *  <li> JXS[7]  = location of table of angular distribution locators (LAND)
 *  <li> JXS[8]  = location of angular distributions (AND)
 *  <li> JXS[9]  = location of table of energy distribution locators (LDLW)
 *  <li> JXS[10] = location of energy distribution (DLW)
 *  <li> JXS[11] = location of photon production total cross section (GPD)
 *  <li> JXS[12] = location of photon production MT array (MTRP)
 *  <li> JXS[13] = location of table of photon production cross section 
 *                 locators (LSIGP)
 *  <li> JXS[14] = location of table of photon production cross sections (SIGP)
 *  <li> JXS[15] = location of table of photon production angular distribution
 *                 locators (LANDP)
 *  <li> JXS[16] = location of photon production angular distributions (ANDP)
 *  <li> JXS[17] = location of table of photon production energy distribution
 *                 locators (LDLWP)
 *  <li> JXS[18] = location of photon production energy distributions (DLWP)
 *  <li> JXS[19] = location of table of yield multipliers (YP)
 *  <li> JXS[20] = location of total fission cross section (FIS)
 *  <li> JXS[21] = location of last element of the table (END)
 *  <li> JXS[22] = location of probability tables (LUNR)
 *  <li> JXS[23] = location of delayed nubar data (DNU)
 *  <li> JXS[24] = location of basic delayed data such as decay constants and
 *                 probabilities (BDD)
 *  <li> JXS[25] = location of table of energy distribution locators (DNEDL)
 *  <li> JXS[26] = location of energy distributions (DNED)
 *  <li> JXS[27] = N/A
 *  <li> JXS[28] = N/A
 *  <li> JXS[29] = N/A
 *  <li> JXS[30] = N/A
 *  <li> JXS[31] = N/A
 * </ul>
 */

/*! The XSS neutron data extractor class
 * \ingroup continuous_energy_neutron_table
 */
class XSSNeutronDataExtractor
{

public:

  //! Constructor
  XSSNeutronDataExtractor( const Teuchos::ArrayView<const int>& nxs,
			   const Teuchos::ArrayView<const int>& jxs,
			   const Teuchos::ArrayRCP<const double>& xss );

  //! Destructor
  ~XSSNeutronDataExtractor()
  { /* ... */ }

  //! Check if the nuclide is fissionable
  bool hasFissionData() const;

  //! Check if the nuclide has delayed neutron data
  bool hasDelayedNeutronData() const;

  //! Check if the nuclide has unresolved resonances
  bool hasUnresolvedResonanceData() const;

  //! Extract the ESZ block from the XSS array
  Teuchos::ArrayView<const double> extractESZBlock() const;

  //! Extract the energy grid from the XSS array
  Teuchos::ArrayView<const double> extractEnergyGrid() const;

  //! Extract the total cross section from the XSS array
  Teuchos::ArrayView<const double> extractTotalCrossSection() const;

  //! Extract the total absorption cross section from the XSS array
  Teuchos::ArrayView<const double> extractTotalAbsorptionCrossSection() const;

  //! Extract the total elastic cross section from the XSS array
  Teuchos::ArrayView<const double> extractElasticCrossSection() const;

  //! Extract the average heating numbers from the XSS array
  Teuchos::ArrayView<const double> extractAverageHeatingNumbers() const;

  //! Extract the NU block form the XSS array
  Teuchos::ArrayView<const double> extractNUBlock() const;

  //! Extract the MTR block from the XSS array
  Teuchos::ArrayView<const double> extractMTRBlock() const;

  //! Extract the MTRP block from the XSS array
  Teuchos::ArrayView<const double> extractMTRPBlock() const;

  //! Extract the LQR block from the XSS array
  Teuchos::ArrayView<const double> extractLQRBlock() const;

  //! Extract the TYR block from the XSS array
  Teuchos::ArrayView<const double> extractTYRBlock() const;

  //! Extract the LSIG block from the XSS array
  Teuchos::ArrayView<const double> extractLSIGBlock() const;
  
  //! Extract the LSIGP block from the XSS array
  Teuchos::ArrayView<const double> extractLSIGPBlock() const;

  //! Extract the SIG block from the XSS array
  Teuchos::ArrayView<const double> extractSIGBlock() const;

  //! Extract the LAND block from the XSS array
  Teuchos::ArrayView<const double> extractLANDBlock() const;

  //! Extract the AND block from the XSS array
  Teuchos::ArrayView<const double> extractANDBlock() const;

  //! Extract the LDLW block from the XSS array
  Teuchos::ArrayView<const double> extractLDLWBlock() const;

  //! Extract the LDLWP block from the XSS array
  Teuchos::ArrayView<const double> extractLDLWPBlock() const;

  //! Extract the DLW block from the XSS array
  Teuchos::ArrayView<const double> extractDLWBlock() const;

  //! Extract the DLWP block from the XSS array
  Teuchos::ArrayView<const double> extractDLWPBlock() const;

  //! Extract the GPD block from the XSS array
  Teuchos::ArrayView<const double> extractGPDBlock() const;

  //! Extract the SIGP block from the XSS array
  Teuchos::ArrayView<const double> extractSIGPBlock() const;

  //! Extract the LANDP block from the XSS array
  Teuchos::ArrayView<const double> extractLANDPBlock() const;

  //! Extract the ANDP block from the XSS array
  Teuchos::ArrayView<const double> extractANDPBlock() const;

  //! Extract the YP block from the XSS array
  Teuchos::ArrayView<const double> extractYPBlock() const;

  //! Extract the FIS block from the XSS array
  Teuchos::ArrayView<const double> extractFISBlock() const;

  //! Extract the UNR block from the XSS array
  Teuchos::ArrayView<const double> extractUNRBlock() const;

  //! Extract the DNU (delayed NU) block form the XSS array
  Teuchos::ArrayView<const double> extractDNUBlock() const;

  //! Extract the BDD (basic delayed data) block from the XSS array
  Teuchos::ArrayView<const double> extractBDDBlock() const;

  //! Extract the DNEDL (delayed neutron LDLW) block from the XSS array
  Teuchos::ArrayView<const double> extractDNEDLBlock() const;

  //! Extract the DNED (delayed neutron DLW) block from the XSS array
  Teuchos::ArrayView<const double> extractDNEDBlock() const;
  
  //! Extract the Ace Laws used for each MT Number from the XSS array
  Teuchos::ArrayRCP<double> extractAceLaws() const;

private:

  // The nxs array (a copy will be stored)
  Teuchos::Array<int> d_nxs;
  
  // The jxs array (a copy will be stored so that modifications can be made)
  Teuchos::Array<int> d_jxs;

  // The xss array (data in this array should never be directly modified)
  Teuchos::ArrayRCP<const double> d_xss;

  // The ESZ block (cached for quick access to cross sections in this block)
  Teuchos::ArrayView<const double> d_esz_block;
};

} // end Data namespace

#endif // end DATA_XSS_NEUTRON_DATA_EXTRACTOR_HPP

//---------------------------------------------------------------------------//
// end Data_XSSNeutronDataExtractor.hpp
//---------------------------------------------------------------------------//
