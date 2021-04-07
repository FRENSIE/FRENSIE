//---------------------------------------------------------------------------//
//!
//! \file   Utility_JustInTimeInitializer.cpp
//! \author Alex Robinson
//! \brief  Just-in-time initialier class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <functional>

// FRENSIE Includes
#include "Utility_JustInTimeInitializer.hpp"

namespace Utility{

// Initialize static member data
std::unique_ptr<JustInTimeInitializer> JustInTimeInitializer::s_instance;

// Get the just-in-time initializer instance
JustInTimeInitializer& JustInTimeInitializer::getInstance()
{
  if( !s_instance )
    s_instance.reset( new JustInTimeInitializer );

  return *s_instance;
}

// Constructor
JustInTimeInitializer::JustInTimeInitializer()
  : d_active( false )
{ /* ... */ }

// Activate the just-in-time initializer
/*! \details The just-in-time initializer must be activated before loading
 * any objects from an archive.
 */
void JustInTimeInitializer::activate()
{
  d_active = true;
}

// Deactivate the just-in-time initializer (default state)
/*! \details The just-in-time initializer is not active by default.
 */
void JustInTimeInitializer::deactivate()
{
  d_active = false;
}

// Check if the just-in-time initializer is active
bool JustInTimeInitializer::isActive() const
{
  return d_active;
}

// Return the number of stored initialization objects
size_t JustInTimeInitializer::getNumberOfObjects() const
{
  return d_initialization_objects.size();
}

// Initialize the stored objects
void JustInTimeInitializer::initializeObjects() const
{
  for( auto&& initialization_object : d_initialization_objects )
    initialization_object->initialize();
}

// Clear the stored objects
/*! \details Make sure that the stored objects have been initialized before
 * calling this method. Failure to do so may result in the objects never
 * being initialized.
 */
void JustInTimeInitializer::clear()
{
  d_initialization_objects.clear();
}

// Initialize the stored objects and clear
void JustInTimeInitializer::initializeObjectsAndClear()
{
  this->initializeObjects();
  this->clear();
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_JustInTimeInitializer.cpp
//---------------------------------------------------------------------------//
