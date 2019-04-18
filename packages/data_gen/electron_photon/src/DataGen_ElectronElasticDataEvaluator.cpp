//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ElectronElasticDataEvaluator.hpp
//! \author Luke Kersting
//! \brief  The electron elastic data evaluator class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "DataGen_ElectronElasticDataEvaluator.hpp"
#include "DataGen_ElasticElectronMomentsEvaluator.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "Utility_SloanRadauQuadrature.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_StaticOutputFormatter.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_LoggingMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace DataGen{

// Constructor from ENDL data container
ElectronElasticDataEvaluator::ElectronElasticDataEvaluator(
    const std::shared_ptr<const Data::ENDLDataContainer>& data_container,
    const double min_energy,
    const double max_energy,
    const double cutoff_angle_cosine,
    const unsigned number_of_moment_preserving_angles,
    const double tabular_evaluation_tol,
    const MonteCarlo::TwoDGridType two_d_grid,
    const MonteCarlo::TwoDInterpolationType two_d_interp,
    const MonteCarlo::CoupledElasticSamplingMethod sampling_method,
    const bool generate_new_distribution_at_min_and_max_energy )
  :  d_min_energy( min_energy ),
     d_max_energy( max_energy ),
     d_cutoff_angle_cosine( cutoff_angle_cosine ),
     d_number_of_moment_preserving_angles( number_of_moment_preserving_angles ),
     d_tabular_evaluation_tol( tabular_evaluation_tol ),
     d_two_d_grid( two_d_grid ),
     d_two_d_interp( two_d_interp ),
     d_sampling_method( sampling_method ),
     d_generate_new_distribution_at_min_and_max_energy( generate_new_distribution_at_min_and_max_energy ),
     d_atomic_number( data_container->getAtomicNumber() ),
     d_energy_grid( std::make_shared<const std::vector<double> >( data_container->getElasticEnergyGrid() ) ),
     d_cutoff_cross_section( std::make_shared<const std::vector<double> >( data_container->getCutoffElasticCrossSection() ) ),
     d_cutoff_threshold_energy_index( 0u ),
     d_total_cross_section( std::make_shared<const std::vector<double> >( data_container->getTotalElasticCrossSection() ) ),
     d_total_threshold_energy_index( 0u ),
     d_angular_energy_grid( data_container->getCutoffElasticAngularEnergyGrid() )
{
  if( d_min_energy < d_energy_grid->front() )
  {
    this->setMinEnergy( d_energy_grid->front() );

    FRENSIE_LOG_WARNING( "the min energy requested is below the ENDL table min "
                         "electron energy! The ENDL table's "
                         "min electron energy (" << d_energy_grid->front() <<
                         ") will be used instead." );
  }

  TEST_FOR_EXCEPTION( d_max_energy <= d_min_energy,
                      std::runtime_error,
                      "The max electron energy must be greater than "
                      << d_min_energy << "!" );

  if( d_max_energy > d_energy_grid->back() )
  {
    this->setMaxEnergy( d_energy_grid->back() );

    FRENSIE_LOG_WARNING( "the max energy requested is above the ENDL table max "
                         "electron energy! The ENDL table's "
                         "max electron energy (" << d_energy_grid->back() <<
                         ") will be used instead." );
  }

  TEST_FOR_EXCEPTION( this->getCutoffAngleCosine() > 1.0,
                      std::runtime_error,
                      "The cutoff angle cosine must be between -1.0 and "
                      "1.0!" );
  TEST_FOR_EXCEPTION( this->getCutoffAngleCosine() <= -1.0,
                      std::runtime_error,
                      "The cutoff angle cosine must be between -1.0 and "
                      "1.0!" );

  TEST_FOR_EXCEPTION( d_tabular_evaluation_tol <= 0.0,
                      std::runtime_error,
                      "The tabular evaluation tolerance must be between 0.0 "
                      "and 1.0!" );
  TEST_FOR_EXCEPTION( d_tabular_evaluation_tol >= 1.0,
                      std::runtime_error,
                      "The tabular evaluation tolerance must be between 0.0 "
                      "and 1.0!" );

  // Set elastic angular distribution
  std::map<double,std::vector<double> > elastic_pdf, elastic_angle;

  /* ENDL gives the angular distribution in terms of the change in angle cosine
   * (delta_angle_cosine = 1 - angle_cosine). For the native format it needs to
   * be in terms of angle_cosine. This for loop flips the distribution and
   * changes the variables to angle_cosine.
   */
  for ( double energy : d_angular_energy_grid )
  {
    this->calculateElasticAngleCosine(
        data_container->getCutoffElasticAnglesAtEnergy( energy ),
        data_container->getCutoffElasticPDFAtEnergy( energy ),
        elastic_angle[energy],
        elastic_pdf[energy] );
  }

  d_elastic_angle = elastic_angle;
  d_elastic_pdf = elastic_pdf;
}

