//---------------------------------------------------------------------------//
//!
//! \file   Utility_ElasticElectronDistribution_def.hpp
//! \author Luke Kersting
//! \brief  Tabular distribution for elastic electron scattering class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ELASTIC_ELECTRONDISTRIBUTION_DEF_HPP
#define UTILITY_ELASTIC_ELECTRONDISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "Utility_DataProcessor.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_KinematicHelpers.hpp"

namespace Utility{

// The cutoff angle above which the screened Rutherford distribution is sampled
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::s_sr_angle = 1.0e-6;

// Default constructor
template<typename InterpolationPolicy>
ElasticElectronDistribution<InterpolationPolicy>::ElasticElectronDistribution()
{ /* ... */ }

// Constructor for ENDL tables data given as PDF
/*! \details The independent values, x, are the scattering angle in units of pi
 * ie: x = (1 - mu), where mu is the scattering angle cosine.
 * They range from 0 (forward scattering) to 2 (backscattering) ( 0 <= x <= 2 )
 * They are assumed to be sorted (lowest to highest).
 */
template<typename InterpolationPolicy>
ElasticElectronDistribution<InterpolationPolicy>::ElasticElectronDistribution(
                      const std::vector<double>& independent_values,
                      const std::vector<double>& dependent_values,
                      const double moliere_screening_constant,
                      const double screened_rutherford_normalization_constant )
  : d_distribution( independent_values.size() ),
    d_norm_constant( 0.0 ),
    d_moliere_screening_constant( moliere_screening_constant ),
    d_screened_rutherford_normalization_constant( screened_rutherford_normalization_constant ),
    d_screened_rutherford_cutoff_cdf( 0.0 )
{
  // Make sure the screened_rutherford_normalization_constant
  testPrecondition( screened_rutherford_normalization_constant > 0 );
  // Make sure that at least two points of the distribution are specified
  testPrecondition( independent_values.size() > 1 );
  // Make sure that at least two points of the distribution are specified
  testPrecondition( independent_values.size() > 1 );
  // Make sure that for n bin boundaries there are n bin values
  testPrecondition( independent_values.size() == dependent_values.size() );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( independent_values.begin(),
                                             independent_values.end() ) );
  // Make sure that the independent_values are valid
  testPrecondition( independent_values.front() >= 0.0 );
  testPrecondition( independent_values.back() <= 2.0 );
  // Make sure that the dependent values are valid
  testPrecondition( dependent_values.front() >= 0.0 );

  this->initializeDistributionENDL( independent_values, dependent_values );
}


// Constructor for ACE tables data given as CDF
  /*! \details For ACE tables data the independent values must be changed from
   * the angle cosine (mu) to angle (x) in units of pi ( x = 1 - mu )
   * The dependent values must also be changed to be in reverse ascending order
   * where: cdf(x) = 1 - cdf(mu)
   */
template<typename InterpolationPolicy>
ElasticElectronDistribution<InterpolationPolicy>::ElasticElectronDistribution(
			      const std::vector<double>& independent_values,
			      const std::vector<double>& dependent_values,
                              const double energy,
                              const int atomic_number )
  : d_distribution( independent_values.size() ),
    d_norm_constant( 0.0 ),
    d_moliere_screening_constant( 0.0 ),
    d_screened_rutherford_normalization_constant( 0.0 ),
    d_screened_rutherford_cutoff_cdf( 0.0 )
{
  // Make sure the energy is valid
  testPrecondition( energy > 0 );
  // Make sure the atomic number is valid
  testPrecondition( atomic_number > 0u );
  testPrecondition( atomic_number <= 100u );
  // Make sure that at least two points of the distribution are specified
  testPrecondition( independent_values.size() > 1 );
  // Make sure that at least two points of the distribution are specified
  testPrecondition( independent_values.size() > 1 );
  // Make sure that for n bin boundaries there are n bin values
  testPrecondition( independent_values.size() == dependent_values.size() );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( independent_values.begin(),
                                             independent_values.end() ) );
  // Make sure that the bin values are sorted
  testPrecondition( Sort::isSortedAscending( dependent_values.begin(),
                                             dependent_values.end() ) );
  // Make sure that the independent values are valid
  testPrecondition( independent_values.front() >= -1.0 );
  testPrecondition( independent_values.back() <= 1.0 );
  // Make sure that the dependent values are valid
  testPrecondition( dependent_values.front() >= 0.0 );
  testPrecondition( dependent_values.back() <= 1.0 );

  this->initializeDistributionACE( independent_values,
                                   dependent_values,
                                   energy,
                                   atomic_number );
}

