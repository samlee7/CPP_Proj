#include <vector>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <map>

//size of the matrix
const int n=290;
const int m=35;


using namespace std;

uint64_t IsPrime(uint64_t in)		//function to check prime
{

	if(in%2==0 && in!=2)			//check if number is even
	{								//n/t=q, qxt==n is more efficient
		return 2;
	}
	if(in==2)						//check if its 2
	{
		return 2;
	}

	for(uint64_t i=2; i*i<in; i++)	//check from 2 to square root of inputted number
	{								//and check if its divisible by something
		if(in%i==0)
		{
			return i;
		}
	}
	return in;					

}

void Decompose(uint64_t &in)		//function to decompose non prime number
{
	uint64_t get=IsPrime(in);
	cout<<get<<" ";					//print divisor d
	uint64_t next=in/get;			//solve to m in the function n=dm
	if(get!=in) Decompose(next);	//decompose m
}


//function to read the frequency of alphabet and space with a map.
map<char,int> freq(vector<char> in)
{
    map<char,int> ret;
    ret['A']=0;ret['B']=0;ret['C']=0;ret['D']=0;ret['E']=0;ret['F']=0;ret['G']=0;ret['H']=0;
    ret['I']=0;ret['J']=0;ret['K']=0;ret['L']=0;ret['M']=0;ret['N']=0;ret['O']=0;ret['P']=0;
    ret['Q']=0;ret['R']=0;ret['S']=0;ret['T']=0;ret['U']=0;ret['V']=0;ret['W']=0;ret['X']=0;
    ret['Y']=0;ret['Z']=0;ret[' ']=0;
    for(int i=0;i<in.size(); i++)
    {
        if(in[i]=='A')ret['A']++; if(in[i]=='B')ret['B']++; if(in[i]=='C')ret['C']++;
        if(in[i]=='D')ret['D']++; if(in[i]=='E')ret['E']++; if(in[i]=='F')ret['F']++; 
        if(in[i]=='G')ret['G']++; if(in[i]=='H')ret['H']++; if(in[i]=='I')ret['I']++;
        if(in[i]=='J')ret['J']++; if(in[i]=='K')ret['K']++; if(in[i]=='L')ret['L']++; 
        if(in[i]=='M')ret['M']++; if(in[i]=='N')ret['N']++; if(in[i]=='O')ret['O']++;
        if(in[i]=='P')ret['P']++; if(in[i]=='Q')ret['Q']++; if(in[i]=='R')ret['R']++;
        if(in[i]=='S')ret['S']++; if(in[i]=='T')ret['T']++; if(in[i]=='U')ret['U']++;
        if(in[i]=='V')ret['V']++; if(in[i]=='W')ret['W']++; if(in[i]=='X')ret['X']++;
        if(in[i]=='Y')ret['Y']++; if(in[i]=='Z')ret['Z']++; if(in[i]==' ')ret[' ']++;  
    }
    return ret;
}



int main(int argc, char* argv[])
{
//frequency counter
//try random nxm transposition

    vector<char> v;
    //vector<vector<char> > matrix(50, vector<char>(203));
    char matrix[n][m];
    char x;
    ifstream in (argv[1]);
    if(in.is_open())
    {
        while(in.good())
        {
            x=in.get();
            v.push_back(x);
        }
    }
	//uncomment to see the frequency of character.
    //cout<<v.size()<<endl;
    /*map<char,int> counter=freq(v);
    cout<<"A: "<<counter['A']<<endl;
    cout<<"B: "<<counter['B']<<endl;
    cout<<"C: "<<counter['C']<<endl;
    cout<<"D: "<<counter['D']<<endl;
    cout<<"E: "<<counter['E']<<endl;
    cout<<"F: "<<counter['F']<<endl;
    cout<<"G: "<<counter['G']<<endl;
    cout<<"H: "<<counter['H']<<endl;
    cout<<"I: "<<counter['I']<<endl;
    cout<<"J: "<<counter['J']<<endl;
    cout<<"K: "<<counter['K']<<endl;
    cout<<"L: "<<counter['L']<<endl;
    cout<<"M: "<<counter['M']<<endl;
    cout<<"N: "<<counter['N']<<endl;
    cout<<"O: "<<counter['O']<<endl;
    cout<<"P: "<<counter['P']<<endl;
    cout<<"Q: "<<counter['Q']<<endl;
    cout<<"R: "<<counter['R']<<endl;
    cout<<"S: "<<counter['S']<<endl;
    cout<<"T: "<<counter['T']<<endl;
    cout<<"U: "<<counter['U']<<endl;
    cout<<"V: "<<counter['V']<<endl;
    cout<<"W: "<<counter['W']<<endl;
    cout<<"X: "<<counter['X']<<endl;
    cout<<"Y: "<<counter['Y']<<endl;
    cout<<"Z: "<<counter['Z']<<endl;
    cout<<"space: "<<counter[' ']<<endl;*/

    uint64_t vsize=v.size();
	//uncomment to find the factors of vsize;
    //Decompose(vsize);

	//Fill out the matrix with input
    int counter=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0; j<m; j++)
        {   
            matrix[i][j]=v[counter];
            counter++;
        }
    }

	//replace the alphabet: read alphabet in matrix and change the alphabet and put
	//it into result
    char result[m][n];
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            if(matrix[i][j]=='G')
                result[j][i]=' ';
            else if(matrix[i][j]=='J')
                result[j][i]='e';
            else if(matrix[i][j]=='X')
                result[j][i]='t';
            else if(matrix[i][j]=='K')
                result[j][i]='a';
            else if(matrix[i][j]=='M')
                result[j][i]='s';
            else if(matrix[i][j]=='P')
                result[j][i]='h';
            else if(matrix[i][j]=='U')
                result[j][i]='o';
            else if(matrix[i][j]=='C')
                result[j][i]='r';
            else if(matrix[i][j]=='A')
                result[j][i]='i';
            else if(matrix[i][j]=='Y')
                result[j][i]='n';
            else if(matrix[i][j]=='T')
                result[j][i]='d';
            else if(matrix[i][j]=='B')
                result[j][i]='l';
            else if(matrix[i][j]=='E')
                result[j][i]='b';
            else if(matrix[i][j]=='L')
                result[j][i]='w';
            else if(matrix[i][j]=='Q')
                result[j][i]='u';
            else if(matrix[i][j]=='O')
                result[j][i]='k';
            else if(matrix[i][j]==' ')
                result[j][i]='y';
            else if(matrix[i][j]=='F')
                result[j][i]='v';
            else if(matrix[i][j]=='D')
                result[j][i]='f';
            else if(matrix[i][j]=='Z')
                result[j][i]='p';
            else if(matrix[i][j]=='V')
                result[j][i]='c';
            else if(matrix[i][j]=='S')
                result[j][i]='g';
            else if(matrix[i][j]=='W')
                result[j][i]='m';
            else if(matrix[i][j]=='R')
                result[j][i]='j';
            else if(matrix[i][j]=='H')
                result[j][i]='x';
            else if(matrix[i][j]=='I')
                result[j][i]='q';
            else if(matrix[i][j]=='N')
                result[j][i]='z';
            else
                result[j][i]=matrix[i][j];
        }
    }

	//print out the matrix
    for(int i=0; i<m; i++)
    {
        for(int j=0;j<n; j++)
            cout<<result[i][j];
        cout<<endl;
    }
    


}