// Constructor from Native data file
ElectronElasticDataEvaluator::ElectronElasticDataEvaluator(
    const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>& data_container,
    const double min_energy,
    const double max_energy,
    const double cutoff_angle_cosine,
    const unsigned number_of_moment_preserving_angles,
    const double tabular_evaluation_tol,
    const MonteCarlo::TwoDGridType two_d_grid,
    const MonteCarlo::TwoDInterpolationType two_d_interp,
    const MonteCarlo::CoupledElasticSamplingMethod sampling_method,
    const bool generate_new_distribution_at_min_and_max_energy )
  :  d_min_energy( min_energy ),
     d_max_energy( max_energy ),
     d_cutoff_angle_cosine( cutoff_angle_cosine ),
     d_number_of_moment_preserving_angles( number_of_moment_preserving_angles ),
     d_tabular_evaluation_tol( tabular_evaluation_tol ),
     d_two_d_grid( two_d_grid ),
     d_two_d_interp( two_d_interp ),
     d_sampling_method( sampling_method ),
     d_generate_new_distribution_at_min_and_max_energy( generate_new_distribution_at_min_and_max_energy ),
     d_atomic_number( data_container->getAtomicNumber() ),
     d_energy_grid( std::make_shared<const std::vector<double> >( data_container->getElectronEnergyGrid() ) ),
     d_cutoff_cross_section( std::make_shared<const std::vector<double> >( data_container->getCutoffElasticCrossSection() ) ),
     d_cutoff_threshold_energy_index( data_container->getCutoffElasticCrossSectionThresholdEnergyIndex() ),
     d_total_cross_section( std::make_shared<const std::vector<double> >( data_container->getTotalElasticCrossSection() ) ),
     d_total_threshold_energy_index( data_container->getTotalElasticCrossSectionThresholdEnergyIndex() ),
     d_angular_energy_grid( data_container->getElasticAngularEnergyGrid() ),
     d_elastic_angle( data_container->getCutoffElasticAngles() ),
     d_elastic_pdf( data_container->getCutoffElasticPDF() )
{
  if( d_min_energy < d_energy_grid->front() )
  {
    this->setMinEnergy( d_energy_grid->front() );

    FRENSIE_LOG_WARNING( "the min energy requested is below the Native table min "
                         "electron energy! The Native table's "
                         "min electron energy (" << d_energy_grid->front() <<
                         ") will be used instead." );
  }

  TEST_FOR_EXCEPTION( d_max_energy <= d_min_energy,
                      std::runtime_error,
                      "The max electron energy must be greater than "
                      << d_min_energy << "!" );

  if( d_max_energy > d_energy_grid->back() )
  {
    this->setMaxEnergy( d_energy_grid->back() );

    FRENSIE_LOG_WARNING( "the max energy requested is above the Native table max "
                         "electron energy! The Native table's "
                         "max electron energy (" << d_energy_grid->back() <<
                         ") will be used instead." );
  }

  TEST_FOR_EXCEPTION( d_angular_energy_grid.front() > d_energy_grid->front(),
                      std::runtime_error,
                      "The min angular energy grid point " <<
                      d_angular_energy_grid.front() <<
                      " must be greater than the min energy grid point " <<
                      d_energy_grid->front() << "!" );

  TEST_FOR_EXCEPTION( d_angular_energy_grid.back() < d_max_energy,
                      std::runtime_error,
                      "The max angular energy grid point " <<
                      d_angular_energy_grid.back() <<
                      " cannot be less than the max energy " <<
                      d_max_energy << "!" );
  TEST_FOR_EXCEPTION( d_energy_grid->back() < d_max_energy,
                      std::runtime_error,
                      "The max energy grid point " <<
                      d_energy_grid->back() <<
                      " cannot be less than the max energy " <<
                      d_max_energy << "!" );

  TEST_FOR_EXCEPTION( this->getCutoffAngleCosine() > 1.0,
                      std::runtime_error,
                      "The cutoff angle cosine must be between -1.0 and "
                      "1.0!" );
  TEST_FOR_EXCEPTION( this->getCutoffAngleCosine() <= -1.0,
                      std::runtime_error,
                      "The cutoff angle cosine must be between -1.0 and "
                      "1.0!" );

  TEST_FOR_EXCEPTION( d_tabular_evaluation_tol <= 0.0,
                      std::runtime_error,
                      "The tabular evaluation tolerance must be between 0.0 "
                      "and 1.0!" );
  TEST_FOR_EXCEPTION( d_tabular_evaluation_tol >= 1.0,
                      std::runtime_error,
                      "The tabular evaluation tolerance must be between 0.0 "
                      "and 1.0!" );
}

// Basic Constructor from Native data file
ElectronElasticDataEvaluator::ElectronElasticDataEvaluator(
    const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>& data_container,
    const bool generate_new_distribution_at_min_and_max_energy )
  :  d_generate_new_distribution_at_min_and_max_energy( generate_new_distribution_at_min_and_max_energy ),
     d_min_energy( data_container->getMinElectronEnergy() ),
     d_max_energy( data_container->getMaxElectronEnergy() ),
     d_cutoff_angle_cosine( data_container->getCutoffAngleCosine() ),
     d_number_of_moment_preserving_angles( data_container->getNumberOfMomentPreservingAngles() ),
     d_tabular_evaluation_tol( data_container->getElectronTabularEvaluationTolerance() ),
     d_sampling_method( MonteCarlo::MODIFIED_TWO_D_UNION ),
     d_atomic_number( data_container->getAtomicNumber() ),
     d_energy_grid( std::make_shared<const std::vector<double> >( data_container->getElectronEnergyGrid() ) ),
     d_cutoff_cross_section( std::make_shared<const std::vector<double> >( data_container->getCutoffElasticCrossSection() ) ),
     d_cutoff_threshold_energy_index( data_container->getCutoffElasticCrossSectionThresholdEnergyIndex() ),
     d_total_cross_section( std::make_shared<const std::vector<double> >( data_container->getTotalElasticCrossSection() ) ),
     d_total_threshold_energy_index( data_container->getTotalElasticCrossSectionThresholdEnergyIndex() ),
     d_angular_energy_grid( data_container->getElasticAngularEnergyGrid() ),
     d_elastic_angle( data_container->getCutoffElasticAngles() ),
     d_elastic_pdf( data_container->getCutoffElasticPDF() )
{

  // Set the TwoDGridType
  if ( data_container->getElectronTwoDGridPolicy() == "Direct" ||
       data_container->getElectronTwoDGridPolicy() == "Unit-base" )
  {
    d_two_d_grid = MonteCarlo::DIRECT_GRID;
  }
  else if ( data_container->getElectronTwoDGridPolicy() == "Correlated" ||
            data_container->getElectronTwoDGridPolicy() == "Unit-base Correlated" )
  {
    d_two_d_grid = MonteCarlo::CORRELATED_GRID;
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Error: the desired bivariate grid policy " <<
                     data_container->getElectronTwoDGridPolicy() <<
                     " is currently not supported!" );
  }

  // Set the TwoDInterpType
  if ( data_container->getElectronTwoDInterpPolicy() == "Log-Log-Log" )
  {
    d_two_d_interp = MonteCarlo::LOGLOGLOG_INTERPOLATION;
  }
  else if ( data_container->getElectronTwoDInterpPolicy() == "Lin-Lin-Lin" )
  {
    d_two_d_interp = MonteCarlo::LINLINLIN_INTERPOLATION;
  }
  else if ( data_container->getElectronTwoDInterpPolicy() == "Lin-Lin-Log" )
  {
    d_two_d_interp = MonteCarlo::LINLINLOG_INTERPOLATION;
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Error: the desired 2D interpolation policy " <<
                     data_container->getElectronTwoDInterpPolicy() <<
                     " is currently not supported!" );
  }
}

