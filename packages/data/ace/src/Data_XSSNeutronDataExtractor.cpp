//---------------------------------------------------------------------------//
//!
//! \file   Data_XSSNeutronDataExtractor.cpp
//! \author Alex Robinson (primary), additions by Lewis Gross
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

  // names of each block in the order they appear in the manual and the FRENSIE
  // (C++) index they correspond to
  enum blockId  {  esz, // 0
                    nu, // 1 
                    mtr, // 2
                    lqr, // 3
                    tyr, // 4
                    lsig, // 5
                    sig, // 6
                    landb, // 7
                    andb, // 8
                    ldlw, // 9
                    dlw, // 10
                    gpd, // 11
                    mtrp, // 12
                    lsigp, // 13
                    sigp, // 14
                    landp, // 15
                    andp, // 16
                    ldlwp, // 17
                    dlwp, // 18
                    yp, // 19
                    fis, // 20
                    end, // 21
                    lunr, // 22
                    dnu, // 23
                    bdd, //24
                    dnedl, // 25
                    dned // 26 
                    }; 
  
  // Locator key list in increasing order of value, for starts
  std::vector<int> start = {  d_jxs[esz]    ,
                              d_jxs[nu]     ,
                              d_jxs[mtr]    ,
                              d_jxs[lqr]    ,
                              d_jxs[tyr]    ,
                              d_jxs[lsig]   ,
                              d_jxs[sig]    ,
                              d_jxs[landb]  , // added b suffix to correspond locators to actutal angular dist in naming convention
                              d_jxs[andb]   , // added b suffix because of reserved word and, i.e. and block
                              d_jxs[ldlw]   ,
                              d_jxs[dlw]    ,
                              d_jxs[lunr]   , // referred to as iurpt in NJOY
                              d_jxs[dnu]    , // referred to as nud in NJOY 
                              d_jxs[bdd]    , // referred to as dndat in NJOY
                              d_jxs[dnedl]  , // referred to as ,]ldnd in NJOY
                              d_jxs[dned]   , // referred to as dnd in NJOY
                              d_jxs[gpd]    ,
                              d_jxs[mtrp]   ,
                              d_jxs[lsigp]  ,
                              d_jxs[sigp]   ,
                              d_jxs[landp]  ,
                              d_jxs[andp]   ,
                              d_jxs[ldlwp]  ,
                              d_jxs[dlwp]   ,
                              d_jxs[yp]     ,
                              d_jxs[fis]    ,
                              d_jxs[end] } ;

  // find irrelevant blocks and remove them from start
  // TODO

  // likely can ignore as we are not doing particle production in FRENSIE
  /* jxsd(i), i=1,2 ;
  ptype;
  ntro;
  ploc; // */

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

// LOOKHERE, why not syntax highlighting?
// Find next non-zero value in d_jxs array to ensure size parameter in ___ is positive
// const so we don't alter the arrays, static since it isn't in the header file, according to 
// https://stackoverflow.com/questions/42775004/in-c-class-do-i-always-need-to-declare-function-in-the-header-file

static int XSSNeutronDataExtractor::findNextIndex( int start_index ) const
{
  // start index is the index corresponding to the location of the start of
  // next block to be extracted
  // jxs[21] contains the locator for the end of the table, so if there are all zeros until
  // jxs[21], then this is the next locator needed to be passed into size 
  int final_index = start_index;
  while(final_index!=21 && d_jxs[final_index]==-1)
  {
    final_index++;
  }
  return final_index;
}

// Extract the ESZ block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractESZBlock() const
{
  return d_esz_block;
}

