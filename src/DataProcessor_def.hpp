//---------------------------------------------------------------------------//
// \file   DataProcessor_def.hpp
// \author Alex Robinson
// \brief  Data Processor base class template definitions
//---------------------------------------------------------------------------//

#ifndef DATA_PROCESSOR_DEF_HPP
#define DATA_PROCESSOR_DEF_HPP

// Std Lib Includes
#include <cmath>
#include <limits>
#include <iterator>

// FACEMC Includes
#include "Tuple.hpp"
#include "TupleGetSetMemberPolicy.hpp"
#include "ContractException.hpp"

namespace FACEMC{

/*! \details This function processes the independent and dependent data points
 * in a table of continuous data using the desired data processing policy (see
 * FACEMC::DataProcessor::LogLogDataProcessingPolicy or 
 * FACEMC::DataProcessor::SquareSquareDataProcessingPolicy). Since this data
 * will be stored in a Teuchos::Array of Tuples (FACEMC::Pair, FACEMC::Trip,
 * or FACEMC::Quad) this function must also know which members of the tuple
 * store the raw independent data values and the raw dependent data values. 
 * This function will only compile if the desired tuple members are actually 
 * available in Tuple.
 * \tparam DataProcessingPolicy A policy class that is used to process the
 * independent and dependent data values in the data table. Only two such
 * policies are provided by the DataProcessor. However, any policy class that
 * adheres to the necessary interface can be used (the static members 
 * processIndependentVar and processDependentVar must be defined or a compile
 * time error will be given).
 * \tparam indepMember A member of the enumeration FACEMC::TupleMember, 
 * which is used to refer to the member of Tuple that stores the independent 
 * data values.
 * \tparam depMember A member of the enumeration FACEMC::TupleMember, 
 * which is used to refer to the member of Tuple that stores the dependent 
 * data values.
 * \tparam Tuple A FACEMC tuple struct (either FACEMC::Pair, FACEMC::Trip, or
 * FACEMC::Quad) that is used to store processed data.
 * \param[in,out] data The array of tuple structs which contains the 
 * raw table data.
 * \pre A valid array, which is any array of tuples with at least one element,
 * must be given to this function.
 * \note Developers: The FACEMC::TupleGetSetMemberPolicy is critical to the
 * generality of this function. Review this struct to better understand how
 * this function operates. 
 */
template<typename DataProcessingPolicy,
	 TupleMember indepMember,
	 TupleMember depMember,
	 typename Tuple>
void DataProcessor::processContinuousData( Teuchos::Array<Tuple> &data )
{
  // Make sure that the array is valid
  testPrecondition( data.size() > 0 );

  typename Teuchos::Array<Tuple>::iterator data_point = data.begin();
  typename Teuchos::Array<Tuple>::iterator end = data.end();

  typedef TupleGetSetMemberPolicy<Tuple,indepMember> indepTGSMP;
  typedef TupleGetSetMemberPolicy<Tuple,depMember> depTGSMP;

  typename indepTGSMP::tupleMemberType indep_value;
  typename depTGSMP::tupleMemberType dep_value;

  while( data_point != end )
  {
    indep_value = DataProcessingPolicy::processIndependentVar( indepTGSMP::get( *data_point ) );
    dep_value = DataProcessingPolicy::processDependentVar( depTGSMP::get( *data_point ) );

    indepTGSMP::set( *data_point, indep_value );
    depTGSMP::set( *data_point, dep_value );

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
 * \tparam member A member of the enumeration FACEMC::TupleMember, which
 * is used to refer to the member of Tuple that stores the value that will be
 * tested against the value of interest.
 * \tparam Tuple A FACEMC tuple struct (either FACEMC::Pair, FACEMC::Trip, or
 * FACEMC::Quad) that is used to store the table data.
 * \param[in,out] data The array of tuple structs which contain the raw table
 * data. 
 * \param[in] value The minimum value that all Tuples in the array will be 
 * compared against. Tuples with FACEMC::TupleMember <em> member </em> less 
 * than <b> value </b> will be removed from the array.
 * \pre A valid array, which is any array of tuples with at least one element,
 * must be given to this function.
 * \post A valid array, which is any array of tuples with at least one element,
 * must be returned from this function. If the testing value is set too high
 * it is possible for all elements to be eliminated from the array, which is
 * surely not an intended results.
 * \note Developers: The FACEMC::TupleGetSetMemberPolicy is critical to the
 * generality of this function. Review this struct to better understand how
 * this function operates. 
 */
template<TupleMember member,
	 typename Tuple>
void DataProcessor::removeElementsLessThanValue( Teuchos::Array<Tuple> &data,
						 const double value )
{
  // Make sure that the array is valid
  testPrecondition( data.size() > 0 );
  // Make sure that array is sorted (need a check for this)
  
  typename Teuchos::Array<Tuple>::iterator data_point_1 = data.begin();
  typename Teuchos::Array<Tuple>::iterator data_point_2 = data_point_1 + 1;
  typename Teuchos::Array<Tuple>::iterator end = data.end();

  typedef TupleGetSetMemberPolicy<Tuple,member> dataTGSMP;
  
  // Loop through the array and find the element range to remove
  typename Teuchos::Array<Tuple>::size_type max_index = 0;
  while( data_point_2 != end )
  {
    if( dataTGSMP::get( *data_point_1 ) < value &&
	dataTGSMP::get( *data_point_2 ) <= value )
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
 * \tparam member A member of the enumeration FACEMC::TupleMember, which
 * is used to refer to the member of Tuple that stores the value that will be
 * tested against the value of interest. 
 * \tparam Tuple A FACEMC tuple struct (either FACEMC::Pair, FACEMC::Trip, or
 * FACEMC::Quad) that is used to store the table data.
 * \param[in,out] data The array of tuple structs which contain the raw table
 * data.
 * \param[in] The maximum value that all Tuples in the array will be compared
 * against. Tuples with FACEMC::TupleMember <em> member </em> greater than 
 * <b> value </b> will be removed from the array.
 * \pre A valid array, which is any array of tuples with at least one element,
 * must be given to this function. 
 * \post A valid array, which is any array of tuples with at least one element,
 * must be returned from this function. If the testing value is set too low it
 * is possible for all elements to be eliminated from the array, which is surely
 * not an intended result.
 * \note Developers: The FACEMC::TupleGetSetMemberPolicy is critical to the
 * generality of this function. Review this struct to better understand how
 * this function operates.
 */
template<TupleMember member,
	 typename Tuple>
void DataProcessor::removeElementsGreaterThanValue( Teuchos::Array<Tuple> &data,
						    const double value )
{
  // Make sure that the array is valid
  testPrecondition( data.size() > 0 );
  // Make sure that array is sorted (need a check for this)
  
  // Use bidirectional iterator in reverse to improve performance
  typename Teuchos::Array<Tuple>::iterator data_point_1 = data.end() - 1;
  typename Teuchos::Array<Tuple>::iterator data_point_2 = data_point_1 - 1;
  typename Teuchos::Array<Tuple>::iterator end = data.begin() - 1;

  typedef TupleGetSetMemberPolicy<Tuple,member> dataTGSMP;
  
  // Loop through the array and find the element range to remove
  typename Teuchos::Array<Tuple>::size_type max_index = 0;
  while( data_point_2 != end )
  {
    if( dataTGSMP::get( *data_point_1 ) > value &&
	dataTGSMP::get( *data_point_2 ) >= value )
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
 * \tparam member A member of the enumeration FACEMC::TupleMember, which is used
 * to refer to the member of Tuple that stores the value that will be tested.
 * \tparam Tuple A FACEMC tuple struct (either FACEMC::Pair, FACEMC::Trip,
 * FACEMC::Quad) that is used to store the table data. 
 * \param[in,out] data The array of tuple structs which contain the raw table 
 * data.
 * \pre A valid array, which is any array of tuples with at least <em> three
 * </em> elements, must be given to this function.
 * \post A valid array, which is any array of tuples with at least <em> two
 * </em> elements, must be returned from this function.
 * \note Developers: The FACEMC::TupleGetSetMemberPolicy is critical to the
 * generality of this function. Review this struct to better understand how
 * this function operates. 
 */ 
template<TupleMember member,
	 typename Tuple>
void DataProcessor::coarsenConstantRegions( Teuchos::Array<Tuple> &data )
{
  // Make sure that the array is valid
  testPrecondition( data.size() > 2 );

  // Use bidirectional iterator in reverse to improve performance
  // when the constant region is at the end of the array
  typename Teuchos::Array<Tuple>::iterator data_point_1 = data.end()-1;
  typename Teuchos::Array<Tuple>::iterator data_point_2, data_point_3;
  typename Teuchos::Array<Tuple>::iterator end = data.begin()-1;

  typedef TupleGetSetMemberPolicy<Tuple,member> dataTGSMP;

  data_point_2 = data_point_1-1;
  data_point_3 = data_point_2-1;
  while( data_point_3 != end )
  {
    if( dataTGSMP::get( *data_point_1 ) == dataTGSMP::get( *data_point_2 ) &&
	dataTGSMP::get( *data_point_1 ) == dataTGSMP::get( *data_point_3 ) )
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
 * points. Since this data will be stored in an Array of Tuples
 * (either FACEMC::Trip or FACEMC::Quad) this function must know which
 * members of the tuple store the processed independent data values and the
 * processed dependent data values. This function must also know which member
 * of the tuple will store the slope value that is calculated. The tuple with
 * the smaller independent variable will store the slope value for the pair.
 * This is desirable since conducting a search for a value in the table will
 * always return the lower bin boundary (the tuple with the smaller independent
 * variable). This function will only compile if the desired tuple members are
 * actually available in Tuple.
 * \tparam indepMember A member of the enumeration FACEMC::TupleMember, which
 * is used to refer to the member of Tuple that stores the independent data
 * values. 
 * \tparam depMember A member of the enumeration FACEMC::TupleMember, which
 * is used to refer to the member of Tuple that stores the dependent data
 * values. 
 * \tparam slopeMember A member of the enumeration FACEMC::TupleMember, which
 * is used to refer to the member of Tuple that stores the slope values. 
 * \tparam Tuple A FACEMC tuple struct (either FACEMC::Trip or FACEMC::Quad)
 * that is used to store processed data. 
 * \tparam Array An array class with a single template parameter. Only the
 * Teuchos::Array or Teuchos::ArrayView classes should be used. Because
 * std::vector has two template parameters it cannot be used. The Teuchos array
 * classes are all extensions of the std::vector though. 
 * \param[in,out] data The array of tuple structs which contain the raw table
 * data.
 * \pre A valid array, which is any array of tuples with at least two elements,
 * must be given to this function.
 * \note Developers: 
 * <ul>
 *  <li> The FACEMC::TupleGetSetMemberPolicy is critical to the
 *       generality of this function. Review this struct to better understand 
 *       how this function operates. 
 *  <li> The Tuple template parameter and Array template template parameter 
 *       could be combined into a single template parameter Array. The tuple
 *       type could then be accessed using "typename Array::value_type". This
 *       would allow for std::vector to be used. The current method seems
 *       more verbose. In either case, the Array and Tuple types never need
 *       to be given explicitly since they can be deduced by the compiler. 
 * </ul>
 */
template<TupleMember indepMember, 
	 TupleMember depMember,
	 TupleMember slopeMember,
	 typename Tuple,
	 template<typename> class Array>
void DataProcessor::calculateSlopes( Array<Tuple> &data  )
{
  // Make sure that the array has more than one element
  testPrecondition( (data.size() > 1) );
  
  typename Array<Tuple>::iterator data_point_1, data_point_2;
  typename Array<Tuple>::iterator end = data.end();

  data_point_1 = data.begin();
  data_point_2 = data_point_1 + 1;

  typedef TupleGetSetMemberPolicy<Tuple,indepMember> indepTGSMP;
  typedef TupleGetSetMemberPolicy<Tuple,depMember> depTGSMP;
  typedef TupleGetSetMemberPolicy<Tuple,slopeMember> slopeTGSMP;
  
  typename slopeTGSMP::tupleMemberType slope;
  
  while( data_point_2 != end )
  {
    slope = (depTGSMP::get( *data_point_2 ) - depTGSMP::get( *data_point_1 ))/
      (indepTGSMP::get( *data_point_2 ) - indepTGSMP::get( *data_point_1 ));
    
    slopeTGSMP::set( *data_point_1, slope );
    slopeTGSMP::set( *data_point_2, 0 );

    ++data_point_1;
    ++data_point_2;
  }
}

/*! \details This function calculates a CDF from an array of continuous
 * data points. Since this data will be stored in an Array of Tuples (only
 * FACEMC::Quad) this function must know which members of the tuple store the
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
 * \tparam indepMember A member of the enumeration FACEMC::TupleMember, which is
 * used to refer to the member of Tuple that stores the independent data values.
 * \tparam pdfMember A member of the enumeration FACEMC::TupleMember, which is
 * used to refer to the member of Tuple that stores the PDF data values.
 * \tparam cdfMember A member of the enumeration FACEMC::TupleMember, which is
 * used to refer to the member of Tuple that will store the CDF data values.
 * \tparam Tuple A FACEMC tuple struct (only FACEMC::Quad) that is used to
 * store the processed data.
 * \tparam Array An array class with a single template parameter. Only the
 * Teuchos::Array and the Teuchos::ArrayView classes should be used. Because
 * std::vector has two template parameters it cannot be used. The Teuchos array
 * classes are all extensions of the std::vector though.
 * \param[in,out] data The array of tuple structs which contain the table data.
 * \pre A valid array, which is any array of tuples with at least two
 * elements, must be given to this function.
 * \note Developers:
 * <ul>
 *  <li> The FACEMC::TupleGetSetMemberPolicy is critical to the
 *       generality of this function. Review this struct to better understand 
 *       how this function operates. 
 *  <li> The Tuple template parameter and Array template template parameter 
 *       could be combined into a single template parameter Array. The tuple
 *       type could then be accessed using "typename Array::value_type". This
 *       would allow for std::vector to be used. The current method seems
 *       more verbose. In either case, the Array and Tuple types never need
 *       to be given explicitly since they can be deduced by the compiler. 
 * </ul>
 */
template<TupleMember indepMember,
	 TupleMember pdfMember,
	 TupleMember cdfMember,
	 typename Tuple,
	 template<typename> class Array>
void DataProcessor::calculateContinuousCDF( Array<Tuple> &data )
{
  // Make sure that the array has more than one element
  testPrecondition( (data.size() > 1) );
  
  typename Array<Tuple>::iterator data_point_1, data_point_2;
  typename Array<Tuple>::iterator end = data.end();

  data_point_1 = data.begin();
  data_point_2 = data.begin() + 1;

  typedef TupleGetSetMemberPolicy<Tuple,indepMember> indepTGSMP;
  typedef TupleGetSetMemberPolicy<Tuple,pdfMember> pdfTGSMP;
  typedef TupleGetSetMemberPolicy<Tuple,cdfMember> cdfTGSMP;

  typename cdfTGSMP::tupleMemberType cdf_value;

  // Initialize the CDF
  cdfTGSMP::set( *data_point_1, 0 );
  
  // Calculate the CDF
  // CDF(x) = CDF(x1)+PDF(x1)*(x-x1)+0.5*(PDF(x)-PDF(x1))/(x2-x1)*(x-x1)^2
  while( data_point_2 != end )
  {
    cdf_value = cdfTGSMP::get( *data_point_1 ) +
      pdfTGSMP::get( *data_point_1 )*
      (indepTGSMP::get( *data_point_2 ) - indepTGSMP::get( *data_point_1 )) +
      0.5*(pdfTGSMP::get( *data_point_2 ) - pdfTGSMP::get( *data_point_1 ))*
      (indepTGSMP::get( *data_point_2) - indepTGSMP::get( *data_point_1 ));
    
    cdfTGSMP::set( *data_point_2, cdf_value );
    
    ++data_point_1;
    ++data_point_2;
  }

  // Normalize the CDF and PDF
  typename cdfTGSMP::tupleMemberType cdf_max, cdf_norm_value;
  cdf_max = cdfTGSMP::get( data.back() );
  typename pdfTGSMP::tupleMemberType pdf_norm_value;
  data_point_1 = data.begin();
  
  while( data_point_1 != end )
  {
    cdf_norm_value = cdfTGSMP::get( *data_point_1 )/cdf_max;
    cdfTGSMP::set( *data_point_1, cdf_norm_value );

    pdf_norm_value = pdfTGSMP::get( *data_point_1 )/cdf_max;
    pdfTGSMP::set( *data_point_1, pdf_norm_value );
    
    ++data_point_1;
  }
}

/*! \details This function calculates a discrete CDF from an array of discrete
 * data points. Since this data will be stored in a Teuchos::Array of Tuples
 * (either FACEMC::Pair, FACEMC::Trip or FACEMC::Quad) this function must know 
 * which member of the tuple stores the processed PDF value and which member of 
 * the tuple will store the CDF value that is calculated. This function will 
 * only compile if the desired tuple members are actually available in Tuple.
 * \tparam pdfMember A member of the enumeration FACEMC::TupleMember, which is
 * used to refer to the member of Tuple that stores the PDF data values.
 * \tparam cdfMember A member of the enumeration FACEMC::TupleMember, which is
 * used to refer to the member of Tuple that will store the CDF data values.
 * \tparam Tuple A FACEMC tuple struct (either FACEMC::Pair, FACEMC::Trip or
 * FACEMC::Quad) that is used to store the processed data. 
 * \param[in,out] data The array of tuple structs which contain the table data.
 * \pre A valid array, which is any array of tuples with at least two elements,
 * must be given to this function. 
 * \note Developers: The FACEMC::TupleGetSetMemberPolicy is critical to the 
 * generality of this function. Review this struct to better understand how this
 * function operates. 
 */
template<TupleMember pdfMember,
	 TupleMember cdfMember,
	 typename Tuple>
void DataProcessor::calculateDiscreteCDF( Teuchos::Array<Tuple> &data )
{
  // Make sure that the array has more than one element
  testPrecondition( (data.size() > 1) );
  
  typename Teuchos::Array<Tuple>::iterator data_point;
  typename Teuchos::Array<Tuple>::iterator end = data.end();

  data_point = data.begin();

  typedef TupleGetSetMemberPolicy<Tuple,pdfMember> pdfTGSMP;
  typedef TupleGetSetMemberPolicy<Tuple,cdfMember> cdfTGSMP;

  typename cdfTGSMP::tupleMemberType cdf_value = 0;

  // Create the discrete CDF
  while( data_point != end )
  {
    cdf_value += pdfTGSMP::get( *data_point );
    cdfTGSMP::set( *data_point, cdf_value );
    
    ++data_point;
  }

  // Normalize the CDF
  data_point = data.begin();
  while( data_point != end )
  {
    cdf_value = cdfTGSMP::get( *data_point )/cdfTGSMP::get( data.back() );
    cdfTGSMP::set( *data_point, cdf_value );
    
    ++data_point;
  }
}

/*! \details This function copies the data in the desired tuple member of one
 * tuple to the desired tuple member of another tuple. The two arrays of 
 * tuples must be distinct (no in place copying).
 * \tparam origMember A member of the enumeration FACEMC::TupleMember, which is
 * used to refer to the member of the tuple whose value will be copied.
 * \tparam copyMember A member of the enumeration FACEMC::TupleMember, which is
 * used to refer to the member of the new tuple that will store the copy.
 * \tparam origTuple A FACEMC tuple struct (either FACEMC::Pair, FACEMC::Trip or
 * FACEMC::Quad) that will have a member value copied.
 * \tparam copyTuple A FACEMC tuple struct (either FACEMC::Pair, FACEMC::Trip or
 * FACEMC::Quad) that will store a copy in one of its members. This tuple does
 * not need to be the same as the <em> origTuple </em>.
 * \tparam Array An array class with a single template parameter. Only the 
 * Teuchos::Array and the Teuchos::ArrayView classes should be used. Because
 * std::vector has two template parameters it cannot be used. The Teuchos array
 * classes are all extensions of the std::vector though.
 * \param[in] orig_data The array of tuple structs which contain the data that
 * will be copied.
 * \param[in,out] copy_data The array of tuple structs that will store the
 * copied data.
 * \pre
 * <ul>
 *  <li> A valid array, which is any array of tuples with at least two elements,
 *       must be given to this function.
 *  <li> The two arrays must have the same number of elements.
 *  <li> The two arrays must be distinct.
 * </ul>
 * \note Developers:
 * <ul>
 *  <li> The FACEMC::TupleGetSetMemberPolicy is critical to the generality of
 *       this function. Review this struct to better understand how this 
 *       function operates. 
 *  <li> The Tuple template parameter and Array template template parameter
 *       could be combined into a single template parameter Array. The tuple
 *       type could then be accessed using "typename Array::value_type". This
 *       would allow for std::vector to be used. The current method seems more
 *       verbose. In either case, the Array and Tuple types never need to be
 *       given explicitly since they can be deduced by the compiler. 
 * </ul>
 */
template<TupleMember origMember, 
	 TupleMember copyMember,
	 typename origTuple,
	 typename copyTuple,
	 template<typename> class Array>
void DataProcessor::copyTupleMemberData( const Array<origTuple> &orig_data,
					 Array<copyTuple> &copy_data )
{
  // Make sure that the arrays are valid
  testPrecondition( (orig_data.size() > 0) );
  testPrecondition( (orig_data.size() == copy_data.size()) );
  testPrecondition( &orig_data[0] != 
		    reinterpret_cast<origTuple*>( &copy_data[0] ) );
  
  typename Array<origTuple>::const_iterator orig_data_point, end;
  typename Array<copyTuple>::iterator copy_data_point;
  orig_data_point = orig_data.begin();
  copy_data_point = copy_data.begin();
  end = orig_data.end();
  
  typedef TupleGetSetMemberPolicy<origTuple,origMember> origTGSMP;
  typedef TupleGetSetMemberPolicy<copyTuple,copyMember> copyTGSMP;
  while( orig_data_point != end )
  {
    copyTGSMP::set( *copy_data_point, origTGSMP::get( *orig_data_point ) );
    
    ++orig_data_point;
    ++copy_data_point;
  }
}

/*! \details This function swaps the data in two tuple members. It can be used
 * to reorganize the processed data in a table.
 * \tparam member1 A member of the enumeration FACEMC::TupleMember, which is
 * used to refer to the member of the tuple whose value will be swapped.
 * \tparam member2 A member of the enumeration FACEMC::TupleMember, which is 
 * used to refer to the member of the tuple whose value will be swapped.
 * \tparam Tuple A FACEMC tuple struct (either FACEMC::Pair, FACEMC::Trip,
 * or FACEMC::Quad) that is used to store processed data. 
 * \tparam Array An array class with a single template parameter. Only the
 * Teuchos::Array and the Teuchos::ArrayView classes should be used. Because
 * std::vector has two template parameters it cannot be used. The Teuchos array
 * classes are all extensions of the std::vector though. 
 * \param[in,out] data The array of tuple structs which contain the table data.
 * \pre 
 * <ul>
 *  <li> The tuple members that will swap data must be distinct.
 *  <li> A valid array, which is any array of tuples with at least one element,
 *       must be given to this function.
 * </ul>
 * \note Developers:
 * <ul>
 *  <li> The FACEMC::TupleGetSetMemberPolicy is critical to the generality of
 *       this function. Review this struct to better understand how this 
 *       function operates. 
 *  <li> The Tuple template parameter and Array template template parameter
 *       could be combined into a single template parameter Array. The tuple
 *       type could then be accessed using "typename Array::value_type". This
 *       would allow for std::vector to be used. The current method seems more
 *       verbose. In either case, the Array and Tuple types never need to be
 *       given explicitly since they can be deduced by the compiler. 
 * </ul>
 */
template<TupleMember member1,
	 TupleMember member2,
	 typename Tuple,
	 template<typename> class Array>
void DataProcessor::swapTupleMemberData( Array<Tuple> &data )
{
  // Make sure that the members are valid
  testPrecondition( member1 != member2 );
  // Make sure that the arrays are valid
  testPrecondition( (data.size() > 0) );
  
  typename Array<Tuple>::iterator data_point, end;
  data_point = data.begin();
  end = data.end();

  typedef TupleGetSetMemberPolicy<Tuple,member1> TGSMP_1;
  typedef TupleGetSetMemberPolicy<Tuple,member2> TGSMP_2;
  while( data_point != end )
  {
    typename TGSMP_1::tupleMemberType copy = TGSMP_1::get( *data_point );
    TGSMP_1::set( *data_point, TGSMP_2::get( *data_point ) );
    TGSMP_2::set( *data_point, copy );

    ++data_point;
  }
}

//---------------------------------------------------------------------------//
// LogLogDataProcessingPolicy definitions
//---------------------------------------------------------------------------//

/*! \tparam T Any integer or floating point type.
 * \param[in] indep_var The independent variable that will be processed.
 * \return The processed independent variable. 
 */
template<typename T>
inline T DataProcessor::LogLogDataProcessingPolicy::processIndependentVar( const T indep_var )
{
  if( indep_var >= 0 )
    return static_cast<T>( log( static_cast<double>(indep_var) ) );
  else
    return 0;
}

/*! \tparam T Any integer or floating point type.
 * \param[in] dep_var The dependent variable that will be processed.
 * \return The processed dependent variable. 
 */
template<typename T>
inline T DataProcessor::LogLogDataProcessingPolicy::processDependentVar( const T dep_var )
{
  if( dep_var >= 0 )
    return static_cast<T>( log( static_cast<double>(dep_var) ) );
  else
    return 0;
}

//---------------------------------------------------------------------------//
// SquareSquareDataProcessingPolicy definitions
//---------------------------------------------------------------------------//

/*! \tparam T Any integer or floating point type.
 * \param[in] indep_var The independent variable that will be processed.
 * \return The processed independent variable. 
 */
template<typename T>
inline T DataProcessor::SquareSquareDataProcessingPolicy::processIndependentVar( const T indep_var )
{
  return indep_var*indep_var;
}

/*! \tparam T Any integer or floating point type.
 * \param[in] dep_var The dependent variable that will be processed.
 * \return The processed dependent variable. 
 */
template<typename T>
inline T DataProcessor::SquareSquareDataProcessingPolicy::processDependentVar( const T dep_var )
{
  return dep_var*dep_var;
}

} // end FACEMC namespace

#endif // end DATA_PROCESSOR_DEF_HPP

//---------------------------------------------------------------------------//
// end DataProcessor_def.hpp
//---------------------------------------------------------------------------//

