#include<bits/stdc++.h>
using namespace std;

int norm(int x, int m){
    return (x%m + m)%m;
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
    string c = "khoor567";
    
    int lcm = 26 * 10 / __gcd(26, 10);
    for(int key = 0; key < lcm; key++){
        cout << "Key: " << key << " " << "decrypted text: " << decrypt(c, key) << endl;
    }
    return 0;
}