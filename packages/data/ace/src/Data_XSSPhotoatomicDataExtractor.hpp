//---------------------------------------------------------------------------//
//!
//! \file   Data_XSSPhotoatomicDataExtractor.hpp
//! \author Alex Robinson
//! \brief  XSS array (from ace table) photoatomic data extractor class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_XSS_PHOTOATOMIC_DATA_EXTRACTOR_HPP
#define DATA_XSS_PHOTOATOMIC_DATA_EXTRACTOR_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayView.hpp>

namespace Data{

/*! \defgroup continuous_energy_photoatomic_table Continuous Energy Photoatomic
 * Table
 * \ingroup ace_table
 * \note This table format is obsolete. The \ref continuous_energy_epr_table
 * "EPR Table" is recommended instead.
 * \todo Add reference for table layout.
 *
 * After a continuous energy photoatomic table has been read by the
 * Data::ACEFileHandler the individual data blocks must be extracted from the
 * XSS array using the Data::XSSPhotoatomicDataExtractor. Both the NXS array
 * and the JXS array are required to successfully extract the blocks. The NXS
 * array elements have the following meanings:
 * <ul>
 *  <li> NXS[0] = length of XSS array</li>
 *  <li> NXS[1] = Z</li>
 *  <li> NXS[2] = number of energies (NES)</li>
 *  <li> NXS[3] = length of fluorescence data divided by 4 (NFLO)</li>
 *  <li> NXS[4] = number of electron shells (NSH)</li>
 * </ul>
 * The JXS array elements have the following meanings:
 * <ul>
 *  <li> JXS[0] = location of energy table (ESZG)</li>
 *  <li> JXS[1] = location of incoherent form factors (JINC)</li>
 *  <li> JXS[2] = location of coherent form factors (JCOH)</li>
 *  <li> JXS[3] = location of fluorescense data (JFLO)</li>
 *  <li> JXS[4] = location of heating numbers (LHNM)</li>
 *  <li> JXS[5] = location of the number of electrons per shell (LNEPS)</li>
 *  <li> JXS[6] = location of binding energy per shell (LBEPS)</li>
 *  <li> JXS[7] = location of prob of interacting per shell (LPIPS)</li>
 *  <li> JXS[8] = location of array of offsets to shellwise data (LSWD)</li>
 *  <li> JXS[9] = location of shellwise data in PDF and CDF form (SWD)</li>
 * </ul>
 */

/*! The XSS photoatomic data extractor class
 * \ingroup continuous_energy_photoatomic_table
 */
class XSSPhotoatomicDataExtractor
{

public:

  //! Constructor
  XSSPhotoatomicDataExtractor( const Teuchos::ArrayView<const int>& nxs,
			       const Teuchos::ArrayView<const int>& jxs,
			       const Teuchos::ArrayRCP<const double>& xss );

  //! Destructor
  ~XSSPhotoatomicDataExtractor()
  { /* ... */ }

  //! Check if fluorescence data is present
  bool hasFluorescenceData() const;

  //! Check if electron shell occupancy data is present
  bool hasElectronShellOccupancyData() const;

  //! Check if compton profile data is present
  bool hasComptonProfileData() const;

  //! Extract the ESZG block
  Teuchos::ArrayView<const double> extractESZGBlock() const;

  //! Extract the incoming energy grid
  Teuchos::ArrayView<const double> extractEnergyGrid() const;

  //! Extract the incoherent cross section
  Teuchos::ArrayView<const double> extractIncoherentCrossSection() const;

  //! Extract the coherent cross section
  Teuchos::ArrayView<const double> extractCoherentCrossSection() const;

  //! Extract the photoelectric cross section
  Teuchos::ArrayView<const double> extractPhotoelectricCrossSection() const;

  //! Extract the pair production cross section
  Teuchos::ArrayView<const double> extractPairProductionCrossSection() const;

  //! Extract the JINC block
  Teuchos::ArrayView<const double> extractJINCBlock() const;

  //! Extract the JCOH block
  Teuchos::ArrayView<const double> extractJCOHBlock() const;

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

private:

  // The nxs array (a copy will be stored)
  Teuchos::Array<int> d_nxs;

  // The jxs array (a copy will be stored so that modifications can be made)
  Teuchos::Array<int> d_jxs;

  // The xss array (data in this array should never be directly modified)
  Teuchos::ArrayRCP<const double> d_xss;

  // The ESZG block (cached for quick access to cross sections in this block)
  Teuchos::ArrayView<const double> d_eszg_block;
};

} // end Data namespace

#endif // end DATA_XSS_PHOTOATOMIC_DATA_EXTRACTOR_HPP

//---------------------------------------------------------------------------//
// end Data_XSSPhotoatomicDataExtractor.hpp
//---------------------------------------------------------------------------//