// Set the min energy
void ElectronElasticDataEvaluator::setMinEnergy(
                                             const double min_energy )
{
  // Make sure the min electron energy is valid
  testPrecondition( min_energy > 0.0 );

  d_min_energy = min_energy;
}

// Return the min energy
double ElectronElasticDataEvaluator::getMinEnergy() const
{
  return d_min_energy;
}

// Set the max energy
void ElectronElasticDataEvaluator::setMaxEnergy( const double max_energy )
{
  // Make sure the max electron energy is valid
  testPrecondition( this->getMinEnergy() < max_energy );

  d_max_energy = max_energy;
}

// Return the max energy
double ElectronElasticDataEvaluator::getMaxEnergy() const
{
  return d_max_energy;
}

// Set the cutoff angle cosine
void ElectronElasticDataEvaluator::setCutoffAngleCosine(
                                             const double cutoff_angle_cosine )
{
  // Make sure the cutoff angle cosine is valid
  TEST_FOR_EXCEPTION( cutoff_angle_cosine < -1.0,
                      std::runtime_error,
                      "The cutoff angle cosine must be between -1.0 and "
                      "1.0!" );
  TEST_FOR_EXCEPTION( cutoff_angle_cosine > 1.0,
                      std::runtime_error,
                      "The cutoff angle cosine must be between -1.0 and "
                      "1.0!" );

  d_cutoff_angle_cosine = cutoff_angle_cosine;
}

// Get the cutoff angle cosine
double ElectronElasticDataEvaluator::getCutoffAngleCosine() const
{
  return d_cutoff_angle_cosine;
}

// Set the number of moment preserving angles
void ElectronElasticDataEvaluator::setNumberOfMomentPreservingAngles(
                                              const unsigned number_of_angles )
{
  d_number_of_moment_preserving_angles = number_of_angles;
}

// Get the number of moment preserving angles
double ElectronElasticDataEvaluator::getNumberOfMomentPreservingAngles() const
{
  return d_number_of_moment_preserving_angles;
}

// Set the FullyTabularTwoDDistribution evaluation tolerance
void ElectronElasticDataEvaluator::setTabularEvaluationTolerance(
    const double evaluation_tolerance )
{
  // Make sure the evaluation tolerance is valid
  TEST_FOR_EXCEPTION( evaluation_tolerance <= 0.0,
                      std::runtime_error,
                      "The tabular evaluation tolerance must be between 0.0 "
                      "and 1.0!" );
  TEST_FOR_EXCEPTION( evaluation_tolerance >= 1.0,
                      std::runtime_error,
                      "The tabular evaluation tolerance must be between 0.0 "
                      "and 1.0!" );

  d_tabular_evaluation_tol = evaluation_tolerance;
}

// Get the FullyTabularTwoDDistribution evaluation tolerance
double ElectronElasticDataEvaluator::getTabularEvaluationTolerance() const
{
  return d_tabular_evaluation_tol;
}

// Set the electron TwoDInterpPolicy (LogLogLog by default)
/*! \details When the Y interpolation of the electron 2D interpolation policy
 * is Log (e.g. Lin-Log-Lin, Log-Log-Log, etc) the elastic 2D interpolation uses the LogCos
 * equivelent (e.g. Lin-LogCos-Lin, Log-LogCos-Log, etc).
 */
void ElectronElasticDataEvaluator::setElectronTwoDInterpPolicy(
                               MonteCarlo::TwoDInterpolationType two_d_interp )
{
  d_two_d_interp = two_d_interp;;
}

// Return the electron TwoDInterpPolicy
MonteCarlo::TwoDInterpolationType ElectronElasticDataEvaluator::getElectronTwoDInterpPolicy() const
{
  return d_two_d_interp;
}

// Set the electron TwoDGridPolicy (UnitBaseCorrelated by default)
void ElectronElasticDataEvaluator::setElectronTwoDGridPolicy(
                                      MonteCarlo::TwoDGridType two_d_grid )
{
  d_two_d_grid = two_d_grid;
}

// Return the electron TwoDGridPolicy
MonteCarlo::TwoDGridType ElectronElasticDataEvaluator::getElectronTwoDGridPolicy() const
{
  return d_two_d_grid;
}

// Set the CoupledElasticSamplingMethod (Modified Two D Union by default)
void ElectronElasticDataEvaluator::setCoupledElasticSamplingMethod(
                                      MonteCarlo::CoupledElasticSamplingMethod method )
{
  d_sampling_method = method;
}

// Return the CoupledElasticSamplingMethod
MonteCarlo::CoupledElasticSamplingMethod ElectronElasticDataEvaluator::getCoupledElasticSamplingMethod() const
{
  return d_sampling_method;
}

// Turn generate new distribution at the min and max energy off (off by default)
void ElectronElasticDataEvaluator::setGenerateNewDistributionAtMinAndMaxEnergyOff()
{
  d_generate_new_distribution_at_min_and_max_energy = false;
}

// Turn generate new distribution at the min and max energy on (off by default)
void ElectronElasticDataEvaluator::setGenerateNewDistributionAtMinAndMaxEnergyOn()
{
  d_generate_new_distribution_at_min_and_max_energy = true;
}

// Return if generate new distribution at the min and max energy is on (off by default)
bool ElectronElasticDataEvaluator::isGenerateNewDistributionAtMinAndMaxEnergyOn() const
{
  return d_generate_new_distribution_at_min_and_max_energy;
}

// Evaluate the electron elastic secondary distribution
/*! \details Secondary distributions will be evaluated on the angular grid. If
 *  the angular energy grid is empty the endl energy grid points will be used.
 */
