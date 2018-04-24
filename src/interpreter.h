#pragma once

#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <chrono>
#include <thread>

#include <string_view>
#include <unordered_map>
#include <cstdlib>

#ifdef WINDOWS
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
char _getch(){
	char buf=0;
	struct termios old={0};
	fflush(stdout);
	if(tcgetattr(0, &old)<0)
		perror("tcsetattr()");
	old.c_lflag&=~ICANON;
	old.c_lflag&=~ECHO;
	old.c_cc[VMIN]=1;
	old.c_cc[VTIME]=0;
	if(tcsetattr(0, TCSANOW, &old)<0)
		perror("tcsetattr ICANON");
	if(read(0,&buf,1)<0)
		perror("read()");
	old.c_lflag|=ICANON;
	old.c_lflag|=ECHO;
	if(tcsetattr(0, TCSADRAIN, &old)<0)
		perror ("tcsetattr ~ICANON");
	return buf;
}
#endif

//Don't pollute global namespace
namespace Msqr{
enum types{ INT, CHAR };
using variable = std::tuple<std::string, types>;
class Parser;



namespace misc{
	void pause(){ system("pause"); }
	void run(std::string &str){ system(str.data()); }
	void print(std::string &str){ std::cout << str << ' '; }
	void add_var(){ 

namespace exec{
	void pause(){ std::cout<<"Press any key to continue..."; _getch();}
	void run(std::string_view str){ system(str.data()); }
	void print(std::string_view str){ std::cout << str ; //the user should be able to choose wether to add a \n or not }
	void exit(){ std::exit(0);}
	void add_var(std::unordered_map<std::string, variable>& varData){

		std::string str; int i;
		std::cin >> str >> i;
		varData.insert({str, {std::to_string(i), types::INT }});
	}

	void exit(){ std::exit(0); }
	void sleep(uint64_t&& ms){ std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }
}

namespace lxr{
	std::map<std::string, void*>
	commands = { 
		{ "pause", (void*)&misc::pause },
		{ "run", (void*)&misc::run },
		{ "print", (void*)&misc::print },
		{ "vINT", (void*)&misc::add_var },
		{ "exit", (void*)&misc::exit },
		{ "sleep", (void*)&misc::sleep }};

	/* Takes line, returns vector of tokens


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
	 * Tail is arguments 
	 * I've tried to make this code as generic as possible*/
	template<
		class _Char,
		class _Traits = std::char_traits<_Char>,
		class _Alloc = std::allocator<_Char>>
	std::vector<std::basic_string<_Char, _Traits, _Alloc>>
	parse(const std::basic_string<_Char, _Traits, _Alloc>& line,
		_Char&& delimiter)
	{
		std::vector<std::basic_string<_Char, _Traits, _Alloc>> ls;
		std::basic_istringstream<_Char, _Traits, _Alloc> linestr(line);
		std::basic_string<_Char, _Traits, _Alloc> buf;
		while(std::getline(linestr, buf, delimiter))
			ls.push_back(buf);
		return ls;
	}

	
	/* Takes vector of commands and command name
	 * Searches for given command in this vector
	 * Returns true if this command exists otherwise false */
	bool is_comma(const std::map<std::string, void*>& ls, const std::string& comma){
		return ls.find(comma) != ls.end() || comma.at(0) == '@';


	/* Takes list of commands and command name
	 * Searches for given command in this list
	 * Returns true if this command exists otherwise false */
	bool is_comma(std::string_view comma){
		return commands.find(comma.data()) != commands.end() || comma.at(0) == '@';

	}

namespace file{
	/* Reads file, returns vector of strings */
	std::vector<std::string>
	read(const std::string& fname){
		std::vector<std::string> ls;
		std::ifstream file(fname, std::ios::in);
		std::string buf;
		while(!file.eof() || !file.badbit){
			std::getline(file, buf);
			if(!buf.empty())
				ls.push_back(buf);
		}
		return ls;
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
