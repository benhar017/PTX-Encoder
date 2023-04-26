#include <iostream>
#include <fstream>
#include <string>
#include<bits/stdc++.h>
using namespace std;



void trim(string& s)
{
   size_t p = s.find_first_not_of(" \t");
   s.erase(0, p);

   p = s.find_last_not_of(" \t");
   if (string::npos != p)
      s.erase(p+1);
}

string toBinary_ten_bit(int num){
    string res = "";
    while(num){
        int t = num%2;
        if(t==0)
            res+="0";
        else
            res+="1";
        num/=2;
    }
    int pad = 32-res.length();
    string temp = "";
    while(pad--)
        temp+="0";
    res+=temp;
    reverse(res.begin(),res.end());
    return res;
}

string toBinary_eight_bit(int num){
    string res = "";
    while(num){
        int t = num%2;
        if(t==0)
            res+="0";
        else
            res+="1";
        num/=2;
    }
    int pad = 8-res.length();
    string temp = "";
    while(pad--)
        temp+="0";
    res+=temp;
    reverse(res.begin(),res.end());
    return res;
}

string toBinary_six_bit(int num){
    string res = "";
    while(num){
        int t = num%2;
        if(t==0)
            res+="0";
        else
            res+="1";
        num/=2;
    }
    int pad = 6-res.length();
    string temp = "";
    while(pad--)
        temp+="0";
    res+=temp;
    reverse(res.begin(),res.end());
    return res;
}



string findNthWord(string sentence, int n) {
    string word = "";
    int count = 0;
    for (int i = 0; i < sentence.length(); i++) {
        if (sentence[i] == ' ') {
            count++;
            if (count == n) {
                break;
            }
            word = "";
        } else {
            word += sentence[i];
        }
    }
    return word;
}

string param_encode(string s,unordered_map<string,string> &inst,unordered_map<string,string> &second,unordered_map<string,string>& variables,int &count){
      string ans ="";
      ans += inst[findNthWord(s,1).substr(1)];
      ans += second[findNthWord(s,2).substr(1)];
      string word = findNthWord(s,3);
      variables[word] = toBinary_six_bit(count);
      count++;
      for (char c : word) {
        bitset<8> binaryValue(c);
        //cout << binaryValue << " ";
        ans+=binaryValue.to_string();
    }
      return ans;
}

string const_encode(string s, unordered_map<string,string> &inst,unordered_map<string,string> &second){
   string ans="";
   ans += inst[findNthWord(s,1).substr(1)];
   ans += second[findNthWord(s,2).substr(1)];
   int n = 3;
   /*while(findNthWord(s,n++).size() > 1){
      for (char c : findNthWord(s,n)) {
        bitset<8> binaryValue(c);
        //cout << binaryValue << " ";
        ans+=binaryValue.to_string();
      }
   }*/
   for(int i=3;i<8;i++){
      for (char c : findNthWord(s,i)) {
        bitset<8> binaryValue(c);
        //cout << binaryValue << " ";
        ans+=binaryValue.to_string();
      }
   }
   return ans;

}

unordered_map<string, string> reverse_map(unordered_map<string,string>& map) {
    unordered_map<string, string> reverse;
    for (auto x : map) {
        reverse[x.second] = x.first;
    }
    return reverse;
}

void write_to_file(const std::unordered_map<std::string, std::string>& map, const std::string& filename) {
    std::ofstream ofs(filename);

    if (ofs.is_open()) {
        for (auto x : map) {
            ofs << x.first << " " << x.second << std::endl;
        }
        ofs.close();
    }
    else {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
    }
}