// Copy constructor
template<typename InterpolationPolicy>
ElasticElectronDistribution<InterpolationPolicy>::ElasticElectronDistribution(
		const ElasticElectronDistribution<InterpolationPolicy>& dist_instance )
  : d_distribution( dist_instance.d_distribution ),
    d_norm_constant( dist_instance.d_norm_constant ),
    d_moliere_screening_constant( dist_instance.d_moliere_screening_constant ),
    d_screened_rutherford_normalization_constant( dist_instance.d_screened_rutherford_normalization_constant ),
    d_screened_rutherford_cutoff_cdf( dist_instance.d_screened_rutherford_cutoff_cdf )
{
  // Make sure the distribution is valid
  testPrecondition( dist_instance.d_distribution.size() > 0 );
}

// Assignment operator
template<typename InterpolationPolicy>
ElasticElectronDistribution<InterpolationPolicy>&
ElasticElectronDistribution<InterpolationPolicy>::operator=(
		const ElasticElectronDistribution<InterpolationPolicy>& dist_instance )
{
  // Make sure the distribution is valid
  testPrecondition( dist_instance.d_distribution.size() > 0 );

  if( this != &dist_instance )
  {
    d_distribution = dist_instance.d_distribution;
    d_norm_constant = dist_instance.d_norm_constant;
    d_moliere_screening_constant = dist_instance.d_moliere_screening_constant;
    d_screened_rutherford_normalization_constant = dist_instance.d_screened_rutherford_normalization_constant;
    d_screened_rutherford_cutoff_cdf = dist_instance.d_screened_rutherford_cutoff_cdf;
  }

  return *this;
}

// Evaluate the distribution
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::evaluate(
					   const double indep_var_value ) const
{
  return this->evaluatePDF( indep_var_value );
}

// Evaluate the PDF
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::evaluatePDF(
					   const double indep_var_value ) const
{
  if( indep_var_value < 0.0 )
    return 0.0;
  else if( indep_var_value < s_sr_angle )
  {
    return d_screened_rutherford_normalization_constant/(
            ( indep_var_value + d_moliere_screening_constant )*
            ( indep_var_value + d_moliere_screening_constant ) );
  }
  else if( indep_var_value > Utility::get<0>( d_distribution.back() ) )
    return 0.0;
  else if( indep_var_value == Utility::get<0>( d_distribution.back() ) )
    return Utility::get<2>( d_distribution.back() );
  else
  {
    DistributionArray::const_iterator start, end, lower_bin_boundary,
      upper_bin_boundary;
    start = d_distribution.begin();
    end = d_distribution.end();

    lower_bin_boundary = Search::binaryLowerBound<FIRST>( start,
							  end,
							  indep_var_value );

    upper_bin_boundary = lower_bin_boundary;
    ++upper_bin_boundary;

    double lower_indep_value = Utility::get<0>( *lower_bin_boundary );
    double lower_pdf_value = Utility::get<2>( *lower_bin_boundary );
    double upper_indep_value = Utility::get<0>( *upper_bin_boundary );
    double upper_pdf_value = Utility::get<2>( *upper_bin_boundary );

    return InterpolationPolicy::interpolate( lower_indep_value,
					     upper_indep_value,
					     indep_var_value,
					     lower_pdf_value,
					     upper_pdf_value );
  }
}

// Evaluate the CDF
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::evaluateCDF(
					   const double indep_var_value ) const
{
  if( indep_var_value < 0.0 )
    return 0.0;
  else if( indep_var_value < s_sr_angle )
  {
    return indep_var_value*d_screened_rutherford_normalization_constant/(
            d_moliere_screening_constant*
            ( indep_var_value + d_moliere_screening_constant ) )*
            d_norm_constant;
  }
  else if( indep_var_value > Utility::get<0>( d_distribution.back() ) )
    return 1.0;
  else
  {
    DistributionArray::const_iterator start, end, lower_bin_boundary;
    start = d_distribution.begin();
    end = d_distribution.end();

    lower_bin_boundary = Search::binaryLowerBound<FIRST>( start,
							  end,
							  indep_var_value );

    double indep_diff =
      indep_var_value - Utility::get<0>( *lower_bin_boundary );

    return Utility::get<1>( *lower_bin_boundary ) +
      indep_diff*Utility::get<2>( *lower_bin_boundary ) +
      indep_diff*indep_diff/2.0 * Utility::get<3>( *lower_bin_boundary );
  }
}

// Return a random sample from the distribution
template<typename InterpolationPolicy>
inline double ElasticElectronDistribution<InterpolationPolicy>::sample() const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  unsigned dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample and record the number of trials
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::sampleAndRecordTrials(
						       DistributionTraits::Counter& trials ) const
{
  ++trials;

  return this->sample();
}

