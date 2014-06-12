//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ObserverRegistrationHelpers_def.hpp
//! \author Alex Robinson
//! \brief  Event dispatcher helper function definitions
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_OBSERVER_REGISTRATION_HELPERS_DEF_HPP
#define FACEMC_OBSERVER_REGISTRATION_HELPERS_DEF_HPP

namespace Facemc{

// Register the observer with dispatchers associated with BeginEventTag tag
template<typename BeginEventTagIterator, typename EndEventTagIterator>
template<typename Observer, typename EntityHandle>
inline void 
ObserverRegistrationHelper<BeginEventTagIterator,EndEventTagIterator>::operator()( 
			       Teuchos::RCP<Observer>& observer,
			       const Teuchos::Array<EntityHandle>& entity_ids )
{
  registerObserver( observer, 
		    entity_ids,
		    boost::mpl::deref<BeginEventTagIterator>::type );
  
  ObserverRegistrationHelper<typename boost::mpl::next<BeginEventTagIterator>::type,EndEventTagIterator>( 
				                                  observer,
								  entity_ids );
}

template<typename EndEventTagIterator>
template<typename Observer, typename EntityHandle>
inline void 
ObserverRegistrationHelper<EndEventTagIterator,EndEventTagIterator>::operator()( 
			       Teuchos::RCP<Observer>& observer,
			       const Teuchos::Array<EntityHandle>& entity_ids )
{ /* ... */ }

struct register_with_each_dispatcher
{
  template<typename Observer, typename EntityHandle>
  inline void operator()( Teuchos::RCP<Observer>& observer,
			  const Teuchos::Array<EntityHandle>& entity_ids )
  { /* ... */  }
}

//! Register an observer with the appropriate dispatcher
template<typename Observer, typename EntityHandle>
inline void registerObserver( Teuchos::RCP<Observer>& observer,
			      const Teuchos::Array<EntityHandle>& entity_ids );
{
  typedef typename boost::mpl::begin<typename Observer::EventTags>::type
    BeginEventTagIterator;
  typedef typename typename boost::mpl::end<typename Observer::EventTags>::type
    EndEventTagIterator;
  
  ObserverRegistrationHelper<BeginEventTagIterator,EndEventTagIterator>( 
								  observer,
								  entity_ids );
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
  testStaticPrecondition((boost::is_same<typename boost::mpl::deref<typename boost::mpl::find<typename Observer::EventTags,ParticleCollidingInCellEventObserver::EventTag>::type>::type,ParticleCollidingInCellEventObserver::EventTag>::type));
  
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
  testStaticPrecondition((boost::is_same<typename boost::mpl::deref<typename boost::mpl::find<typename Observer::EventTags,ParticleCrossingSurfaceEventObserver::EventTag>::type>::type,ParticleCrossingSurfaceEventObserver::EventTag>::type));
  
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
  testStaticPrecondition((boost::is_same<typename boost::mpl::deref<typename boost::mpl::find<typename Observer::EventTags,ParticleEnteringCellEventObserver::EventTag>::type>::type,ParticleEnteringCellEventObserver::EventTag>::type));
  
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
  testStaticPrecondition((boost::is_same<typename boost::mpl::deref<typename boost::mpl::find<typename Observer::EventTags,ParticleLeavingCellEventObserver::EventTag>::type>::type,ParticleLeavingCellEventObserver::EventTag>::type));
  
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
  // Make sure the Observer class has the corrent event tag
  testStaticPrecondition((boost::is_same<typename boost::mpl::deref<typename boost::mpl::find<typename Observer::EventTags,ParticleSubtrackEndingInCellEventObserver::EventTag>::type>::type,ParticleSubtrackEndingInCellEventObserver::EventTag>::type));
  
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

} // end Facemc namespace

//! Macro for simple registering of observers
#define REGISTER_OBSERVER_WITH_DISPATCHERS( observer, entity_ids ) \
  Facemc::registerObserver( observer, entity_ids ) 

#endif // end FACEMC_OBSERVER_REGISTRATION_HELPERS_DEF_HPP

//---------------------------------------------------------------------------//
// end Facemc_ObserverRegistrationHelpers_def.hpp
//---------------------------------------------------------------------------//
