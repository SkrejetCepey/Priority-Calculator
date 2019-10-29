#include <iostream>
#include <stack>
#include <sstream>
#include <cstdlib>
#include <math.h>
#include <vector>

using namespace std;

vector <string> test;

void Calc(string *str, stack <double> *steck1)
{
	if (isdigit(str[0][0])) 
	{
		stringstream ss(*str);
		double d = 0;
		ss >> d;
		steck1->push(d);
	}
	else if (*str=="+") 
		{
			double temp1, temp2, summ;
			temp1 = steck1->top();
			steck1->pop();
			temp2 = steck1->top();
			steck1->pop();
			summ = temp1 + temp2;
			steck1->push(summ);
		}
	else if (*str=="-") 
		{
			double temp1, temp2, diff;
			temp1 = steck1->top();
			steck1->pop();
			temp2 = steck1->top();
			steck1->pop();
			diff = temp2 - temp1;
			steck1->push(diff);
		}
	else if(*str=="/")
		{
			double temp1, temp2, multi;
			temp1 = steck1->top();
			steck1->pop();
			temp2 = steck1->top();
			steck1->pop();
			multi = temp2 / temp1;
			steck1->push(multi);
		}
	else if (*str=="*") 
		{
			double temp1, temp2, multi;
			temp1 = steck1->top();
			steck1->pop();
			temp2 = steck1->top();
			steck1->pop();
			multi = temp2 * temp1;
			steck1->push(multi);
		}
}

int prior(string s)
{
        if (s=="(") {return 1;}
        else if (s=="+" || s=="-") {return 2;}
        else if (s=="*" || s=="/") {return 3;}
        else {return 0;}
}

void Conv(string *str, stack <string> *steck)
{
	if (isdigit(str[0][0]))
	{
		test.push_back(*str);
	}
	else if (*str=="+" || *str=="-" || *str=="/" || *str=="*")
	{
		if(steck->empty() || prior(*str) > prior(steck->top())){steck->push(*str);}
		else if(prior(steck->top())>= prior(*str)) 
		{
			while(!steck->empty() && prior(steck->top())>=prior(*str))
			{
				test.push_back(steck->top());
				steck->pop();
			}
			if(steck->empty() || prior(*str) > prior(steck->top())){steck->push(*str);}
		}
	}
	else if(*str=="(") {steck->push(*str);}
	else if(*str==")") 
	{
		while(steck->top()!="(")
			{
				test.push_back(steck->top());
				steck->pop();
			}
			steck->pop();
	}
}

int main(int argc, char **argv)
{
		stack <string> *steck;	
		steck = new stack<string>();
		
		stack <double> *steck1;	
		steck1 = new stack<double>();
		
		string str;
		string loop;
		
		stringstream *ss;
	    ss = new stringstream();
	    
	    //if (argv==NULL || argc==NULL) { cout << "No input example!\nTry next time!" << endl;return 0; }
	    	
		for(int i=1;i<argc;i++) //translate all example to the 1 word
		{		
			loop+=argv[i];
			if(i!=argc-1){loop+=" ";}
		}
		*ss << loop;
		                     
      
		       while (!ss->eof())
		       {
				 *ss >> str;				
				 Conv(&str, steck);				
			   }				  
		       while(!steck->empty() && prior(steck->top())>=prior(str))
				{
					test.push_back(steck->top());
					steck->pop();
			    }
			  //
			  //for(unsigned int i = 0; i < test.size(); i++) 
			  //{
			  //	  cout << "Debug: " << test[i] << ' ';
			  //}
			  //cout << endl;
			  //	
			  for(unsigned int i = 0; i < test.size(); i++) 
			  {
					str = test[i];
					Calc(&str, steck1);	
			  }
			  if (!steck1->top())
					{
						//cout << "Identity" << endl;
						cout << "Zero" << endl;
					}
					else 
					{
						//cout << "Non an identity" << endl;
						cout << steck1->top() << endl;
					}
			  cout << endl;
	return 0;
}
