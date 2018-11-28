//---------------------------------------------------------------------------//
//!
//! \file   Utility_JustInTimeInitializer.hpp
//! \author Alex Robinson
//! \brief  Just-in-time initializer class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_JUST_IN_TIME_INITIALIZER_HPP
#define UTILITY_JUST_IN_TIME_INITIALIZER_HPP

// Std Lib Includes
#include <memory>
#include <list>

namespace Utility{

namespace Details{

// The just-in-time initialization object base class forward declaration
class JustInTimeInitializationObject;

} // end Details namespace

/*! The just-in-time initializer
 * 
 * Classes that can take a long time to initialize after being loaded from
 * an archive can use this class so that they are initialized just-in-time.
 * Like the boost::serialization::access class, this class must be a friend
 * of the class of interest. In the load method, instead of calling an
 * initialization method, add the class object to the just-in-time initializer
 * (e.g. Utility::JustInTimeInitializer::addObject( *this )), which can then be
 * used to initialize all loaded objects when they are actually needed.
 * Classes that utilize the JustInTimeInitializer must have a method called
 * isInitialized (e.g. bool isInitialized() const) and a method called 
 * initializeJustInTime (e.g. void initializeJustInTime()). These methods
 * can have any access level.
 */
class JustInTimeInitializer
{

public:
  
  //! Get the just-in-time initializer instance
  static JustInTimeInitializer& getInstance();

  //! Destructor
  ~JustInTimeInitializer()
  { /* ... */ }

  //! Activate the just-in-time initializer
  void activate();

  //! Deactivate the just-in-time initializer (default state)
  void deactivate();

  //! Check if the just-in-time initializer is active
  bool isActive() const;

  //! Add an object that will be initialized just in time
  template<typename T>
  void addObject( T& object );

  //! Return the number of stored initialization objects
  size_t getNumberOfObjects() const;

  //! Initialize the stored objects
  void initializeObjects() const;

  //! Clear the stored objects
  void clear();

  //! Initialize the stored objects and clear
  void initializeObjectsAndClear();
  
private:

  //! Constructor
  JustInTimeInitializer();

  //! Initialize an object
  template<typename T>
  void initializeObject( T& raw_object );

  // The JustInTimeInitializationObject is a friend
  friend class Details::JustInTimeInitializationObject;

  // The just-in-time initializer instance
  static std::unique_ptr<JustInTimeInitializer> s_instance;

  // Active or inactive
  bool d_active;

  // The just-in-time initialization objects
  std::list<std::unique_ptr<Details::JustInTimeInitializationObject> > d_initialization_objects;
};  

} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_JustInTimeInitializer_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_JUST_IN_TIME_INITIALIZER_HPP

//---------------------------------------------------------------------------//
// end Utility_JustInTimeInitializer.hpp
//---------------------------------------------------------------------------//
