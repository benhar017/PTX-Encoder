#include <iostream>
#include <fstream>
#include <string>
#include<bits/stdc++.h>
using namespace std;

unordered_map<string,string> variable;
unordered_map<string,string> rev_inst;
unordered_map<string,string> spec;
unordered_map<string,string> spec1;
unordered_map<string,string> spec2;
unordered_map<string,string> opr;

ofstream MyFile("decoded.ptx");

void convert(unordered_map<string,string>&m,string s)
{
     std::ifstream file(s);
    std::string line;
    if (file.is_open()) {
        while (getline(file, line)) {

            string key="",value="";
            int i=0;
           while(line[i]!=' ')
            {
                key+=line[i];
                i++;
            } 

            i++;
            while(line[i]!='\0')
            {
                value+=line[i];
                i++;
            }

            m[key]=value;
        
            
        }

        file.close();
    }
    else {
        std::cout << "Unable to open file" << std::endl;
    }
}

string my_decode(string str){
	// cout<<str<<endl;
	int n = str.length();
	string res = "";
	vector<int> lengths = {8,6,6,6,8,8,8,8};
	int k = 0;
	for(int i=0;i<lengths.size();i++){
		string temp = "";
		for(int j=0;j<lengths[i];j++){
			temp+=str[j+k];
			//k++;
		}
		k+=lengths[i];
		// cout<<temp<<k<<" ";
		if(i==0){
			if(rev_inst.find(temp)!=rev_inst.end()){
				res+=rev_inst[temp];
			}
			//res+=".";
		}
		else if(i==1){
			if(temp=="000000")
				continue;
			res+=".";
			if(spec.find(temp)!=spec.end()){
				res+=spec[temp];
			}
			
		}
		else if(i==2){
			if(temp=="000000")
				continue;
			res+=".";
			if(spec1.find(temp)!=spec1.end()){
				res+=spec1[temp];
			}
			//res+=".";
		}
		else if(i==3){
			if(temp=="000000"){
				res+="  ";
				continue;
			}
			res+=".";
			if(spec2.find(temp)!=spec2.end()){
				res+=spec2[temp];
				res+="  ";
			}
			
		}
		else if(i==4){
			if(temp=="00000000")
				continue;
			if(opr.find(temp)!=opr.end()){
				res+=opr[temp];
				//res+=",";
			}
			
		}
		else if(i==5){
			if(temp=="00000000")
				continue;
			res+=",";
			if(opr.find(temp)!=opr.end()){
				res+=opr[temp];
			}
			
		}
		else if(i==6){
			if(temp=="00000000")
				continue;
			res+=",";
			if(opr.find(temp)!=opr.end()){
				res+=opr[temp];
				//res+=",";
			}
			
		}
		else if(i==7){
			if(temp=="00000000")
				continue;
			res+=",";
			if(opr.find(temp)!=opr.end()){
				res+=opr[temp];
			}
			//res+=";";
		}
	}
	res+=";";
	// cout<<endl;
	return res;
}

int main(){
	
	convert(rev_inst,"reverse_inst.txt");
	convert(spec,"reverse_specifier.txt");
	convert(spec1,"reverse_specifier1.txt");
	convert(spec2,"reverse_specifier2.txt");
	convert(opr,"reverse_opr_map.txt");
	convert(variable,"reverse_Init_Specifier.txt");


  	//variable["1111111111"] = "wala";
	fstream newfile;
	string main_encoder = "";
	newfile.open("encoder.txt",ios::in); //open a file to perform read operation using file object
	if (newfile.is_open()){   //checking whether the file is open
		//cout<<"file is open";
		string tp;
		int var_count = 0;
		while(getline(newfile, tp)){ //read data from file object and put it into string.
	    	if(tp.length()==0)
	        	continue;
	       	else if(tp.length()==32){
	       		if(variable.find(tp)!=variable.end()){
	       			// Write to the file
  					MyFile << variable[tp]<<"\n";
	       		}
	       		else{
	       			MyFile<<"yet to figure"<<"\n";
	       		}
	       	}
	       	else{
	       		string res = my_decode(tp);
	       		MyFile<<res<<"\n";
	       	}
	  	}
	}
	newfile.close(); 
}