void ElectronElasticDataEvaluator::evaluateElasticSecondaryDistribution(
  std::vector<double>& angular_energy_grid,
  std::map<double,std::vector<double> >& elastic_angle,
  std::map<double,std::vector<double> >& elastic_pdf,
  std::vector<double>& moment_preserving_cross_section_reduction,
  std::map<double,std::vector<double> >& moment_preserving_angles,
  std::map<double,std::vector<double> >& moment_preserving_weights,
  const double grid_convergence_tol,
  const double absolute_diff_tol,
  const double distance_tol ) const
{
  if( angular_energy_grid.size() < 2 )
  {
    // Evaluate the analog data
    this->evaluateAnalogElasticSecondaryDistribution(
        angular_energy_grid,
        elastic_angle,
        elastic_pdf,
        grid_convergence_tol,
        absolute_diff_tol,
        distance_tol );
  }
  else
  {
    // Evaluate the analog data on the given angular grid
    this->evaluateAnalogElasticSecondaryDistributionInPlace(
        angular_energy_grid,
        elastic_angle,
        elastic_pdf,
        grid_convergence_tol,
        absolute_diff_tol,
        distance_tol );
  }

  // Check if moment preserving data can be generated
  if ( this->getCutoffAngleCosine() > 0.999999 ||
       this->getNumberOfMomentPreservingAngles() < 1 )
  {
    if( this->getCutoffAngleCosine() > 0.999999 )
    {
      FRENSIE_LOG_NOTIFICATION( Utility::BoldCyan( "Note: " )
                                << "Moment preserving data was not generated "
                                << "because the cutoff angle cosine is "
                                << "greater than 0.999999 (mu="
                                << this->getCutoffAngleCosine() << ")." );
    }

    if( this->getNumberOfMomentPreservingAngles() < 1 )
    {
      FRENSIE_LOG_NOTIFICATION( Utility::BoldCyan( "Note: " )
                                << "Moment preserving data was not "
                                << "generated because the number of moment "
                                << "preserving angles is less than 1." );
    }
  }
  // Evaluate the moment preserving data
  else
  {
    this->evaluateMomentPreservingElasticData(
        angular_energy_grid,
        elastic_angle,
        elastic_pdf,
        moment_preserving_cross_section_reduction,
        moment_preserving_angles,
        moment_preserving_weights );
  }
}

// Create the analog cutoff elastic cross section evaluator
void ElectronElasticDataEvaluator::createCutoffCrossSectionEvaluator(
  std::shared_ptr<const Utility::UnivariateDistribution>& cross_section_evaluator ) const
{
  cross_section_evaluator.reset(
    new Utility::TabularDistribution<Utility::LogLog>(
      *d_energy_grid,
      *d_cutoff_cross_section ) );
}

// Create the analog cutoff elastic cross section evaluator
void ElectronElasticDataEvaluator::createCutoffCrossSectionEvaluator(
  std::shared_ptr<MonteCarlo::ElectroatomicReaction>& cross_section_evaluator ) const
{
  // Create the hash-based grid searcher
  std::shared_ptr<Utility::HashBasedGridSearcher<double> > forward_grid_searcher =
   std::make_shared<Utility::StandardHashBasedGridSearcher<std::vector<double>,false> >(
                         d_energy_grid,
                         d_energy_grid->front(),
                         d_energy_grid->back(),
                         d_energy_grid->size()/10 + 1 );

  // Create the reaction
  cross_section_evaluator.reset(
    new MonteCarlo::VoidElectroatomicReaction<Utility::LogLog>(
        d_energy_grid,
        d_cutoff_cross_section,
        d_cutoff_threshold_energy_index,
        forward_grid_searcher ) );
}

// Create the analog total elastic cross section evaluator
void ElectronElasticDataEvaluator::createTotalCrossSectionEvaluator(
  std::shared_ptr<const Utility::UnivariateDistribution>& cross_section_evaluator ) const
{
  cross_section_evaluator.reset(
      new Utility::TabularDistribution<Utility::LogLog>(
        *d_energy_grid,
        *d_total_cross_section ) );
}

//! Create the analog total elastic cross section evaluator
void ElectronElasticDataEvaluator::createTotalCrossSectionEvaluator(
  std::shared_ptr<MonteCarlo::ElectroatomicReaction>& cross_section_evaluator ) const
{
  // Create the hash-based grid searcher
  std::shared_ptr<Utility::HashBasedGridSearcher<double> > forward_grid_searcher =
   std::make_shared<Utility::StandardHashBasedGridSearcher<std::vector<double>,false> >(
                         d_energy_grid,
                         d_energy_grid->front(),
                         d_energy_grid->back(),
                         d_energy_grid->size()/10 + 1 );

  // Create the reaction
  cross_section_evaluator.reset(
    new MonteCarlo::VoidElectroatomicReaction<Utility::LogLog>(
        d_energy_grid,
        d_total_cross_section,
        d_total_threshold_energy_index,
        forward_grid_searcher ) );
}

// Evaluate the analog screened Rutherford elastic cross section
void ElectronElasticDataEvaluator::evaluateScreenedRutherfordCrossSection(
  const std::vector<double>& total_elastic_cross_section,
  const std::vector<double>& cutoff_elastic_cross_section,
  std::vector<double>& rutherford_cross_section,
  unsigned& rutherford_cross_section_threshold_energy_index,
  const double evaluation_tolerance ) const
{
  // Make the the cross sections are valid
  testPrecondition( total_elastic_cross_section.size() > 0 );
  testPrecondition( total_elastic_cross_section.size() ==
                    cutoff_elastic_cross_section.size() );

  rutherford_cross_section_threshold_energy_index = 0;

  std::vector<double> raw_cross_section( total_elastic_cross_section.size() );
  for( int i = 0; i < total_elastic_cross_section.size(); ++i )
  {
    raw_cross_section[i] = total_elastic_cross_section[i] - cutoff_elastic_cross_section[i];

    // Calculate the relative difference between the total and cutoff cross sections
    double relative_difference = raw_cross_section[i]/total_elastic_cross_section[i];

    // Check for roundoff error and reduce to zero if needed
    if( relative_difference < evaluation_tolerance )
    {
      raw_cross_section[i] = 0.0;

      // Update threshold index
      rutherford_cross_section_threshold_energy_index = i+1;
    }
  }

  std::vector<double>::iterator start = raw_cross_section.begin();
  std::advance( start, rutherford_cross_section_threshold_energy_index );

  rutherford_cross_section.assign( start, raw_cross_section.end() );
}

