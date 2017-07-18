//---------------------------------------------------------------------------//
//!
//! \file   Utility_EquiprobableBinDistribution_def.hpp
//! \author Alex Robinson
//! \brief  Equiprobable bin distribution class definition.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_EQUIPROBABLE_BIN_DISTRIBUTION_DEF_HPP
#define UTILITY_EQUIPROBABLE_BIN_DISTRIBUTION_DEF_HPP

// Std Lib Includes
#include <algorithm>

// FRENSIE Includes
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareEquiprobableBinDistribution<void,void> );

// Default constructor
template<typename IndependentUnit, typename DependentUnit>
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::UnitAwareEquiprobableBinDistribution()
{ /* ... */ }

// Basic constructor
template<typename IndependentUnit, typename DependentUnit>
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::UnitAwareEquiprobableBinDistribution(
				 const std::vector<double>& bin_boundaries )
  : d_bin_boundaries( bin_boundaries.size() )
{
  this->initializeDistribution( bin_boundaries );
}

// Constructor
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity>
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::UnitAwareEquiprobableBinDistribution(
	           const std::vector<InputIndepQuantity>& bin_boundaries )
  : d_bin_boundaries( bin_boundaries.size() )
{
  this->initializeDistribution( bin_boundaries );
}

// Copy constructor
/*! \details Just like boost::units::quantity objects, the unit-aware
 * distribution can be explicitly cast to a distribution with compatible
 * units. If the units are not compatible, this function will not compile. Note
 * that this allows distributions to be scaled safely (unit conversions
 * are completely taken care of by boost::units)!
 */
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepUnit, typename InputDepUnit>
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::UnitAwareEquiprobableBinDistribution(
  const UnitAwareEquiprobableBinDistribution<InputIndepUnit,InputDepUnit>& dist_instance )
  : d_bin_boundaries()
{
  this->initializeDistribution( dist_instance.d_bin_boundaries );
}

// Copy constructor (copying from unitless distribution only)
template<typename IndependentUnit, typename DependentUnit>
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::UnitAwareEquiprobableBinDistribution(
 const UnitAwareEquiprobableBinDistribution<void,void>& unitless_dist_instance, int )
  : d_bin_boundaries()
{
  this->initializeDistribution( unitless_dist_instance.d_bin_boundaries );
}

// Construct distribution from a unitless dist. (potentially dangerous)
/*! \details Constructing a unit-aware distribution from a unitless
 * distribution is potentially dangerous. By forcing users to construct objects
 * using this method instead of a standard constructor we are trying to make
 * sure users are aware of the danger. This is designed to mimic the interface
 * of the boost::units::quantity, which also has to deal with this issue.
 */
template<typename IndependentUnit, typename DependentUnit>
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::fromUnitlessDistribution(
 const UnitAwareEquiprobableBinDistribution<void,void>& unitless_distribution )
{
  return ThisType( unitless_distribution, 0 );
}

// Assignment operator
template<typename IndependentUnit, typename DependentUnit>
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>&
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::operator=(
		             const UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>& dist_instance )
{
  if( this != &dist_instance )
    d_bin_boundaries = dist_instance.d_bin_boundaries;

  return *this;
}


// Evaulate the distribution
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::DepQuantity
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::evaluate(
  const typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  return QuantityTraits<DepQuantity>::initializeQuantity(
		      getRawQuantity( this->evaluatePDF( indep_var_value ) ) );
}

// Evaluate the PDF
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::evaluatePDF(
    const typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < d_bin_boundaries.front() )
    return QuantityTraits<InverseIndepQuantity>::zero();
  else if( indep_var_value > d_bin_boundaries.back() )
    return QuantityTraits<InverseIndepQuantity>::zero();
  else
  {
    typename std::vector<IndepQuantity>::const_iterator lower_bin_boundary,
      upper_bin_boundary;

    if( indep_var_value >= d_bin_boundaries.front() &&
	indep_var_value < d_bin_boundaries.back() )
    {
      lower_bin_boundary =
	Search::binaryLowerBound( d_bin_boundaries.begin(),
				  d_bin_boundaries.end(),
				  indep_var_value );

     upper_bin_boundary = lower_bin_boundary;
     ++upper_bin_boundary;
    }
    else
    {
      upper_bin_boundary = d_bin_boundaries.end();
      --upper_bin_boundary;

      lower_bin_boundary = upper_bin_boundary;
      --lower_bin_boundary;
    }

    return (1.0/(d_bin_boundaries.size()-1))/
      (*upper_bin_boundary - *lower_bin_boundary);
  }
}

