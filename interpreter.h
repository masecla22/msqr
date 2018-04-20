#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <windows.h>
using namespace std; //Yes, I will use it, no matter what you tell me. -Matt; If you can change the program everynow and again to make it compatible without using namespace std;, be my guest.

//flLines - Counts the amount of lines in a file. (takes paramter as array of chars)
int varsDeclared=0;
class variable {
public:
  char content[255]; // declares a char
  char name[255]; // declares another char
  int types=0; // declares an integer
  //1 = int 2 = char
};
variable userV[255];
int flLines(char fileName[255]){
    ifstream fin(fileName); //open filestream
    char a[255]; //create a random variable for fin.getline() to work
    int h=0;//this is the variable that contorises the
    while(fin.getline(a,255))h++; //using fin.getline() in order to capture the completeness of a line
    fin.close(); //closing the file stream
    return h;}//return the amount of lines. Damn it is it annoying to comment everything you do.

//obtains the command out of a line. It takes 2 paramters. The first one is the entire line that was read,
//and the second one is the buffer to compensate for C++ lack of abilty to return arrays
void getCommand(char command[255],char buffer[255]){
      int i=0;
      while(command[i]!=' '&&command[i]!=0)
          buffer[i]=command[i++];//appends the command i char to buffers i char
      buffer[i]=0;} //closes the string

//obtains the argument out of a command. Takes 4 parameters. First is the command, second is the buffer,
//third is which argument to retrieve and the fourth is whether it should return it with quotes or without.
// the function will for example :
// the second argument of: sleep 500 100 495 is 100
//the first arg in : move "My name is Jeff" 400 800 is "My name is Jeff"
// when noQuotes=1 the buffer will be My name is Jeff
      int getArgument(char command[255],char buffer[255],int arg,bool noQuotes=0)
      {
        if(arg<1) return -1; //Protects against illegal arguments that are on illegal positions (<1)
          int g=0,contorSpace=0,quoteCounter=0;//just some menial variables
          for(int i=0; i<int(strlen(command)); i++)
          {
              if(command[i]=='\"')quoteCounter++; //checks if a quote is inserted.
              if(contorSpace==arg) // checks if contorSpace is equal to arg
              {
                  if(noQuotes==1 && command[i]!='\"')buffer[g++]=command[i];
                  if(noQuotes==0)buffer[g++]=command[i];
              } //basically the way this works is if there is an odd amount of amount of ". If so it means that the quotes are unclosed, therefore it ignores the
              //space rule and keeps on adding to the buffer (if the number of quotes is even then there are no unclosed "")
              if(command[i]==' '&&quoteCounter%2==0)contorSpace++;
          }
          buffer[g]=0; //closes the string
          return 0;
      }
      //check if given command is an actual command, will have to make better later.
      bool isCommand(char command[255])
      {
          char buffer[255];
          getCommand(command,buffer);
          if(strcmp(buffer,"sleep")==0)return 1; //checks if buffer = "sleep"
          else if(strcmp(buffer,"run")==0)return 1; // checks if buffer = "run"
          else if(strcmp(buffer,"MouseMove")==0)return 1; // checks if buffer = "MouseMove"
          else if(strcmp(buffer,"exec")==0)return 1; // checks if buffer = "exec"
          else if(strcmp(buffer,"print")==0)return 1; // checks if buffer = "print"
          else if(strcmp(buffer,"vINT")==0)return 1; // checks if buffer = "vINT"
          else if(buffer[0]=='@')return 1; // checks if the first character from buffer is "@"
          else return 0;
      }