// Extract the energy grid from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractEnergyGrid() const
{
  Utility::ArrayView<const double> energy_grid = d_esz_block( 0, d_nxs[2] );
  // Utility::ArrayView<const double> energy_grid = d_esz_block( jxs[0] , d_nxs[2] - jxs[0] ); is maybe better?

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

// Extract the NU (neutrons emitted from fission) block form the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractNUBlock() const
{
  if( d_jxs[1] >= 0 )
  //if( d_jxs[1] != 0 ) LOOKHERE
  { 
    //findNextIndex(1), expected to be 2
    return d_xss_view( d_jxs[1], d_jxs[2]-d_jxs[1] );
  }
  else
    return Utility::ArrayView<const double>();
}

// Extract the MTR (list of ENDF MT numbers) block from the XSS array
/*! \details  nxs[3] is number of neutron reactions excluding elastic, list of MT numbers */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractMTRBlock() const
{
  if( d_nxs[3] != 0 )
    return d_xss_view( d_jxs[2], d_nxs[3] ); 
  else
    return Utility::ArrayView<const double>();
}

// Extract the MTRP (list of ENDF MT numbers) block from the XSS array
/*! \details  nxs[5] is number of photon production reactions
* MTRP is list of MT numbers for photon rections */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractMTRPBlock() const
{
  if( d_nxs[5] != 0 )
    return d_xss_view( d_jxs[12], d_nxs[5] ); 
  else
    return Utility::ArrayView<const double>();
}

// Extract the LQR (list kinematic Q-Values) block from the XSS array
/*! \details  nxs[3] is number of neutron reactions excluding elastic
 * list of MT numbers
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractLQRBlock() const
{
  if( d_nxs[3] != 0 )
    return d_xss_view( d_jxs[3], d_nxs[3] ); 
  else
    return Utility::ArrayView<const double>();
}

// Extract the TYR (neutron reactions other than elastic scattering ) block from the XSS array
/*! \details  nxs[3] is number of neutron reactions excluding elastic
 * secondary neutron information for reatctions 
*/
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractTYRBlock() const
{
  if( d_nxs[3] != 0 )
    return d_xss_view( d_jxs[4], d_nxs[3] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the LSIG block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 * nxs[3] is number of neutron reactions excluding elastic
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractLSIGBlock() const
{
  if( d_nxs[3] != 0 )
    return d_xss_view( d_jxs[5], d_nxs[3] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the LSIGP (list of locators for photon production reactions) block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 * nxs[5] is number of photon production reactions
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractLSIGPBlock() const
{
  if( d_nxs[5] != 0 )
    return d_xss_view( d_jxs[13], d_nxs[5] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the SIG block from the XSS array
/*! \details cross sections for all reactions other than elastic scattering
*/
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractSIGBlock() const
{
  if( d_nxs[3] != 0 )
  {
    //findNextIndex(6), expected to be 7, note jxs[7] always exists, so maybe this one isn't necessary
    return d_xss_view( d_jxs[6], d_jxs[7]-d_jxs[6] );
  }
  else
    return Utility::ArrayView<const double>();
}

// Extract the LAND (list of locators for angular distributions) block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractLANDBlock() const
{
  return d_xss_view( d_jxs[7], d_nxs[4]+1 );
}

// Extract the AND block from the XSS array
/*! \details Angular distributions for all reactions producing secondary neutrons
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractANDBlock() const
{
    //findNextIndex(8), expected to be 9
  return d_xss_view( d_jxs[8], d_jxs[9]-d_jxs[8] );
}

// Extract the LDLW block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 * nxs[4] is the number of reations excluding elastic that produce secondary neutrons
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractLDLWBlock() const
{
  if( d_nxs[4] != 0 )
    return d_xss_view( d_jxs[9], d_nxs[4] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the LDLWP block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 * nxs[5] is number of photon production reactions
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractLDLWPBlock() const
{
  if( d_nxs[5] != 0 )
    return d_xss_view( d_jxs[17], d_nxs[5] );
  else
    return Utility::ArrayView<const double>();
}

/* // old fix with alex, not good
// Extract the DLW block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractDLWBlock() const
{
  if( d_nxs[4] != 0 )
  {
    // If photon data is not present, d_jxs[11] <= 0 which means DLWBlock is the last block
    // In this case, use the size of the entire array (d_nxs[0]) to find the correct size
    if( d_jxs[11] > 0 )
      return d_xss_view( d_jxs[dlwb], d_jxs[dlwb]-d_jxs[dlwb+1] );
    else
      return d_xss_view( d_jxs[10], d_jxz[end]-d_jxs[10] );
  }
  else
    return Utility::ArrayView<const double>();
} // */

// THIS JUSTIFICATION, CHECK 430999.710NC SEQUENTIAL ORDER OF LOCATORS IN JXS ARRAY
// noticed jxs[11] < jxs[23] < jxs[22]
// Extract the DLW block from the XSS array
/*! \details contains energy distributions for all reactions producing secondary 
 *  neutrons except for elastic scattering
 */

Utility::ArrayView<const double> XSSNeutronDataExtractor::extractDLWBlock() const
{
  int dlw_start = dlw;
  int dlw_end;
  if( iurpt != 0)
  {
    dlw_end = iurpt;
  }
  else if(gpd!=0)
  {
    dlw_end = gpd;
  }

  if( d_nxs[4] != 0 )
  { 
    return d_xss_view( dlw_start, dlw_end - dlw_start );
  }
  else
    return Utility::ArrayView<const double>();
}

// Extract the DLWP block from the XSS array
/*! \details contains photon energy distributions for all photon production reactions
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractDLWPBlock() const
{
  if( d_nxs[5] != 0 )
  {
    //findNextIndex(18)
    return d_xss_view( d_jxs[18], d_jxs[19]-d_jxs[18] );
  }
  else
    return Utility::ArrayView<const double>();
}

// Extract the GPD block from the XSS array
/*! \details For newer evaluations the GPD block only contains the total
 * photon production cross section (size=nxs[2]). For older evaluations, the
 * block also contains the 30*20 matrix of secondary photon energies.
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractGPDBlock() const
{
  if( d_jxs[11] >= 0 )
  {
    //findNextIndex(11)
    return d_xss_view( d_jxs[11], d_jxs[12]-d_jxs[11] );
  }
  else
    return Utility::ArrayView<const double>();
}

// Extract the SIGP block from the XSS array
/*! \details ontains cross sections for all photon production reactions.
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractSIGPBlock() const
{
  if( d_nxs[5] != 0 )
  {
    testInvariant(d_jxs[15]>d_jxs[14]);
    return d_xss_view( d_jxs[14], d_jxs[15]-d_jxs[14] );
  }
  else
    return Utility::ArrayView<const double>();
}

// Extract the LANDP block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 * List of angular distribution locators for all photon production reactions
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractLANDPBlock() const
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
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractANDPBlock() const
{
  if( d_nxs[5] != 0 )
  {
    //findNextIndex(16)
    return d_xss_view( d_jxs[16], d_jxs[17]-d_jxs[16] );
  }
  else
    return Utility::ArrayView<const double>();
}

// Extract the YP block from the XSS array
/*! \details Contains a list of MT identifiers of neutron reaction cross sections 
 *  required as photon production yield multipliers
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractYPBlock() const
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
/*! \details Contains the total fission cross section tabulated on the ESZ energy grid
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractFISBlock() const
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
/*! \details Contains the unresolved resonance range probability tables
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractUNRBlock() const
{
  if( d_jxs[22] >= 0 )
  {
    testInvariant(d_jxs[23]>d_jxs[22]);
    return d_xss_view( d_jxs[22], d_jxs[23]-d_jxs[22] );
  }
  else
    return Utility::ArrayView<const double>();
}

// Extract the DNU (delayed NU) block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractDNUBlock() const
{
  if( this->hasDelayedNeutronData() )
  {
    testInvariant( d_jxs[24] > d_jxs[23] );
    return d_xss_view( d_jxs[23], d_jxs[24]-d_jxs[23] );
  }
  else
    return Utility::ArrayView<const double>();
}

// Extract the BDD (basic delayed data) block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractBDDBlock() const
{
  if( this->hasDelayedNeutronData() )
  {
    testInvariant( d_jxs[25] > d_jxs[24] );
    return d_xss_view( d_jxs[24], d_jxs[25] - d_jxs[24] );
  }
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
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractDNEDBlock() const
{
  if( d_nxs[7] != 0 )
  {
    //! \todo Look into if this is a special case or works generallly
    testInvariant( d_jxs[12] <= 0 );
    testInvariant( d_jxs[11] > d_jxs[26] );
    return d_xss_view( d_jxs[26], d_jxs[11] - d_jxs[26] );
  }
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

