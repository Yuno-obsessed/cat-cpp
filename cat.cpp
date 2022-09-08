// Program that will take names of text files as arguments and print out
// their content in console.Also is able to take flags as arguments

#include<iostream>
#include<string>
#include<fstream>
#include<vector>

// function to figure out how many spaces should be on line with -n and -b arguments
std::string spacesCount(int digitsInNumber) {
	std::string spaces{};
	if (digitsInNumber < 10) {
		spaces = "     ";
	}
	else if (digitsInNumber >= 10 && digitsInNumber < 100) {
		spaces = "    ";
	}
	else if (digitsInNumber >= 100 && digitsInNumber < 1000) {
		spaces = "   ";
	}
	else if (digitsInNumber >= 1000 && digitsInNumber < 10000) {
		spaces = "  ";
	}
	else if (digitsInNumber >= 10000 && digitsInNumber < 100000) {
		spaces = " ";
	}
	else {
		spaces = "";
	}
	return spaces;
}

// function to open,read and do operations corresponding to args on file
void readFile(std::string name,bool numberNonEmpty,bool showEnds, bool numberLines, bool showTabs) {
	std::vector<std::string> lines;
	std::string line;
	std::fstream simpleFile;
	simpleFile.open(name, std::ios::in);
	if (!simpleFile.is_open()) {
		std::cerr << "Could not open the file - '"
			<< name << "'";
		EXIT_FAILURE;
	}
	int i = 1;
	std::string spaces{}, nl{}, se{};
	// loop to read from file line-by-line
	while (getline(simpleFile, line)) {
		if (numberNonEmpty == true) {
			// if line is empty, it's number output skips
			if (line == "") {
				nl = " ";
			}
			// if line isn't empty, write it's number with spaces
			else {
				nl = spacesCount(i) + std::to_string(i) + "  ";
				i++;
			}
		}
		if (numberLines == true) {
			nl = spacesCount(i) + std::to_string(i) + "  ";
			i++;
		}
		if (showEnds == true) {
			se = '$';
		}
		if (showTabs == true) {
		// loop to find tabs and replace it
			for (int i = 0; i < int(line.length()); i++) {
				if (line[i] == '\t') {
					line.replace(i,1,"^I");
				}
			}
		}
		// line's final look
		lines.push_back(nl + line + se);
	}
	// loop to output all lines of file
	for (const auto& i : lines) {
		std::cout << i << std::endl;
	}
	simpleFile.close();
	EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
	std::string flags[7]{ "-A", "-b","-E","-n","-T","--help","--version"};
	bool numberNonEmpty{},showEnds{}, numberLines{}, showTabs{};
	// loop to give instructions on what to perform if program confronts any arguments
	for (int i = 1; i < argc; i++) {
		if (std::string(argv[i]) == flags[5]) {
			readFile("help.txt", false, false, false, false);
			EXIT_SUCCESS;
		}
		else if (std::string(argv[i]) == flags[6]) {
			readFile("version.txt", false,false, false, false);
			EXIT_SUCCESS;
		}
		else if (std::string(argv[i]) == flags[0]) {
			showEnds = true;
			numberLines = true;
			showTabs = true;
		}
		else if (std::string(argv[i]) == flags[2]) {
			showEnds = true;
		}
		else if (std::string(argv[i]) == flags[3]) {
			numberLines = true;
		}
		else if (std::string(argv[i]) == flags[1]) {
			numberNonEmpty = true;
			numberLines = false;
		}
		else if (std::string(argv[i]) == flags[4]) {
			showTabs = true;
		}
	}
	bool checkFlags{};
	// loop to check if user tries to pass a flag that doesn't exist
	for (int i = 1; i < argc; i++)
	{
		int isFlag = 0;
		for (int j = 0; j < int(sizeof(flags)/sizeof(flags[0])); j++) {
			if (std::string(argv[i]) == flags[j]) {
				checkFlags = true;
			}
			else if (std::string(argv[i]) != flags[j] && std::string(argv[i])[0] == '-') {
				isFlag++;
			}
			if (isFlag == sizeof(flags)/sizeof(flags[0])) {
				std::cout << argv[0] << " invalid option " << argv[i] << "\nTry " << argv[0] << " --help\n";
				checkFlags = true;
			}
		}
		if (checkFlags == true) {
			checkFlags = false;
			continue;
		}
		// final execution of a program with desired output
		readFile(argv[i], numberNonEmpty,showEnds, numberLines,showTabs);

	}
	return 0;
	//cl /EHsc cat.cpp
	//cat.exe ...args
}