// Return a random sample and bin index from the distribution
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::sampleAndRecordBinIndex(
					    unsigned& sampled_bin_index ) const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleImplementation( random_number, sampled_bin_index );
}

// Return a sample from the distribution at the given CDF value
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::sampleWithRandomNumber(
					     const double random_number ) const
{
  unsigned dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample from the corresponding CDF in a subrange
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::sampleInSubrange(
					     const double max_indep_var ) const
{
  // Make sure the maximum indep var is valid
  testPrecondition( max_indep_var >= this->getLowerBoundOfIndepVar() );

  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleWithRandomNumberInSubrange( random_number,
						 max_indep_var );
}

// Return a random sample from the distribution at the given CDF value in a subrange
template<typename InterpolationPolicy>
inline double ElasticElectronDistribution<InterpolationPolicy>::sampleWithRandomNumberInSubrange(
					     const double random_number,
					     const double max_indep_var ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  // Make sure the maximum indep var is valid
  testPrecondition( max_indep_var >= this->getLowerBoundOfIndepVar() );

  // Calculate a scaled random number
  double scaled_random_number =
    random_number*this->evaluateCDF( max_indep_var );

  unsigned dummy_index;

  return this->sampleImplementation( scaled_random_number, dummy_index );
}

// Return a random sample using the random number and record the bin index
/*! !\details If the screened Rutherford portion is sampled a bin index of 0
 *  will be returned
 */
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::sampleImplementation(
					    double random_number,
					    unsigned& sampled_bin_index ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  // Calculate the sampled independent value
  double sample;

  if ( random_number >= d_screened_rutherford_cutoff_cdf )
  {
    DistributionArray::const_iterator start, end, lower_bin_boundary;
    start = d_distribution.begin();
    end = d_distribution.end();

    lower_bin_boundary = Search::binaryLowerBound<SECOND>( start,
                                                           end,
                                                           random_number );

    // Calculate the sampled bin index
    sampled_bin_index = std::distance(d_distribution.begin(),lower_bin_boundary);

    double indep_value = Utility::get<0>( *lower_bin_boundary );
    double cdf_diff = random_number - Utility::get<1>( *lower_bin_boundary );
    double pdf_value = Utility::get<2>( *lower_bin_boundary );
    double slope = Utility::get<3>( *lower_bin_boundary );

    // x = x0 + [sqrt(pdf(x0)^2 + 2m[cdf(x)-cdf(x0)]) - pdf(x0)]/m
    if( slope != 0.0 )
    {
      sample = indep_value +
        (sqrt( pdf_value*pdf_value + 2*slope*cdf_diff ) - pdf_value)/slope;
    }
    // x = x0 + [cdf(x)-cdf(x0)]/pdf(x0) => L'Hopital's rule
    else
      sample =  indep_value + cdf_diff/pdf_value;
  }
  else if ( random_number > 0.0 )
  {
    sampled_bin_index = 0.0;
    sample = random_number*
              d_moliere_screening_constant*d_moliere_screening_constant/
            ( d_screened_rutherford_normalization_constant -
              d_moliere_screening_constant*random_number );
  }
  else
  {
    sampled_bin_index = 0.0;
    sample = 0.0;
  }

  // Make sure the sample is valid
  testPostcondition( !Utility::QuantityTraits<double>::isnaninf( sample ) );
  // Make sure the random number is valid
  testPrecondition( sample >= 0.0 );
  testPrecondition( sample <= 2.0 );

  return sample;
}

// Return the upper bound of the distribution independent variable
template<typename InterpolationPolicy>
double
ElasticElectronDistribution<InterpolationPolicy>::getUpperBoundOfIndepVar() const
{
  return Utility::get<0>( d_distribution.back() );
}

// Return the lower bound of the distribution independent variable
template<typename InterpolationPolicy>
double
ElasticElectronDistribution<InterpolationPolicy>::getLowerBoundOfIndepVar() const
{
  return 0.0;
}

// Return the distribution type
template<typename InterpolationPolicy>
OneDDistributionType
ElasticElectronDistribution<InterpolationPolicy>::getDistributionType() const
{
  return ElasticElectronDistribution<InterpolationPolicy>::distribution_type;
}

// Test if the distribution is continuous
template<typename InterpolationPolicy>
bool ElasticElectronDistribution<InterpolationPolicy>::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
template<typename InterpolationPolicy>
void ElasticElectronDistribution<InterpolationPolicy>::toStream(
						       std::ostream& os ) const
{
  std::vector<double> independent_values( d_distribution.size() );
  std::vector<double> dependent_values( d_distribution.size() );

  for( unsigned i = 0u; i < d_distribution.size(); ++i )
  {
    independent_values[i] = Utility::get<0>( d_distribution[i] );
    dependent_values[i] = Utility::get<2>( d_distribution[i] );
  }

  os << "{" << Utility::convertOneDDistributionTypeToString( ElasticElectronDistribution<InterpolationPolicy>::distribution_type )
     << " " << InterpolationPolicy::name()
     << ", " << independent_values
     << ", " << dependent_values
     << ", " << d_moliere_screening_constant
     << ", " << d_screened_rutherford_normalization_constant
     << "}";
}

// Method for initializing the object from an input stream
template<typename InterpolationPolicy>
void ElasticElectronDistribution<InterpolationPolicy>::fromStream(
                                                           std::istream& is,
                                                           const std::string& )
{
  VariantVector distribution_data;

  try{
    Utility::fromStream( is, distribution_data );
  }
  EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                           "Could not extract the distribution data from the "
                           "stream!" );

  // Verify that the correct amount of distribution data is present
  TEST_FOR_EXCEPTION( distribution_data.size() != 5,
                      Utility::StringConversionException,
                      "The elastic electron distribution cannot be "
                      "constructed because the string representation is not "
                      "valid!" );

  // Verify that the distribution type is elastic electron
  this->verifyDistributionType( distribution_data[0] );

  // Extract the independent values
  std::vector<double> independent_values;

  this->extractIndependentValues( distribution_data[1], independent_values );

  // Extract the dependent values
  std::vector<double> dependent_values;

  this->extractDependentValues( distribution_data[2], dependent_values );

  // Extract the moliere screening constant
  this->extractMoliereScreeningConstant( distribution_data[3] );

  // Extract the screened rutherford normalization constant
  this->extractScreenedRutherfordNormalizationConstant( distribution_data[4] );

  // Verify that the values are valid
  this->verifyValidValues( independent_values, dependent_values );

  this->initializeDistributionENDL( independent_values, dependent_values );
}

