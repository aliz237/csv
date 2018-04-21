#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <sstream>
#include <vector>

using namespace std;



class Obj{
public:
  virtual ostream& print(ostream& out=cout)=0;
  virtual int getDouble()=0;
  virtual char getChar()=0;

};

ostream& operator<<(ostream& out, Obj* obj){
  return obj->print(out);
}

class Double :public Obj{
  int x;
public:
  Double(int val): x(val) {}
  ostream& print(ostream& out) { return out<<x;}
  int getDouble() { return x;}
  char getChar(){ return (char)x;}
};

class Char :public Obj{
  char s;
public:
  
  Char(char ch): s{ch} {}
  ostream& print(ostream& out){ return out<<s;}
  char getChar() {return s;}
  int getDouble(){return (int)s;}
};


string type_code(istringstream is){
  
  //code[i]=1 if objs of col i are numbers
  //and 0 otherwise.
  //length(s) = num of data cols
  // 
  //ifstream f(name);
  //if(!f) throw exep("couldn't open");
  //string s,t, code;
  //getline(f, s); //skip the header(if it exists or not)
  //getline(f,s); //read one line of data
  //cout<<"this whole line:"<<s<<"\n\n";
  //istringstream ss(s);
  string t;
  while(getline(is,t,','))
  
    isdigit(t[0])? code.append("1"):code.append("0");
  
  //f.close();
  
  return code;
}
  /*int sz = i;
  float num = stof(s[0]);
  cout<<num<<"\n";
  */
  
vector<Obj*> data_frame(string name){

  ifstream fin(name);

  string header;
  getline(fin, header);

  string s,temp;
  getline(fin, s);
  istringstream ss(s);
  string code = type_code(ss);
  
  double d; 
  for(int i=0;(getline(ss,temp,',');++i)
	a[i] = code[i] ? new Double{stod(temp)} : new Char{temp};

      
int main(){
  //  string s = type_code("Credit.csv");
  //  int n=s.length();
  //read_csv("Credit.csv", s)

  Obj* a[2];
  a[0] = new Double{5};
  a[1] = new Char{'a'};
  a[0]->print();
  a[1]->print();
  int res = a[0]->getDouble();
  cout<<res;
  cout<<"\n"<<a[0]<<"\n"<<a[1];
  return 0;
}
