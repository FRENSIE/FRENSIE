//---------------------------------------------------------------------------//
//!
//! \file   Data_XSSPhotoatomicDataExtractor.hpp
//! \author Alex Robinson
//! \brief  XSS array (from ace table) photoatomic data extractor class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_XSS_PHOTOATOMIC_DATA_EXTRACTOR_HPP
#define DATA_XSS_PHOTOATOMIC_DATA_EXTRACTOR_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "Utility_Vector.hpp"
#include "Utility_Array.hpp"
#include "Utility_ArrayView.hpp"

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
 * and the JXS array are required to successfully extract the blocks.
 */

namespace Data{

/*! The XSS photoatomic data extractor class
 * \ingroup continuous_energy_photoatomic_table
 */
class XSSPhotoatomicDataExtractor
{

public:

  //! Constructor
  XSSPhotoatomicDataExtractor( const Utility::ArrayView<const int>& nxs,
			       const Utility::ArrayView<const int>& jxs,
			       const std::shared_ptr<const std::vector<double> >& xss );

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
  Utility::ArrayView<const double> extractESZGBlock() const;

  //! Extract the incoming energy grid
  Utility::ArrayView<const double> extractEnergyGrid() const;

  //! Extract the incoherent cross section
  Utility::ArrayView<const double> extractIncoherentCrossSection() const;

  //! Extract the coherent cross section
  Utility::ArrayView<const double> extractCoherentCrossSection() const;

  //! Extract the photoelectric cross section
  Utility::ArrayView<const double> extractPhotoelectricCrossSection() const;

  //! Extract the pair production cross section
  Utility::ArrayView<const double> extractPairProductionCrossSection() const;

  //! Extract the JINC block
  Utility::ArrayView<const double> extractJINCBlock() const;

  //! Extract the JCOH block
  Utility::ArrayView<const double> extractJCOHBlock() const;

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
};

} // end Data namespace

#endif // end DATA_XSS_PHOTOATOMIC_DATA_EXTRACTOR_HPP

//---------------------------------------------------------------------------//
// end Data_XSSPhotoatomicDataExtractor.hpp
//---------------------------------------------------------------------------//
