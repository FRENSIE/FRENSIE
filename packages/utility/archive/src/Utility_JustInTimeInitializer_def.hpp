//---------------------------------------------------------------------------//
//!
//! \file   Utility_JustInTimeInitializer_def.hpp
//! \author Alex Robinson
//! \brief  Just-in-time initializer template definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_JUST_IN_TIME_INITIALIZER_DEF_HPP
#define UTILITY_JUST_IN_TIME_INITIALIZER_DEF_HPP

namespace Utility{

namespace Details{

  //! The just-in-time initialization object
class JustInTimeInitializationObject
{

public:

  //! Constructor
  JustInTimeInitializationObject()
  { /* ... */ }

  //! Destructor
  ~JustInTimeInitializationObject()
  { /* ... */ }

  //! Initialize the object
  virtual void initialize() = 0;

protected:

  /*! Redirect initialization to the JustInTimeInitializer, which should have
   * private access through friendship
   */
  template<typename T>
  void redirectObjectInitialization( T& raw_object )
  { Utility::JustInTimeInitializer::getInstance().initializeObject( raw_object ); }
};

//! The standard just-in-time initialization object
template<typename T>
class StandardJustInTimeInitializationObject : public JustInTimeInitializationObject
{
  
public:

  //! Constructor
  StandardJustInTimeInitializationObject( T& raw_object )
    : d_raw_object( raw_object )
  { /* ... */ }

  //! Destructor
  ~StandardJustInTimeInitializationObject()
  { /* ... */ }

  //! Initialize the object
  void initialize() final override
  { this->redirectObjectInitialization( d_raw_object.get() ); }

private:

  // The raw object
  std::reference_wrapper<T> d_raw_object;
};
  
} // end Details namespace

// Add an object that will be initialized just in time
/*! \details If the just-in-time initializer is not active, initialization will
 * occur here.
 */
template<typename T>
void JustInTimeInitializer::addObject( T& object )
{
  if( d_active )
  {
    d_initialization_objects.emplace_back( std::make_unique<Details::StandardJustInTimeInitializationObject<T> >( object ) );
  }
  else
    this->initializeObject( object );
}

// Initialize an object
template<typename T>
void JustInTimeInitializer::initializeObject( T& raw_object )
{
  // Only initialize if needed
  if( !raw_object.isInitialized() )
    raw_object.initializeJustInTime();
}
  
} // end Utility namespace

#endif // end UTILITY_JUST_IN_TIME_INITIALIZER_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_JustInTimeInitializer_def.hpp
//---------------------------------------------------------------------------//