//checks a file for errors
bool checkFile(char a[255])
{
    ifstream fin(a); //opens the stream
    int liness=flLines(a); //count lines
    bool hasErrors=0;//verify whether there are errors
    for(int i=0; i<liness; i++) //iterate the lines
    {
        char command[255];//clears up the last command/
        fin.getline(command,255);//reads from file
        if(!isCommand(command))//checks if it's a command
        {
            char buffs[255];//create a buffer
            getCommand(command,buffs);//get the command
            hasErrors=1;//mark that the file has errors
            cout<<"At line "<<i<<" "<<buffs<<" is undefined"<<endl;//alert error and pass on the line
        }
    }
    fin.close();//close the fstream
    return hasErrors;//return the errors
}
void shift(char buffer[255],int pos=1)//shifts a string to the left and shortens it. Ex: hello shifted 1 = ello
{
  int a = strlen(buffer); // a is equal to the len of buffer
  for(int i=0;i<a;i++) // iterate the values from 0 to a
    buffer[i]=buffer[i+pos]; // shift the string
  buffer[a-pos]=0;//close the string
}
int getIndexByName(char a[255])//find the index of a variable based on its name
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
int countArrs(char a[255]){int contor=0;for(int i=0;i<strlen(a);i++)contor+=(a[i]=='@');return contor;}
//my god, buckle up for this one

//interprets the current command, and needs the line for some debugging.
int interpret(char command[255],int line)
{
  //performs an additional check of command.
    if(!isCommand(command))
    {
        char buffer[255];
        getCommand(command,buffer);
        cout<<"At line "<<line<<" "<<buffer<<" is undefined"<<endl; //outputs error message
    }//if command is correct, it goes on.
    else
    {
        char buffer[255];//creates a buffer
        getCommand(command,buffer);//gets the command
        if(strcmp(buffer,"sleep")==0)//checks the command to be sleep
        {
            char Arg1[255];//takes first argument
            getArgument(command,Arg1,1);
            int h=atoi(Arg1);//gets value
            Sleep(h);//sleeps
        }
        if(strcmp(buffer,"run")==0)//checks the command to be run
        {
            char Arg1[255];//create first arg
            getArgument(command,Arg1,1,1);//get arg1
            char toberun[255];//initialise the command
            strcpy(toberun,"start ");//give it an inital value
            strcat(toberun,Arg1);//concatenate the argument
            system(toberun);//execute it
        }
        if(strcmp(buffer,"MouseMove")==0)//checks the command to be MouseMove
        {
            char x[255],y[255];
            getArgument(command,x,1);
            getArgument(command,y,2);//create and get arg1 and arg2
            POINT coords;
            coords.x=atoi(x);
            coords.x=atoi(y);//assign the variables
            SetCursorPos(coords.x,coords.y);//move the mouse
        }
        if(strcmp(buffer,"exec")==0) { //no idea why i am making this but i feel like it
          char argument[255];
          //wont work with command that require quotes within them
          getArgument(command,argument,1,1);
          interpret(argument,line); //nice
        }
        if(strcmp(buffer,"print")==0){ //checks if buffer = "print"
            char toPrint[255];
            getArgument(command,toPrint,1,1);
            cout<<toPrint;
        }
        if(strcmp(buffer,"vINT")==0)
        {
          userV[varsDeclared].types=1;
          char name[255]; getArgument(command,name,1,0);
          if(name[0]!='@')
          {
            cout<<"Expected @ at line "<<line<<" but instead got "<<name[0]<<endl;
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
          char firstName[255];
          shift(command);
          int i=0;
          while(command[i]!='=') firstName[i++]=command[i];firstName[i]=0;//close dem string
          shift(command,strlen(firstName));
          if(arrs!=1){
          char firstVar[255],secondVar[255];
          i=0;
          int operators;
          while(isOperator(command[i])!=0) firstVar[i++]=command[i]; firstVar[i]=0;
          shift(command,strlen(firstVar));
          shift(firstVar);
          strcpy(secondVar,command);
          shift(secondVar);
          cout<<firstName<<"   "<<firstVar<<"     "<<secondVar<<endl;
          }
        else{
          int position = getIndexByName(firstName);
          strcpy(userV[position].content,command);
        }
        }
    }
    return 0;
}