// Method for placing an object in the desired property tree node
template<typename InterpolationPolicy>
void ElasticElectronDistribution<InterpolationPolicy>::toNode(
                                                 const std::string& node_key,
                                                 Utility::PropertyTree& ptree,
                                                 const bool inline_data ) const
{
  if( inline_data )
  {
    std::ostringstream oss;

    this->toStream( oss );

    ptree.put( node_key, oss.str() );
  }
  else
  {
    Utility::PropertyTree child_tree;

    std::string type_name = 
      Utility::convertOneDDistributionTypeToString( ElasticElectronDistribution<InterpolationPolicy>::distribution_type );

    type_name += " ";
    type_name += InterpolationPolicy::name();
    
    child_tree.put( "type", type_name );

    std::vector<double> independent_values( d_distribution.size() );
    std::vector<double> dependent_values( d_distribution.size() );

    for( size_t i = 0; i < d_distribution.size(); ++i )
    {
      independent_values[i] = Utility::get<0>( d_distribution[i] );
      dependent_values[i] = Utility::get<2>( d_distribution[i] );
    }

    child_tree.put( "independent values", independent_values );
    child_tree.put( "dependent values", dependent_values );
    child_tree.put( "moliere screening constant", d_moliere_screening_constant );
    child_tree.put( "screened rutherford norm constant", d_screened_rutherford_normalization_constant );

    ptree.put_child( node_key, child_tree );
  }
}

