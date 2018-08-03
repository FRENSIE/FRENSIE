//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleHistorySimulationCompletionCriterion.cpp
//! \author Alex Robinson
//! \brief  The particle history simulation completion criterion class def.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <functional>

// FRENSIE Includes
#include "FRENSIE_Archives.hpp"
#include "MonteCarlo_ParticleHistorySimulationCompletionCriterion.hpp"
#include "Utility_GlobalMPISession.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

//! The history count particle history simulation completion criterion
class HistoryCountParticleHistorySimulationCompletionCriterion : public ParticleHistorySimulationCompletionCriterion
{

public:

  //! Default constructor
  HistoryCountParticleHistorySimulationCompletionCriterion()
  { /* ... */ }
  
  //! Constructor
  HistoryCountParticleHistorySimulationCompletionCriterion( const uint64_t history_wall )
    : d_history_wall( history_wall ),
      d_num_completed_histories( 0 ),
      d_count_histories( false )
  { /* ... */ }

  //! Destructor
  ~HistoryCountParticleHistorySimulationCompletionCriterion()
  { /* ... */ }

  //! Check if the simulation is complete
  bool isSimulationComplete() const final override
  { return d_num_completed_histories >= d_history_wall; }

  //! Start the criterion
  void start() final override
  { d_count_histories = true; }

  //! Stop the criterion
  void stop() final override
  { d_count_histories = false; }

  //! Clear cached criterion data
  void clearCache() final override
  { d_num_completed_histories = 0; }

  //! Enable support for multiple threads
  void enableThreadSupport( const unsigned ) final override
  { /* ... */ }

  //! Check if the observer has uncommitted history contributions
  bool hasUncommittedHistoryContribution() const final override
  { return true; }

  //! Commit the contribution from the current history to the observer
  void commitHistoryContribution() final override
  {
    if( d_count_histories )
    {
      #pragma omp atomic
      ++d_num_completed_histories;
    }
  }

  //! Reset the observer data
  void resetData() final override
  { d_num_completed_histories = 0; }

  //! Reduce the object data on all processes in comm and collect on root
  void reduceData( const Utility::Communicator& comm,
                   const int root_process ) final override
  {
    if( comm.rank() == root_process )
    {
      uint64_t reduced_num_completed_histories;
      
      Utility::reduce( comm,
                       d_num_completed_histories,
                       reduced_num_completed_histories,
                       std::plus<uint64_t>(),
                       root_process );
      
      d_num_completed_histories = reduced_num_completed_histories;
    }
    else
    {
      Utility::reduce( comm,
                       d_num_completed_histories,
                       std::plus<uint64_t>(),
                       root_process );

      d_num_completed_histories = 0;
    }
  }

  //! Get a description of the criterion
  std::string description() const final override
  {
    return std::string( "completed histories (" ) +
      Utility::toString( d_num_completed_histories ) + ") >= " +
      Utility::toString( d_history_wall );
  }

private:

  // Serialize the completion criterion
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  {
    // Serialize the base class member data
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleHistorySimulationCompletionCriterion );

    // Serialize the local member data
    ar & BOOST_SERIALIZATION_NVP( d_num_completed_histories );
    ar & BOOST_SERIALIZATION_NVP( d_history_wall );
    ar & BOOST_SERIALIZATION_NVP( d_count_histories );
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The number of completed histories
  uint64_t d_num_completed_histories;

  // The history wall
  uint64_t d_history_wall;

  // Active flag
  bool d_count_histories;
};

//! The wall time particle history simulation completion criterion
class WallTimeParticleHistorySimulationCompletionCriterion : public ParticleHistorySimulationCompletionCriterion
{

public:

  //! Default constructor
  WallTimeParticleHistorySimulationCompletionCriterion()
  { /* ... */ }

  //! Constructor
  WallTimeParticleHistorySimulationCompletionCriterion( const double wall_time )
    : d_wall_time( wall_time ),
      d_timer( Utility::GlobalMPISession::createTimer() )
  { testPrecondition( wall_time > 0.0 ); }
  
