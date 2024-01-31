#include <iostream>
#include <string>
using namespace std;
string readinstruction(){
    char c;
    int PCval = 0;
    int i = 0, j = 0;
    string s = "";
    while ((c = cin.get()) != EOF)
    {
        if (c != '0') while ((c = cin.get()) != '\n');
        else {
            c = cin.get();//得x
            char c1, c2, c3;
            c1 = cin.get(); c2 = cin.get(); c3 = cin.get();//得PC的3位
            if (c1 >='0' && c1 <='9') PCval += (c1 - '0') * 256;
            if (c1 >='a' && c1 <='f') PCval += (c1 - 'a' + 10) * 256;
            if (c2 >='0' && c2 <='9') PCval += (c2 - '0') * 16;
            if (c2 >='a' && c2 <='f') PCval += (c2 - 'a' + 10) * 16;
            if (c3 >='0' && c3 <='9') PCval += (c3 - '0');
            if (c3 >='a' && c3 <='f') PCval += (c3 - 'a' + 10);//计算PC值
            if (i != PCval){
                int distance = PCval - i;
                for (int k = 1; k <= distance; k++){
                    s.push_back('0'); s.push_back('0');
                    i++;
                }
            }
            c = cin.get();//得:
            c = cin.get();//得空格
            while ((c = cin.get()) != ' '){
                s.push_back(c);
                j ++;
            }
            i += j/2; j = 0; PCval = 0;
        }
    }
    return s;
}