// Method for initializing the object from a property tree node
template<typename InterpolationPolicy>
void ElasticElectronDistribution<InterpolationPolicy>::fromNode(
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
                                Utility::PTreeNodeConversionException,
                                "Could not create the elastic electron "
                                "distribution!" );
  }
  // Initialize from child nodes
  else
  {
    Utility::PropertyTree::const_iterator node_it, node_end;
    node_it = node.begin();
    node_end = node.end();

    bool type_verified = false;
    bool independent_vals_extracted = false;
    bool dependent_vals_extracted = false;
    bool moliere_screening_const_extracted = false;
    bool screened_rutherford_norm_const_extracted = false;

    std::vector<double> independent_values, dependent_values;

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
                                    Utility::PTreeNodeConversionException,
                                    "Could not create the elastic electron "
                                    "distribution!" );

        type_verified = true;
      }

      // Extract the independent values
      else if( child_node_key.find( "indep" ) < child_node_key.size() )
      {
        try{
          this->extractIndependentValues( node_it->second.data(),
                                          independent_values );
        }
        EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                    Utility::PTreeNodeConversionException,
                                    "Could not create the elastic electron "
                                    "distribution!" );

        independent_vals_extracted = true;
      }

      // Extract the dependent values
      else if( child_node_key.find( "dep" ) < child_node_key.size() )
      {
        try{
          this->extractDependentValues( node_it->second.data(),
                                        dependent_values );
        }
        EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                    Utility::PTreeNodeConversionException,
                                    "Could not create the elastic electron "
                                    "distribution!" );

        dependent_vals_extracted = true;
      }

      // Extract the moliere screening constant
      else if( child_node_key.find( "moliere" ) < child_node_key.size() )
      {
        try{
          this->extractMoliereScreeningConstant( node_it->second.data() );
        }
        EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                    Utility::PTreeNodeConversionException,
                                    "Could not create the elastic electron "
                                    "distribution!" );
        
        moliere_screening_const_extracted = true;
      }

      // Extract the screened rutherford normalization constant
      else if( child_node_key.find( "rutherford" ) < child_node_key.size() )
      {
        try{
          this->extractScreenedRutherfordNormalizationConstant( node_it->second.data() );
        }
        EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                    Utility::PTreeNodeConversionException,
                                    "Could not create the elastic electron "
                                    "distribution!" );
        
        screened_rutherford_norm_const_extracted = true;
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
                        Utility::PTreeNodeConversionException,
                        "The elastic electron distribution could not be "
                        "constructed because the type could not be "
                        "verified!" );

    // Make sure that the independent values were set
    TEST_FOR_EXCEPTION( !independent_vals_extracted,
                        Utility::PTreeNodeConversionException,
                        "The elastic electron distribution could not be "
                        "constructed because the independent values were not "
                        "specified!" );

    // Make sure that the dependent values were set
    TEST_FOR_EXCEPTION( !dependent_vals_extracted,
                        Utility::PTreeNodeConversionException,
                        "The elastic electron distribution could not be "
                        "constructed because the dependent values were not "
                        "specified!" );

    // Make sure that the molier screening constant was set
    TEST_FOR_EXCEPTION( !moliere_screening_const_extracted,
                        Utility::PTreeNodeConversionException,
                        "The elastic electron distribution could not be "
                        "constructed because the moliere screening constant "
                        "was not specified!" );
    
    // Make sure that the screened rutherford normalization constant was set
    TEST_FOR_EXCEPTION( !screened_rutherford_norm_const_extracted,
                        Utility::PTreeNodeConversionException,
                        "The elastic electron distribution could not be "
                        "constructed because the screened rutherford "
                        "normalization constant was not specified!" );

    // Verify that the values are valid
    try{
      this->verifyValidValues( independent_values, dependent_values );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                                Utility::PTreeNodeConversionException,
                                "Could not create the elastic electron "
                                "distribution!" );

    this->initializeDistributionENDL( independent_values, dependent_values );
  }
}

// Verify that the distribution type is elastic electron
template<typename InterpolationPolicy>
void ElasticElectronDistribution<InterpolationPolicy>::verifyDistributionType(
                                            const Utility::Variant& type_data )
{
  std::string distribution_type = type_data.toString();
  boost::algorithm::to_lower( distribution_type );

  TEST_FOR_EXCEPTION( distribution_type.find( "elastic electron" ) >=
                      distribution_type.size(),
                      Utility::StringConversionException,
                      "The elastic electron distribution cannot be "
                      "constructed because the distribution type ("
                      << distribution_type << ") does not match!" );

  TEST_FOR_EXCEPTION( distribution_type.find( boost::algorithm::to_lower_copy(InterpolationPolicy::name()) ) >=
                      distribution_type.size(),
                      Utility::StringConversionException,
                      "The elastic electron distribution cannot be "
                      "constructed because the interpolation type ("
                      << InterpolationPolicy::name() << ") does not match!" );
}

// Set the independent values
template<typename InterpolationPolicy>
void ElasticElectronDistribution<InterpolationPolicy>::extractIndependentValues(
                                      const Utility::Variant& indep_data,
                                      std::vector<double>& independent_values )
{
  try{
    independent_values =
      Utility::variant_cast<std::vector<double> >( indep_data );
  }
  EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                           "The elastic electron distribution cannot be "
                           "constructed because the independent values are "
                           "not valid!" );

  TEST_FOR_EXCEPTION( !Sort::isSortedAscending( independent_values.begin(),
                                                independent_values.end() ),
                      Utility::StringConversionException,
                      "The elastic electron distribution cannot be "
                      "constructed because the independent values "
                      << indep_data.toString() << " are not sorted!" );

  TEST_FOR_EXCEPTION( !InterpolationPolicy::isIndepVarInValidRange( independent_values.front() ),
                      Utility::StringConversionException,
                      "The elastic electron distribution cannot be "
                      "constructed because the independent values "
                      << indep_data.toString() << " are not compatible with "
                      "the requested interpolation type ("
                      << InterpolationPolicy::name() << ")!" );
}

