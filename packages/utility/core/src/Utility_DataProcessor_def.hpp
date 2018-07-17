//---------------------------------------------------------------------------//
//!
//! \file   Utility_DataProcessor_def.hpp
//! \author Alex Robinson
//! \brief  Data Processor base class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DATA_PROCESSOR_DEF_HPP
#define UTILITY_DATA_PROCESSOR_DEF_HPP

// Std Lib Includes
#include <cmath>
#include <limits>
#include <iterator>

// FRENSIE Includes
#include "Utility_Tuple.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_DesignByContract.hpp"

namespace Utility{

/*! \details This function processes the independent and dependent data points
 * in a table of continuous data using the desired data processing policy (see
 * Utility::LogLogDataProcessingPolicy or
 * Utility::SquareSquareDataProcessingPolicy). Since this data
 * will be stored in an Array of Tuples this function must also know which 
 * members of the tuple store the raw independent data values and the raw 
 * dependent data values.
 * This function will only compile if the desired tuple members are actually
 * available in Tuple.
 * \tparam DataProcessingPolicy A policy class that is used to process the
 * independent and dependent data values in the data table. Only two such
 * policies are provided by the DataProcessor. However, any policy class that
 * adheres to the necessary interface can be used (the static members
 * processIndependentVar and processDependentVar must be defined or a compile
 * time error will be given).
 * \tparam Tuple A tuple struct that is used to store processed data.
 * \param[in,out] data The array of tuple structs which contains the
 * raw table data.
 * \pre A valid array, which is any array of tuples with at least one element,
 * must be given to this function.
 */
template<typename DataProcessingPolicy,
	 size_t indepMember,
	 size_t depMember,
         template<typename,typename...> class STLCompliantContainer,
	 typename Tuple>
void DataProcessor::processContinuousData( STLCompliantContainer<Tuple>& data )
{
  // Make sure that the array is valid
  testPrecondition( data.size() > 0 );

  typename STLCompliantContainer<Tuple>::iterator data_point = data.begin();
  typename STLCompliantContainer<Tuple>::iterator end = data.end();

  typename TupleElement<indepMember,Tuple>::type indep_value;
  typename TupleElement<depMember,Tuple>::type dep_value;

  while( data_point != end )
  {
    indep_value = DataProcessingPolicy::processIndependentVar(
                                    Utility::get<indepMember>( *data_point ) );
    dep_value = DataProcessingPolicy::processDependentVar(
                                    Utility::get<depMember>( *data_point ) );

    set<indepMember>( *data_point, indep_value );
    set<depMember>( *data_point, dep_value );

    ++data_point;
  }
}

/*! \details This function removes elements of an array if the specified tuple
 * member is less than the given value. This function is primarily used to
 * remove data points from a table with independent values below some
 * threshold. For instance, photon data tables can contain data for energies
 * in the eV range. Typically, one is only interested in photons with energies
 * in the keV range and above. All data below the keV range can therefore be
 * ignored. To allow for accurate interpolation, the data point closest to the
 * given value but below it will be kept. If the tuple member of interest does
 * not exist in Tuple, a compile time error will be given.
 * \tparam member refers to the member of Tuple that stores the value that will
 * be
 * tested against the value of interest.
 * \tparam Tuple A tuple struct that is used to store the table data.
 * \param[in,out] data The array of tuple structs which contain the raw table
 * data.
 * \param[in] value The minimum value that all Tuples in the array will be
 * compared against. Tuples with <em> member </em> less than <b> value </b> 
 * will be removed from the array.
 * \pre A valid array, which is any array of tuples with at least one element,
 * must be given to this function.
 * \post A valid array, which is any array of tuples with at least one element,
 * must be returned from this function. If the testing value is set too high
 * it is possible for all elements to be eliminated from the array, which is
 * surely not an intended results.
 */
template<size_t member,
         template<typename,typename...> class STLCompliantContainer,
	 typename Tuple>
void DataProcessor::removeElementsLessThanValue(
                                            STLCompliantContainer<Tuple>& data,
                                            const double value )
{
  // Make sure that the array is valid
  testPrecondition( data.size() > 0 );
  // Make sure that array is sorted (need a check for this)

  typename STLCompliantContainer<Tuple>::iterator data_point_1 = data.begin();
  typename STLCompliantContainer<Tuple>::iterator data_point_2 = data_point_1 + 1;
  typename STLCompliantContainer<Tuple>::iterator end = data.end();

  // Loop through the array and find the element range to remove
  typename STLCompliantContainer<Tuple>::size_type max_index = 0;
  while( data_point_2 != end )
  {
    if( Utility::get<member>( *data_point_1 ) < value &&
	Utility::get<member>( *data_point_2 ) <= value )
      ++max_index;
    else
      break;

    ++data_point_1;
    ++data_point_2;
  }

  // Remove the elements from the array
  data_point_1 = data.begin();
  data_point_2 = data.begin() + max_index;
  data.erase( data_point_1, data_point_2 );

  // Make sure that the array is still valid
  testPostcondition( data.size() > 0 );
}

/*! \details This function removes elements of an array if the specified tuple
 * member is greater than the given value. This function is primarily used to
 * remove data points from a table with independent values above some threshold.
 * For instance, photon data tables can contain data for energies in the GeV
 * range. Typically, one is only interested in photons with energies in the
 * MeV range and below. All data above a few tens of MeV can therefore be
 * ignored. To allow for accurate interpolation, the data point closest to the
 * give value but above it will be kept. If the tuple member of interest does
 * not exist in Tuple, a compile time error will be given.
 * \tparam member refers to the member of Tuple that stores the value that will
 * be
 * tested against the value of interest.
 * \tparam Tuple A tuple struct that is used to store the table data.
 * \param[in,out] data The array of tuple structs which contain the raw table
 * data.
 * \param[in] The maximum value that all Tuples in the array will be compared
 * against. Tuples with <em> member </em> greater than <b> value </b> will be 
 * removed from the array.
 * \pre A valid array, which is any array of tuples with at least one element,
 * must be given to this function.
 * \post A valid array, which is any array of tuples with at least one element,
 * must be returned from this function. If the testing value is set too low it
 * is possible for all elements to be eliminated from the array, which is surely
 * not an intended result.
 */
template<size_t member,
         template<typename,typename...> class STLCompliantContainer,
	 typename Tuple>
void DataProcessor::removeElementsGreaterThanValue(
                                            STLCompliantContainer<Tuple>& data,
                                            const double value )
{
  // Make sure that the array is valid
  testPrecondition( data.size() > 0 );
  // Make sure that array is sorted (need a check for this)

  // Use bidirectional iterator in reverse to improve performance
  typename STLCompliantContainer<Tuple>::iterator data_point_1 = data.end() - 1;
  typename STLCompliantContainer<Tuple>::iterator data_point_2 = data_point_1 - 1;
  typename STLCompliantContainer<Tuple>::iterator end = data.begin() - 1;

  // Loop through the array and find the element range to remove
  typename STLCompliantContainer<Tuple>::size_type max_index = 0;
  while( data_point_2 != end )
  {
    if( Utility::get<member>( *data_point_1 ) > value &&
        Utility::get<member>( *data_point_2 ) >= value )
      ++max_index;
    else
      break;

    --data_point_1;
    --data_point_2;
  }

  // Remove the elements from the array
  data_point_2 = data.end();
  data_point_1 = data_point_2 - max_index;
  data.erase( data_point_1, data_point_2 );

  // Make sure that the array is still valid
  testPostcondition( data.size() > 0 );
}

/*! \details This function removes an adjacent data point if the values of
 * interest are the same (constant region). By eliminating the amount of data
 * points in a table the memory requirements and the search time can be
 * reduced. If the tuple member of interest does not exist in Tuple, a compile
 * time error will be given.
 * \tparam member refers to the member of Tuple that stores the value that will
 * be tested.
 * \tparam Tuple A tuple struct that is used to store the table data.
 * \param[in,out] data The array of tuple structs which contain the raw table
 * data.
 * \pre A valid array, which is any array of tuples with at least <em> three
 * </em> elements, must be given to this function.
 * \post A valid array, which is any array of tuples with at least <em> two
 * </em> elements, must be returned from this function.
 */
template<size_t member,
         template<typename,typename...> class STLCompliantContainer,
	 typename Tuple>
void DataProcessor::coarsenConstantRegions( STLCompliantContainer<Tuple>& data )
{
  // Make sure that the array is valid
  testPrecondition( data.size() > 2 );

  // Use bidirectional iterator in reverse to improve performance
  // when the constant region is at the end of the array
  typename STLCompliantContainer<Tuple>::iterator data_point_1 = data.end()-1;
  typename STLCompliantContainer<Tuple>::iterator data_point_2, data_point_3;
  typename STLCompliantContainer<Tuple>::iterator end = data.begin()-1;

  data_point_2 = data_point_1-1;
  data_point_3 = data_point_2-1;
  while( data_point_3 != end )
  {
    if( Utility::get<member>( *data_point_1 ) ==
        Utility::get<member>( *data_point_2 ) &&
	Utility::get<member>( *data_point_1 ) ==
        Utility::get<member>( *data_point_3 ) )
    {
      data_point_1 = data.erase( data_point_1 );
    }

    --data_point_1;
    data_point_2 = data_point_1-1;
    data_point_3 = data_point_2-1;
  }

  // Make sure that the array is still valid
  testPostcondition( data.size() > 1 );
}

/*! \details This function calculates the slopes between each pair of data
 * points. Since this data will be stored in an array of Tuples
 * this function must know which members of the tuple store the processed 
 * independent data values and the processed dependent data values. This
 * function must also know which member of the tuple will store the slope value
 * that is calculated. The tuple with the smaller independent variable will
 * store the slope value for the pair. This is desirable since conducting a 
 * search for a value in the table will always return the lower bin boundary 
 * (the tuple with the smaller independent variable). This function will only 
 * compile if the desired tuple members are actually available in Tuple.
 * \tparam indepMember refers to the member of Tuple that stores the 
 * independent data values.
 * \tparam depMember refers to the member of Tuple that stores the dependent 
 * data values.
 * \tparam slopeMember refers to the member of Tuple that stores the slope 
 * values.
 * \param[in,out] data The array of tuple structs which contain the raw table
 * data.
 * \pre A valid array, which is any array of tuples with at least two elements,
 * must be given to this function.
 */
template<size_t indepMember,
	 size_t depMember,
	 size_t slopeMember,
         template<typename,typename...> class STLCompliantContainer,
	 typename Tuple>
void DataProcessor::calculateSlopes( STLCompliantContainer<Tuple>& data  )
{
  // Make sure that the array has more than one element
  testPrecondition( (data.size() > 1) );

  typename STLCompliantContainer<Tuple>::iterator data_point_1, data_point_2;
  typename STLCompliantContainer<Tuple>::iterator end = data.end();

  data_point_1 = data.begin();
  data_point_2 = data_point_1 + 1;

  typename TupleElement<slopeMember,Tuple>::type slope;

  while( data_point_2 != end )
  {
    slope = (Utility::get<depMember>( *data_point_2 ) -
             Utility::get<depMember>( *data_point_1 ))/
      (Utility::get<indepMember>( *data_point_2 ) -
       Utility::get<indepMember>( *data_point_1 ));

    set<slopeMember>( *data_point_1, slope );
    set<slopeMember>( *data_point_2,
                      Utility::QuantityTraits<decltype(slope)>::zero() );

    ++data_point_1;
    ++data_point_2;
  }
}

/*! \details This function calculates a CDF from an array of continuous
 * data points. Since this data will be stored in an array of Tuples (must have
 * size >= 4) this function must know which members of the tuple store the
 * processed independent data values and the processed dependent data values
 * (PDF values). This function must also know which member of the tuple will
 * store the CDF value that is calculated. To calculate the CDF values a
 * Taylor series expansion to second order is conducted on the function which
 * represents the CDF:
 * \f{align}{
 *   CDF(x) & \approx CDF(x_0) + CDF^{'}(x_0)*(x - x_0) +
 *   \frac{1}{2}CDF^{''}(x_0)*(x - x_0)^2 \nonumber \\
 *   & = CDF(x_0) + PDF(x_0)*(x - x_0) + \frac{1}{2}\left[\frac{d}{dx} PDF(x)
 *   \right]\Bigg|_{x_0}(x - x_0)^2 \nonumber \\
 *   & = CDF(x_0) + PDF(x_0)*(x - x_0) + \frac{1}{2}\left[
 *   \frac{PDF(x_1) - PDF(x_0)}{x_1 - x_0} \right](x - x_0)^2. \nonumber
 * \f}
 * \tparam indepMember refers to the member of Tuple that stores the 
 * independent data values.
 * \tparam pdfMember refers to the member of Tuple that stores the PDF data 
 * values.
 * \tparam cdfMember refers to the member of Tuple that will store the CDF data
 * values.
 * \tparam Tuple A tuple struct that is used to store the processed data.
 * \param[in,out] data The array of tuple structs which contain the table data.
 * \pre A valid array, which is any array of tuples with at least two
 * elements, must be given to this function.
 */
template<size_t indepMember,
	 size_t pdfMember,
	 size_t cdfMember,
         template<typename,typename...> class STLCompliantContainer,
	 typename Tuple>
typename QuantityTraits<typename TupleElement<cdfMember,Tuple>::type>::template GetQuantityToPowerType<-1>::type
DataProcessor::calculateContinuousCDF( STLCompliantContainer<Tuple>& data,
				       const bool normalize )
{
  // Make sure that the array has more than one element
  testPrecondition( (data.size() > 1) );

  typedef QuantityTraits<typename TupleElement<cdfMember,Tuple>::type> CDFQT;

  typename STLCompliantContainer<Tuple>::iterator data_point_1, data_point_2;
  typename STLCompliantContainer<Tuple>::iterator end = data.end();

  data_point_1 = data.begin();
  data_point_2 = data.begin() + 1;

  typename TupleElement<cdfMember,Tuple>::type cdf_value;

  // Initialize the CDF
  set<cdfMember>( *data_point_1, CDFQT::zero() );

  // Calculate the CDF
  // CDF(x) = CDF(x1)+PDF(x1)*(x-x1)+0.5*(PDF(x)-PDF(x1))/(x2-x1)*(x-x1)^2
  while( data_point_2 != end )
  {
    cdf_value = Utility::get<cdfMember>( *data_point_1 ) +
      Utility::get<pdfMember>( *data_point_1 )*
      (Utility::get<indepMember>( *data_point_2 ) -
       Utility::get<indepMember>( *data_point_1 )) +
      0.5*(Utility::get<pdfMember>( *data_point_2 ) -
           Utility::get<pdfMember>( *data_point_1 ))*
      (Utility::get<indepMember>( *data_point_2 ) -
       Utility::get<indepMember>( *data_point_1 ));

    set<cdfMember>( *data_point_2, cdf_value );

    ++data_point_1;
    ++data_point_2;
  }

  typename TupleElement<cdfMember,Tuple>::type cdf_max =
    Utility::get<cdfMember>( data.back() );

  // Normalize the CDF and PDF
  if( normalize )
  {
    typename TupleElement<cdfMember,Tuple>::type cdf_norm_value;

    typename TupleElement<pdfMember,Tuple>::type pdf_norm_value;

    data_point_1 = data.begin();

    while( data_point_1 != end )
    {
      cdf_norm_value =
	Utility::get<cdfMember>( *data_point_1 )/getRawQuantity( cdf_max );
      set<cdfMember>( *data_point_1, cdf_norm_value );

      pdf_norm_value =
	Utility::get<pdfMember>( *data_point_1 )/getRawQuantity( cdf_max );
      set<pdfMember>( *data_point_1, pdf_norm_value );

      ++data_point_1;
    }
  }

  // Return the normalization constant
  return 1.0/cdf_max;
}


// Create a pdf from an array of data using a first order approximation
template<size_t indepMember,
         size_t pdfMember,
         size_t cdfMember,
         template<typename,typename...> class STLCompliantContainer,
         typename Tuple>
void DataProcessor::calculateContinuousPDF( STLCompliantContainer<Tuple>& data )
{
  // Make sure that the array has more than one element
  testPrecondition( (data.size() > 1) );

  typename STLCompliantContainer<Tuple>::iterator data_point_1, data_point_2;
  typename STLCompliantContainer<Tuple>::iterator end = data.end();

  data_point_1 = data.begin();
  data_point_2 = data.begin() + 1;

  // Calculate the slope of the cdf
  typename TupleElement<pdfMember,Tuple>::type
    pdf_value = (Utility::get<cdfMember>( *data_point_2 ) -
		 Utility::get<cdfMember>( *data_point_1 ) )/
    (Utility::get<indepMember>( *data_point_2 ) -
     Utility::get<indepMember>( *data_point_1 ));

  // Initialize the PDF
  set<pdfMember>( *data_point_1, pdf_value );

  // Calculate the PDF (slope of cdf)
  while( data_point_2 != end )
  {
    pdf_value = (Utility::get<cdfMember>( *data_point_2 ) -
		 Utility::get<cdfMember>( *data_point_1 ) )/
    (Utility::get<indepMember>( *data_point_2 ) -
     Utility::get<indepMember>( *data_point_1 ));

    set<pdfMember>( *data_point_2, pdf_value );

    ++data_point_1;
    ++data_point_2;
  }
}

/*! \details This function calculates a discrete CDF from an array of discrete
 * data points. Since this data will be stored in an array of Tuples
 * this function must know which member of the tuple stores the processed PDF 
 * value and which member of the tuple will store the CDF value that is 
 * calculated. This function will only compile if the desired tuple members 
 * are actually available in Tuple.
 * \tparam pdfMember refers to the member of Tuple that stores the PDF data 
 * values.
 * \tparam cdfMember refers to the member of Tuple that will store the CDF data
 * values.
 * \param[in,out] data The array of tuple structs which contain the table data.
 * \pre A valid array, which is any array of tuples with at least two elements,
 * must be given to this function.
 */
template<size_t pdfMember,
	 size_t cdfMember,
         template<typename,typename...> class STLCompliantContainer,
	 typename Tuple>
void DataProcessor::calculateDiscreteCDF( STLCompliantContainer<Tuple>& data )
{
  // Make sure that the array has at least one element
  testPrecondition( data.size() > 0 );

  typename STLCompliantContainer<Tuple>::iterator data_point;
  typename STLCompliantContainer<Tuple>::iterator end = data.end();

  data_point = data.begin();

  typename TupleElement<cdfMember,Tuple>::type cdf_value = 0;

  // Create the discrete CDF
  while( data_point != end )
  {
    cdf_value += Utility::get<pdfMember>( *data_point );
    set<cdfMember>( *data_point, cdf_value );

    ++data_point;
  }

  // Normalize the CDF
  data_point = data.begin();
  while( data_point != end )
  {
    cdf_value = Utility::get<cdfMember>( *data_point )/
      Utility::get<cdfMember>( data.back() );
    
    set<cdfMember>( *data_point, cdf_value );

    ++data_point;
  }
}

/*! \details This function copies the data in the desired tuple member of one
 * tuple to the desired tuple member of another tuple. The two arrays of
 * tuples must be distinct (no in place copying).
 * \tparam origMember refers to the member of the tuple whose value will be 
 * copied.
 * \tparam copyMember refers to the member of the new tuple that will store the
 * copy.
 * \param[in] orig_data The array of tuple structs which contain the data that
 * will be copied.
 * \param[in,out] copy_data The array of tuple structs that will store the
 * copied data.
 * \pre
 * <ul>
 *  <li> A valid array, which is any array of tuples with at least two
 *       elements, must be given to this function.
 *  <li> The two arrays must have the same number of elements.
 *  <li> The two arrays must be distinct.
 * </ul>
 */
template<size_t origMember,
	 size_t copyMember,
	 template<typename,typename...> class STLCompliantContainerA,
         template<typename,typename...> class STLCompliantContainerB,
         typename TupleA,
         typename TupleB>
void DataProcessor::copyTupleMemberData(
                               const STLCompliantContainerA<TupleA>& orig_data,
                               STLCompliantContainerB<TupleB>& copy_data )
{
  // Make sure that the arrays are valid
  testPrecondition( (orig_data.size() > 0) );
  testPrecondition( (orig_data.size() == copy_data.size()) );
  remember(typedef typename STLCompliantContainerA<TupleA>::pointer origTuplePointer);
  testPrecondition( &orig_data.front() !=
		    reinterpret_cast<origTuplePointer>( &copy_data.front() ) );

  typename STLCompliantContainerA<TupleA>::const_iterator orig_data_point, end;
  typename STLCompliantContainerB<TupleB>::iterator copy_data_point;
  orig_data_point = orig_data.begin();
  copy_data_point = copy_data.begin();
  end = orig_data.end();

  while( orig_data_point != end )
  {
    set<copyMember>( *copy_data_point,
                     Utility::get<origMember>( *orig_data_point ) );

    ++orig_data_point;
    ++copy_data_point;
  }
}

/*! \details This function swaps the data in two tuple members. It can be used
 * to reorganize the processed data in a table.
 * \tparam member1 refers to the member of the tuple whose value will be 
 * swapped.
 * \tparam member2 refers to the member of the tuple whose value will be 
 * swapped.
 * \tparam Array An array class of tuple structs.
 * \param[in,out] data The array of tuple structs which contain the table data.
 * \pre
 * <ul>
 *  <li> The tuple members that will swap data must be distinct.
 *  <li> A valid array, which is any array of tuples with at least one element,
 *       must be given to this function.
 * </ul>
 */
template<size_t member1,
	 size_t member2,
	 template<typename,typename...> class STLCompliantContainer,
         typename Tuple>
void DataProcessor::swapTupleMemberData( STLCompliantContainer<Tuple>& data )
{
  // Make sure that the members are valid
  testPrecondition( member1 != member2 );
  // Make sure that the arrays are valid
  testPrecondition( (data.size() > 0) );

  typename STLCompliantContainer<Tuple>::iterator data_point, end;
  data_point = data.begin();
  end = data.end();

  typename TupleElement<member1,Tuple>::type copy;

  while( data_point != end )
  {
    copy = Utility::get<member1>( *data_point );
    set<member1>( *data_point, Utility::get<member2>( *data_point ) );
    set<member2>( *data_point, copy );

    ++data_point;
  }
}

} // end Utility namespace

#endif // end UTILITY_DATA_PROCESSOR_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_DataProcessor_def.hpp
//---------------------------------------------------------------------------//

