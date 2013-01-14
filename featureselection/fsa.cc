//Sam Lee
//860957929

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include "Timer.h"

using namespace std;

//Cross validation function
double Do_Cross_Validation(vector< vector<double> > data, vector<double> w)
{
  double count=0;
  double dist=99999; //set distance to a large number
  double temp=0;
  int best=0;
  for(int i=0; i<data.size()-1; i++)
  {
    for(int j=0; j<data.size()-1; j++)
    {
      if(i!=j)
      {
        //Euclidean function to find the distance
        for(int k=1; k<w.size()+1;k++)
        {
          temp+=w[k]*pow(data[i][k]-data[j][k],2);
        }
        temp=sqrt(temp);
        if(temp<dist){ dist=temp; best=j;} 
        temp=0;
      }
    }
  if(data[i][0]==data[best][0]) count=count+1; 
  dist=99999;
  }
  double ret=count/(data.size()-1);
  return ret;
}

int main(){
  //variables for timer class
  Timer t;
  double etime;
  int choice=0;
  string filen="";
  string fileline="";
  string buf;
  int i=0;
  double per=0;
  double bestper=0;
  
  cout<<"Sam Lee's Feature Selection Algorithm"<<endl
      <<"Name of file: ";
  cin>>filen;

  cout<<"Algorithm choices: "<<endl
      <<"1: Forward Selection"<<endl
      <<"2. Backward Selection"<<endl
      <<"3. Sam's Algorithm"<<endl;
  cin>>choice;

  vector< vector<double> > data;
  ifstream infile;
  infile.open(filen.c_str()); //open the file

  while(!infile.eof()) //load the numbers into the vector by using stringstream
  {
    getline(infile, fileline);
    stringstream ss(fileline);
    data.push_back(vector<double>());
    while(ss>>buf)
    {
      double t=atof(buf.c_str());  
      data[i].push_back(t); 
    } 
    i++;   
  }
  //print out of number of feature and instances
  int feature=data[0].size()-1;
  int inst=data.size()-1;
  cout<<"The dataset has "<<feature<<" features."<<endl;
  cout<<"The dataset has "<<inst<<" instances."<<endl<<endl;

  //Forward selection
  if(choice==1)
  {
    t.start();
    cout<<"Beginning Search"<<endl;
    double temp=0;
    double temp2=0;
    //set all values in vector to 0s
    vector<double> x (feature+1,0);
    vector<double> cpy (feature+1,0);
    vector<double> cpy2=x;
    vector<double> best=x;
    for(int i=1; i<feature+1; i++)
    { 
      for(int j=1; j<feature+1; j++)
      {
        cpy=x;
        if(x[j]==0) //if value is 0 set it to 1
        {
          cpy[j]=1;
          temp=Do_Cross_Validation(data,cpy);
          if(temp>per)
          {
            cpy2=cpy;
            per=temp;
            //check if cross validation gave the best value
            if(temp>bestper)
            {
              best=cpy;
              bestper=temp;
            }
          }
        }  
      }
      x=cpy2;
      
      temp2=per;
      for(int k=1; k<feature+1; k++)
      {
        cout<<x[k]<<" ";
      }
      cout<<endl<<per*100<<"%"<<endl;
      per=0;
    }
    //print out of time, best feature and percentage
    t.elapsedUserTime(etime);
    cout<<"Best features to use are: "<<endl;
    for(int k=1; k<feature+1; k++)
    {
      cout<<best[k]<<" ";
    }
    cout<<endl<<bestper*100<<"%"<<endl;
    cout<<etime<<endl;
    cout<<"Program took "<<etime<<" seconds."<<endl;
  }

  //Backward selection
  if(choice==2)
  {
    t.start();
    cout<<"Beginning Search"<<endl;
    double temp=0;
    double temp2=0;
    int first=0;
    //set all values in vectors to 1s
    vector<double> x (feature+1,1);
    vector<double> cpy (feature+1,1);
    vector<double> cpy2=x;
    vector<double> best=x;
    vector<double> check (feature+1,0);
    check[0]=1;
    for(int i=1; i<feature+1; i++)
    { 
      //this makes the program run the all 1 vector
      if(first==0)
      {
        temp=Do_Cross_Validation(data,cpy);
        if(temp>per)
        {
          cpy2=cpy;
          per=temp;
          if(temp>bestper)
          {
            best=cpy;
            bestper=temp;
          }          
        }
        x=cpy2;
        temp2=per;
        for(int k=1; k<feature+1; k++)
        {
          cout<<x[k]<<" ";
        }
        cout<<endl<<per*100<<"%"<<endl;
        per=0;
        first=1;
      }
      for(int j=1; j<feature+1; j++)
      {
        cpy=x;
        if(x[j]==1) //if value is 1 set it to 0
        {
          cpy[j]=0;
          temp=Do_Cross_Validation(data,cpy);
          if(temp>per)
          {
            cpy2=cpy;
            per=temp;
            //check if cross validation gave the best value
            if(temp>bestper)
            {
              best=cpy;
              bestper=temp;
            }
          }
        }  
      }
      x=cpy2;
      temp2=per;
      for(int k=1; k<feature+1; k++)
      {
        cout<<x[k]<<" ";
      }
      cout<<endl<<per*100<<"%"<<endl;
      per=0;
    }
    //print out of time, best feature and percentage
    t.elapsedUserTime(etime);
    cout<<"Best features to use are: "<<endl;
    for(int k=1; k<feature+1; k++)
    {
      cout<<best[k]<<" ";
    }
    cout<<endl<<bestper*100<<"%"<<endl;
    cout<<etime<<endl;
    cout<<"Program took "<<etime<<" seconds."<<endl;
  }

  //Sam's algorithm
  if(choice==3)
  {
    t.start();
    cout<<"Beginning Search"<<endl;
    double temp=0;
    double temp2=0;
    int check=0;
    //variables to check which direction is better
    double better1=0;
    double better2=0;
    vector<double> x (feature+1,0);
    vector<double> cpy (feature+1,0);
    vector<double> cpy2=x;
    vector<double> best=x;
    //set first half of vector to 1s
    for(int i=1; i<(feature+1)/2; i++) x[i]=1;
    for(int i=1; i<(feature+1)/2; i++)
    { 
      for(int j=1; j<feature+1; j++)
      {
        if(check==0||check==1)
        {
          cpy=x;
          if(x[j]==0)
          {
            cpy[j]=1;
            temp=Do_Cross_Validation(data,cpy);
            if(temp>per)
            {
              cpy2=cpy;
              per=temp;
              if(temp>bestper)
              {
                best=cpy;
                bestper=temp;
                better1=temp;
              }
            }
          }
        } 
        if(check==0||check==2)
        {
          cpy=x;
          if(x[j]==0) //if value is 0 set it to 1
          {
            cpy[j]=1;
            temp=Do_Cross_Validation(data,cpy);
            if(temp>per)
            {
              cpy2=cpy;
              per=temp;
              //check if cross validation gave the best value
              if(temp>bestper)
              {
                best=cpy;
                bestper=temp;
                better2=temp;
              }
            }
          }
        }
        //decide on the direction
        if(check==0)
        {
          if(better1>=better2) check=1;
          else check=2;
        } 
      }
      x=cpy2;
      
      temp2=per;
      for(int k=1; k<feature+1; k++)
      {
        cout<<x[k]<<" ";
      }
      cout<<endl<<per*100<<"%"<<endl;
      per=0;
    }
    //print out of time, best feature and percentage
    t.elapsedUserTime(etime);
    cout<<"Best features to use are: "<<endl;
    for(int k=1; k<feature+1; k++)
    {
      cout<<best[k]<<" ";
    }
    cout<<endl<<bestper*100<<"%"<<endl;
    cout<<etime<<endl;
    cout<<"Program took "<<etime<<" seconds."<<endl;
  }
  
  infile.close(); // close the file
}
