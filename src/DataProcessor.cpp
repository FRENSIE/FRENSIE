//---------------------------------------------------------------------------//
// \file   DataProcessor.cpp
// \author Alex Robinson
// \brief  DataProcessor function definitions
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>
#include <string>

// FACEMC Includes
#include "DataProcessor.hpp"

namespace FACEMC{

/*! \details This function simply converts the integer electron shell number to 
 * a string.
 * \param[in] shell An integer representing the electron shell number
 * \return A string of the electron shell number. 
 */
std::string DataProcessor::uintToShellStr( const unsigned int shell )
{
  std::stringstream shell_str;
  shell_str << shell;
  return shell_str.str();
}  

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end DataProcessor.cpp
//---------------------------------------------------------------------------//

