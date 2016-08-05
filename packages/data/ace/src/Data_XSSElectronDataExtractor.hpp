//---------------------------------------------------------------------------//
//!
//! \file   Data_XSSELectronDataExtractor.hpp
//! \author Luke Kersting
//! \brief  XSS array (from ace table) electron condensed history extractor dec
//!
//---------------------------------------------------------------------------//

#ifndef DATA_XSS_ELECTRON_DATA_EXTRACTOR_HPP
#define DATA_XSS_EL03_DATA_EXTRACTOR_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayView.hpp>
#include <Teuchos_ArrayRCP.hpp>

namespace Data{

/*! \defgroup el03_condensed_history_table EL03 Electron Condensed History Table
 * \ingroup ace_table
 * \todo Add reference for table layout.
 *
 * After a continuous energy EL03 table has been read by the
 * Data::ACEFileHandler the individual data blocks must be extracted from the
 * XSS array using the Data::XSSElectronDataExtractor. Both the NXS array
 * and the JXS array are required to successfully extract the blocks. The NXS
 * array elements have the following meanings:
 * <ul>
 *  <li> NXS[0] = length of XSS array</li>
 *  <li> NXS[1] = Z</li>
 *  <li> NXS[2] = number of radiation stopping power interpolation points</li>
 *  <li> NXS[3] = number of mott scattering cross section corrections</li>
 *  <li> NXS[4] = number of electron energy points for bremsstrahlung
                  interpolation</li>
 *  <li> NXS[5] = number of photon ration points for bremsstrahlung
                  interpolation</li>
 *  <li> NXS[6] = unused</li>
 *  <li> NXS[7] = unused</li>
 *  <li> NXS[8] = number of interpolation points inthe bremsstrahlung database
                  for spectrum calcaulation</li>
 *  <li> NXS[9] = number of interpolation points inthe bremsstrahlung database
                  for angular/energy calcaulation</li>
 *  <li> NXS[10] = number of oscillator points for density effect calculation</li>
 *  <li> NXS[11] = unused</li>
 *  <li> NXS[12] = unused</li>
 *  <li> NXS[13] = unused</li>
 *  <li> NXS[14] = unused</li>
 *  <li> NXS[15] = 3</li>
 * </ul>
 * The JXS array elements have the following meanings:
 * <ul>
 *  <li> JXS[0] = 1 (offset for line data)</li>
 *  <li> JXS[1] = location of radiative stopping power numbers<li>
 *  <li> JXS[2] = location of Mott cross section corrections<li>
 *  <li> JXS[3] = location of Riley cross section evaluation<li>
 *  <li> JXS[4] = location of ITS3.0 bremsstrahlung production database</li>
 *  <li> JXS[5] = unused</li>
 *  <li> JXS[6] = offset for internally calculated Riley cross sections</li>
 *  <li> JXS[7] = offset for internally calculated functions of Z</li>
 *  <li> JXS[8] = location of photon energy ratios (rkt)</li>
 *  <li> JXS[9] = location of photon energy ratio for angular distribution (rka)</li>
 *  <li> JXS[10] = location of oscillator descriptions for density effect
                   calculation</li>
 */

/*! The XSS electron condensed history data extractor class
 * \ingroup el03_condensed_history_table
 */
class XSSElectronDataExtractor
{

public:

  //! Constructor
  XSSElectronDataExtractor( const Teuchos::ArrayView<const int>& nxs,
                            const Teuchos::ArrayView<const int>& jxs,
                            const Teuchos::ArrayRCP<const double>& xss );

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
  Teuchos::ArrayView<const double> extractStoppingPowersBlock() const;

  //! Extract the Mott scattering correction points data block
  Teuchos::ArrayView<const double> extractMottScatteringCorrectionBlock() const;

  //! Extract the Riley scattering cross section data block
  Teuchos::ArrayView<const double> extractRileyBlock() const;

  //! Extract the Bremsstrahlung interpolation data block
  Teuchos::ArrayView<const double> extractBremsstrahlungInterpolationBlock() const;

  //! Extract the photon to electron energy ratios for spectrum calculations (rkt)
  Teuchos::ArrayView<const double> extractEnergySpectrumRatios() const;

  //! Extract the photon to electron energy ratios for angular distribution calculations (rka)
  Teuchos::ArrayView<const double> extractEnergyAngularRatios() const;

  //! Extract the occupation number of electron for each level
  Teuchos::ArrayView<const double> extractOccupationNumbers() const;

  //! Extract the oscillator strength or binding energy for each level
  Teuchos::ArrayView<const double> extractBindingEnergy() const;

private:

  // The nxs array (a copy will be stored)
  Teuchos::Array<int> d_nxs;

  // The jxs array (a copy will be stored so that modifications can be made)
  Teuchos::Array<int> d_jxs;

  // The xss array (data in this array should never be directly modified)
  Teuchos::ArrayRCP<const double> d_xss;
};

} // end Data namespace

#endif // end DATA_XSS_EL03_DATA_EXTRACTOR_HPP

//---------------------------------------------------------------------------//
// end Data_XSSEL03DataExtractor.hpp
//---------------------------------------------------------------------------//
