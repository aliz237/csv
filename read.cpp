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
  virtual string getString()=0;

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
  string getString(){ return to_string(x);}
};

class String :public Obj{
  string s;
public:
  
  String(string str): s{str} {}
  ostream& print(ostream& out){ return out<<s;}
  string getString() {return s;}
  double getDouble(){return stod(s);}
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
    res[i] = code[i]=='1' ? static_cast<Obj*>(new Double{stod(s)}) : static_cast<Obj*>(new String{s});
  }

  fin.close();

  return move(res);
}
  

      
int main(){

  vector<Obj*> v = data_frame("Credit.csv");
  cout<<v[9];
  return 0;
}