// Evaluate the electron analog elastic secondary distribution
void ElectronElasticDataEvaluator::evaluateAnalogElasticSecondaryDistribution(
  std::vector<double>& angular_energy_grid,
  std::map<double,std::vector<double> >& elastic_angle,
  std::map<double,std::vector<double> >& elastic_pdf,
  const double grid_convergence_tol,
  const double absolute_diff_tol,
  const double distance_tol ) const
{
  angular_energy_grid.clear();
  elastic_angle.clear();
  elastic_pdf.clear();

  // Get the upper boundary of the min energy
  auto energy_bin =
    Utility::Search::binaryLowerBound( d_angular_energy_grid.begin(),
                                       d_angular_energy_grid.end(),
                                       d_min_energy );

  // Create new distribution at min energy
  if( *energy_bin != d_min_energy && this->isGenerateNewDistributionAtMinAndMaxEnergyOn() )
  {
    // Set the min energy
    angular_energy_grid.push_back( d_min_energy );

    std::vector<double> angles, pdf;
    double max_cutoff_angle_cosine = 1.0;

    // Get the angular grid and pdf at the max energy
    if( d_two_d_grid == MonteCarlo::DIRECT_GRID ||
        d_two_d_grid == MonteCarlo::UNIT_BASE_GRID )
    {
      if ( d_two_d_interp == MonteCarlo::LOGLOGLOG_INTERPOLATION )
      {
        MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::evaluateAngularGridAndPDF<Utility::LogNudgedLogCosLog,Utility::Direct>(
          angles,
          pdf,
          d_elastic_angle,
          d_elastic_pdf,
          d_min_energy,
          max_cutoff_angle_cosine,
          d_tabular_evaluation_tol,
          grid_convergence_tol,
          absolute_diff_tol,
          distance_tol );
      }
      else if ( d_two_d_interp == MonteCarlo::LINLINLIN_INTERPOLATION )
      {
        MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::evaluateAngularGridAndPDF<Utility::LinLinLin,Utility::Direct>(
          angles,
          pdf,
          d_elastic_angle,
          d_elastic_pdf,
          d_min_energy,
          max_cutoff_angle_cosine,
          d_tabular_evaluation_tol,
          grid_convergence_tol,
          absolute_diff_tol,
          distance_tol );
      }
      else if ( d_two_d_interp == MonteCarlo::LINLINLOG_INTERPOLATION )
      {
        MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::evaluateAngularGridAndPDF<Utility::LinLinLog,Utility::Direct>(
          angles,
          pdf,
          d_elastic_angle,
          d_elastic_pdf,
          d_min_energy,
          max_cutoff_angle_cosine,
          d_tabular_evaluation_tol,
          grid_convergence_tol,
          absolute_diff_tol,
          distance_tol );
      }
      else
      {
        THROW_EXCEPTION( std::runtime_error,
                          "the desired 2D interpolation policy " <<
                          d_two_d_interp <<
                          " is currently not supported!" );
      }
    }
    else if( d_two_d_grid == MonteCarlo::CORRELATED_GRID ||
            d_two_d_grid == MonteCarlo::UNIT_BASE_CORRELATED_GRID )
    {
      if ( d_two_d_interp == MonteCarlo::LOGLOGLOG_INTERPOLATION )
      {
        MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::evaluateAngularGridAndPDF<Utility::LogNudgedLogCosLog,Utility::Correlated>(
          angles,
          pdf,
          d_elastic_angle,
          d_elastic_pdf,
          d_min_energy,
          max_cutoff_angle_cosine,
          d_tabular_evaluation_tol,
          grid_convergence_tol,
          absolute_diff_tol,
          distance_tol );
      }
      else if ( d_two_d_interp == MonteCarlo::LINLINLIN_INTERPOLATION )
      {
        MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::evaluateAngularGridAndPDF<Utility::LinLinLin,Utility::Correlated>(
          angles,
          pdf,
          d_elastic_angle,
          d_elastic_pdf,
          d_min_energy,
          max_cutoff_angle_cosine,
          d_tabular_evaluation_tol,
          grid_convergence_tol,
          absolute_diff_tol,
          distance_tol );
      }
      else if ( d_two_d_interp == MonteCarlo::LINLINLOG_INTERPOLATION )
      {
        MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::evaluateAngularGridAndPDF<Utility::LinLinLog,Utility::Correlated>(
          angles,
          pdf,
          d_elastic_angle,
          d_elastic_pdf,
          d_min_energy,
          max_cutoff_angle_cosine,
          d_tabular_evaluation_tol,
          grid_convergence_tol,
          absolute_diff_tol,
          distance_tol );
      }
      else
      {
        THROW_EXCEPTION( std::runtime_error,
                          "the desired 2D interpolation policy " <<
                          d_two_d_interp <<
                          " is currently not supported!" );
      }
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                        "the desired bivariate grid policy " <<
                        d_two_d_grid <<
                        " is currently not supported!" );
    }

    // Set the distribution at the min energy
    elastic_angle[d_min_energy] = angles;
    elastic_pdf[d_min_energy] = pdf;

    // Advance energy bin to the first energy greater than the min energy
    ++energy_bin;
  }

  // Add all distribution between the min (or before) and max energy
  for( energy_bin; energy_bin != d_angular_energy_grid.end(); ++energy_bin )
  {
    // Make sure the energy bins don't go above the max energy
    if ( *energy_bin > d_max_energy )
      break;

    // Set the distribution at the energy bin
    angular_energy_grid.push_back( *energy_bin );
    elastic_angle[*energy_bin] = d_elastic_angle.at(*energy_bin);
    elastic_pdf[*energy_bin] = d_elastic_pdf.at(*energy_bin);
  }

  if( angular_energy_grid.back() != d_max_energy )
  {
    // Create a distribution at the max energy
    if( this->isGenerateNewDistributionAtMinAndMaxEnergyOn() )
    {
      // Set the max energy
      angular_energy_grid.push_back( d_max_energy );

      std::vector<double> angles, pdf;
      double max_cutoff_angle_cosine = 1.0;

      // Get the angular grid and pdf at the max energy
      if( d_two_d_grid == MonteCarlo::DIRECT_GRID ||
          d_two_d_grid == MonteCarlo::UNIT_BASE_GRID )
      {
        if ( d_two_d_interp == MonteCarlo::LOGLOGLOG_INTERPOLATION )
        {
          MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::evaluateAngularGridAndPDF<Utility::LogNudgedLogCosLog,Utility::Direct>(
            angles,
            pdf,
            d_elastic_angle,
            d_elastic_pdf,
            d_max_energy,
            max_cutoff_angle_cosine,
            d_tabular_evaluation_tol,
            grid_convergence_tol,
            absolute_diff_tol,
            distance_tol );
        }
        else if ( d_two_d_interp == MonteCarlo::LINLINLIN_INTERPOLATION )
        {
          MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::evaluateAngularGridAndPDF<Utility::LinLinLin,Utility::Direct>(
            angles,
            pdf,
            d_elastic_angle,
            d_elastic_pdf,
            d_max_energy,
            max_cutoff_angle_cosine,
            d_tabular_evaluation_tol,
            grid_convergence_tol,
            absolute_diff_tol,
            distance_tol );
        }
        else if ( d_two_d_interp == MonteCarlo::LINLINLOG_INTERPOLATION )
        {
          MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::evaluateAngularGridAndPDF<Utility::LinLinLog,Utility::Direct>(
            angles,
            pdf,
            d_elastic_angle,
            d_elastic_pdf,
            d_max_energy,
            max_cutoff_angle_cosine,
            d_tabular_evaluation_tol,
            grid_convergence_tol,
            absolute_diff_tol,
            distance_tol );
        }
        else
        {
          THROW_EXCEPTION( std::runtime_error,
                            "the desired 2D interpolation policy " <<
                            d_two_d_interp <<
                            " is currently not supported!" );
        }
      }
      else if( d_two_d_grid == MonteCarlo::CORRELATED_GRID ||
              d_two_d_grid == MonteCarlo::UNIT_BASE_CORRELATED_GRID )
      {
        if ( d_two_d_interp == MonteCarlo::LOGLOGLOG_INTERPOLATION )
        {
          MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::evaluateAngularGridAndPDF<Utility::LogNudgedLogCosLog,Utility::Correlated>(
            angles,
            pdf,
            d_elastic_angle,
            d_elastic_pdf,
            d_max_energy,
            max_cutoff_angle_cosine,
            d_tabular_evaluation_tol,
            grid_convergence_tol,
            absolute_diff_tol,
            distance_tol );
        }
        else if ( d_two_d_interp == MonteCarlo::LINLINLIN_INTERPOLATION )
        {
          MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::evaluateAngularGridAndPDF<Utility::LinLinLin,Utility::Correlated>(
            angles,
            pdf,
            d_elastic_angle,
            d_elastic_pdf,
            d_max_energy,
            max_cutoff_angle_cosine,
            d_tabular_evaluation_tol,
            grid_convergence_tol,
            absolute_diff_tol,
            distance_tol );
        }
        else if ( d_two_d_interp == MonteCarlo::LINLINLOG_INTERPOLATION )
        {
          MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::evaluateAngularGridAndPDF<Utility::LinLinLog,Utility::Correlated>(
            angles,
            pdf,
            d_elastic_angle,
            d_elastic_pdf,
            d_max_energy,
            max_cutoff_angle_cosine,
            d_tabular_evaluation_tol,
            grid_convergence_tol,
            absolute_diff_tol,
            distance_tol );
        }
        else
        {
          THROW_EXCEPTION( std::runtime_error,
                            "the desired 2D interpolation policy " <<
                            d_two_d_interp <<
                            " is currently not supported!" );
        }
      }
      else
      {
        THROW_EXCEPTION( std::runtime_error,
                          "the desired bivariate grid policy " <<
                          d_two_d_grid <<
                          " is currently not supported!" );
      }

      // Set the distribution at the min energy
      elastic_angle[d_max_energy] = angles;
      elastic_pdf[d_max_energy] = pdf;
    }
    // Add the distribution right above the max energy
    else
    {
      // Set the distribution at the energy bin right above the max energy
      angular_energy_grid.push_back( *energy_bin );
      elastic_angle[*energy_bin] = d_elastic_angle.at(*energy_bin);
      elastic_pdf[*energy_bin] = d_elastic_pdf.at(*energy_bin);
    }
  }
}

