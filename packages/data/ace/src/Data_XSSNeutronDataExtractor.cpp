//---------------------------------------------------------------------------//
//!
//! \file   Data_XSSNeutronDataExtractor.cpp
//! \author Alex Robinson, Lewis Gross
//! \brief  XSS array (from ace table) neutron data extractor class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_ExceptionCatchMacros.hpp"

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

  // Create the XSS view
  d_xss_view = Utility::arrayViewOfConst( *d_xss );

  // Extract and cache the ESZ block
  d_esz_block = d_xss_view( d_jxs[0], 5*d_nxs[nes] );

  // sort given jxs array into map data structure to be used later
  // perhaps turn below into a class method and call from the constructor

  // first, add available blocks 
  // this is the index of the last block that FRENSIE knows how to process
  // if FRENSIE gains particle production blocks or new blocks from MCNP, 
  // this should be changed from dned to the index of the last block in the array
  int last_block = dned;
  std::vector<std::pair<int,int> > available_blocks;
    for(int block = 0 ; block <= last_block ; block++) {
    if(d_jxs[block]>=0) {
      available_blocks.push_back(std::make_pair(d_jxs[block],block));
    }
  }

  // sort pairs by first (jxs locations) to get monotone order
  std::sort(available_blocks.begin(),available_blocks.end());

  // first parameter is the block's start, second parameter is the length of that block
  for(std::vector<std::pair<int,int> >::iterator soi=available_blocks.begin() ; soi<available_blocks.end() -1 ; soi++ ) {
      // soi stands for sorted order iterator 
      int block_id = soi->second;    // grab the block corresponding to the first value in the pair
      int start = soi->first;       // grab the jxs position corresponding to the current block
      int next_start = (soi+1)->first;   // grab the jxs position corresponding to the current block
      int length = next_start - start ;    // the difference next - curr is the length of the block curr
      block_to_start_length_pair.insert(std::make_pair(block_id,std::make_pair(start,length)));
  }
}

// Check if the nuclide is fissionable
bool XSSNeutronDataExtractor::hasFissionData() const
{
  // need a const iterator since this function is declared const
  std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(nu);
  if(it!=block_to_start_length_pair.end() && it->second.first >= 0 ) // check that d_jxs[nu]>=0
    return true;
  else
    return false;
}

// check if the nuclide has delayed neutron data
bool XSSNeutronDataExtractor::hasDelayedNeutronData() const
{
  // need a const iterator since this function is declared const
  std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(dnu);
  if(it!=block_to_start_length_pair.end() && it->second.first >= 0)  // check that d_jxs[dnu]>=0
    return true;
  else
    return false;
}

// Check if the nuclide has unresolved resonances
bool XSSNeutronDataExtractor::hasUnresolvedResonanceData() const
{
  // need a const iterator since this function is declared const
  std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(lunr);
  if( it!=block_to_start_length_pair.end() && it->second.first >= 0) // check that d_jxs[lunr]>=0
    return true;
  else
    return false;
}

// given a block index, return the size in the map
int XSSNeutronDataExtractor::queryBlockSize(int block_index) const
{
  // need a const iterator since this function is declared const
  std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(block_index);
  if ( it!=block_to_start_length_pair.end() ) {
    // if block exists, return the length 
    return it->second.second;
  } else {
    // block does not exist, return 0
    return 0;
    } 
}

int XSSNeutronDataExtractor::queryNXS(int nxs_index) const
{
  if(nxs_index < last_nxs) {
    return d_nxs[nxs_index];
  } else {
    return 0;
  }
}

// TODO, should we return the negative 1 or just a 0 in that case?
int XSSNeutronDataExtractor::queryJXS(int jxs_index) const 
{
  if(jxs_index < last_jxs) {
    return d_jxs[jxs_index];
  } else {
    return 0;
  }
}

// Extract the ESZ block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractESZBlock() const
{
  return d_esz_block;
}

// Extract the energy grid from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractEnergyGrid() const
{
  Utility::ArrayView<const double> energy_grid = d_esz_block( 0, d_nxs[nes] );

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
                  Utility::ArrayView<const Energy>::size_type(d_nxs[nes]) ); 

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
  return d_esz_block( d_nxs[nes], d_nxs[nes] );
}

// Extract the total cross section from the XSS array
auto XSSNeutronDataExtractor::extractTotalCrossSectionInBarns() const -> Utility::ArrayView<const Area>
{
  return Utility::ArrayView<const Area>(
           Utility::reinterpretAsQuantity<Area>( d_esz_block.data()+d_nxs[nes] ),
           Utility::ArrayView<const Area>::size_type(d_nxs[nes]) );
}

