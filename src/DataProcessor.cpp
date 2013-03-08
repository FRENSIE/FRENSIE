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

//! Convert an unsigned int to an electron shell string
std::string DataProcessor::uintToShellStr( unsigned int shell )
{
  std::stringstream shell_str;
  shell_str << shell;
  return shell_str.str();
}  

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end DataProcessor.cpp
//---------------------------------------------------------------------------//