// Evaluate the electron analog elastic secondary distribution on the angular energy grid
void ElectronElasticDataEvaluator::evaluateAnalogElasticSecondaryDistributionInPlace(
  const std::vector<double>& angular_energy_grid,
  std::map<double,std::vector<double> >& elastic_angle,
  std::map<double,std::vector<double> >& elastic_pdf,
  const double grid_convergence_tol,
  const double absolute_diff_tol,
  const double distance_tol ) const
{
  // Make sure the angular_energy_grid is valid
  testPrecondition( angular_energy_grid.size() > 1 );
  testPrecondition( angular_energy_grid.front() == d_min_energy );
  testPrecondition( angular_energy_grid.back() == d_max_energy );

  // Make sure the secondary grids are clear
  elastic_angle.clear();
  elastic_pdf.clear();

  // Create new distribution at the energy
  for( auto&& energy : angular_energy_grid )
  {
    std::vector<double> angles, pdf;
    double max_cutoff_angle_cosine = 1.0;

    // Get the angular grid and pdf at the energy
    if( d_two_d_grid == MonteCarlo::DIRECT_GRID ||
        d_two_d_grid == MonteCarlo::UNIT_BASE_GRID )
    {
      if ( d_two_d_interp == MonteCarlo::LOGLOGLOG_INTERPOLATION )
      {
        MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::evaluateAngularGridAndPDF<Utility::LogNudgedLogCosLog,Utility::Direct>(
          angles,
          pdf,
          d_elastic_angle,
          d_elastic_pdf,
          energy,
          max_cutoff_angle_cosine,
          d_tabular_evaluation_tol,
          grid_convergence_tol,
          absolute_diff_tol,
          distance_tol );
      }
      else if ( d_two_d_interp == MonteCarlo::LINLINLIN_INTERPOLATION )
      {
        MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::evaluateAngularGridAndPDF<Utility::LinLinLin,Utility::Direct>(
          angles,
          pdf,
          d_elastic_angle,
          d_elastic_pdf,
          energy,
          max_cutoff_angle_cosine,
          d_tabular_evaluation_tol,
          grid_convergence_tol,
          absolute_diff_tol,
          distance_tol );
      }
      else if ( d_two_d_interp == MonteCarlo::LINLINLOG_INTERPOLATION )
      {
        MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::evaluateAngularGridAndPDF<Utility::LinLinLog,Utility::Direct>(
          angles,
          pdf,
          d_elastic_angle,
          d_elastic_pdf,
          energy,
          max_cutoff_angle_cosine,
          d_tabular_evaluation_tol,
          grid_convergence_tol,
          absolute_diff_tol,
          distance_tol );
      }
      else
      {
        THROW_EXCEPTION( std::runtime_error,
                          "the desired 2D interpolation policy " <<
                          d_two_d_interp <<
                          " is currently not supported!" );
      }
    }
    else if( d_two_d_grid == MonteCarlo::CORRELATED_GRID ||
             d_two_d_grid == MonteCarlo::UNIT_BASE_CORRELATED_GRID )
    {
      if ( d_two_d_interp == MonteCarlo::LOGLOGLOG_INTERPOLATION )
      {
        MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::evaluateAngularGridAndPDF<Utility::LogNudgedLogCosLog,Utility::Correlated>(
          angles,
          pdf,
          d_elastic_angle,
          d_elastic_pdf,
          energy,
          max_cutoff_angle_cosine,
          d_tabular_evaluation_tol,
          grid_convergence_tol,
          absolute_diff_tol,
          distance_tol );
      }
      else if ( d_two_d_interp == MonteCarlo::LINLINLIN_INTERPOLATION )
      {
        MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::evaluateAngularGridAndPDF<Utility::LinLinLin,Utility::Correlated>(
          angles,
          pdf,
          d_elastic_angle,
          d_elastic_pdf,
          energy,
          max_cutoff_angle_cosine,
          d_tabular_evaluation_tol,
          grid_convergence_tol,
          absolute_diff_tol,
          distance_tol );
      }
      else if ( d_two_d_interp == MonteCarlo::LINLINLOG_INTERPOLATION )
      {
        MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::evaluateAngularGridAndPDF<Utility::LinLinLog,Utility::Correlated>(
          angles,
          pdf,
          d_elastic_angle,
          d_elastic_pdf,
          energy,
          max_cutoff_angle_cosine,
          d_tabular_evaluation_tol,
          grid_convergence_tol,
          absolute_diff_tol,
          distance_tol );
      }
      else
      {
        THROW_EXCEPTION( std::runtime_error,
                          "the desired 2D interpolation policy " <<
                          d_two_d_interp <<
                          " is currently not supported!" );
      }
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                        "the desired bivariate grid policy " <<
                        d_two_d_grid <<
                        " is currently not supported!" );
    }

    // Set the distribution at the min energy
    elastic_angle[energy] = angles;
    elastic_pdf[energy] = pdf;
  }
}