// Extract the total absorption cross section from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractTotalAbsorptionCrossSection() const
{
  return d_esz_block( 2*d_nxs[nes], d_nxs[nes] );
}

// Extract the total absorption cross section from the XSS array
auto XSSNeutronDataExtractor::extractTotalAbsorptionCrossSectionInBarns() const -> Utility::ArrayView<const Area>
{
  return Utility::ArrayView<const Area>(
         Utility::reinterpretAsQuantity<Area>( d_esz_block.data()+2*d_nxs[nes] ),
         Utility::ArrayView<const Area>::size_type(d_nxs[nes]) );
}

// Extract the elastic cross section from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractElasticCrossSection() const
{
  return d_esz_block( 3*d_nxs[nes], d_nxs[nes] );
}

// Extract the elastic cross section from the XSS array
auto XSSNeutronDataExtractor::extractElasticCrossSectionInBarns() const -> Utility::ArrayView<const Area>
{
  return Utility::ArrayView<const Area>(
         Utility::reinterpretAsQuantity<Area>( d_esz_block.data()+3*d_nxs[nes] ),
         Utility::ArrayView<const Area>::size_type(d_nxs[nes]) );
}

// Extract the average heating numbers from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractAverageHeatingNumbers() const
{
  return d_esz_block( 4*d_nxs[nes], d_nxs[nes] );
}

// Extract the average heating numbers from the XSS array
auto XSSNeutronDataExtractor::extractAverageHeatingNumbersInMeV() const -> Utility::ArrayView<const Energy>
{
  return Utility::ArrayView<const Energy>(
       Utility::reinterpretAsQuantity<Energy>( d_esz_block.data()+4*d_nxs[nes] ),
       Utility::ArrayView<const Energy>::size_type(d_nxs[nes]) );
}

// Extract the NU block form the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractNUBlock() const
{
  // need a const iterator since this function is declared const
  std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(nu);
  if ( it!=block_to_start_length_pair.end() && it->second.first >= 0) {
    // this block requires a subtraction, use map implementation for both
    int start = it->second.first;
    int length = it->second.second;
    return d_xss_view( start , length);
  } else {
    return Utility::ArrayView<const double>();
  }
}

// Extract the MTR block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractMTRBlock() const
{
  // need a const iterator since this function is declared const
  std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(mtr);
  if ( it!=block_to_start_length_pair.end() && d_nxs[ntr] != 0 ) {
    // this block has a length defined by the MCNP manual
    int start = it->second.first;  
    int length = d_nxs[ntr];
    return d_xss_view( start , length );
  } else {
    return Utility::ArrayView<const double>(); 
  }
}

// Extract the MTRP block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractMTRPBlock() const
{
  // need a const iterator since this function is declared const
  std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(mtrp);
  if ( it!=block_to_start_length_pair.end() && d_nxs[ntrp] != 0 ) {
    // this block has a length defined by the MCNP manual
    int start = it->second.first;  
    int length = d_nxs[ntrp];
    return d_xss_view( start , length);
  } else {
    return Utility::ArrayView<const double>();
  }
}

// Extract the LQR block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractLQRBlock() const
{
  // need a const iterator since this function is declared const
  std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(lqr);
  if ( it!=block_to_start_length_pair.end() && d_nxs[ntr] != 0 ) {
    // this block has a length defined by the MCNP manual
    int start = it->second.first;  
    int length = d_nxs[ntr];
    return d_xss_view( start , length );
  } else {
    return Utility::ArrayView<const double>();
  }
}

// Extract the TYR block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractTYRBlock() const
{
  // need a const iterator since this function is declared const
  std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(tyr);

  if ( it!=block_to_start_length_pair.end() && d_nxs[ntr] != 0 ) {
    // this block has a length defined by the MCNP manual
    int start = it->second.first;  
    int length = d_nxs[ntr];
    return d_xss_view( start , length );
  } else {
    return Utility::ArrayView<const double>();
  }
}

// Extract the LSIG block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractLSIGBlock() const
{
  // need a const iterator since this function is declared const
  std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(lsig);
  if ( it!=block_to_start_length_pair.end() && d_nxs[ntr] != 0 ) {
    // this block has a length defined by the MCNP manual
    int start = it->second.first;  
    int length = d_nxs[ntr];
    return d_xss_view( start , length );
  } else {
    return Utility::ArrayView<const double>();
  }
}

// Extract the LSIGP block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractLSIGPBlock() const
{
  // need a const iterator since this function is declared const 
  std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(lsigp); 
  if ( it!=block_to_start_length_pair.end() && d_nxs[ntrp] != 0 ) {
    // this block has a length defined by the MCNP manual
    int start = it->second.first;  
    int length = d_nxs[ntrp];
    return d_xss_view( start , length);
  } else {
    return Utility::ArrayView<const double>();
  }
}

