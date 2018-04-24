#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <chrono>
#include <thread>
#include <cstdlib>

//default size for our buffers
//now you can easily change it whenever you want
//plus, constexpr instead of macro makes sense
constexpr size_t size_default = 255;

//enumeration of types
enum types{ INT, CHAR };

//variable is just a tuple of 2 elements
using variable = std::tuple<std::string, types>;

//store for variables
static std::map<std::string, variable> var_data;

namespace misc{
	void pause(){ system("pause"); }
	void run(std::string &str){ system(str.data()); }
	void print(std::string &str){ std::cout << str << ' '; }
	void add_var(){ 
		std::string str; int i;
		std::cin >> str >> i;
		var_data.insert({str, {std::to_string(i), types::INT }});
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
	}
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
		
	}
	
}
