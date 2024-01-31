#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>

#include"CPU.h"

using namespace std;


CPU::CPU(string str){
    s = str;
    str_length = s.length();
    PC = 0;
    ZF = 1;
    SF = OF = 0;
    for(int i = 0; i < REG_SIZE; i++){
        reg[i] = 0;
    }
    memset(mem, 0, MEM_SIZE);
    stat = 1;
    for(int i = 0;i < S;i++){
        cache[i].dirty = 0;
        cache[i].valid = 0;
        cache[i].tag = 0;
        memset(cache[i].block,0,16);
    }
}

bool CPU::storeInstruct(){
    string temp_s = s;
    int temp_PC = 0;
    int temp_s_len = temp_s.size();
    for (int i = 0; i < temp_s_len; i += 2, temp_PC++){
        uint8_t temp_code_1, temp_code_2;
        temp_code_1 = (uint8_t)s[i]; temp_code_2 = (uint8_t)s[i + 1];
        if (temp_code_1>='0' && temp_code_1<='9'){
            temp_code_1 -= '0';
        } else if (temp_code_1>='a' && temp_code_1<='f'){
            temp_code_1 = temp_code_1 - 'a' + 10;
        } else if (temp_code_1>='A' && temp_code_1<='F'){
            temp_code_1 = temp_code_1 - 'A' + 10;
        }
        else return false;
        if (temp_code_2>='0' && temp_code_2<='9'){
            temp_code_2 -= '0';
        } else if (temp_code_2>='a' && temp_code_2<='f'){
            temp_code_2 = temp_code_2 - 'a' + 10;
        } else if (temp_code_2>='A' && temp_code_2<='F'){
            temp_code_2 = temp_code_2 - 'A' + 10;
        }
        else return false;
        mem[temp_PC] = (temp_code_1<<4) + temp_code_2;
    }
    return true;
}

uint64_t CPU::read_reg(int name){
    if(name >= REG_SIZE||name < 0){stat = ADR;return 0;}
    return reg[name];
}

bool CPU::write_reg(uint64_t val, int name){
    if(name >= REG_SIZE||name < 0){stat = ADR;return false;}
    reg[name] = val;
    return true;
}

uint64_t CPU::read_mem(uint64_t pos){
    if (pos + 7 >= MEM_SIZE||pos < 0) {stat = ADR;return 0;}
    uint64_t return_mem = 0;
    for (int i = 7; i >= 0; i--){
        return_mem *= 256;
        return_mem += mem[pos + i];
    }
    return return_mem;
}

uint64_t CPU::read_mem_(uint64_t pos){
    return read_mem(pos);
}

bool CPU::write_mem(uint64_t val,uint64_t pos){
    if(pos + 7 >= MEM_SIZE||pos < 0) {stat = ADR;return false;}
    for (int i = 0; i < 8; i++){
        uint8_t temp_mem;
        temp_mem = (uint8_t)(val & 0xff);
        mem[pos + i] = temp_mem;
        val = val >> 8;
    }
    return true;
}

uint64_t CPU::read_cache_8bits(uint64_t pos){
    if (pos + 7 >= MEM_SIZE||pos < 0) {stat = ADR;return 0;}
    uint8_t temp_s,temp_b;;
    bitset<56> temp_t;
    temp_b = pos &0x0f;
    temp_s = (pos>>4) & 0x0f;
    temp_t = (pos>>8) & 0xffffffffffffff;
    if((cache[temp_s].tag == temp_t)&&cache[temp_s].valid == 1){
        uint64_t return_val = 0;
        for (int i = 7; i >= 0; i--){
            return_val *= 256;
            return_val += cache[temp_s].block[temp_b + i];
        }
        return return_val;
    }
    else{
        uint64_t temp_pos = pos &0xfffffffffffffff0;
        for(int i = 0;i < B;i++){
            cache[temp_s].block[i] = mem[temp_pos + i];
        }
        cache[temp_s].valid = 1;
        cache[temp_s].tag = temp_t;
        return read_cache_8bits(pos);
    }
}

