#include<iostream>
#include"src/interpreter.h"

int main(){
	std::cout << "Atleast it compiles" << std::endl;
	std::string str;
	while(true){
		std::cin >> str;
		auto ls = lxr::parse(str);
		if(!lxr::is_comma(lxr::commands, ls.front())){
			std::cout << "Not a command\n";
			continue;
		}
		/* Here we perform double search for no reason
		 * I'll fix it later */
		auto iter = lxr::commands.find(ls.front());
		if(iter->first == "print"){
			auto* fptr = (decltype(&misc::print))(iter->second);
			fptr("Hello");
		}
		if(iter->first == "pause"){
			auto* fptr = (decltype(&misc::pause))(iter->second);
			fptr();
		}
		if(iter->first == "exit"){
			auto *fptr = (decltype(&misc::exit))(iter->second);
			fptr();
		}
		std::cout << '\n';
	}
	return 0;
}

