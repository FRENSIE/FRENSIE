//---------------------------------------------------------------------------//
//!
//! \file   Data_XSSEPRDataExtractor.hpp
//! \author Alex Robinson
//! \brief  XSS array (from ace table) electron-photon-relaxation extractor dec
//!
//---------------------------------------------------------------------------//

#ifndef DATA_XSS_EPR_DATA_EXTRACTOR_HPP
#define DATA_XSS_EPR_DATA_EXTRACTOR_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "Utility_Vector.hpp"
#include "Utility_Array.hpp"
#include "Utility_ArrayView.hpp"
#include "Utility_ElectronVoltUnit.hpp"
#include "Utility_BarnUnit.hpp"
#include "Utility_QuantityTraits.hpp"

/*! \defgroup continuous_energy_epr_table Continuous Energy Electron-Photon-Relaxation Table
 * \ingroup ace_table
 * \todo Add reference for table layout.
 *
 * After a continuous energy EPR table has been read by the
 * Data::ACEFileHandler the individual data blocks must be extracted from the
 * XSS array using the Data::XSSPhotoatomicDataExtractor. Both the NXS array
 * and the JXS array are required to successfully extract the blocks.
 */

namespace Data{

/*! The XSS electron-photon-relaxation data extractor class
 * \ingroup continuous_energy_epr_table
 */
class XSSEPRDataExtractor
{

public:

  //! The energy unit
  typedef Utility::Units::MegaElectronVolt EnergyUnit;

  //! The energy quantity
  typedef boost::units::quantity<EnergyUnit> Energy;

  //! The area unit
  typedef Utility::Units::Barn AreaUnit;

  //! The area quantity
  typedef boost::units::quantity<AreaUnit> Area;

  //! Constructor
  XSSEPRDataExtractor( const Utility::ArrayView<const int>& nxs,
		       const Utility::ArrayView<const int>& jxs,
		       const std::shared_ptr<const std::vector<double> >& xss );

  //! Destructor
  ~XSSEPRDataExtractor()
  { /* ... */ }

  //! Check if the file version is eprdata14
  bool isEPRVersion14() const;

  //! Check if old fluorescence data is present
  bool hasOldFluorescenceData() const;

  //! Check if fluorescence data is present
  bool hasFluorescenceData() const;

  //! Extract the atomic number
  unsigned extractAtomicNumber() const;

  //! Extract the ESZG block
  Utility::ArrayView<const double> extractESZGBlock() const;

  //! Extract the incoming photon (log) energy grid
  Utility::ArrayView<const double> extractPhotonEnergyGrid() const;

  //! Extract the incoherent cross section (log)
  Utility::ArrayView<const double> extractIncoherentCrossSection() const;

  //! Extract the coherent cross section (log)
  Utility::ArrayView<const double> extractCoherentCrossSection() const;

  //! Extract the photoelectric cross section (log)
  Utility::ArrayView<const double> extractPhotoelectricCrossSection() const;

  //! Extract the pair production cross section (log)
  Utility::ArrayView<const double> extractPairProductionCrossSection() const;

  //! Extract the JINCE block
  Utility::ArrayView<const double> extractJINCEBlock() const;

  //! Extract the JCOHE block
  Utility::ArrayView<const double> extractJCOHEBlock() const;

  //! Extract the JFLO block
  Utility::ArrayView<const double> extractJFLOBlock() const;

  //! Extract the LHNM block
  Utility::ArrayView<const double> extractLHNMBlock() const;

  //! Extract the LNEPS block
  Utility::ArrayView<const double> extractLNEPSBlock() const;

  //! Extract the LBEPS block
  Utility::ArrayView<const double> extractLBEPSBlock() const;

  //! Extract the LPIPS block
  Utility::ArrayView<const double> extractLPIPSBlock() const;

  //! Extract the LSWD block
  Utility::ArrayView<const double> extractLSWDBlock() const;

  //! Extract the SWD block
  Utility::ArrayView<const double> extractSWDBlock() const;

  //! Extract the SUBSH block
  Utility::ArrayView<const double> extractSUBSHBlock() const;

  //! Extract the ENDF subshell designators
  Utility::ArrayView<const double> extractSubshellENDFDesignators() const;

  //! Extract the subshell occupancies
  Utility::ArrayView<const double> extractSubshellOccupancies() const;

  //! Extract the subshell binding energies
  Utility::ArrayView<const double> extractSubshellBindingEnergies() const;

  //! Extract the subshell binding energies
  Utility::ArrayView<const Energy> extractSubshellBindingEnergiesInMeV() const;

  //! Extract the subshell Compton interaction cdf
  Utility::ArrayView<const double> extractSubshellComptonInteractionCDF() const;

  //! Extract the number of transitions to fill a vacancy in each subshell
  Utility::ArrayView<const double> extractSubshellVacancyTransitionPaths() const;