uint8_t CPU::read_cache_bit(uint64_t pos){
    if (pos >= MEM_SIZE||pos < 0) {stat = ADR;return 0;}
    uint8_t temp_s,temp_b;;
    bitset<56> temp_t;
    temp_b = pos & 0x0f;
    temp_s = (pos>>4) & 0x0f;
    temp_t = (pos>>8) & 0xffffffffffffff;
    if((cache[temp_s].tag == temp_t)&&cache[temp_s].valid == 1){
        return cache[temp_s].block[temp_b];
    }
    else{
        uint64_t temp_pos = pos & 0xfffffffffffffff0;
        for(int i = 0;i < B;i++){
            cache[temp_s].block[i] = mem[temp_pos + i];
        }
        cache[temp_s].valid = 1;
        cache[temp_s].tag = temp_t;
        return cache[temp_s].block[temp_b];
    }
}

bool CPU::write_cache_8bits(uint64_t val,uint64_t pos){
    if(pos + 7 >= MEM_SIZE||pos < 0) {stat = ADR;return false;}
    uint8_t temp_s,temp_b;;
    bitset<56> temp_t;
    temp_b = pos & 0x0f;
    temp_s = (pos>>4) & 0x0f;
    temp_t = (pos>>8) & 0xffffffffffffff;
    uint8_t temp_val;
    if((cache[temp_s].tag == temp_t)&&cache[temp_s].valid == 1){
        for(int i = 0;i < 8;i++){
            temp_val = (uint8_t)(val & 0xff);
            cache[temp_s].block[temp_b + i] = temp_val;
            mem[pos + i] = temp_val;
            val = val>>8;
        }
        cache[temp_s].dirty = 1;
    }
    else{
        write_mem(val,pos);
        uint64_t temp_pos = pos & 0xfffffffffffffff0;
        for(int i = 0;i < B;i++){
            cache[temp_s].block[i] = mem[temp_pos + i];
        }
        cache[temp_s].valid = 1;
        cache[temp_s].tag = temp_t;
    }
    return true;
}

void CPU::fetch(){
    uint8_t icode_ifun = read_cache_bit(PC);
    icode = ((icode_ifun & 0xf0) >> 4) & 0x0f;
    ifun = (icode_ifun & 0x0f);
    switch (icode){
        case 0x00:
            stat = HLT;
            break;
        case 0x01:
        case 0x09:
            valP = 1 + PC;
            break;
        case 0x02:
        case 0x06:
        case 0x0a:
        case 0x0b:
            if((PC + 1) <= str_length/2){
                rA = (read_cache_bit(PC + 1) >> 4) & 0x0f;
                rB = (read_cache_bit(PC + 1) & 0x0f);
                valP = 2 + PC;
            }
            else stat = INS;
            break;
        case 0x03:
        case 0x04:
        case 0x05:
            if((PC + 9) <= str_length/2){
                rA = ((read_cache_bit(PC + 1) & 0xf0) >> 4) & 0x0f;
                rB = (read_cache_bit(PC + 1) & 0x0f);
                for (int i = 0; i<8; i++){
                    valC *= 256;
                    valC += read_cache_bit(PC + 9 - i);
                }
                valP = 10 + PC;
            }
            else stat = INS;
            break;
        case 0x07:
        case 0x08:
            if((PC + 8) <= str_length/2){
                for (int i = 0; i<8; i++){
                    valC *= 256;
                    valC += read_cache_bit(PC + 8 - i);
                }
                valP = 9 + PC;
            }
            else stat = INS;
            break;
        case 0x0c:
            if((PC + 9) <= str_length/2){
                    rB = (read_cache_bit(PC + 1) & 0x0f);
                    for (int i = 0; i<8; i++){
                        valC *= 256;
                        valC += read_cache_bit(PC + 9 - i);
                    }
                    valP = 10 + PC;
                }
            else stat = INS;
            break;
        default:
            stat = INS;
    }
}

void CPU::decode(){
    switch (icode){
        case 0x02:
        case 0x03:
        case 0x04:
        case 0x06:
            valA = reg[rA];
            valB = reg[rB];
            break;
        case 0x05:
            valB = reg[rB];
            break;
        case 0x08:
        case 0x09:
            valA = reg[4];
            valB = reg[4];
            break;
        case 0x0a:
            valA = reg[rA];
            valB = reg[4];
            break;
        case 0x0b:
            valA = reg[4];
            valB = reg[4];
            break;
        case 0x0c:
            valB = reg[rB];
        default:
            return;
    }
}