// Evaluate the CDF
template<typename IndependentUnit, typename DependentUnit>
double UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::evaluateCDF(
   const typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < d_bin_boundaries.front() )
    return 0.0;
  else if( indep_var_value >= d_bin_boundaries.back() )
    return 1.0;
  else
  {
    unsigned bin_index =
      Search::binaryLowerBoundIndex( d_bin_boundaries.begin(),
				     d_bin_boundaries.end(),
				     indep_var_value );

    unsigned bins = d_bin_boundaries.size()-1;

    double bin_contribution = (indep_var_value - d_bin_boundaries[bin_index])/
      (d_bin_boundaries[bin_index+1] - d_bin_boundaries[bin_index]);

    return (bin_index + bin_contribution)/bins;
  }
}

// Return a random sample from the distribution
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::sample() const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  unsigned dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample and record the number of trials
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials( DistributionTraits::Counter& trials ) const
{
  ++trials;

  return this->sample();
}

// Return a random sample from the distribution and the sampled index
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::sampleAndRecordBinIndex(
					    unsigned& sampled_bin_index ) const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleImplementation( random_number, sampled_bin_index );
}

// Return a random sample from the distribution at the given CDF value
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::sampleWithRandomNumber(
					     const double random_number ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  unsigned dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample from the distribution in a subrange
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::sampleInSubrange(
 const typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the max independent variable is valid
  testPrecondition( max_indep_var >= d_bin_boundaries.front() );

  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleWithRandomNumberInSubrange( random_number,
						 max_indep_var );
}

// Return a random sample using the random number and record the bin index
template<typename IndependentUnit, typename DependentUnit>
inline typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::sampleImplementation(
				            double random_number,
				            unsigned& sampled_bin_index ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  double bin_location = random_number*(d_bin_boundaries.size()-1);

  sampled_bin_index = (unsigned)floor(bin_location);

  return d_bin_boundaries[sampled_bin_index] +
    (bin_location - sampled_bin_index)*(d_bin_boundaries[sampled_bin_index+1]-
					d_bin_boundaries[sampled_bin_index]);
}

// Return a random sample from the distribution at the given CDF value in a subrange
template<typename IndependentUnit, typename DependentUnit>
inline typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::sampleWithRandomNumberInSubrange(
     const double random_number,
     const typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  // Make sure the max independent variable is valid
  testPrecondition( max_indep_var >= d_bin_boundaries.front() );

  // Compute the scaled random number
  double scaled_random_number =
    random_number*this->evaluateCDF( max_indep_var );

  unsigned dummy_index;

  return this->sampleImplementation( scaled_random_number, dummy_index );
}

// Return the upper bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const
{
  return d_bin_boundaries.back();
}

// Return the lower bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const
{
  return d_bin_boundaries.front();
}

// Return the distribution type
template<typename IndependentUnit, typename DependentUnit>
OneDDistributionType UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::getDistributionType() const
{
  return ThisType::distribution_type;
}

template<typename IndependentUnit, typename DependentUnit>
std::string UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::getDistributionTypeName(
                                                       const bool verbose_name,
                                                       const bool lowercase )
{
  std::string name = "Equiprobable";

  if( verbose_name )
    name += " Bin Distribution";

  if( lowercase )
    boost::algorithm::to_lower( name );

  return name;
}

// Check if the type name matches the distribution type name
/*! \detail The type name comparison is case-insensitive. A positive match
 * will be reported if the type name has a substring equal to "equiprobable".
 */
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::doesTypeNameMatch( const std::string type_name )
{
  std::string lower_type_name = boost::algorithm::to_lower_copy( type_name );
  
  return lower_type_name.find(ThisType::getDistributionTypeName( false, true )) < lower_type_name.size();
}

// Test if the distribution is continuous
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::toStream( std::ostream& os ) const
{
  std::vector<double> raw_bin_boundaries( d_bin_boundaries.size() );

  for( size_t i = 0; i < d_bin_boundaries.size(); ++i )
    raw_bin_boundaries[i] = Utility::getRawQuantity( d_bin_boundaries[i] );

  os << Utility::container_start_char
     << this->getDistributionTypeName()
     << Utility::next_container_element_char << " "
     << raw_bin_boundaries
     << Utility::container_end_char;
}

// Method for initializing the object from an input stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::fromStream(
                                                           std::istream& is,
                                                           const std::string& )
{
  VariantVector distribution_data;

  try{
    Utility::fromStream( is, distribution_data );
  }
  EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                           "Could not extract the distribution data from "
                           "the stream!" );

  // Verify that the correct amount of distribution data is present
  TEST_FOR_EXCEPTION( distribution_data.size() != 2,
                      Utility::StringConversionException,
                      "The equiprobable bin distribution cannot be "
                      "constructed because the string representation is not "
                      "valid!" );

  // Verify that the distribution type is discrete
  this->verifyDistributionType( distribution_data[0] );

  // Extract the bin boundaries
  std::vector<double> bin_boundaries;

  this->extractBinBoundaries( distribution_data[1], bin_boundaries );

  // Verify that the bin boundaries are valid
  this->verifyValidBinBoundaries( bin_boundaries );

  // Initialize the distribution
  this->initializeDistribution( bin_boundaries );
}