  //! Check if the simulation is complete
  bool isSimulationComplete() const final override
  { return d_timer->elapsed().count() >= d_wall_time; }

  //! Start the criterion
  void start() final override
  { d_timer->start(); }

  //! Stop the criterion
  void stop() final override
  { d_timer->stop(); }

  //! Clear cached criterion data
  void clearCache() final override
  { d_timer = Utility::GlobalMPISession::createTimer(); }

  //! Enable support for multiple threads
  void enableThreadSupport( const unsigned num_threads ) final override
  { /* ... */ }

  //! Check if the observer has uncommitted history contributions
  bool hasUncommittedHistoryContribution() const final override
  { return false; }

  //! Commit the contribution from the current history to the observer
  void commitHistoryContribution() final override
  { /* ... */ }

  //! Reset the observer data
  void resetData() final override
  { /* ... */ }

  //! Reduce the object data on all processes in comm and collect on root
  void reduceData( const Utility::Communicator& comm,
                   const int root_process ) final override
  { /* ... */ }

  //! Get a description of the criterion
  std::string description() const final override
  {
    return std::string( "elapsed time (" ) +
      Utility::toString( d_timer->elapsed().count() ) + ") >= " +
      Utility::toString( d_wall_time );
  }

private:

  // Save the completion criterion
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const
  {
    // Save the base class member data
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleHistorySimulationCompletionCriterion );

    // Save the local member data
    ar & BOOST_SERIALIZATION_NVP( d_wall_time );
  }

  // Load the completion criterion
  template<typename Archive>
  void load( Archive& ar, const unsigned version )
  {
    // Load the base class member data
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleHistorySimulationCompletionCriterion );

    // Load the local member data
    ar & BOOST_SERIALIZATION_NVP( d_wall_time );

    d_timer = Utility::GlobalMPISession::createTimer();
  }

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The wall time
  double d_wall_time;

  // The timer
  std::shared_ptr<Utility::Timer> d_timer;
};

//! The combined particle history simulation completion criterion
template<typename LogicalOperationFunctor>
class CombinedParticleHistorySimulationCompletionCriterion : public ParticleHistorySimulationCompletionCriterion
{

public:

  //! Default constructor
  CombinedParticleHistorySimulationCompletionCriterion()
  { /* ... */ }

  //! Constructor
  CombinedParticleHistorySimulationCompletionCriterion(
     const std::shared_ptr<ParticleHistorySimulationCompletionCriterion>& lhs,
     const std::shared_ptr<ParticleHistorySimulationCompletionCriterion>& rhs )
    : d_lhs( lhs ), d_rhs( rhs )
  { /* ... */ }

  //! Destructor
  ~CombinedParticleHistorySimulationCompletionCriterion()
  { /* ... */ }

  //! Check if the simulation is complete
  bool isSimulationComplete() const final override
  {
    return s_op(d_lhs->isSimulationComplete(), d_rhs->isSimulationComplete());
  }

  //! Start the criterion
  void start() final override
  {
    d_lhs->start();
    d_rhs->start();
  }

  //! Stop the criterion
  void stop() final override
  {
    d_lhs->stop();
    d_rhs->stop();
  }

  //! Clear cached criterion data
  void clearCache() final override
  {
    d_lhs->clearCache();
    d_rhs->clearCache();
  }

  //! Enable support for multiple threads
  void enableThreadSupport( const unsigned num_threads ) final override
  {
    d_lhs->enableThreadSupport( num_threads );
    d_rhs->enableThreadSupport( num_threads );
  }

  //! Check if the observer has uncommitted history contributions
  bool hasUncommittedHistoryContribution() const final override
  {
    return d_lhs->hasUncommittedHistoryContribution() ||
      d_rhs->hasUncommittedHistoryContribution();
  }

