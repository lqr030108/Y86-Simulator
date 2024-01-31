#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include "CPU.h"
#include "CPU.cpp"
#include <bitset>
#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/filewritestream.h"
#include "include/rapidjson/prettywriter.h"
#include "include/rapidjson/filereadstream.h"

bool writeJson(CPU &temp_cpu){

    rapidjson::Document jsonDoc;    //生成一个dom元素Document
    rapidjson::Document::AllocatorType &allocator = jsonDoc.GetAllocator(); //获取分配器
    jsonDoc.SetObject();

    rapidjson::Value REG(rapidjson::kObjectType);
    REG.SetObject();

    uint64_t *Reg;
    Reg = temp_cpu.getREG();
    REG.AddMember("rax",(int64_t)Reg[0],allocator);
    REG.AddMember("rcx",(int64_t)Reg[1],allocator);
    REG.AddMember("rdx",(int64_t)Reg[2],allocator);
    REG.AddMember("rbx",(int64_t)Reg[3],allocator);
    REG.AddMember("rsp",(int64_t)Reg[4],allocator);
    REG.AddMember("rbp",(int64_t)Reg[5],allocator);
    REG.AddMember("rsi",(int64_t)Reg[6],allocator);
    REG.AddMember("rdi",(int64_t)Reg[7],allocator);
    REG.AddMember("r8",(int64_t)Reg[8],allocator);
    REG.AddMember("r9",(int64_t)Reg[9],allocator);
    REG.AddMember("r10",(int64_t)Reg[10],allocator);
    REG.AddMember("r11",(int64_t)Reg[11],allocator);
    REG.AddMember("r12",(int64_t)Reg[12],allocator);
    REG.AddMember("r13",(int64_t)Reg[13],allocator);
    REG.AddMember("r14",(int64_t)Reg[14],allocator);

    rapidjson::Value MEM(rapidjson::kObjectType);
    MEM.SetObject();
    int64_t temp_mem;
    string temp;
    for(int temp_pos = 0;temp_pos < MEM_SIZE;temp_pos = temp_pos + 8){
        temp_mem = temp_cpu.read_mem_(temp_pos);
        if(temp_mem != 0){
            temp = to_string(temp_pos);
	        rapidjson::Value v(rapidjson::kStringType);
	        v.SetString(temp.c_str(), temp.size(), allocator); 
            MEM.AddMember(v,temp_mem,allocator);
        }
    }

    rapidjson::Value CC(rapidjson::kObjectType);
    CC.SetObject();

    CC.AddMember ("ZF",temp_cpu.get_ZF(),allocator);
    CC.AddMember ("SF",temp_cpu.get_SF(),allocator);
    CC.AddMember ("OF",temp_cpu.get_OF(),allocator);

    rapidjson::Value cache(rapidjson::kObjectType);
    cache.SetObject();

    CACHE *temp_cache;
    temp_cache = temp_cpu.get_cache();

    for(int i = 0;i < S;i++){
        rapidjson::Value everyvalue(rapidjson::kArrayType);
        everyvalue.SetArray();
        bitset<1> temp_valid = temp_cache[i].valid;
        bitset<56> temp_tag = temp_cache[i].tag;
        string temp_valid_str,temp_tag_str;
        temp_valid_str = temp_valid.to_string();
        temp_tag_str = temp_tag.to_string();
        rapidjson::Value val_valid(rapidjson::kObjectType);
        rapidjson::Value val_tag(rapidjson::kObjectType);
        val_valid.AddMember("valid", rapidjson::Value(temp_valid_str.c_str(), allocator), allocator);
        everyvalue.PushBack(val_valid,allocator);
        val_tag.AddMember("tag", rapidjson::Value(temp_tag_str.c_str(), allocator), allocator);
        everyvalue.PushBack(val_tag,allocator);
        rapidjson::Value everyblock(rapidjson::kArrayType);
        everyblock.SetArray();
        for(int j = 0;j < B;j++){
            everyblock.PushBack(temp_cache[i].block[j],allocator);
        }
        rapidjson::Value block(rapidjson::kObjectType);
        block.AddMember("block",everyblock,allocator);
        everyvalue.PushBack(block,allocator);
        string temp_s;
        temp_s = to_string(i);
	    rapidjson::Value val(rapidjson::kStringType);
        val.SetString(temp_s.c_str(), temp_s.size(), allocator);
        cache.AddMember(val,everyvalue,allocator);
    }

    //https://www.jianshu.com/p/2e24dedd2f93
          
    jsonDoc.AddMember("PC", temp_cpu.getPC(), allocator);
    jsonDoc.AddMember("REG", REG, allocator);
    jsonDoc.AddMember("MEM", MEM, allocator);
    jsonDoc.AddMember("CC", CC, allocator);
    jsonDoc.AddMember("STAT", temp_cpu.get_stat(), allocator);
    jsonDoc.AddMember("cache",cache,allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    jsonDoc.Accept(writer);

    std::string command_string = buffer.GetString();
    std::cout<<command_string<<std::endl;
    return true;
}