/*
Names: Sam Lee
Login: slee103
Email: slee103@student.ucr.edu
Lab Section: 022
Assignment: Lab 3
I acknowledge all content is original.
*/

#include <fstream>
#include <iostream>
#include <string>
#include <map>


using namespace std;

string intToBin(int x) //32 bit converter
{
	string ret="";
	unsigned int store=2147483648u;
	for(int i=0; i <32; i++)
	{
		if(x/store==1)
		{
			ret+="1";
			x-=store;	
		}
		else ret+="0";
		store=store/2;
	}
	return ret;
	
}

string intToBin2(int x) //5 bit converter
{
	string ret="";
	unsigned int store=16;
	for(int i=0; i <5; i++)
	{
		if(x/store==1)
		{
			ret+="1";
			x-=store;	
		}
		else ret+="0";
		store=store/2;
	}
	return ret;
	
}

string intToBin3(int x) //16 bit converter
{
	string ret="";
	unsigned int store=32768;
	for(int i=0; i <16; i++)
	{
		if(x/store==1)
		{
			ret+="1";
			x-=store;	
		}
		else ret+="0";
		store=store/2;
	}
	return ret;
	
}

string intToBin4(int x) //26 bit converter
{
	string ret="";
	unsigned int store=33554432;
	for(int i=0; i <26; i++)
	{
		if(x/store==1)
		{
			ret+="1";
			x-=store;	
		}
		else ret+="0";
		store=store/2;
	}
	return ret;
	
}