  //! Commit the contribution from the current history to the observer
  void commitHistoryContribution() final override
  {
    d_lhs->commitHistoryContribution();
    d_rhs->commitHistoryContribution();
  }

  //! Reset the observer data
  void resetData() final override
  {
    d_lhs->resetData();
    d_rhs->resetData();
  }

  //! Reduce the object data on all processes in comm and collect on root
  void reduceData( const Utility::Communicator& comm,
                   const int root_process ) final override
  {
    d_lhs->reduceData( comm, root_process );
    d_rhs->reduceData( comm, root_process );
  }

  //! Get a description of the criterion
  std::string description() const final override
  {
    return std::string( "(" ) + d_lhs->description() +
      " " + this->getOpString() + " " + d_rhs->description() + ")";
  }

protected:

  //! Return the operation string
  virtual std::string getOpString() const = 0;

private:

  // Serialize the criterion
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { 
    // Serialize the base class member data
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleHistorySimulationCompletionCriterion );

    // Serialize the local member data
    ar & BOOST_SERIALIZATION_NVP( d_lhs );
    ar & BOOST_SERIALIZATION_NVP( d_rhs );
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The operation function
  static const LogicalOperationFunctor s_op;

  // The lhs criterion
  std::shared_ptr<ParticleHistorySimulationCompletionCriterion> d_lhs;

  // The rhs criterion
  std::shared_ptr<ParticleHistorySimulationCompletionCriterion> d_rhs;
};

// Initialize static member data
template<typename LogicalOperationFunctor>
const LogicalOperationFunctor CombinedParticleHistorySimulationCompletionCriterion<LogicalOperationFunctor>::s_op = LogicalOperationFunctor();

//! The OR CombinedParticleHistorySimulationCompletionCriterion
class ORCombinedParticleHistorySimulationCompletionCriterion : public CombinedParticleHistorySimulationCompletionCriterion<std::logical_or<bool> >
{
  // The base type
  typedef CombinedParticleHistorySimulationCompletionCriterion<std::logical_or<bool> > BaseType;

public:

  //! Constructor
  using CombinedParticleHistorySimulationCompletionCriterion<std::logical_or<bool> >::CombinedParticleHistorySimulationCompletionCriterion;

  //! Destructor
  ~ORCombinedParticleHistorySimulationCompletionCriterion()
  { /* ... */ }

private:

  // Return the operation string
  std::string getOpString() const final override
  { return "||"; }

  // Serialize the completion criterion
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType ); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

//! The AND CombinedParticleHistorySimulationCompletionCriterion
class ANDCombinedParticleHistorySimulationCompletionCriterion : public CombinedParticleHistorySimulationCompletionCriterion<std::logical_and<bool> >
{
  // The base type 
  typedef CombinedParticleHistorySimulationCompletionCriterion<std::logical_and<bool> > BaseType;

public:

  //! Constructor
  using CombinedParticleHistorySimulationCompletionCriterion<std::logical_and<bool> >::CombinedParticleHistorySimulationCompletionCriterion;

  //! Destructor
  ~ANDCombinedParticleHistorySimulationCompletionCriterion()
  { /* ... */ }

private:

  //! Return the operation string
  std::string getOpString() const final override
  { return "&&"; }

  // Serialize the completion criterion
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseType ); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

// Get a history count completion criterion
std::shared_ptr<ParticleHistorySimulationCompletionCriterion>
ParticleHistorySimulationCompletionCriterion::createHistoryCountCriterion(
                                                  const uint64_t history_wall )
{
  return std::make_shared<HistoryCountParticleHistorySimulationCompletionCriterion>( history_wall );
}

// Get a wall time (s) completion criterion
std::shared_ptr<ParticleHistorySimulationCompletionCriterion>
ParticleHistorySimulationCompletionCriterion::createWallTimeCriterion(
                                                       const double wall_time )
{
  TEST_FOR_EXCEPTION( wall_time <= 0.0,
                      std::runtime_error,
                      "The wall time must be greater than 0.0!" );
  
  return std::make_shared<WallTimeParticleHistorySimulationCompletionCriterion>( wall_time );
}

