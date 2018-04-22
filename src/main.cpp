#include<iostream>
#include"interpreter.h"

int main(){
	std::cout << "Atleast it compiles" << std::endl;
	std::string str;
	Msqr::Parser parser;
	while(true){
		std::cin >> str;
		auto ls = parser.parse(str);
		if(!parser.is_comma(ls.front())){
			std::cout << "Not a command\n";
			continue;
		}
		/* Here we perform double search for no reason
		 * I'll fix it later */
		auto iter = parser.find(ls.front());
		if(iter->first == "print"){
			auto* fptr = (decltype(&Msqr::exec::print))(iter->second);
			fptr("Hello");
		}
		if(iter->first == "pause"){
			auto* fptr = (decltype(&Msqr::exec::pause))(iter->second);
			fptr();
		}
		if(iter->first == "exit"){
			auto *fptr = (decltype(&Msqr::exec::exit))(iter->second);
			fptr();
		}
		std::cout << '\n';
	}
	return 0;
}