// Extract the SIG block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractSIGBlock() const
{
  // need a const iterator since this function is declared const
  std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(sig);
  if ( it!=block_to_start_length_pair.end() && d_nxs[ntr] != 0 ) {
    // no fixed size in the MCNP manual, this block requires the map implementation 
    int start = it->second.first;
    int length = it->second.second;
    return d_xss_view( start , length );
  } else {
    return Utility::ArrayView<const double>();
  }
}

// Extract the LAND block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractLANDBlock() const
{
  // need a const iterator since this function is declared const
  std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(landb);
  if ( it!=block_to_start_length_pair.end() ){ 
    // this block has a length defined by the MCNP manual
    int start = it->second.first;
    int length = d_nxs[nr] + 1 ;
    return d_xss_view( start , length);
  } else {
    // this else statement should never be entered
    // because there should always be an key 
    // corresponding to the and block in the map
    THROW_EXCEPTION(std::runtime_error, "Entered a forbidden else statement: expected land block to be found in jxs block map ")
    THROW_EXCEPTION(std::logic_error, "Entered a forbidden else statement: expected land block to be found in jxs block map ")
  }
}

// Extract the AND block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractANDBlock() const
{
  // need a const iterator since this function is declared const
  std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(andb);
  if ( it!=block_to_start_length_pair.end() ) {
    // no fixed size in the MCNP manual, this block requires the map implementation 
    int start = it->second.first;
    int length = it->second.second;
    return d_xss_view( start, length );
  } else {
    // this else statement should never be entered
    // because there should always be an key 
    // corresponding to the and block in the map
    //THROW_EXCEPTION(std::runtime_error, "Entered a forbidden else statement: expected and block to be found in jxs block map ")
    THROW_EXCEPTION(std::logic_error, "Entered a forbidden else statement: expected and block to be found in jxs block map ")
  }
}

// Extract the LDLW block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractLDLWBlock() const
{
  // need a const iterator since this function is declared const
  std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(ldlw);
  if ( it!=block_to_start_length_pair.end() && d_nxs[nr] != 0 ) {
    // this block has a length defined by the MCNP manual
    int start = it->second.first;
    int length = d_nxs[nr];
    return d_xss_view( start , length );
  } else {
    return Utility::ArrayView<const double>();
  }
}

// Extract the LDLWP block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractLDLWPBlock() const
{
  // need a const iterator since this function is declared const
  std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(ldlwp);
  if ( it!=block_to_start_length_pair.end() && d_nxs[ntrp] != 0 ) {
    // this block has a length defined by the MCNP manual
    int start = it->second.first;  
    int length = d_nxs[ntrp];
    return d_xss_view( start , length);
  }  else {
    return Utility::ArrayView<const double>();
  }
}

// Extract the DLW block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractDLWBlock() const
{
  // need a const iterator since this function is declared const
  std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(dlw);
  if( it!=block_to_start_length_pair.end() && d_nxs[nr] != 0 ) {
    // no fixed size in the MCNP manual, this block requires the map implementation 
    int start = it->second.first;
    int length = it->second.second;
    return d_xss_view( start , length );
  } else {
    return Utility::ArrayView<const double>();
  }
}

// Extract the DLWP block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractDLWPBlock() const
{
  // need a const iterator since this function is declared const
  std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(dlwp);
  if( it!=block_to_start_length_pair.end() && d_nxs[ntrp] != 0 ) {
    // no fixed size in the MCNP manual, this block requires the map implementation 
    int start = it->second.first;
    int length = it->second.second;
    return d_xss_view( start , length);
  } else {
    return Utility::ArrayView<const double>();
  }
}