int main()
{
	ifstream in;
	int readNum, varNum, parenLoc, parenLoc2;
	string fileName,word,addStr,save, line, varTemp ;
	int dataStart=127; // start of the data section
	int textStart=0; // start of the text section
	string zeros="00000000000000000000000000000000"; 

	map<string,int> varData; //map that stores variables and corresponding value
	map<string,int> varLabel; //map that stores labels and its location

	char *file;
	cout<<"Enter name of the file"<<endl; // read the name of the file
	cin>>fileName;

	fileName="test.s";

	file=new char[fileName.size()+1];
	strcpy(file, fileName.c_str());

	in.open(file);

	ofstream write;
	write.open("init.coe");
	
	//first 2 lines of the file
	write<<"memory_initialization_radix = 2;"<<endl; 
	write<<"memory_initialization_vector = "<<endl;

	string store[256];
	//string dataVal[127];


	while(in>>word)
	{
		if(word==".text")
			break;
		else
		{		
			//stores data into store array
	
			if(word.substr(0,1)=="V")
			{
				
				if(word.substr(word.length()-1,1)==":")
				{
					varTemp=word.substr(0,word.length()-1);
				}
				else
				{
					varTemp=word;
					in>>word;
				}
				in>>word;
				in>>readNum;
				varData[varTemp]=readNum;
				addStr=intToBin(readNum);
				store[dataStart]=addStr;
				dataStart++;
			}
		}
	}
	
	while(in>>word)
	{
		if(word=="lw") // Convert lw instruction
		{
			addStr="";
			save="";
			addStr+="100011";
			getline(in, line);

			int i=0, j=0;
			char x='.';
			while(x!='$')
			{
				x=line[i];
				i++;
			}
			j=i;
			while(x!=',')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);
	
			varNum=atoi(varTemp.c_str());
			save=intToBin2(varNum);
			

			for(int k=i; k<line.length();k++)
			{
				if(line[k]=='(') parenLoc=k;
				if(line[k]==')') parenLoc2=k;
			}

			varTemp=line.substr(parenLoc+1,(parenLoc2-parenLoc-1));
			addStr+=intToBin2(atoi(varTemp.c_str()));
			addStr+=save;
			varTemp=line.substr(i,parenLoc-i);
			if(varTemp.substr(0,1)=="V")
			varNum=varData[varTemp];
			else if (varTemp.substr(1,1)=="V")
			{
				varTemp=varTemp.substr(1, varTemp.size()-1);
				varNum=varData[varTemp];
			}
			else
			varNum=atoi(varTemp.c_str());
			addStr+=intToBin3(varNum);

			store[textStart]=addStr;
			textStart++;

		}
		if(word=="sw") // Convert lw instruction
		{
			addStr="";
			save="";
			addStr+="101011";
			getline(in, line);

			int i=0, j=0;
			char x='.';
			while(x!='$')
			{
				x=line[i];
				i++;
			}
			j=i;
			while(x!=',')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);
	
			varNum=atoi(varTemp.c_str());
			save=intToBin2(varNum);
			

			for(int k=i; k<line.length();k++)
			{
				if(line[k]=='(') parenLoc=k;
				if(line[k]==')') parenLoc2=k;
			}

			varTemp=line.substr(parenLoc+1,(parenLoc2-parenLoc-1));
			addStr+=intToBin2(atoi(varTemp.c_str()));
			addStr+=save;
			varTemp=line.substr(i,parenLoc-i);

			if(varTemp.substr(0,1)=="V")
			varNum=varData[varTemp];
			else
			varNum=atoi(varTemp.c_str());
			addStr+=intToBin3(varNum);

			store[textStart]=addStr;
			textStart++;

		}

		else if(word=="add") //Convert add instruction
		{
			addStr="";
			addStr+="000000";
			getline(in, line);
			int i=0, j=0;
			char x='.';
			while(x!='$')
			{
				x=line[i];
				i++;
			}
			j=i;
			while(x!=',')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);
			varNum=atoi(varTemp.c_str());
			save=intToBin2(varNum);
			while(x!='$')
			{
				x=line[i];
				i++;
			}
			j=i;
			while(x!=',')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);

			addStr+=intToBin2(atoi(varTemp.c_str()));

			while(x!='$')
			{
				x=line[i];
				i++;
			}
			j=i;
			while(x!=' ')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);
	
			addStr+=intToBin2(atoi(varTemp.c_str()));
			addStr+=save;
			addStr+="00000100000";
			
			store[textStart]=addStr;
			textStart++;
		}

		else if(word=="addu") //Convert add instruction
		{
			addStr="";
			addStr+="000000";
			getline(in, line);

			int i=0, j=0;
			char x='.';
			while(x!='$')
			{
				x=line[i];
				i++;
			}
			j=i;
			while(x!=',')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);
	
			varNum=atoi(varTemp.c_str());
			save=intToBin2(varNum);

			while(x!='$')
			{
				x=line[i];
				i++;
			}
			j=i;
			while(x!=',')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);
	
			addStr+=intToBin2(atoi(varTemp.c_str()));

			while(x!='$')
			{
				x=line[i];
				i++;
			}
			j=i;
			while(x!=' ')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);
	
			addStr+=intToBin2(atoi(varTemp.c_str()));
			addStr+=save;
			addStr+="00000100001";
			
			store[textStart]=addStr;
			textStart++;
		}

		else if(word=="sub") //Convert add instruction
		{
			addStr="";
			addStr+="000000";
			getline(in, line);

			int i=0, j=0;
			char x='.';
			while(x!='$')
			{
				x=line[i];
				i++;
			}
			j=i;
			while(x!=',')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);
	
			varNum=atoi(varTemp.c_str());
			save=intToBin2(varNum);

			while(x!='$')
			{
				x=line[i];
				i++;
			}
			j=i;
			while(x!=',')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);
	
			addStr+=intToBin2(atoi(varTemp.c_str()));

			while(x!='$')
			{
				x=line[i];
				i++;
			}
			j=i;
			while(x!=' ')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);
	
			addStr+=intToBin2(atoi(varTemp.c_str()));
			addStr+=save;
			addStr+="00000100010";
			
			store[textStart]=addStr;
			textStart++;
		}

		else if(word=="subu") //Convert add instruction
		{
			addStr="";
			addStr+="000000";
			getline(in, line);

			int i=0, j=0;
			char x='.';
			while(x!='$')
			{
				x=line[i];
				i++;
			}
			j=i;
			while(x!=',')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);
	
			varNum=atoi(varTemp.c_str());
			save=intToBin2(varNum);

			while(x!='$')
			{
				x=line[i];
				i++;
			}
			j=i;
			while(x!=',')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);
	
			addStr+=intToBin2(atoi(varTemp.c_str()));

			while(x!='$')
			{
				x=line[i];
				i++;
			}
			j=i;
			while(x!=' ')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);
	
			addStr+=intToBin2(atoi(varTemp.c_str()));
			addStr+=save;
			addStr+="00000100011";
			
			store[textStart]=addStr;
			textStart++;
		}

		else if(word=="and") //Convert add instruction
		{
			addStr="";
			addStr+="000000";
			getline(in, line);

			int i=0, j=0;
			char x='.';
			while(x!='$')
			{
				x=line[i];
				i++;
			}
			j=i;
			while(x!=',')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);
	
			varNum=atoi(varTemp.c_str());
			save=intToBin2(varNum);

			while(x!='$')
			{
				x=line[i];
				i++;
			}
			j=i;
			while(x!=',')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);
	
			addStr+=intToBin2(atoi(varTemp.c_str()));

			while(x!='$')
			{
				x=line[i];
				i++;
			}
			j=i;
			while(x!=' ')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);
	
			addStr+=intToBin2(atoi(varTemp.c_str()));
			addStr+=save;
			addStr+="00000100100";
			
			store[textStart]=addStr;
			textStart++;
		}

		else if(word=="or") //Convert add instruction
		{
			addStr="";
			addStr+="000000";
			getline(in, line);

			int i=0, j=0;
			char x='.';
			while(x!='$')
			{
				x=line[i];
				i++;
			}
			j=i;
			while(x!=',')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);
	
			varNum=atoi(varTemp.c_str());
			save=intToBin2(varNum);

			while(x!='$')
			{
				x=line[i];
				i++;
			}
			j=i;
			while(x!=',')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);
	
			addStr+=intToBin2(atoi(varTemp.c_str()));

			while(x!='$')
			{
				x=line[i];
				i++;
			}
			j=i;
			while(x!=' ')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);
	
			addStr+=intToBin2(atoi(varTemp.c_str()));
			addStr+=save;
			addStr+="00000100101";
			
			store[textStart]=addStr;
			textStart++;
		}

		else if(word=="slt") //Convert add instruction
		{
			addStr="";
			addStr+="000000";
			getline(in, line);

			int i=0, j=0;
			char x='.';
			while(x!='$')
			{
				x=line[i];
				i++;
			}
			j=i;
			while(x!=',')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);
	
			varNum=atoi(varTemp.c_str());
			save=intToBin2(varNum);

			while(x!='$')
			{
				x=line[i];
				i++;
			}
			j=i;
			while(x!=',')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);
	
			addStr+=intToBin2(atoi(varTemp.c_str()));

			while(x!='$')
			{
				x=line[i];
				i++;
			}
			j=i;
			while(x!=' ')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);
	
			addStr+=intToBin2(atoi(varTemp.c_str()));
			addStr+=save;
			addStr+="00000101010";
			
			store[textStart]=addStr;
			textStart++;
		}

		else if(word=="beq") //Convert add instruction
		{
			addStr="";
			addStr+="000100";
			getline(in, line);

			int i=0, j=0;
			char x='.';
			while(x!='$')
			{
				x=line[i];
				i++;
			}
			j=i;
			while(x!=',')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);
	
			addStr+=intToBin2(atoi(varTemp.c_str()));
			

			while(x!='$')
			{
				x=line[i];
				i++;
			}
			j=i;
			while(x!=',')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);
	
			addStr+=intToBin2(atoi(varTemp.c_str()));

			while(x==' ')
			{
				x=line[i];
				i++;
			}
			j=i;
			x=line[i];
			while(x!=' ')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);
	
			varNum=varLabel[varTemp];
			int labelLoc=varNum-textStart;
			if(labelLoc<0)
			{
				int labelLoc2= 65535+labelLoc;
				addStr+=intToBin3(labelLoc2);
			}
			else
			{
			addStr+=intToBin2(labelLoc);
			}
			store[textStart]=addStr;
			textStart++;
		}
		
		else if(word=="dbnz") //Convert add instruction
		{
			addStr="";
			addStr+="000110";
			getline(in, line);

			int i=0, j=0;
			char x='.';
			while(x!='$')
			{
				x=line[i];
				i++;
			}
			j=i;
			while(x!=',')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);
			if(varTemp!="1")
			{
				varTemp="0";
			}
			addStr+=intToBin2(atoi(varTemp.c_str()));
			addStr+="00000";

			while(x==' ')
			{
				x=line[i];
				i++;
			}
			j=i;
			x=line[i];
			while(x!=' ')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);
	
			varNum=varLabel[varTemp];
			int labelLoc=varNum-textStart;
			if(labelLoc<0)
			{
				int labelLoc2= 65535+labelLoc;
				addStr+=intToBin3(labelLoc2);
			}
			else
			{
			addStr+=intToBin2(labelLoc);
			}
			store[textStart]=addStr;
			textStart++;
		}

		else if(word=="j") //Convert add instruction
		{
			addStr="";
			addStr+="000010";
			getline(in, line);

			int i=0, j=0;
			char x='.';
			while(x!=' ')
			{
				x=line[i];
				i++;
			}
			j=i;
			while(x!=',')
			{
				x=line[i];
				i++;
			}
			varTemp=line.substr(j,i-j-1);		
	
			varNum=varLabel[varTemp];
			addStr+=intToBin4(varNum);
			store[textStart]=addStr;
			textStart++;
		}
		
		else
		{
			varTemp=word.substr(0,word.length()-1);
			varLabel[varTemp]=textStart;
		}
	}
	

	//Fill unused data space with zeros
	for(dataStart; dataStart<256; dataStart++)
	{
		store[dataStart]=zeros;
	}
	
	for(textStart; textStart<127; textStart++)
	{
		store[textStart]=zeros;
	}


	//write to coe file
	for(int i=0; i<256; i++)
	{
		write<<store[i]<<endl;
	}


}
