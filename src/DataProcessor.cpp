//! Convert an unsigned int to an electron shell string
std::string ENDLIB97FileHandler::uintToShellStr( unsigned int shell )
{
  std::stringstream shell_str;
  shell_str << shell;
  return shell_str.str();
}  