// Create a mixed criterion (# histories || wall time)
std::shared_ptr<ParticleHistorySimulationCompletionCriterion>
ParticleHistorySimulationCompletionCriterion::createMixedCriterion(
                                        const uint64_t num_completed_histories,
                                        const double wall_time )
{
  return std::shared_ptr<ParticleHistorySimulationCompletionCriterion>(
    new ORCombinedParticleHistorySimulationCompletionCriterion(
           ParticleHistorySimulationCompletionCriterion::createHistoryCountCriterion( num_completed_histories ),
           ParticleHistorySimulationCompletionCriterion::createWallTimeCriterion( wall_time ) ) );
}

// Print a summary of the data
void ParticleHistorySimulationCompletionCriterion::printSummary( std::ostream& os ) const
{
  os << "Simulation Completion Criterion: " << this->description()
     << std::endl;
}
  
} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( HistoryCountParticleHistorySimulationCompletionCriterion, MonteCarlo, 0 );
BOOST_SERIALIZATION_CLASS_VERSION( WallTimeParticleHistorySimulationCompletionCriterion, MonteCarlo, 0 );
BOOST_SERIALIZATION_CLASS1_VERSION( CombinedParticleHistorySimulationCompletionCriterion, MonteCarlo, 0 );
BOOST_SERIALIZATION_CLASS_VERSION( ORCombinedParticleHistorySimulationCompletionCriterion, MonteCarlo, 0 );
BOOST_SERIALIZATION_CLASS_VERSION( ANDCombinedParticleHistorySimulationCompletionCriterion, MonteCarlo, 0 );

BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( HistoryCountParticleHistorySimulationCompletionCriterion, MonteCarlo );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( WallTimeParticleHistorySimulationCompletionCriterion, MonteCarlo );
BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS1( CombinedParticleHistorySimulationCompletionCriterion, MonteCarlo );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ORCombinedParticleHistorySimulationCompletionCriterion, MonteCarlo );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ANDCombinedParticleHistorySimulationCompletionCriterion, MonteCarlo );

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( HistoryCountParticleHistorySimulationCompletionCriterion, MonteCarlo );
BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( WallTimeParticleHistorySimulationCompletionCriterion, MonteCarlo );
BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( ORCombinedParticleHistorySimulationCompletionCriterion, MonteCarlo );
BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( ANDCombinedParticleHistorySimulationCompletionCriterion, MonteCarlo );

EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::HistoryCountParticleHistorySimulationCompletionCriterion );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::WallTimeParticleHistorySimulationCompletionCriterion );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::ORCombinedParticleHistorySimulationCompletionCriterion );
EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo::ANDCombinedParticleHistorySimulationCompletionCriterion );
EXPLICIT_CLASS_SERIALIZE_INST_ALWAYS( MonteCarlo::ParticleHistorySimulationCompletionCriterion );

// Create a mixed criterion using the || operator
std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion> operator||(
     const std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>& lhs,
     const std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>& rhs )
{
  // Make sure that both criterion pointers are valid
  testPrecondition( lhs.get() );
  testPrecondition( rhs.get() );

  return std::make_shared<MonteCarlo::ORCombinedParticleHistorySimulationCompletionCriterion>( lhs, rhs );
}

// Create a mixed criterion using the && operator
std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion> operator&&(
     const std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>& lhs,
     const std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>& rhs )
{
  // Make sure that both criterion pointers are valid
  testPrecondition( lhs.get() );
  testPrecondition( rhs.get() );

  return std::make_shared<MonteCarlo::ANDCombinedParticleHistorySimulationCompletionCriterion>( lhs, rhs );
}

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleHistorySimulationCompletionCriterion.cpp
//---------------------------------------------------------------------------//