// Evaluate the electron moment preserving elastic data
void ElectronElasticDataEvaluator::evaluateMomentPreservingElasticData(
  const std::vector<double>& angular_energy_grid,
  const std::map<double,std::vector<double> >& elastic_angle,
  const std::map<double,std::vector<double> >& elastic_pdf,
  std::vector<double>& cross_section_reduction,
  std::map<double,std::vector<double> >& moment_preserving_angles,
  std::map<double,std::vector<double> >& moment_preserving_weights ) const
{
  // Create the coupled elastic distribution (combined Cutoff and Screened Rutherford)
  std::shared_ptr<const MonteCarlo::CoupledElasticElectronScatteringDistribution>
        coupled_distribution;

  // Get the coupled elastic distribution
  if( d_two_d_grid == MonteCarlo::DIRECT_GRID ||
      d_two_d_grid == MonteCarlo::UNIT_BASE_GRID )
  {
    if ( d_two_d_interp == MonteCarlo::LOGLOGLOG_INTERPOLATION )
    {
      MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution<Utility::LogNudgedLogCosLog,Utility::Direct>(
        coupled_distribution,
        d_cutoff_cross_section,
        d_total_cross_section,
        d_energy_grid,
        elastic_angle,
        elastic_pdf,
        angular_energy_grid,
        d_atomic_number,
        d_sampling_method,
        d_tabular_evaluation_tol );
    }
    else if ( d_two_d_interp == MonteCarlo::LINLINLIN_INTERPOLATION )
    {
      MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution<Utility::LinLinLin,Utility::Direct>(
        coupled_distribution,
        d_cutoff_cross_section,
        d_total_cross_section,
        d_energy_grid,
        elastic_angle,
        elastic_pdf,
        angular_energy_grid,
        d_atomic_number,
        d_sampling_method,
        d_tabular_evaluation_tol );
    }
    else if ( d_two_d_interp == MonteCarlo::LINLINLOG_INTERPOLATION )
    {
      MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution<Utility::LinLinLog,Utility::Direct>(
        coupled_distribution,
        d_cutoff_cross_section,
        d_total_cross_section,
        d_energy_grid,
        elastic_angle,
        elastic_pdf,
        angular_energy_grid,
        d_atomic_number,
        d_sampling_method,
        d_tabular_evaluation_tol );
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                        "Error: the desired 2D interpolation policy " <<
                        d_two_d_interp <<
                        " is currently not supported!" );
    }
  }
  else if( d_two_d_grid == MonteCarlo::CORRELATED_GRID ||
           d_two_d_grid == MonteCarlo::UNIT_BASE_CORRELATED_GRID )
  {
    if ( d_two_d_interp == MonteCarlo::LOGLOGLOG_INTERPOLATION )
    {
      MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution<Utility::LogNudgedLogCosLog,Utility::Correlated>(
        coupled_distribution,
        d_cutoff_cross_section,
        d_total_cross_section,
        d_energy_grid,
        elastic_angle,
        elastic_pdf,
        angular_energy_grid,
        d_atomic_number,
        d_sampling_method,
        d_tabular_evaluation_tol );
    }
    else if ( d_two_d_interp == MonteCarlo::LINLINLIN_INTERPOLATION )
    {
      MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution<Utility::LinLinLin,Utility::Correlated>(
        coupled_distribution,
        d_cutoff_cross_section,
        d_total_cross_section,
        d_energy_grid,
        elastic_angle,
        elastic_pdf,
        angular_energy_grid,
        d_atomic_number,
        d_sampling_method,
        d_tabular_evaluation_tol );
    }
    else if ( d_two_d_interp == MonteCarlo::LINLINLOG_INTERPOLATION )
    {
      MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution<Utility::LinLinLog,Utility::Correlated>(
        coupled_distribution,
        d_cutoff_cross_section,
        d_total_cross_section,
        d_energy_grid,
        elastic_angle,
        elastic_pdf,
        angular_energy_grid,
        d_atomic_number,
        d_sampling_method,
        d_tabular_evaluation_tol );
    }
    else
    {
      THROW_EXCEPTION( std::runtime_error,
                        "Error: the desired 2D interpolation policy " <<
                        d_two_d_interp <<
                        " is currently not supported!" );
    }
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                      "Error: the desired bivariate grid policy " <<
                      d_two_d_grid <<
                      " is currently not supported!" );
  }

  // Construct the hash-based grid searcher for this atom
  std::shared_ptr<Utility::HashBasedGridSearcher<double> > grid_searcher =
    std::make_shared<Utility::StandardHashBasedGridSearcher<std::vector<double>, false> >(
             d_energy_grid,
             100u );

  // Create the elastic traits
  auto elastic_traits =
    std::make_shared<MonteCarlo::ElasticElectronTraits>( d_atomic_number );


  // Get the screened Rutherford cross section threshold energy index
  std::vector<double> rutherford_cross_section;
  unsigned rutherford_threshold_index;

  this->evaluateScreenedRutherfordCrossSection(
    *d_total_cross_section,
    *d_cutoff_cross_section,
    rutherford_cross_section,
    rutherford_threshold_index );

  // Create the moment evaluator of the elastic scattering distribution
  auto moments_evaluator =
    std::make_shared<DataGen::ElasticElectronMomentsEvaluator>(
        elastic_angle,
        d_energy_grid,
        grid_searcher,
        d_cutoff_cross_section,
        d_total_cross_section,
        rutherford_threshold_index,
        coupled_distribution,
        elastic_traits,
        this->getCutoffAngleCosine() );

  // Moment preserving discrete angles and weights
  std::vector<double> discrete_angles, weights;

  // weights for a discrete angle cosine = 1
  cross_section_reduction.resize( angular_energy_grid.size() );

  // iterate through all angular energy bins
  for ( unsigned i = 0; i < angular_energy_grid.size(); ++i )
  {
    this->calculateDiscreteAnglesAndWeights(
        moments_evaluator,
        angular_energy_grid[i],
        discrete_angles,
        weights,
        cross_section_reduction[i] );

    moment_preserving_angles[angular_energy_grid[i] ] = discrete_angles;
    moment_preserving_weights[angular_energy_grid[i] ] = weights;
  }
}