// Set the dependent values
template<typename InterpolationPolicy>
void ElasticElectronDistribution<InterpolationPolicy>::extractDependentValues(
                                        const Utility::Variant& dep_data,
                                        std::vector<double>& dependent_values )
{
  try{
    dependent_values = Utility::variant_cast<std::vector<double> >( dep_data );
  }
  EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                           "The elastic electron distribution cannot be "
                           "constructed because the dependent values are not "
                           "valid!" );

  for( size_t i = 0; i < dependent_values.size(); ++i )
  {
    TEST_FOR_EXCEPTION( !InterpolationPolicy::isDepVarInValidRange( dependent_values[i] ),
                        Utility::StringConversionException,
                        "The elastic electron distribution cannot be "
                        "constructed because dependent value " << i << "("
                        << dependent_values[i] << ") is not compatible with "
                        "the requested interpolation type ("
                        << InterpolationPolicy::name() << ")!" );
  }
}

// Set the moliere screening constant
template<typename InterpolationPolicy>
void ElasticElectronDistribution<InterpolationPolicy>::extractMoliereScreeningConstant( const Utility::Variant& dep_data )
{
  try{
    d_moliere_screening_constant = Utility::variant_cast<double>( dep_data );
  }
  EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                           "The elastic electron distribution cannot be "
                           "constructed because the moliere screening "
                           "constant is not valid!" );
}

// Set the screened rutherford normalization constant
template<typename InterpolationPolicy>
void ElasticElectronDistribution<InterpolationPolicy>::extractScreenedRutherfordNormalizationConstant( const Utility::Variant& dep_data )
{
  try{
    d_screened_rutherford_normalization_constant =
      Utility::variant_cast<double>( dep_data );
  }
  EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                           "The elastic electron distribution cannot be "
                           "constructed because the screened rutherford "
                           "normalization constant is not valid!" );

  TEST_FOR_EXCEPTION( d_screened_rutherford_normalization_constant <= 0,
                      Utility::StringConversionException,
                      "The elastic electron distribution cannot be "
                      "constructed because the screened rutherford "
                      "normalization constant is not valid!" );
}

// Verify that the values are valid
template<typename InterpolationPolicy>
void ElasticElectronDistribution<InterpolationPolicy>::verifyValidValues(
                                 const std::vector<double>& independent_values,
                                 const std::vector<double>& dependent_values )
{
  TEST_FOR_EXCEPTION( independent_values.size() != dependent_values.size(),
		      Utility::StringConversionException,
		      "The elastic electron distribution cannot be "
                      "constructed because the number of independent values ("
                      << independent_values.size() << ") does not match the "
                      "number of dependent values ("
		      << dependent_values.size() << ")!" );

  TEST_FOR_EXCEPTION( independent_values.size() == 0,
                      Utility::StringConversionException,
                      "The elastic electron distribution cannot be "
                      "constructed because no independent values have been "
                      "specified!" );

}

// Equality comparison operator
template<typename InterpolationPolicy>
bool ElasticElectronDistribution<InterpolationPolicy>::operator==(
                               const ElasticElectronDistribution& other ) const
{
  return d_distribution == other.d_distribution &&
    d_norm_constant == other.d_norm_constant &&
    d_moliere_screening_constant == other.d_moliere_screening_constant &&
    d_screened_rutherford_normalization_constant == other.d_screened_rutherford_normalization_constant;
}

// Inequality comparison operator
template<typename InterpolationPolicy>
bool ElasticElectronDistribution<InterpolationPolicy>::operator!=(
                               const ElasticElectronDistribution& other ) const
{
  return d_distribution != other.d_distribution ||
    d_norm_constant != other.d_norm_constant ||
    d_moliere_screening_constant != other.d_moliere_screening_constant ||
    d_screened_rutherford_normalization_constant != other.d_screened_rutherford_normalization_constant;
    d_norm_constant != other.d_norm_constant;
}

// Return Moliere's screening constant
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::getMoliereScreeningConstant() const
{
  return d_moliere_screening_constant;
}

// Return the normalization constant for the screened Rutherford component of the distribution
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::getScreenedRutherfordNormalizationConstant() const
{
  return d_screened_rutherford_normalization_constant;
}