void CPU::execute(){
    if(icode == 1)return;
    if(icode == 2){
        valE = valA;
        Cnd = IsJumpOrMov();
    }
    if(icode == 3) valE = valC;
    if(icode == 4 || icode == 5) valE = valB + valC;
    if(icode == 6) ALU();
    if(icode == 7) Cnd = IsJumpOrMov();
    if(icode == 8) valE = valB - 8;
    if(icode == 9) valE = valB + 8;
    if(icode == 0xA) valE = valB - 8;
    if(icode == 0xB) valE = valB + 8;
    if(icode == 0xC) {
        valE = valB + valC;
        int64_t b,c,e;
        b = valB;
        c = valC;
        e = valE;
        if((b > 0 && c > 0 && e < 0)||(b < 0 && c < 0 && e >= 0))
            OF = 1;
        else OF = 0;
        if(valE == 0) ZF = 1;
        else ZF = 0;
        if(e < 0) SF = 1;
        else SF = 0;
    }
}

void CPU::ALU(){
    if(ifun == 0) {
        valE = valB + valA;
        int64_t a,b,e;
        a = valA;
        b = valB;
        e = valE;
        if((b > 0 && a > 0 && e < 0)||(b < 0 && a < 0 && e >= 0))
            OF = 1;
        else OF = 0;
    }
    else if(ifun == 1) {
        valE = valB - valA;
        int64_t a,b,e;
        a = valA;
        b = valB;
        e = valE;
        if((b > 0 && a < 0 && e < 0)||(b < 0 && a > 0 && e > 0))
            OF = 1;
        else OF = 0;
    }
    else if(ifun == 2) valE = valB & valA;
    else if(ifun == 3) valE = valB ^ valA;
    else stat = INS;

    if(valE == 0) ZF = 1;
    else ZF = 0;

    int64_t e = valE;
    if(e < 0) SF = 1;
    else SF = 0;
}

bool CPU::IsJumpOrMov(){
    if(ifun == 0) return true;
    if(ifun == 1) return ((SF ^ OF) | ZF) ? true : false;
    if(ifun == 2) return (SF ^ OF) ? true :false;
    if(ifun == 3) return ZF ? true : false;
    if(ifun == 4) return (ZF==0) ? true : false;
    if(ifun == 5) return ((SF ^ OF)==0) ? true : false;
    if(ifun == 6) {
        if((ZF == 0)&&((SF ^ OF) == 0)) return true;
        else return false;
    }
    else stat = INS;
    return false;
}


void CPU::memory(){
    if(icode == 1)return;
    if(icode == 4) write_cache_8bits(valA,valE);
    if(icode == 0xA) write_cache_8bits(valA,valE);
    if(icode == 5) valM = read_cache_8bits(valE);
    if(icode == 8) write_cache_8bits(valP,valE);
    if(icode == 9) valM = read_cache_8bits(valA);
    if(icode == 0xB) valM = read_cache_8bits(valA);
}

void CPU::writeback(){
    if(icode == 1) return;
    if(icode == 2 && Cnd == true) write_reg(valE,rB);
    if(icode == 3 || icode == 6) write_reg(valE,rB);
    if(icode == 8 || icode == 9||icode == 0xA||icode == 0xB) write_reg(valE,4);
    if(icode == 5 || icode == 0xB) write_reg(valM,rA);
    if(icode == 0xC) write_reg(valE,rB);
}

void CPU::PCupdate(){
    if(icode == 7 && Cnd == true) PC = valC;
    else if (icode == 8) PC = valC;
    else if (icode == 9) PC = valM;
    else PC = valP;
}

uint64_t CPU::getPC(){
    return PC;
}

int CPU::get_stat(){
    return stat;
}

uint64_t * CPU::getREG(){
    return reg;
}

int CPU::get_ZF(){
    return ZF;
}

int CPU::get_SF(){
    return SF;
}

int CPU::get_OF(){
    return OF;
}

CACHE * CPU::get_cache(){
    return cache;
}

