//---------------------------------------------------------------------------//
//!
//! \file   Data_XSSElectronDataExtractor.hpp
//! \author Luke Kersting
//! \brief  XSS array (from ace table) electron condensed history extractor dec
//!
//---------------------------------------------------------------------------//

#ifndef DATA_XSS_ELECTRON_DATA_EXTRACTOR_HPP
#define DATA_XSS_EL03_DATA_EXTRACTOR_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "Utility_Vector.hpp"
#include "Utility_Array.hpp"
#include "Utility_ArrayView.hpp"

/*! \defgroup el03_condensed_history_table EL03 Electron Condensed History Table
 * \ingroup ace_table
 * \todo Add reference for table layout.
 *
 * After a continuous energy EL03 table has been read by the
 * Data::ACEFileHandler the individual data blocks must be extracted from the
 * XSS array using the Data::XSSElectronDataExtractor. Both the NXS array
 * and the JXS array are required to successfully extract the blocks.
 */

namespace Data{

/*! The XSS electron condensed history data extractor class
 * \ingroup el03_condensed_history_table
 */
class XSSElectronDataExtractor
{

public:

  //! Constructor
  XSSElectronDataExtractor( const Utility::ArrayView<const int>& nxs,
                            const Utility::ArrayView<const int>& jxs,
                            const std::shared_ptr<const std::vector<double> >& xss );

  //! Destructor
  ~XSSElectronDataExtractor()
  { /* ... */ }

  //! Extract the atomic number
  unsigned extractAtomicNumber() const;

  //! Extract the K edge below which no electron induced relaxation will occur (edg)
  double extractKEdge() const;

  //! Extract the Auger electron emission energy (eek) = (E_K - 2*E_L)
  double extractAugerEmissionEnergy() const;

  //! Extract the radiation stopping power interpolation data block
  Utility::ArrayView<const double> extractStoppingPowersBlock() const;

  //! Extract the Mott scattering correction points data block
  Utility::ArrayView<const double> extractMottScatteringCorrectionBlock() const;

  //! Extract the Riley scattering cross section data block
  Utility::ArrayView<const double> extractRileyBlock() const;

  //! Extract the Bremsstrahlung interpolation data block
  Utility::ArrayView<const double> extractBremsstrahlungInterpolationBlock() const;

  //! Extract the photon to electron energy ratios for spectrum calculations (rkt)
  Utility::ArrayView<const double> extractEnergySpectrumRatios() const;

  //! Extract the photon to electron energy ratios for angular distribution calculations (rka)
  Utility::ArrayView<const double> extractEnergyAngularRatios() const;

  //! Extract the occupation number of electron for each level
  Utility::ArrayView<const double> extractOccupationNumbers() const;

  //! Extract the oscillator strength or binding energy for each level
  Utility::ArrayView<const double> extractBindingEnergy() const;

private:

  // The nxs array (a copy will be stored)
  std::vector<int> d_nxs;

  // The jxs array (a copy will be stored so that modifications can be made)
  std::vector<int> d_jxs;

  // The xss array (data in this array should never be directly modified)
  std::shared_ptr<const std::vector<double> > d_xss;

  // The xss array view (stored for quicker slicing)
  Utility::ArrayView<const double> d_xss_view;
};

} // end Data namespace

#endif // end DATA_XSS_EL03_DATA_EXTRACTOR_HPP

//---------------------------------------------------------------------------//
// end Data_XSSEL03DataExtractor.hpp
//---------------------------------------------------------------------------//