// Method for converting the type to a property tree
template<typename IndependentUnit, typename DependentUnit>
Utility::PropertyTree UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::toPropertyTree(
                                                 const bool inline_data ) const
{
  Utility::PropertyTree ptree;

  if( inline_data )
    ptree.put_value( *this );
  else
  {
    ptree.put( "type", Utility::convertOneDDistributionTypeToString( ThisType::distribution_type ) );

    std::vector<double> raw_bin_boundaries( d_bin_boundaries.size() );

    for( size_t i = 0; i < d_bin_boundaries.size(); ++i )
      raw_bin_boundaries[i] = Utility::getRawQuantity( d_bin_boundaries[i] );

    ptree.put( "bin boundaries", raw_bin_boundaries );
  }

  return ptree;
}

// Method for initializing the object from a property tree
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::fromPropertyTree(
                                    const Utility::PropertyTree& node,
                                    std::vector<std::string>& unused_children )
{
  // Initialize from inline data
  if( node.size() == 0 )
  {
    std::istringstream iss( node.data().toString() );

    try{
      this->fromStream( iss );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                Utility::PropertyTreeConversionException,
                                "Could not create the equiprobable bin "
                                "distribution!" );
  }
  // Initialize from child nodes
  else
  {
    Utility::PropertyTree::const_iterator node_it, node_end;
    node_it = node.begin();
    node_end = node.end();

    bool type_verified = false;
    bool bin_boundaries_extracted = false;

    std::vector<double> bin_boundaries;

    while( node_it != node_end )
    {
      std::string child_node_key =
        boost::algorithm::to_lower_copy( node_it->first );

      // Verify the distribution type
      if( child_node_key.find( "type" ) < child_node_key.size() )
      {
        try{
          this->verifyDistributionType( node_it->second.data() );
        }
        EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                    Utility::PropertyTreeConversionException,
                                    "Could not create the equiprobable bin "
                                    "distribution!" );

        type_verified = true;
      }

      // Extract the bin boundaries
      else if( child_node_key.find( "bin" ) < child_node_key.size() )
      {
        try{
          this->extractBinBoundaries( node_it->second, bin_boundaries );
        }
        EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                    Utility::PropertyTreeConversionException,
                                    "Could not create the equiprobable bin "
                                    "distribution!" );

        bin_boundaries_extracted = true;
      }

      // This child node is unused (and is not a comment)
      else if( child_node_key.find( PTREE_COMMENT_NODE_KEY ) >=
               child_node_key.size() )
      {
        unused_children.push_back( node_it->first );
      }

      ++node_it;
    }

    // Make sure that the distribution type was verified
    TEST_FOR_EXCEPTION( !type_verified,
                        Utility::PropertyTreeConversionException,
                        "The equiprobable bin distribution could not be "
                        "constructed because the type could not be "
                        "verified!" );

    // Make sure that the bin boundaries were set
    TEST_FOR_EXCEPTION( !bin_boundaries_extracted,
                        Utility::PropertyTreeConversionException,
                        "The equiprobable bin distribution could not be "
                        "constructed because the bin boundaries were not "
                        "specified!" );

    // Verify that the bin boundaries are valid
    try{
      this->verifyValidBinBoundaries( bin_boundaries );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                Utility::PropertyTreeConversionException,
                                "The equiprobable bin distribution could not "
                                "be constructed because the bin boundaries "
                                "are not valid!" );

    // Initialize the distribution
    this->initializeDistribution( bin_boundaries );
  }
}

// Equality comparison operator
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::operator==(
                      const UnitAwareEquiprobableBinDistribution& other ) const
{
  return d_bin_boundaries == other.d_bin_boundaries;
}

// Inequality comparison operator
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::operator!=(
                      const UnitAwareEquiprobableBinDistribution& other ) const
{
  return d_bin_boundaries != other.d_bin_boundaries;
}

