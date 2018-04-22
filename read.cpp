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
  virtual double getDouble()=0;
  virtual char getChar()=0;

};

ostream& operator<<(ostream& out, Obj* obj){
  return obj->print(out);
}

class Double :public Obj{
  double x;
public:
  Double(double val): x(val) {}
  ostream& print(ostream& out) { return out<<x;}
  double getDouble() { return x;}
  char getChar(){ return (char)x;}
};

class Char :public Obj{
  char s;
public:
  
  Char(char ch): s{ch} {}
  ostream& print(ostream& out){ return out<<s;}
  char getChar() {return s;}
  double getDouble(){return (int)s;}
};


string type_code(const string& name){
  ifstream fin(name);

  string s, res;
  getline(fin, s); //skip header
  getline(fin, s); //read one line of data
  istringstream ss{s};  

  while(getline(ss,s,','))
  
    isdigit(s[0])? res.append("1"):res.append("0");

  fin.close();
  
  return res;
}

  
vector<Obj*> data_frame(string name){


  string code = type_code(name);
  vector<Obj*> res{code.length()};
  
  ifstream fin{name};
 
  string s;
  getline(fin,s); //skip header

  getline(fin,s); //read data

  istringstream ss{s};
  cout<<"s="<<s<<endl;
  cout<<"code="<<code<<endl;
  for(int i=0; i!= code.length();++i){
    getline(ss,s,',');
    res[i] = code[i]=='1' ? static_cast<Obj*>(new Double{stod(s)}) : static_cast<Obj*>(new Char{s[0]});
  }

  cout<<endl;
  fin.close();

  return res;
}
  

      
int main(){
  //  string s = type_code("Credit.csv");
  //  int n=s.length();
  //read_csv("Credit.csv", s)

  /* Obj* a[2];
  a[0] = new Double{5};
  a[1] = new Char{'a'};
  a[0]->print();
  a[1]->print();
  int res = a[0]->getDouble();
  cout<<res;
  cout<<"\n"<<a[0]<<"\n"<<a[1];
  */
  vector<Obj*> v = data_frame("Credit.csv");
  cout<<v[8];
  return 0;
}
