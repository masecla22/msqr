#include <iostream>
#include <fstream>
#include <array>
#include <stringview> //TODO: REPLACE EVERY BUFFER<CHAR> IN FUNCTION'S PARAMETERS WITH STRINGVIEW DUE TO USABILITY
#include <cstdlib>

//default size for our buffers
//now you can easily change it whenever you want
//plus, constexpr instead of macro makes sense
constexpr size_t size_default = 255;

//enumeration of types
enum types{ INT, CHAR };

/* raising abstraction level
* always use std::array instead of raw arrays */

//quick alias for array
template<typename T>
using buffer<T> = std::array<T, size_default>;

//full alias for array
template<typename T, size_t S>
using buffer<T, S> = std::array<T, S>;

//name
using name = buffer<char>;
//content
using content = buffer<char>

//flLines - Counts the amount of lines in a file. (takes paramter as array of chars)
static volatile int variables_count = 0;

//variable is just a tuple of 3 elements
using variable = std::tuple<name, content, type>;

//store for variables
buffer<variable> userV;

//count lines in file
auto count_lines(std::string_view fname){
	std::std::ifstream file(fname.data(), std::ios::in);
	char c = 0;
	size_t count = 0;
	while(!file.eof() || !file.badbit){
		if(file >> c; c == '\n' || c == '\v')
			count++;
	file.close();
	return count;
}

//makes you able to compare buffer of chars and C-string
template<size_t S>
bool operator == (buffer<char, size>&& buf, const char* str){
	return std::strcmp(buf.data(), str) == 0; 
}
//length of specified buffer
//just syntactic sugar
template<typename T, size_t S>
constexpr size_t size(buffer<T, S>&& buf){ return S; }

template<size_t S>
size_t length(buffer<char, S>&& buf){ return strlen(buf.data()); }

enum EXP{ EXPECTED, UNEXPECTED }

//functional error handling
template<E, U>
using expected<E, U> = std::variant<EXP, U, E>;

template<typename E, typename U>
auto& value(expected<E, U>&& e){ 
	if(std::get<0>(e) == UNEXPECTED)
		std::abort();
	return std::get<1>(e);
}

template<typename E, typename U>
auto& error(expected<E, U>&& e){
	if(std::get<0>(e) == EXPECTED)
		std::abort();
	return std::get<2>(e);
}

//obtains the argument out of a command. Takes 4 parameters. First is the command, second is the buffer,
//third is which argument to retrieve and the fourth is whether it should return it with quotes or without.
// the function will for example :
// the second argument of: sleep 500 100 495 is 100
//the first arg in : move "My name is Jeff" 400 800 is "My name is Jeff"
// when noQuotes=1 the buffer will be My name is Jeff
expected<buffer<char>, int> getArgument(buffer<char>&& comma, buffer<char>&& buf, size_t number, bool noQuotes = false){
	buffer<char> buf;

	if(!arg) return -1; //Protects against illegal arguments that are on illegal positions (<1)
	int g = 0,
	    contorSpace = 0,
	    quoteCounter = 0;//just some menial variables
        for(size_t i = 0; i < length(comma); i++){
		if(command[i]=='\"')
			quoteCounter++; //checks if a quote is inserted.
        	if(contorSpace==arg){ // checks if contorSpace is equal to arg
        		if(noQuotes && command[i] != '\"')
				buf[g++] = command[i];
        		if(!noQuotes)
				buf[g++] = command[i];
		}
		//basically the way this works is if there is an odd amount of amount of ".
		//If so it means that the quotes are unclosed, therefore it ignores
		//space rule and keeps on adding to the buffer
		//(if the number of quotes is even then there are no unclosed "")
        	if(command[i] == ' ' && quoteCounter & 1 == 0)
			contorSpace++;
        }
	buf[g] = 0; //closes the string
	return buf;
}

buffer<char> getCommand(buffer<char>&& buf){
	buffer<char> comma;
	size_t iter = 0;
	while(iter != ' ');
		comma[i] = buf[i];
	return comma;
}

//check if given command is an actual command, will have to make better later.
bool isCommand(buffer<char>&& comma){
        auto buf = getCommand(comma);
        if(buf == "sleep") return true; 
        if(buf == "run") return true; 
        if(buf == "print") return true;
	if(buf == "exec") return true; // checks if buffer = "exec"
        if(buf == "print") return true; // checks if buffer = "print"
        if(buf == "vINT") return true; // checks if buffer = "vINT"
        if(buffer[0]=='@') return true; // checks if the first character from buffer is "@"
	return false;
}

//checks a file for errors
bool checkFileErr(std::string_view fname){
	std::ifstream fin(fname.data(), std::ios::in); 	//opens the stream
	size_t liness = count_lines(fname.data()); 	//count lines
	bool hasErrors = false;				//verify whether there are errors
	for(int i=0; i<liness; i++){ 			//iterate the lines
		buffer<char> comma;			//clears up the last command/
		fin.getline(comma, size_default);	//reads from file
	if(!isCommand(comma)){				//checks if it's a command
		auto buff = getCommand(comma);//get the command
		hasErrors = true;//mark that the file has errors
		std::cout << "At line " << i << " " << buffs.data() << " is undefined\n"; //alert error and pass on the line
        }
    }
    fin.close();//close the fstream
    return hasErrors;//return the errors
}

void shift(char buffer[size_default], int pos = 1)//shifts a string to the left and shortens it. Ex: hello shifted 1 = ello
{
  int a = strlen(buffer); // a is equal to the len of buffer
  for(int i=0;i<a;i++) // iterate the values from 0 to a
    buffer[i]=buffer[i+pos]; // shift the string
  buffer[a-pos]=0;//close the string
}
int getIndexByName(std::string_view str)//find the index of a variable based on its name
{
  for(int i=0;i<varsDeclared;i++)if(strcmp(a,userV[i].name)==0)return i;return -1; //iterate through the variable names and check if any of them match, if not return -1
}
bool isOperator(char a) // checks if parameter is an operator
{
  if(a=='+') return 1; //returns 1 if a is +
  else if (a=='-')return 2; // returns 2 if a is -
  else if (a=='/')return 3; // returns 3 if a is /
  else if (a=='*')return 4; // returns 4 if a is *
  else if (a=='%')return 5; // returns 5 if a is %
  else return 0; // return 0 if a is not an operator
}
int countArrs(char a[size_default]){int contor=0;for(int i=0;i<strlen(a);i++)contor+=(a[i]=='@');return contor;}
//my god, buckle up for this one

//interprets the current command, and needs the line for some debugging.
int interpret(char command[size_default],int line)
{
  //performs an additional check of command.
    if(!isCommand(command))
    {
        char buffer[size_default];
        getCommand(command,buffer);
        std::cout<<"At line "<<line<<" "<<buffer<<" is undefined"<<endl; //outputs error message
    }//if command is correct, it goes on.
    else
    {
        char buffer[size_default];//creates a buffer
        getCommand(command,buffer);//gets the command
        if(strcmp(buffer,"sleep")==0)//checks the command to be sleep
        {
            char Arg1[size_default];//takes first argument
            getArgument(command,Arg1,1);
            int h=atoi(Arg1);//gets value
            Sleep(h);//sleeps
        }
        if(strcmp(buffer,"run")==0)//checks the command to be run
        {
            char Arg1[size_default];//create first arg
            getArgument(command,Arg1,1,1);//get arg1
            char toberun[size_default];//initialise the command
            strcpy(toberun,"start ");//give it an inital value
            strcat(toberun,Arg1);//concatenate the argument
            system(toberun);//execute it
        }
        if(strcmp(buffer,"MouseMove")==0)//checks the command to be MouseMove
        {
            char x[size_default],y[size_default];
            getArgument(command,x,1);
            getArgument(command,y,2);//create and get arg1 and arg2
            POINT coords;
            coords.x=atoi(x);
            coords.x=atoi(y);//assign the variables
            SetCursorPos(coords.x,coords.y);//move the mouse
        }
        if(strcmp(buffer,"exec")==0) { //no idea why i am making this but i feel like it
          char argument[size_default];
          //wont work with command that require quotes within them
          getArgument(command,argument,1,1);
          interpret(argument,line); //nice
        }
        if(strcmp(buffer,"print")==0){ //checks if buffer = "print"
            char toPrint[size_default];
            getArgument(command,toPrint,1,1);
            std::cout<<toPrint;
        }
        if(strcmp(buffer,"vINT")==0)
        {
          userV[varsDeclared].types=1;
          char name[size_default]; getArgument(command,name,1,0);
          if(name[0]!='@')
          {
            std::cout<<"Expected @ at line "<<line<<" but instead got "<<name[0]<<endl;
            return -1;
          }
          else
          {
            shift(name);
            strcpy(userV[varsDeclared].name,name);
          }
          varsDeclared++;
        }


        if(buffer[0]=='@')
        {
          int arrs = countArrs(command);
          char firstName[size_default];
          shift(command);
          int i=0;
          while(command[i]!='=') firstName[i++]=command[i];firstName[i]=0;//close dem string
          shift(command,strlen(firstName));
          if(arrs!=1){
          char firstVar[size_default],secondVar[size_default];
          i=0;
          int operators;
          while(isOperator(command[i])!=0) firstVar[i++]=command[i]; firstVar[i]=0;
          shift(command,strlen(firstVar));
          shift(firstVar);
          strcpy(secondVar,command);
          shift(secondVar);
          std::cout<<firstName<<"   "<<firstVar<<"     "<<secondVar<<endl;
          }
        else{
          int position = getIndexByName(firstName);
          strcpy(userV[position].content,command);
        }
        }
    }
    return 0;
}