int main(){

   vector<string> command = {"call","mov","add","sub","mul","mad","mul24","mad24","sad","div","rem","abs","neg","min","max","popc","clz","bfind","fns","brev","bfe","bfi","bmsk","szext","dp4a","dp2a","testp","copysign","fma","neg","rcp","sqrt","rsqrt","sin","cos","lg2","ex2","tanh","set","setp","selp","slct","and","or","xor","not","cnot","lop3","shf","shl","shr","prmt","ld","ldu","st","prefetch","prefetchu","isspacep","cvta","cvt","tex","tld4","txq","istypep","suld","sust","sured","suq","stacksave","stackrestore","alloca","vadd","vadd2","vadd4","vsub","vsub2","vsub4","vmad","vavrg2","vavrg4","vabsdiff","vabsdiff2","vabsdiff4","vmin","vmin2","vmin4","vmax","vmax2","vmax4","vshl","vshr","vset","vset2","vset4","vsh","param","const"};
   vector<string> second={"uni","shared","param","u64","u32","gt","to","wide","s16","s64","s32","global","pred","b32","b64","u16","u16x2", "s16x2","hi","lo","relu","shiftamt","clamp", "wrap","f32","f64","rn","rz","rm","rp","approx","full","ftz","rnd"};
   vector<string>threeo={"param","u64","u32","gt","to","wide","s16","s64","s32","global","pred","b32","b64","u16","u16x2", "s16x2","hi","lo","relu","shiftamt","clamp", "wrap","f32","f64","rn","rz","rm","rp","approx","full","ftz","rnd"};
  vector<string>fouro={"u64","u32","u16","u8","s8", "s32", "s64", "f16", "f16x2", "f32", "f64", "sat","b16", "b32", "b64", "bf16x2", "bf16"};
  
   //[piyush]
   vector<string> operand_arr={"%r1","%r2","%r3","%r4","%r5","%r6","%r7","%r8","%r9","%r10","%r11","%r12","%r13","%r14","%r15","%r16","%rd1","%rd2","%rd3","%rd4","%rd5","%rd6","%rd7","%rd8","%rd9","%rd10","%rd11","%p1","[%rd1]","[%rd2]","[%rd3]","[%rd4]","[%rd5]","[%rd6]","[%rd7]","[%rd8]","[%rd9]","[%rd10]","[%rd11]","[%rd12]","[%rd13]","[%rd14]","[%rd15]","[%rd16]","[%r1]","[%r2]","[%r3]","[%r4]","[%r5]","[%r6]","[%r7]","[%r8]","[%r9]","[%r10]","[%r11]","[%r12]","[%r13]","[%r14]","[%r15]","4","%ctaid.x"};//"[_Z6gpuAddPiS_S__param_2]","[_Z6gpuAddPiS_S__param_1]","[_Z6gpuAddPiS_S__param_0]"};
   unordered_map<string,string> opr_map;
   //[piyush]

   unordered_map<string,string> inst;
   unordered_map<string,string> specifier;
      unordered_map<string,string>specifier1;
   unordered_map<string,string>specifier2;
   unordered_map<string,string> variables;
   unordered_map<string,string> Init_Specifier;

   ofstream Encd_file("encoder.txt");
   

   // [piyush_upd]
   int InsMap_ct,SpecMap_ct,SpecMap1_ct,SpecMap2_ct,VarMap_ct,OprMap_ct,InitSpec=66317;

   bool opr = false; // [piyush]
   int k = 0;

   for(int i=0;i<command.size();i++){
      string res = toBinary_eight_bit(i+1);
      inst[command[i]] = res;
      InsMap_ct=i+1;
   }
   cout<<"Comman size- "<<command.size()<<endl;
   InsMap_ct++;

   for(int i=0;i<second.size();i++){
      string res = toBinary_six_bit(i+1);
      specifier[second[i]] = res;
      SpecMap_ct=i+1;
   }
   SpecMap_ct++;

   for(int i=0;i<operand_arr.size();i++){
      string res = toBinary_eight_bit(i+1);
      opr_map[operand_arr[i]] = res;
      OprMap_ct=i+1;
   }
   OprMap_ct++;
   for(int i=0;i<threeo.size();i++)
   {
       string res = toBinary_six_bit(i+1);
      specifier1[threeo[i]] = res;
      SpecMap1_ct=i+1;
   }
   SpecMap1_ct++;

   for(int i=0;i<fouro.size();i++)
   { 
       string res = toBinary_six_bit(i+1);
      specifier2[fouro[i]] = res;
      SpecMap2_ct=i+1;
   }
   SpecMap2_ct++;
 
   unordered_map<string,string> reverse_inst = reverse_map(inst);
   unordered_map<string,string> reverse_specifier = reverse_map(specifier);
      unordered_map<string,string> reverse_specifier1 = reverse_map(specifier1);
   unordered_map<string,string> reverse_specifier2 = reverse_map(specifier2);
   
   

   write_to_file(reverse_inst,"reverse_inst.txt");
   write_to_file(reverse_specifier,"reverse_specifier.txt");
   write_to_file(reverse_specifier1,"reverse_specifier1.txt");
   write_to_file(reverse_specifier2,"reverse_specifier2.txt");
   /*for(auto x : inst)
   {
      cout<<x.first<<" "<<x.second<<endl;
   }
   for(auto x : specifier)
   {
      cout<<x.first<<" "<<x.second<<endl;
   }*/
   fstream newfile;
   
   string main_encoder = "";
   newfile.open("Vector_Add.ptx",ios::in); //open a file to perform read operation using file object
   if (newfile.is_open()){   //checking whether the file is open
      string tp;
      int var_count = 0;
      while(getline(newfile, tp)){ //read data from file object and put it into string.
         if(tp.length()==0)
            continue;
         trim(tp);
         //regex_replace(tp, regex("^\\s+"), string(""));
//[Benhar]
       //   string first_word_of_line = findNthWord(tp,1);
       // //cout<<"The first word is "<<first_word_of_line<<endl;
       //  if(first_word_of_line == ".param"){
       //   cout<<"Declaration detected"<<endl;
       //   cout<<tp<<endl;
       //   //cout<<"Second word "<<findNthWord(tp,2).substr(1)<<endl;
       //   cout<<"Its encoding : "<<endl;
       //   cout<<param_encode(tp,inst,specifier,variables,var_count)<<endl;
       //   continue;
       //  }

       //  if(first_word_of_line == ".const"){
       //   cout<<"Constant detected"<<endl;
       //   cout<<tp<<endl;
       //   cout<<"Its encoding : "<<endl;
       //   cout<<const_encode(tp,inst,specifier)<<endl;
       //   continue;
       //  }
//[Benhar]

         if((tp[0]>=97 && tp[0]<=123)&&(tp.find('.') != std::string::npos)){
            if(tp[0]=='{')
               continue;
            int i=0;
            string command_name="";
            string second_dot = "";
            string operand = ""; // [piyush]
            string opr_converted = ""; // [piyush]
            while(tp[i]!='.' && tp[i]!='\0' && tp[i]!='\t'&& tp[i]!=' '){ // [piyush]
               command_name+=tp[i];
               i++;
            }

            //cout<<command_name<<" "<<inst[command_name]<<endl;
            // [piyush] Check space for operand
            if(tp[i]=='\t')
               opr=true;
            // [piyush]

            if(inst.find(command_name)!=inst.end())
                main_encoder+=inst[command_name];//+to_string(inst[command_name].length());
            else{
                // cout<<"command_name "<<InsMap_ct<<endl;
                string res = toBinary_eight_bit(InsMap_ct++);
                // InsMap_ct++;
                // cout<<"command_name "<<InsMap_ct<<endl;
                inst[command_name] = res;
                main_encoder+=res;//+to_string(res.length());
            }
            // cout<<"command_name end";

            i++;
         //    if(tp[i]=='.' )
         //    {
         //    i++; 
         //    while(tp[i]!='.' && tp[i]!='\0' && tp[i]!=' '){
         //       second_dot+=tp[i];
               
         //       i++;
         //    }
         //    trim(second_dot);
            
         //    main_encoder=main_encoder+specifier[second_dot];
         //    cout<<second_dot<<" "<<specifier[second_dot]<<endl;
         // }
         // else
         // {
         //    main_encoder=main_encoder+"000000";
         //    cout<<second_dot<<" "<<"pad- 000000"<<endl;
         // }
            while(tp[i]!='.' && tp[i]!='\0' && tp[i]!='\t' && tp[i]!=' '){ // [piyush]
               second_dot+=tp[i];
               i++;
            }
            
            trim(second_dot);
            if(second_dot!="")//(tp[i]=='.'|| isspace(tp[i]))
           {
            if(specifier.find(second_dot)!=specifier.end())
                main_encoder+= specifier[second_dot];//+to_string(specifier[second_dot].length());
            else{
                string res = toBinary_six_bit(SpecMap_ct++);
                specifier[second_dot] = res;
                main_encoder+=res;//+to_string(res.length());
            }
            //cout<<second_dot<<" "<<specifier[second_dot]<<endl;
           }
           else
           {
            main_encoder+="000000";//+to_string(6);
            //cout<<second_dot<<" "<<"pad- 000000"<<endl;
           }
            
            string thirdot="";     
            if(tp[i]=='.')
            {
               i++;
               while(tp[i]!='.' && tp[i]!='\0' && tp[i]!=' '){
                  thirdot+=tp[i];
                  
                  i++;
               }
               
            }
            trim(thirdot);
            // if(thirdot !="")
            //    cout<<thirdot<<endl;

             if(thirdot!="")//(tp[i]=='.' || isspace(tp[i]))
           {
            if(specifier1.find(thirdot)!=specifier1.end())
                main_encoder=main_encoder+specifier1[thirdot];//+to_string(specifier1[thirdot].length());
            else{
                string res = toBinary_six_bit(SpecMap1_ct++);
                specifier1[thirdot] = res;
                main_encoder+=res;//+to_string(res.length());
            }
            
            //cout<<thirdot<<" "<<specifier1[thirdot]<<endl;
           }
           else
           {
            main_encoder=main_encoder+"000000";//+to_string(6);
            //cout<<thirdot<<" "<<"pad 000000"<<endl;
           }

            string fourdot="";
           if(tp[i]=='.')
            {
               i++;
               while(tp[i]!='.' && tp[i]!='\0' && tp[i]!=' '){
                  fourdot+=tp[i];
                  
                  i++;
               }
               
            }
            trim(fourdot);

            // if(fourdot !="")
            //    cout<<fourdot<<endl;

             if(fourdot!="")//(tp[i]=='.' || isspace(tp[i]))
           {
            if(specifier2.find(fourdot)!=specifier2.end())
                main_encoder=main_encoder+specifier2[fourdot];//+to_string(specifier2[fourdot].length());
            else{
                string res = toBinary_six_bit(SpecMap2_ct++);
                specifier2[fourdot] = res;
                main_encoder+=res;//+to_string(res.length());
            }
            
           // cout<<fourdot<<" "<<specifier2[fourdot]<<endl;
           }
           else
           {
            main_encoder=main_encoder+"000000";//+to_string(6);
            //cout<<fourdot<<" "<<"pad 000000"<<endl;
           }

            // [piyush] Check space for operand
            if(tp[i]=='\t')
               opr=true;
            // [piyush]

           // main_encoder+="Operand Start";
            // [piyush] Operand Start
            int op_pad=0;
            while(tp[i]!=';' && tp[i]!='\0'){ // [piyush]
               operand ="";
               op_pad++;
               while(tp[i]!=',' && tp[i]!='\t'&& tp[i]!='\0' &&tp[i]!=';'){
                  operand +=tp[i];
                  i++;
               }
               trim(operand); // trim spaces to get from map
               // if(operand == "")
               //      continue;
               if(opr_map.find(operand)!=opr_map.end()){
                  // opr_converted+="1";
                  // opr_converted+= (" "+opr_map[operand]);
                  opr_converted+= (opr_map[operand]);//+to_string(opr_map[operand].length()); 
               }
               else{
                  string res = toBinary_eight_bit(OprMap_ct++);
                  cout<<operand<<"-"<<endl;
                  opr_map[operand] = res;
                  // main_encoder+=(" "+res);
                  // main_encoder+=(res);//+to_string(res.length());
                  opr_converted+=res;
               }

              cout<< operand << " "<<opr_map[operand]<<endl;
               i++;
            }
             while(op_pad<4)
              { opr_converted+="00000000";//+to_string(8);
               op_pad++;

               }
            //cout<<opr_converted<<endl;

            // [piyush] Operand Ends


            main_encoder=main_encoder+opr_converted;
            trim(main_encoder) ;
         cout<<"Inst "<<tp<<" "<<main_encoder<<"   "<<main_encoder.length()<<endl;
         
            
         }
         else{
            if(Init_Specifier.find(tp)!=opr_map.end())
            {
                main_encoder+=Init_Specifier[tp];
            }
            else{
                string res = toBinary_ten_bit(InitSpec++);
                Init_Specifier[tp] = res;
                main_encoder+=res;
            }
            
            cout<<"-----------Extra Inst "<<" "<<tp<<endl<<main_encoder<<"   "<<main_encoder.length()<<endl;
         }
         Encd_file<< main_encoder<<'\n';//<<"  "<<tp[0]
         main_encoder="";
         /*trim(main_encoder) ;
         cout<<"Inst "<<tp<<" "<<main_encoder<<endl;
         main_encoder="";*/
      }
      
      newfile.close(); //close the file object.
   }


   unordered_map<string,string> reverse_opr_map = reverse_map(opr_map);
   unordered_map<string,string> reverse_Init_Specifier = reverse_map(Init_Specifier);
   write_to_file(reverse_opr_map,"reverse_opr_map.txt");
   write_to_file(reverse_Init_Specifier,"reverse_Init_Specifier.txt");
}


/*vector<string> commands = {add,sub,ld};
int k = 0;
for(int i=0;i<=128;i++){
   string res = func(i);
   h[command[i]] = res;
}*/
