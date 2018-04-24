#include<iostream>
#include"interpreter.h"
#include<utility>

int main(){
	std::cout << "Atleast it compiles" << std::endl;
	std::string str;
	while(true){
		std::getline(std::cin, str);
		auto ls = lxr::parse(str, ' ');
		/* Here we perform double search for no reason
		 * I'll fix it later 
		 * Also, I removed checking for command correctness, it worked wrong for unknown reason
		 * Need to fix it asap*/
		auto iter = lxr::commands.find(ls.front());
		if(iter->first == "print"){
			auto* fptr = (decltype(&misc::print))(iter->second);
			for(size_t i = 1; i < ls.size(); i++)
				fptr(ls.at(i));
		}
		if(iter->first == "pause"){
			auto* fptr = (decltype(&misc::pause))(iter->second);
			fptr();
		}
		if(iter->first == "exit"){
			auto *fptr = (decltype(&misc::exit))(iter->second);
			fptr();
		}
		if(iter->first == "sleep"){
			auto* fptr = (decltype(&misc::sleep))(iter->second);
			fptr(std::stoi(ls.at(1)));
		}
		std::cout << '\n';
	}
	return 0;
}

