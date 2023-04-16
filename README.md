# GetOptions -- A C/C++ Command-Line Processing Class
## Author "A. Scott Hopson" <ashopson@gmail.com>

This project is a C++ class to implement Command-Line processing. It provides options similar to what's found in the Apache Commons CLI 1.2 for Java. The class provides a collection of Options and a command-line parser. The current version provides the ability to define options containing both the long and short name where the short name is a single character with a '-' prefix and the long name is one or more characters with '--' prefixed.

### For example:
  Option -f or --filename
  
  A description of the option
  
  A boolean(TRUE | FALSE) indicating whether an argument is expected after the option as in -f file 

### Methods:
  #### void addOption(const char shortname, const char* longName, const char* description, bool hasArg);
  #### void parseArgs(int argc, char* args[]);
  #### vector<ArgOptions> getOptions();
  #### void help(string comment);
  #### void help();
  
  The help() option could be updated to provide more formatting. Currently it just displays the options and any description.
  
  The help(string comment) method displays the same information as above with the comment preceeding it.
  
  