// Initialize the distribution for ACE
template<typename InterpolationPolicy>
void ElasticElectronDistribution<InterpolationPolicy>::initializeDistributionACE(
			      const std::vector<double>& independent_values,
			      const std::vector<double>& dependent_values,
                              const double energy,
                              const double atomic_number )
{
  unsigned size = independent_values.size();

  // Resize the distribution
  d_distribution.resize( size );

  // Set the first two data bins
  Utility::get<0>( d_distribution[0] ) = 1.0 - independent_values[size-1];
  Utility::get<1>( d_distribution[0] ) = 1.0 - dependent_values[size-1];
  Utility::get<0>( d_distribution[1] ) = 1.0 - independent_values[size-2];
  Utility::get<1>( d_distribution[1] ) = 1.0 - dependent_values[size-2];
  
  this->setFirstTwoPDFs( 1.0-dependent_values[size-1],
                         1.0-dependent_values[size-2],
                         energy,
                         atomic_number );

  d_screened_rutherford_cutoff_cdf =  Utility::get<2>( d_distribution[1] );

  // Assign the distribution
  for( int i = 2; i < size; ++i )
  {
    Utility::get<0>( d_distribution[i] ) = 1.0 - independent_values[size-i-1];
    Utility::get<1>( d_distribution[i] ) = 1.0 - dependent_values[size-i-1];

    // Use Lin-Lin interpolation for the pdf and quadratic for the cdf
    if( Utility::get<1>( d_distribution[i-1] ) != Utility::get<1>( d_distribution[i] ) )
    {
      // Calculate the pdf from the cdf
      Utility::get<2>( d_distribution[i] ) =
        -Utility::get<2>( d_distribution[i-1] ) + 2.0 *
        (Utility::get<1>( d_distribution[i] ) - Utility::get<1>( d_distribution[i-1] ))/
        (Utility::get<0>( d_distribution[i] ) - Utility::get<0>( d_distribution[i-1] ));
    }
    else // If the cdf does not change inbetween angular bins, set the pdf to zero
    {
      Utility::get<2>( d_distribution[i] ) = 0.0;
    }
  }

  // Set normalization constant
  d_norm_constant = Utility::get<1>( d_distribution.back() );

  // Verify that the CDF is normalized (in event of round-off errors)
  if( dependent_values.back() != 1.0 )
  {
    for( unsigned j = 0; j < d_distribution.size(); ++j )
    {
      Utility::get<1>( d_distribution[j] ) /= d_norm_constant;
      Utility::get<2>( d_distribution[j] ) /= d_norm_constant;
    }
  }

  // Calculate the slopes of the PDF
  DataProcessor::calculateSlopes<FIRST,THIRD,FOURTH>( d_distribution );
}

// Initialize the distribution for ENDL
template<typename InterpolationPolicy>
void ElasticElectronDistribution<InterpolationPolicy>::initializeDistributionENDL(
			      const std::vector<double>& independent_values,
			      const std::vector<double>& dependent_values )
{
  // Make sure that at least two points of the distribution are specified
  testPrecondition( independent_values.size() > 1 );
  // Make sure that the independent values are sorted
  testPrecondition( Sort::isSortedAscending( independent_values.begin(),
					     independent_values.end() ) );
  // Make sure that every independent value has a dependent value
  testPrecondition( independent_values.size() == dependent_values.size() );

  // Resize the distribution
  d_distribution.resize( independent_values.size() );

  // Assign the raw distribution data
  for( unsigned i = 0; i < independent_values.size(); ++i )
  {
    Utility::get<0>( d_distribution[i] ) = independent_values[i];
    Utility::get<2>( d_distribution[i] ) = dependent_values[i];
  }

  // Create a CDF from the raw distribution data
  double max_tabular_cdf =
    DataProcessor::calculateContinuousCDF<FIRST,THIRD,SECOND>(d_distribution);

  // The cutoff angle above which the screened Rutherford distribution is sampled
  d_screened_rutherford_cutoff_cdf =
    ( s_sr_angle*d_screened_rutherford_normalization_constant )/
    ( d_moliere_screening_constant*( s_sr_angle+d_moliere_screening_constant ) );

  /* Normalize the CDF by:
    (the max cutoff cdf) +
    (the ratio of the screened Ruthreford to the cutoff distribution ) */
  d_norm_constant = max_tabular_cdf + d_screened_rutherford_cutoff_cdf;

  // Normalized the CDF to screened Rutherford peak
  for( unsigned j = 0; j < d_distribution.size(); ++j )
  {
    Utility::get<1>( d_distribution[j] ) /= d_norm_constant;
  }


  // Calculate the slopes of the PDF
  DataProcessor::calculateSlopes<FIRST,THIRD,FOURTH>( d_distribution );
}

