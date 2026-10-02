#include<bits/stdc++.h>
using namespace std;

int manual_xor(int x, int y){
    int res = 0;
    int a = 1;
    while(x || y){
        int x_bit = x & 1;
        int y_bit = y & 1;

        if(x_bit != y_bit)
            res += a;
        a *= 2;
        x >>= 1;
        y >>= 1;
    }
    return res;
}

string encrypt(string text, string key){
    string res = "";

    for(int i = 0; i < text.size(); i++){
        //res += text[i] ^ key[i]; 
        res += manual_xor(text[i], key[i]);
    }

    return res;
}


string decrypt(string text, string key){
    string res = "";

    for(int i = 0; i < text.size(); i++){
        //res += text[i] ^ key[i]; 
        res += manual_xor(text[i], key[i]);
    }

    return res;
}


int main(){

    string plaintext;
    getline(cin, plaintext);
    string key;
    getline(cin, key);

    cout << "Plaintext: " << plaintext << "\n";

    string ciphertext = encrypt(plaintext, key);

    cout << "Encrypted: ";
    for(unsigned char c: ciphertext){
        printf("%02x", c);
    }

    cout<< endl;

    cout << "Decrypted: " << decrypt(ciphertext, key) << "\n";

    return 0;
}
