#include <iostream>
#include <string>
#include <cstdio>
#include "CPU.h"
#include "readinstruction.cpp"


#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/filewritestream.h"
#include "include/rapidjson/prettywriter.h"
#include "include/rapidjson/filereadstream.h"
#include "write_Json.cpp"

using namespace std; 
 
bool writeJson(CPU &temp_cpu);
string readinstruction();

int main(){
    string s;
    s = readinstruction();
    int slen = s.size();
    CPU cpu(s);
    bool tag = false; 
    cpu.storeInstruct(); 
    cout<<"{\"data\": ";
    cout<<"[";
    while(cpu.getPC() < (slen)/2){
        
        cpu.fetch();
        if (cpu.get_stat() == HLT) {cout<<",";writeJson(cpu);break;}
        if (cpu.get_stat() == INS) {cerr << "illegal instruction!" << endl; cout<<",";writeJson(cpu);break;}
        cpu.decode();
        cpu.execute();
        if (cpu.get_stat() == INS) {cerr << "illegal instruction!" << endl; cout<<",";writeJson(cpu);break;}
        cpu.memory();
        cpu.writeback();
        if (cpu.get_stat() == ADR) {cerr << "illegal address!" << endl; cout<<",";writeJson(cpu);break;}
        if (cpu.get_stat() == INS) {cerr << "illegal instruction!" << endl; cout<<",";writeJson(cpu);break;}
        cpu.PCupdate();
        if((cpu.get_stat() == AOK)&&tag == true) cout<<",";
        tag = writeJson(cpu);
    }
    cout<<"]"<<"}";
    return 0;
}