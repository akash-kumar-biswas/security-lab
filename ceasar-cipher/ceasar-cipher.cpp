#include<bits/stdc++.h>
using namespace std;

int norm(int x, int m){
    return (x%m + m)%m;
}

string encrypt(string text, int s){
    string res="";

    for(auto c: text){
        if('A' <= c && c <= 'Z')
            res += (c - 'A' + s) % 26 + 'A';
        else if('a' <= c && c <= 'z')
            res += (c - 'a' + s) % 26 + 'a';  
        else if('0' <= c && c <= '9')  
            res += (c - '0' + s) % 10 + '0';
        else
            res += c;
        
    }

    return res;
}


string decrypt(string text, int s){
    string res="";

    for(auto c: text){
        if('A' <= c && c <= 'Z')
            res += norm(c - 'A' - s, 26) + 'A';
        else if('a' <= c && c <= 'z')
            res += norm(c - 'a' - s, 26) + 'a';  
        else if('0' <= c && c <= '9')  
            res += norm(c - '0' - s, 10) + '0';
        else
            res += c;
        
    }

    return res;
}

int main(){
    string p = "khoor567";
    int key = 3;

    cout << "decrypted text: " << decrypt(p, 3);
}