// Initialize the distribution
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::initializeDistribution(
				 const std::vector<double>& bin_boundaries )
{
  // Make sure there is at least one bin
  testPrecondition( bin_boundaries.size() > 1 );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( bin_boundaries.begin(),
					     bin_boundaries.end() ) );

  // Resize the bin boundaries array
  d_bin_boundaries.resize( bin_boundaries.size() );

  // Copy the bin boundaries
  for( unsigned i = 0; i < bin_boundaries.size(); ++i )
    setQuantity( d_bin_boundaries[i], bin_boundaries[i] );
}

// Initialize the distribution
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity>
void UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::initializeDistribution(
		     const std::vector<InputIndepQuantity>& bin_boundaries )
{
  // Make sure there is at least one bin
  testPrecondition( bin_boundaries.size() > 1 );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( bin_boundaries.begin(),
					     bin_boundaries.end() ) );

  // Resize the bin boundaries array
  d_bin_boundaries.resize( bin_boundaries.size() );

  // Explicitly cast each bin boundary to the desired quantity
  for( unsigned i = 0; i < bin_boundaries.size(); ++i )
    d_bin_boundaries[i] = IndepQuantity( bin_boundaries[i] );
}

// Test if the dependent variable can be zero within the indep bounds
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::canDepVarBeZeroInIndepBounds() const
{
  return false;
}

// Verify that the distribution type is correct
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::verifyDistributionType(
                                            const Utility::Variant& type_data )
{
  std::string distribution_type = type_data.toLowerString();

  TEST_FOR_EXCEPTION( !ThisType::doesTypeNameMatch( distribution_type ),
                      Utility::StringConversionException,
                      "The equiprobable bin distribution cannot be "
                      "constructed because the distribution type ("
                      << distribution_type << ") does not match!" );
}

// Set the bin boundaries
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::extractBinBoundaries(
                                     const Utility::Variant& bin_boundary_data,
                                     std::vector<double>& bin_boundaries )
{
  try{
    bin_boundaries =
      Utility::variant_cast<std::vector<double> >( bin_boundary_data );
  }
  EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                           "The equiprobable bin distribution cannot be "
                           "constructed because the bin boundaries are not "
                           "valid!" );                      
}

// Extract the bin boundaries
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::extractBinBoundaries(
                                const Utility::PropertyTree& bin_boundary_data,
                                std::vector<double>& bin_boundaries )
{
  // Inline array
  if( bin_boundary_data.size() == 0 )
  {
    ThisType::extractBinBoundaries( bin_boundary_data.data(),
                                    bin_boundaries );
  }
  
  // JSON array
  else
  {
    try{
      bin_boundaries =
        Utility::fromPropertyTree<std::vector<double> >( bin_boundary_data );
    }
    EXCEPTION_CATCH_RETHROW( Utility::PropertyTreeConversionException,
                             "The equiprobable bin distribution cannot be "
                             "constructed because the bin boundary data "
                             "is invalid!" );
  }
}

// Verify that the bin boundaries are valid
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::verifyValidBinBoundaries(
                                    const std::vector<double>& bin_boundaries )
{
  TEST_FOR_EXCEPTION( bin_boundaries.size() <= 1,
		      Utility::StringConversionException,
		      "The equiprobable bin distribution cannot be "
		      "constructed because at least one bin (consisting of "
                      "two boundaries) is required!" );

  TEST_FOR_EXCEPTION( !Sort::isSortedAscending( bin_boundaries.begin(),
						bin_boundaries.end() ),
		      Utility::StringConversionException,
		      "The equiprobable bin distribution cannot be "
		      "constructed because the bin boundaries "
		      << bin_boundaries << " are not sorted!" );

  TEST_FOR_EXCEPTION( QT::isnaninf( bin_boundaries.front() ),
                      Utility::StringConversionException,
                      "The equiprobable bin distribution cannot be "
                      "constructed because the first bin boundary is "
                      "invalid!" );

  TEST_FOR_EXCEPTION( QT::isnaninf( bin_boundaries.back() ),
                      Utility::StringConversionException,
                      "The equiprobable bin distribution cannot be "
                      "constructed because the last bin boundary is "
                      "invalid!" );

  TEST_FOR_EXCEPTION( std::adjacent_find( bin_boundaries.begin(),
                                          bin_boundaries.end() ) !=
                      bin_boundaries.end(),
                      Utility::StringConversionException,
                      "The equiprobable bin distribution cannot be "
                      "constructed because there are repeated bin boundaries ("
                      "first repeated value found == "
                      << *(std::adjacent_find( bin_boundaries.begin(),
                                               bin_boundaries.end() ) ) <<
                      ")!" );
}

} // end Utility namespace

#endif // end UTILITY_EQUIPROBABLE_BIN_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_EquiprobableBinDistribution_def.hpp
//---------------------------------------------------------------------------//
