#pragma once

#include <iostream>
#include <fstream>
#include <array>
#include <list>
#include <string>
#include <string_view>
#include <unordered_map>
#include <cstdlib>
#include <conio.h>

//Don't pollute global namespace
namespace Msqr{
enum types{ INT, CHAR };
using variable = std::tuple<std::string, types>;
class Parser;


namespace exec{
	static void pause(){ system("pause"); }
	static void run(std::string_view str){ system(str.data()); }
=======
//store for variables
static std::unordered_map<std::string, variable> var_data;

namespace misc{
	void pause(){ std::cout<<"Press any key to continue..."<<std::endl; _getch();}
	void run(std::string_view str){ system(str.data()); }
	void print(std::string_view str){ std::cout << str << '\n'; }
	void exit(){ std::exit(0); }
	void add_var(std::unordered_map<std::string, variable>& varData){
		std::string str; int i;
		std::cin >> str >> i;
		varData.insert({str, {std::to_string(i), types::INT }});
	}

	/* Reads file, returns list of strings */
	std::list<std::string>
	readFile(std::string_view fname){
		std::list<std::string> ls;
		std::ifstream file(fname.data(), std::ios::in);
		std::string buf;
		while(!file.eof() || !file.badbit){
			std::getline(file, buf);
			if(!buf.empty())
				ls.push_back(buf);
		}
		return ls;
	}
};

class Parser{
private:
	std::unordered_map<std::string, variable> var_data;
	std::unordered_map<std::string, void*>
	commands = {
		{ "pause", (void*)&exec::pause },
		{ "run", (void*)&exec::run },
		{ "print", (void*)&exec::print },
		{ "vINT", (void*)&exec::add_var },
		{ "exit", (void*)&exec::exit } };

public:
	/* Takes line, returns list of tokens
	 * The first one is command name
	 * Tail is arguments */
	std::list<std::string> parse(std::string_view line){
		std::list<std::string> ls;
		while(!line.empty()){
			std::string_view buf(line.data(), line.find_first_of(' ') - 1);
			ls.push_back(buf.data());
			line.remove_prefix(std::min(line.find_first_of(' '), line.size()));
		}
		return ls;
	}

	/* Takes list of commands and command name
	 * Searches for given command in this list
	 * Returns true if this command exists otherwise false */
	bool is_comma(std::string_view comma){
		return commands.find(comma.data()) != commands.end() || comma.at(0) == '@';
	}

	auto find(const std::string str){
		return commands.find(str);
	}

	void add_var(){
		std::string str; int i;
		std::cin >> str >> i;
		var_data.insert({str, {std::to_string(i), types::INT }});
	}

	auto getVardata()
	{
		return var_data;
	}
};
}