// Calculate the elastic angular distribution for the angle cosine
void ElectronElasticDataEvaluator::calculateElasticAngleCosine(
    const std::vector<double>& raw_elastic_angle,
    const std::vector<double>& raw_elastic_pdf,
    std::vector<double>& elastic_angle,
    std::vector<double>& elastic_pdf ) const
{
  int size = raw_elastic_angle.size();
  int r_bin = size - 1;

  elastic_angle.resize( size );
  elastic_pdf.resize( size );

  for ( unsigned bin = 0; bin < size; ++bin )
  {
    elastic_pdf[r_bin] = raw_elastic_pdf[bin];
    long double angle_cosine = 1.0L - raw_elastic_angle[bin];
    elastic_angle[r_bin] = angle_cosine;
    r_bin--;
  }
}

// Calculate the elastic moment preserving discrete angle cosines and weights
void ElectronElasticDataEvaluator::calculateDiscreteAnglesAndWeights(
    const std::shared_ptr<DataGen::ElasticElectronMomentsEvaluator>& moments_evaluator,
    const double& energy,
    std::vector<double>& discrete_angles,
    std::vector<double>& weights,
    double& cross_section_reduction ) const
{
  std::vector<Utility::long_float> legendre_moments;
  double precision = 1e-13;
  int n = ( d_number_of_moment_preserving_angles+1 )*2 -2;

  // Get the elastic moments
  moments_evaluator->evaluateElasticMoment( legendre_moments,
                                            energy,
                                            n,
                                            precision );

  // Use radau quadrature to find the discrete angles and weights from the moments
  auto radau_quadrature =
    std::make_shared<Utility::SloanRadauQuadrature>( legendre_moments );

  radau_quadrature->getRadauNodesAndWeights( discrete_angles,
                                             weights,
                                             d_number_of_moment_preserving_angles+1 );

  // Eliminate the forward discrete angle (mu = 1)
  discrete_angles.pop_back();
  weights.pop_back();

  // Re-normalize weights and set the cross_section_reduction to the sum of the weights
  cross_section_reduction = 0.0;
  for( auto weight : weights )
  {
    cross_section_reduction += weight;
  }

  for( int i = 0; i < weights.size(); ++i )
  {
    weights[i] /= cross_section_reduction;
  }
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_ElectronElasticDataEvaluator.hpp
//---------------------------------------------------------------------------//
