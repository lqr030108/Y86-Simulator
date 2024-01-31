#ifndef Y86_CPU_H
#define Y86_CPU_H

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <bitset>
using namespace std;

const int MEM_SIZE = 0x10000;
const int REG_SIZE = 0x10;
const int AOK = 1;
const int HLT = 2;
const int ADR = 3;
const int INS = 4;
const int S = 16;
const int B = 16;

struct CACHE{
    bitset<1> dirty,valid;
    bitset<56> tag;
    uint8_t block[16];
};

class CPU{
private:
    string s;
    int str_length;
    uint8_t icode, ifun;
    uint8_t rA, rB;
    uint64_t valA, valB, valC, valP, valE, valM;
    uint64_t PC;
    uint64_t reg[REG_SIZE];
    uint8_t mem[MEM_SIZE];
    CACHE cache[16];
    int stat;
    int ZF, SF, OF;
    bool Cnd;
    uint64_t read_reg(int name);
    bool write_reg(uint64_t val, int name);
    uint64_t read_mem(uint64_t pos);
    bool write_mem(uint64_t val, uint64_t pos);
public:
    CPU(string str);
    bool storeInstruct();
    void fetch();
    void decode();
    void execute();
    void ALU();
    bool IsJumpOrMov();
    void memory();
    void writeback();
    void PCupdate();
    uint64_t getPC();
    int get_stat();
    uint64_t *getREG();
    uint64_t read_mem_(uint64_t pos);
    uint64_t read_cache_8bits(uint64_t pos);
    uint8_t read_cache_bit(uint64_t pos);
    bool write_cache_8bits(uint64_t val,uint64_t pos);
    int get_ZF();
    int get_SF();
    int get_OF();
    CACHE *get_cache();
};
#endif