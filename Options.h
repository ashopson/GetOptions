#pragma once
#ifndef __OPTIONS__H__
#define __OPTIONS__H__

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/// <summary>
/// Options class
/// contains all components and methods associated
/// with processing command-line arguments
/// </summary>
class Options
{
public:
	/// <summary>
	/// ArgErrors is a structure used to contain
	/// error information.
	/// </summary>
	typedef struct ArgErrors {
		string message;
		string argument;
	} ArgErrors;

	/// <summary>
	/// ArgOptions is a structure for managing command-line arguments
	/// The class supports both short and long names for the options as well
	/// as a description and a bool to indicate whether a argument is expected
	/// to follow the option. The argument is stored in the struct with the option
	/// </summary>
	typedef struct ArgOptions {
		string longName;	// long name --option1, --option2, ...
		char shortName;		// short name -a, -b, ...
		string description;	// description for help message
		bool hasArg;		// indicates there is an argument expected
		string argument;	// holds parsed argument
	} ArgOption;

	/// <summary>
	/// Methods to be exported from the DLL
	/// </summary>
	__declspec(dllexport) Options();	// default constructor
	__declspec(dllexport) ~Options(); // default destructor
	__declspec(dllexport) void addOption(const char shortName, const char* longName, const char* description, bool hasArg);
	__declspec(dllexport) void parseArgs(int argc, char* argv[]);
	__declspec(dllexport) vector<ArgOptions> getOptions();

private:
	/// <summary>
	/// Private properties and methods used to support the public methods.
	/// </summary>
	string getLongName(string name);
	char getShortName(char name);
	bool hasArg(string name);
	bool hasArg(const char name);
	void setArgument(string name, string argument);
	void setArgument(const char name, string argument);
	void setArgError(const char* argument, const char* message);
	
	vector<ArgOptions> _args;
	vector<ArgErrors> _errors;

};


#endif // __OPTIONS__H__
