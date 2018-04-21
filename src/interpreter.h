#include <iostream>
#include <fstream>
#include <array>
#include <list>
#include <string>
#include <string_view> 
#include <map>

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
	void pause(size_t time){ system("pause"); }
	void run(std::string_view str){ system(str.data()); }
	void print(std::string_view str){ std::cout << str << '\n'; }
	void add_var(){ 
		std::string str; int i;
		std::cin >> str >> i;
		var_data.insert({str, {std::to_string(i), types::INT }});
	}
}

namespace lxr{
	std::map<std::string, size_t*>
	commands = { 
		{ "pause", (size_t*)&misc::pause },
		{ "run", (size_t*)&misc::run },
		{ "print", (size_t*)&misc::print },
		{ "vINT", (size_t*)&misc::add_var } };

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
	bool is_comma(std::list<std::string>&& ls, std::string_view comma){
		return std::find(ls.begin(), ls.end(), comma) != ls.end() || comma.at(0) == '@';
	}
}

namespace file{
	/* Reads file, returns list of strings */
	std::list<std::string>
	read(std::string_view fname){
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
	
}
