#include<bits/stdc++.h>
using namespace std;

 string toBinary(int x){
     string r = "";
     for(int i=0;i<8;i++){
         if(x%2== 0)
             r = "0" + r;
         else
             r = "1" + r;
         x/=2;
     }
     return r;
 }

int toDecimal(string s){
    int r = 0;
    int a = 1;

    for(int i = 7; i >= 0; i--){
        if(s[i]=='1')
            r+=a;
        a*=2;
    }
    return r;
}

string manual(string a, string b){
    string r="";
    for(int i=0; i < a.size();i++){
        if(a[i] == b[i])
            r += '0';
        else
            r += '1';
    }
    return r;
}


string encrypt(string text, string key){
    string enc = "";
    for(int i=0;i<text.size();i++){
        string tb = toBinary(text[i]);
        string kb = toBinary(key[i]);

        string res = manual(tb, kb);
        int resd = toDecimal(res);
        enc += resd;
    }
    return enc;
}


string decrypt(string text, string key){
    string dec= "";
    for(int i=0;i<text.size();i++){
        string tb = toBinary(text[i]);
        string kb = toBinary(key[i]);

        string res = manual(tb, kb);
        int resd = toDecimal(res);
        dec += resd;
    }
    return dec;
}



int main(){

    string arr[2][2] = {{"kuet", "rert"},
                        {"buet", "cuet"}};

    string trans[2][2];

    for(int i=0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            trans[i][j] = arr[j][i];
        }
    }

    string key[2][2] = {{"eidd", "jend"}, {"jdje", "kjdj"}};

    string enc[2][2];

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            enc[i][j] = encrypt(trans[i][j], key[i][j]);
        }
    }

    string dec[2][2];
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            dec[i][j] = encrypt(enc[i][j], key[i][j]);
        }
    }

    string trans_back[2][2];
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            trans_back[i][j] = dec[j][i];
        }
    }

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            cout << trans_back[i][j] << " ";
        }
        cout << endl;
    }   

    return 0;
}