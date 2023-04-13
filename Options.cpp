#include "pch.h"
#include "Options.h"	// contains all the required includes for the defined methods and properties

using namespace std;

/// <summary>
/// Options::Options()
/// default constructor
/// </summary>
Options::Options() {

}

/// <summary>
/// Options::~Options()
/// default destructor
/// </summary>
Options::~Options() {

}

/// <summary>
/// vector<Options::ArgOptions> Options::getOptions()
/// returns the list options type ArgOptions as a vector
/// </summary>
/// <returns></returns>
vector<Options::ArgOptions> Options::getOptions() { return _args; }

/// <summary>
/// void Options::setArgError(const char* argument, const char* message)
/// sets the argument and error mesage for a single char option
/// </summary>
/// <param name="argument"></param>
/// <param name="message"></param>
void Options::setArgError(const char* argument, const char* message) {
	ArgErrors error;
	error.argument = string(argument);
	error.message = string(message);
	_errors.push_back(error);
}

/// <summary>
/// void Options::addOption(const char shortName, const char* longName, const char* description, bool hasArg)
/// add an option including the short name, long name, a description, and whether it expects an argument
/// </summary>
/// <param name="shortName"></param>
/// <param name="longName"></param>
/// <param name="description"></param>
/// <param name="hasArg"></param>
void Options::addOption(const char shortName, const char* longName, const char* description, bool hasArg) {
	ArgOptions arg;
	arg.longName = string(longName);
	arg.shortName = shortName;
	arg.description = string(description);
	arg.hasArg = hasArg;
	_args.push_back(arg);
}

/// <summary>
/// char Options::getShortName(char name)
/// returns either the short name (single character) or NULL
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
char Options::getShortName(char name) {
	char shortName = NULL;
	for (auto it = _args.begin(); it != _args.end(); ++it) {
		ArgOptions arg = *it;
		if (name == arg.shortName) {
			shortName = name;
			break;
		}
	}
	return shortName;
}

/// <summary>
/// string Options::getLongName(string name)
/// returns a string type variable containing the long name
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
string Options::getLongName(string name) {
	string longName;
	for (auto it = _args.begin(); it != _args.end(); it++) {
		ArgOptions args = *it;
		if (name.find(args.longName) != std::string::npos) {
			longName = args.longName;
			break;
		}
	}
	return longName;
}

/// <summary>
/// bool Options::hasArg(string name)
/// returns the hasArg option based on the long name
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
bool Options::hasArg(string name) {
	bool hasArg = false;
	for (auto it = _args.begin(); it != _args.end(); ++it) {
		ArgOptions arg = *it;
		std::size_t found = arg.longName.find(name);
		if (found != std::string::npos) {
			hasArg = arg.hasArg;
			break;
		}
	}
	return hasArg;
}

/// <summary>
/// bool Options::hasArg(const char name)
/// returns the hasArg option based on the short name
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
bool Options::hasArg(const char name) {
	bool hasArg = false;
	for (auto it = _args.begin(); it != _args.end(); ++it) {
		ArgOptions arg = *it;
		if (name == arg.shortName) {
			hasArg = arg.hasArg;
			break;
		}
	}
	return hasArg;
}


/// <summary>
/// void Options::setArgument(string name, string argument)
/// sets the argument for the long name option
/// </summary>
/// <param name="name"></param>
/// <param name="argument"></param>
void Options::setArgument(string name, string argument) {
	for (auto it = _args.begin(); it != _args.end(); ++it) {
		ArgOptions arg = *it;
		if (name == arg.longName) {
			arg.argument = argument;
			*it = arg;
			return;
		}
	}

}

/// <summary>
/// void Options::setArgument(const char name, string argument)
/// sets the argument for the short name option
/// </summary>
/// <param name="name"></param>
/// <param name="argument"></param>
void Options::setArgument(const char name, string argument) {
	for (auto it = _args.begin(); it != _args.end(); ++it) {
		ArgOptions arg = *it;
		if (name == arg.shortName) {
			arg.argument = argument;
			*it = arg;
			return;
		}
	}
}


/// <summary>
/// void Options::parseArgs(int argc, char* argv[])
/// parses the ArgOptions passed in main
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
void Options::parseArgs(int argc, char* argv[]) {
	string opt;
	vector<string> args(argv, argv + argc);
	for (auto it = args.begin() + 1; it != args.end(); ++it) {
		string arg = *it;
		if (arg[0] == '-') {
			if (arg[1] == '-') {	// long name
				string longName = arg.substr(2, arg.length() - 2);
				longName = getLongName(longName);
				if (longName.empty()) {
					setArgError(longName.c_str(), "Unknown Option");
					continue;
				}
				else {
					if (arg.length() > longName.length() + 2) {
						size_t offset = longName.length() + 2;
						opt = arg.substr(offset, arg.length() - offset);
						setArgument(longName, opt);
						continue;
					}
					else {
						opt = *(it + 1);
						setArgument(longName, opt);
					}
				}
			}
			else { // short name
				if (getShortName(arg[1]) == NULL) {
					setArgError((const char*)arg[1], "Unknown Option");
				}
				else {
					if (hasArg((const char)arg[1])) {
						opt = *(it + 1);
						setArgument(arg[1], opt);
					}
				}
			}
		}
	}
}