// Set the first two PDF values
template<typename InterpolationPolicy>
void ElasticElectronDistribution<InterpolationPolicy>::setFirstTwoPDFs(
        const double first_cdf,
        const double second_cdf,
        const double energy,
        const double atomic_number )
{
  // get size of array
  unsigned size = d_distribution.size();

  // get the momentum**2 of the electron in units of electron_rest_mass_energy
  double electron_momentum_squared =
           Utility::calculateDimensionlessRelativisticMomentumSquared(
                          Utility::PhysicalConstants::electron_rest_mass_energy,
                          energy );

  // get the velocity of the electron divided by the speed of light beta = v/c
  double beta_squared = Utility::calculateDimensionlessRelativisticSpeedSquared(
           Utility::PhysicalConstants::electron_rest_mass_energy,
           energy );

  // The fine structure constant squared
  const double fine_structure_const_squared=
        Utility::PhysicalConstants::fine_structure_constant*
        Utility::PhysicalConstants::fine_structure_constant;

  const double screening_param1 =
    fine_structure_const_squared/( 2.0*0.885*0.885 );

  const double screening_param2 = 3.76*fine_structure_const_squared*
    atomic_number*atomic_number;

  const double screening_param3 = 1.0/beta_squared*sqrt( energy/
          ( energy + Utility::PhysicalConstants::electron_rest_mass_energy) );
  
  const double atomic_number_two_thirds_power = pow( atomic_number, 2.0/3.0 );
  
  // Calculate Moliere's atomic screening constant  
  d_moliere_screening_constant =
    screening_param1 * 1.0/electron_momentum_squared *
    atomic_number_two_thirds_power *
    ( 1.13 + screening_param2*screening_param3 );

  const double var = (s_sr_angle + d_moliere_screening_constant);

  // Calculate the normalization constant
  d_screened_rutherford_normalization_constant =
    (second_cdf - first_cdf)*d_moliere_screening_constant*var/s_sr_angle;

  Utility::get<2>( d_distribution[1] ) =
    d_screened_rutherford_normalization_constant/( var*var );
  
  Utility::get<2>( d_distribution[0] ) =
    d_screened_rutherford_normalization_constant/
    ( d_moliere_screening_constant*d_moliere_screening_constant );
}

// Test if the dependent variable can be zero within the indep bounds
template<typename InterpolationPolicy>
inline bool ElasticElectronDistribution<InterpolationPolicy>::canDepVarBeZeroInIndepBounds() const
{
  bool possible_zero = false;

  for( size_t i = 0; i < d_distribution.size(); ++i )
  {
    if( Utility::get<2>( d_distribution[i] ) == 0.0 )
    {
      possible_zero = true;

      break;
    }
  }

  return possible_zero;
}

// Test if the independent variable is compatible with Lin processing
template<typename InterpolationPolicy>
inline bool ElasticElectronDistribution<InterpolationPolicy>::isIndepVarCompatibleWithProcessingType(
                                         const LinIndepVarProcessingTag ) const
{
  return boost::is_same<typename InterpolationPolicy::IndepVarProcessingTag,LinIndepVarProcessingTag>::value;
}
  
// Test if the independent variable is compatible with Log processing
template<typename InterpolationPolicy>
inline bool ElasticElectronDistribution<InterpolationPolicy>::isIndepVarCompatibleWithProcessingType(
                                         const LogIndepVarProcessingTag ) const
{
  return boost::is_same<typename InterpolationPolicy::IndepVarProcessingTag,LogIndepVarProcessingTag>::value;
}

// Test if the dependent variable is compatible with Lin processing
template<typename InterpolationPolicy>
inline bool ElasticElectronDistribution<InterpolationPolicy>::isDepVarCompatibleWithProcessingType(
                                           const LinDepVarProcessingTag ) const
{
  return boost::is_same<typename InterpolationPolicy::DepVarProcessingTag,LinDepVarProcessingTag>::value;
}

// Test if the dependent variable is compatible with Log processing
template<typename InterpolationPolicy>
bool ElasticElectronDistribution<InterpolationPolicy>::isDepVarCompatibleWithProcessingType(
                                           const LogDepVarProcessingTag ) const
{
  return boost::is_same<typename InterpolationPolicy::DepVarProcessingTag,LogDepVarProcessingTag>::value;
}

} // end Utility namespace

#endif // end Utility_ElasticElectronDistribution_def.hpp

//---------------------------------------------------------------------------//
// end Utility_ElasticElectronDistribution_def.hpp
//---------------------------------------------------------------------------//
