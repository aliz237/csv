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
  ostream& print(ostream& out) {
    out.precision(20);
    return out<<x;
  }
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

using df = vector<vector<unique_ptr<Obj>>>;

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

  
vector<vector<unique_ptr<Obj>>> data_frame(string name){

  string code = type_code(name);
  vector<vector<unique_ptr<Obj>>> res{code.length()};
  ifstream fin{name};
 
  string s;
  getline(fin,s); //skip header

  while(getline(fin,s)){
    
    istringstream ss{s};

    for(int j=0; j!= code.length();++j){
      getline(ss,s,',');
      auto o = code[j]=='1'? unique_ptr<Obj>{new Double{stod(s)}} :
      unique_ptr<Obj>{new String{s}};
      res[j].push_back(move(o));
    }
  }

  fin.close();

  return res;
}
  
void head(df &d, int n){
  int col = d.size();
  int row= n<d[0].size()? n : d[0].size();

  for(int i=0; i!=row; ++i){
    for(int j=0; j!=col; ++j){
      d[j][i]->print(); cout<<" ";
    }
    cout<<endl;
  }
    
}
      
int main(){
  
  df w = data_frame("big.csv");

  head(w,2);

  return 0;
}
