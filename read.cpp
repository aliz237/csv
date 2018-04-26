#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;



class Obj{
public:
  virtual ostream& print(ostream& out=cout)=0;
  virtual double getDouble()=0;
  virtual string getString()=0;
  virtual ~Obj(){}

};


ostream& operator<<(ostream& out, Obj* obj){
  return obj->print(out);
}

class Double :public Obj{
  double x;
public:
  Double(double val): x(val) {}
  ~Double(){}
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
  ~String(){}
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

  
vector<unique_ptr<Obj>> data_frame(string name){


  string code = type_code(name);
  vector<unique_ptr<Obj>> res;
  ifstream fin{name};
 
  string s;
  getline(fin,s); //skip header

  getline(fin,s); //read data

  istringstream ss{s};
  cout<<"s="<<s<<endl;
  cout<<"code="<<code<<endl;
  for(int i=0; i!= code.length();++i){
    getline(ss,s,',');
    auto o = code[i]=='1'? unique_ptr<Obj>{new Double{stod(s)}} :
    unique_ptr<Obj>{new String{s}};
    res.push_back(move(o));
  }

  fin.close();

  return res;
  }
  
Obj* f(){
  return new Double{5};
}
      
int main(){

  vector<unique_ptr<Obj>> w = data_frame("Credit.csv");
  //w[0]->print();

  vector<vector<unique_ptr<Obj>>> v{2};
  v[0].push_back(unique_ptr<Obj>{new Double{3}});
  v[1].push_back(unique_ptr<Obj>{new Double{3}});
  v[0].push_back(unique_ptr<Obj>{new Double{2}});
  v[0][0]->print();
  v[0][1]->print();
  v[1][0]->print();
  return 0;
}