  //! Extract the SPHEL block
  Utility::ArrayView<const double> extractSPHELBlock() const;

  //! Extract the RELO block
  Utility::ArrayView<const double> extractRELOBlock() const;

  //! Extract the XPROB block
  Utility::ArrayView<const double> extractXPROBBlock() const;

  //! Extract the ESZE block
  Utility::ArrayView<const double> extractESZEBlock() const;

  //! Extract the ESZE2 block - only in epr14
  Utility::ArrayView<const double> extractESZE2Block() const;

  //! Extract the incoming electron energy grid
  Utility::ArrayView<const double> extractElectronEnergyGrid() const;

  //! Extract the incoming electron energy grid
  Utility::ArrayView<const Energy> extractElectronEnergyGridInMeV() const;

  //! Extract the electron total cross section
  Utility::ArrayView<const double> extractElectronTotalCrossSection() const;

  //! Extract the electron total cross section
  Utility::ArrayView<const Area> extractElectronTotalCrossSectionInBarns() const;

  //! Extract the electron elastic total cross section
  Utility::ArrayView<const double> extractElasticTotalCrossSection() const;

  //! Extract the electron elastic total cross section
  Utility::ArrayView<const Area> extractElasticTotalCrossSectionInBarns() const;

  //! Extract the electron elastic cutoff cross section ( mu = -1 to 0.999999 )
  Utility::ArrayView<const double> extractElasticCutoffCrossSection() const;

  //! Extract the electron elastic cutoff cross section ( mu = -1 to 0.999999 )
  Utility::ArrayView<const Area> extractElasticCutoffCrossSectionInBarns() const;

  //! Extract the electron elastic transport cross section
  Utility::ArrayView<const double> extractElasticTransportCrossSection() const;

  //! Extract the electron elastic transport cross section
  Utility::ArrayView<const Area> extractElasticTransportCrossSectionInBarns() const;

  //! Extract the bremsstrahlung cross section
  Utility::ArrayView<const double> extractBremsstrahlungCrossSection() const;

  //! Extract the bremsstrahlung cross section
  Utility::ArrayView<const Area> extractBremsstrahlungCrossSectionInBarns() const;

  //! Extract the excitation cross section
  Utility::ArrayView<const double> extractExcitationCrossSection() const;

  //! Extract the excitation cross section
  Utility::ArrayView<const Area> extractExcitationCrossSectionInBarns() const;

  //! Extract the total electroionization cross section
  Utility::ArrayView<const double> extractElectroionizationCrossSection() const;

  //! Extract the total electroionization cross section
  Utility::ArrayView<const Area> extractElectroionizationCrossSectionInBarns() const;

  //! Extract the electroionization subshell cross sections
  Utility::ArrayView<const double> extractElectroionizationSubshellCrossSections() const;

  //! Extract the electroionization subshell cross sections
  Utility::ArrayView<const Area> extractElectroionizationSubshellCrossSectionsInBarns() const;

  //! Extract the EXCIT block
  Utility::ArrayView<const double> extractEXCITBlock() const;

  //! Extract the ELASI block
  Utility::ArrayView<const double> extractELASIBlock() const;

  //! Extract the ELAS block
  Utility::ArrayView<const double> extractELASBlock() const;

  //! Extract the EION block
  Utility::ArrayView<const double> extractEIONBlock() const;

  //! Extract the BREMI block
  Utility::ArrayView<const double> extractBREMIBlock() const;

  //! Extract the BREME block
  Utility::ArrayView<const double> extractBREMEBlock() const;

  //! Extract the BREML block
  Utility::ArrayView<const double> extractBREMLBlock() const;

  //! Return the EION data block location in xss array
  unsigned returnEIONLoc() const;

private:

  // The nxs array (a copy will be stored)
  std::vector<int> d_nxs;

  // The jxs array (a copy will be stored so that modifications can be made)
  std::vector<int> d_jxs;

  // The xss array (data in this array should never be directly modified)
  std::shared_ptr<const std::vector<double> > d_xss;

  // The xss array view (stored for quicker slicing)
  Utility::ArrayView<const double> d_xss_view;

  // The ESZG block (cached for quick access to cross sections in this block)
  Utility::ArrayView<const double> d_eszg_block;

  // The SUBSH block (cached for quick access to subshell data in this block)
  Utility::ArrayView<const double> d_subsh_block;

  // The ESZE block (cached for quick access to cross sections in this block)
  Utility::ArrayView<const double> d_esze_block;

  // The ESZE2 block (cached for quick access to cross sections in this block)
  Utility::ArrayView<const double> d_esze2_block;
};

} // end Data namespace

#endif // end DATA_XSS_EPR_DATA_EXTRACTOR_HPP

//---------------------------------------------------------------------------//
// end Data_XSSEPRDataExtractor.hpp
//---------------------------------------------------------------------------//