// Extract the GPD block from the XSS array
/*! \details For newer evaluations the GPD block only contains the total
 * photon production cross section (size=nxs[2]). For older evaluations, the
 * block also contains the 30*20 matrix of secondary photon energies.
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractGPDBlock() const
{
  // need a const iterator since this function is declared const
  std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(gpd);
  if( it!=block_to_start_length_pair.end() && it->second.first >= 0 ) {
    // no fixed size in the MCNP manual, this block requires the map implementation 
    int start = it->second.first;
    int length = it->second.second;
    return d_xss_view( start , length);
  } else {
    return Utility::ArrayView<const double>();
  }
}

// Extract the SIGP block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractSIGPBlock() const
{
  // need a const iterator since this function is declared const
  std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(sigp);
  if ( it!=block_to_start_length_pair.end() && d_nxs[ntrp] != 0 ) {
    // no fixed size in the MCNP manual, this block requires the map implementation 
    int start = it->second.first;
    int length = it->second.second;
    return d_xss_view( start , length );
  } else {
    return Utility::ArrayView<const double>();
  }
}

// Extract the LANDP block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractLANDPBlock() const
{
  // need a const iterator since this function is declared const
  std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(landp);
  if( it!=block_to_start_length_pair.end() && d_nxs[ntrp] != 0 ) {
    // this block has a length defined by the MCNP manual
    int start = it->second.first;  
    int length = d_nxs[ntrp];
    return d_xss_view( start , length );
  } else {
    return Utility::ArrayView<const double>();
  }
}

// Extract the ANDP block from the XSS array
/*! \details Even if photon production interactions are present (nxs[5] != 0 ),
 * it is possible that there will be no ANDP block. This can occur if every
 * entry in the LANDP block is 0 (indicating that the outgoing photon angle is
 * isotropic in the lab frame).
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractANDPBlock() const
{
  // need a const iterator since this function is declared const
  std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(andp);
  if( it!=block_to_start_length_pair.end() && d_nxs[ntrp] != 0 ) {
    // no fixed size in the MCNP manual, this block requires the map implementation 
    int start = it->second.first;
    int length = it->second.second;
    return d_xss_view( start , length );
  } else {
    return Utility::ArrayView<const double>();
  }
}

// Extract the YP block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractYPBlock() const
{
  // need a const iterator since this function is declared const
  std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(yp);
  if( it!=block_to_start_length_pair.end() && d_nxs[ntrp] != 0 ) {
    // this block has a length defined by the MCNP manual
    int start = it->second.first;  
    int length = (int)d_xss_view[d_jxs[yp]] + 1;
    return d_xss_view( start , length );
  } else {
    return Utility::ArrayView<const double>();
  }
}

// Extract the FIS block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractFISBlock() const
{
  // need a const iterator since this function is declared const
  std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(fis);
  if( it!=block_to_start_length_pair.end() && d_jxs[fis] >= 0 ) { 
    // this block has a length defined by the MCNP manual
    int start = it->second.first;
    int length = (int)d_xss_view[d_jxs[fis]+1] + 2;
    return d_xss_view( start , length );
  } else {
    return Utility::ArrayView<const double>();
  }
}

// Extract the UNR block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractUNRBlock() const
{
  // need a const iterator since this function is declared const
  std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(lunr);
  if( it!=block_to_start_length_pair.end() && it->second.first >= 0 ) {  
    // no fixed size in the MCNP manual, this block requires the map implementation 
    int start = it->second.first;
    int length = it->second.second;
    return d_xss_view( start , length);
  } else {
    return Utility::ArrayView<const double>();
  }
}

// Extract the DNU (delayed NU) block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractDNUBlock() const
{
  if( this->hasDelayedNeutronData() ){
  // need a const iterator since this function is declared const
    std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(dnu);
    // no fixed size in the MCNP manual, this block requires the map implementation 
    int start = it->second.first;
    int length = it->second.second;
    return d_xss_view( start, length);
  } else { 
    return Utility::ArrayView<const double>(); 
  }
}

// Extract the BDD (basic delayed data) block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractBDDBlock() const
{
  if( this->hasDelayedNeutronData() ){
    // need a const iterator since this function is declared const
    std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(bdd);
    // no fixed size in the MCNP manual, this block requires the map implementation 
    int start = it->second.first;
    int length = it->second.second;
    return d_xss_view( start, length);
  } else {
    return Utility::ArrayView<const double>();
  }
}

// Extract the DNEDL (delayed neutron LDLW) block from the XSS array
/*! \details All indices in this array are for Fortran arrays.
 * Subtract by one to get the corresponding C array indices.
 */
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractDNEDLBlock() const
{
  // need a const iterator since this function is declared const
  std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(dnedl);
  if( it!=block_to_start_length_pair.end() && d_nxs[npcr] != 0 ) {
    // this block has a length defined by the MCNP manual
    int start = it->second.first;
    int length = d_nxs[npcr];
    return d_xss_view( start , length);
  } else {
    return Utility::ArrayView<const double>();
  }
}

// Extract the delayed neutron DLW block from the XSS array
Utility::ArrayView<const double> XSSNeutronDataExtractor::extractDNEDBlock() const
{
  // need a const iterator since this function is declared const
  std::map<int,std::pair<int,int> >::const_iterator it = block_to_start_length_pair.find(dned);
  if( it!=block_to_start_length_pair.end() && d_nxs[npcr] != 0 ) {
    // no fixed size in the MCNP manual, this block requires the map implementation 
    int start = it->second.first;
    int length = it->second.second;
    return d_xss_view( start , length);
  } else {
    return Utility::ArrayView<const double>();
  }
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

