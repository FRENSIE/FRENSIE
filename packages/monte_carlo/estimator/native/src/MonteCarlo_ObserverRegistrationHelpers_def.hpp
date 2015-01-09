//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ObserverRegistrationHelpers_def.hpp
//! \author Alex Robinson
//! \brief  Event dispatcher helper function definitions
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_OBSERVER_REGISTRATION_HELPERS_DEF_HPP
#define FACEMC_OBSERVER_REGISTRATION_HELPERS_DEF_HPP

namespace MonteCarlo{

// Register the observer with dispatchers associated with BeginEventTag tag
template<typename BeginEventTagIterator, typename EndEventTagIterator>
template<typename Observer, typename EntityHandle>
inline void 
ObserverRegistrationHelper<BeginEventTagIterator,
			   EndEventTagIterator>::registerObserverWithTag(
			       Teuchos::RCP<Observer>& observer,
			       const Teuchos::Array<EntityHandle>& entity_ids )
{
  registerObserver( observer, 
		    entity_ids,
		    typename boost::mpl::deref<BeginEventTagIterator>::type());
  
  ObserverRegistrationHelper<typename boost::mpl::next<BeginEventTagIterator>::type,
                             EndEventTagIterator>::registerObserverWithTag(
				                                  observer,
								  entity_ids );
}

// Register the global observer with the global dispatcher associated with
// BeginEventTag tag
template<typename BeginEventTagIterator, typename EndEventTagIterator>
template<typename Observer>
inline void
ObserverRegistrationHelper<BeginEventTagIterator,
			   EndEventTagIterator>::registerGlobalObserverWithTag(
					     Teuchos::RCP<Observer>& observer )
{
  registerObserver( observer,
		    typename boost::mpl::deref<BeginEventTagIterator>::type());

  ObserverRegistrationHelper<typename boost::mpl::next<BeginEventTagIterator>::type,
			     EndEventTagIterator>::registerObserverWithTag(
								    observer );
}

// End registration iteration
template<typename EndEventTagIterator>
template<typename Observer, typename EntityHandle>
inline void 
ObserverRegistrationHelper<EndEventTagIterator,
			   EndEventTagIterator>::registerObserverWithTag(
			       Teuchos::RCP<Observer>& observer,
			       const Teuchos::Array<EntityHandle>& entity_ids )
{ /* ... */ }

// End global registration iteration
template<typename EndEventTagIterator>
template<typename Observer>
inline void
ObserverRegistrationHelper<EndEventTagIterator,
			   EndEventTagIterator>::registerGlobalObserverWithTag(
					     Teuchos::RCP<Observer>& observer )
{ /* ... */ }

//! Register an observer with the appropriate dispatcher
template<typename Observer, typename EntityHandle>
inline void registerObserver( Teuchos::RCP<Observer>& observer,
			      const Teuchos::Array<EntityHandle>& entity_ids )
{
  typedef typename boost::mpl::begin<typename Observer::EventTags>::type
    BeginEventTagIterator;
  typedef typename boost::mpl::end<typename Observer::EventTags>::type
    EndEventTagIterator;
  
  ObserverRegistrationHelper<BeginEventTagIterator,
                             EndEventTagIterator>::registerObserverWithTag(
								  observer,
								  entity_ids );
}

//! Register a global observer with the appropriate dispatcher
template<typename Observer>
inline void registerGlobalObserver( Teuchos::RCP<Observer>& observer )
{
  typedef typename boost::mpl::begin<typename Observer::EventTags>::type
    BeginEventTagIterator;
  typedef typename boost::mpl::end<typename Observer::EventTags>::type
    EndEventTagIterator;

  ObserverRegistrationHelper<BeginEventTagIterator,
			   EndEventTagIterator>::registerGlobalObserverWithTag(
								    observer );
}

/* Register an observer with the appropriate particle colliding in cell event 
 * dispatcher
 */
template<typename Observer, typename EntityHandle>
inline void registerObserver( Teuchos::RCP<Observer>& observer,
			      const Teuchos::Array<EntityHandle>& entity_ids,
			      ParticleCollidingInCellEventObserver::EventTag )
{
  // Make sure the Observer class has the corrent event tag
  testStaticPrecondition((boost::mpl::contains<typename Observer::EventTags,ParticleCollidingInCellEventObserver::EventTag>::value));
  
  Teuchos::RCP<ParticleCollidingInCellEventObserver> observer_base = 
    Teuchos::rcp_dynamic_cast<ParticleCollidingInCellEventObserver>( observer );
  
  for( unsigned i = 0u; i < entity_ids.size(); ++i )
  {
    ParticleCollidingInCellEventDispatcherDB::attachObserver(entity_ids[i],
							     observer->getId(),
							     observer_base );
  }
}

/* Register an observer with the appropriate particle crossing surface event
 * dispatcher
 */
template<typename Observer, typename EntityHandle>
inline void registerObserver( Teuchos::RCP<Observer>& observer,
			      const Teuchos::Array<EntityHandle>& entity_ids,
			      ParticleCrossingSurfaceEventObserver::EventTag )
{
  // Make sure the Observer class has the corrent event tag
  testStaticPrecondition((boost::mpl::contains<typename Observer::EventTags,ParticleCrossingSurfaceEventObserver::EventTag>::value));
  
  Teuchos::RCP<ParticleCrossingSurfaceEventObserver> observer_base = 
    Teuchos::rcp_dynamic_cast<ParticleCrossingSurfaceEventObserver>( observer );
  
  for( unsigned i = 0u; i < entity_ids.size(); ++i )
  {
    ParticleCrossingSurfaceEventDispatcherDB::attachObserver(entity_ids[i],
							     observer->getId(),
							     observer_base );
  }
}

/* Register an observer with the appropriate particle entering cell event
 * dispatcher
 */
template<typename Observer, typename EntityHandle>
inline void registerObserver( Teuchos::RCP<Observer>& observer,
			      const Teuchos::Array<EntityHandle>& entity_ids,
			      ParticleEnteringCellEventObserver::EventTag )
{
  // Make sure the Observer class has the corrent event tag
  testStaticPrecondition((boost::mpl::contains<typename Observer::EventTags,ParticleEnteringCellEventObserver::EventTag>::value));
  
  Teuchos::RCP<ParticleEnteringCellEventObserver> observer_base = 
    Teuchos::rcp_dynamic_cast<ParticleEnteringCellEventObserver>( observer );
  
  for( unsigned i = 0u; i < entity_ids.size(); ++i )
  {
    ParticleEnteringCellEventDispatcherDB::attachObserver( entity_ids[i],
							   observer->getId(),
							   observer_base );
  }
}

/* Register an observer with the appropriate particle leaving cell event
 * dispatcher
 */
template<typename Observer, typename EntityHandle>
inline void registerObserver( Teuchos::RCP<Observer>& observer,
			      const Teuchos::Array<EntityHandle>& entity_ids,
			      ParticleLeavingCellEventObserver::EventTag )
{
  // Make sure the observer has the expected event tag
  testStaticPrecondition((boost::mpl::contains<typename Observer::EventTags,ParticleLeavingCellEventObserver::EventTag>::value));
  
  Teuchos::RCP<ParticleLeavingCellEventObserver> observer_base = 
    Teuchos::rcp_dynamic_cast<ParticleLeavingCellEventObserver>( observer );
  
  for( unsigned i = 0u; i < entity_ids.size(); ++i )
  {
    ParticleLeavingCellEventDispatcherDB::attachObserver( entity_ids[i],
							  observer->getId(),
							  observer_base );
  }
}

/* Register an observer with the appropriate particle subtrack ending in cell
 * event dispatcher
 */
template<typename Observer, typename EntityHandle>
inline void registerObserver( 
			  Teuchos::RCP<Observer>& observer,
			  const Teuchos::Array<EntityHandle>& entity_ids,
			  ParticleSubtrackEndingInCellEventObserver::EventTag )
{
  // Make sure the Observer class has the expected event tag
  testStaticPrecondition((boost::mpl::contains<typename Observer::EventTags,ParticleSubtrackEndingInCellEventObserver::EventTag>::value));
  
  Teuchos::RCP<ParticleSubtrackEndingInCellEventObserver> observer_base = 
    Teuchos::rcp_dynamic_cast<ParticleSubtrackEndingInCellEventObserver>( 
								    observer );
  
  for( unsigned i = 0u; i < entity_ids.size(); ++i )
  {
    ParticleSubtrackEndingInCellEventDispatcherDB::attachObserver(
							     entity_ids[i],
							     observer->getId(),
							     observer_base );
  }
}

/* Register a global observer with the appropraite particle subtrack ending
 * global event dispatcher
 */
template<typename Observer>
inline void registerGlobalObserver( 
			 Teuchos::RCP<Observer>& observer,
			 ParticleSubtrackEndingGlobalEventObserver::EventTag )
{
  // Make sure the Observer class has the expected event tag
  testStaticPrecondition((boost::mpl::contains<typename Observer::EventTags,ParticleSubtrackEndingGlobalEventObserver::EventTag>::value));

  Teuchos::RCP<ParticleSubtrackEndingGlobalEventObserver> observer_base = 
    observer;

  ParticleSubtrackEndingGlobalEventDispatcher::attachObserver(
							     observer->getId(),
							     observer_base );
}

} // end MonteCarlo namespace

#endif // end FACEMC_OBSERVER_REGISTRATION_HELPERS_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ObserverRegistrationHelpers_def.hpp
//---------------------------------------------------------------------------//
