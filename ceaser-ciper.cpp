#include <iostream>
#include <string>
using namespace std;
string encrypt(string text, int s){
    string result = "";
    for( char c : text){
        if (c>='A' && c<= 'Z'){
            result += char(int(c -'A' + s) %26) + 'A';
        } else if(c>='a' && c<='z'){
            result += char(int(c - 'a' + s) %26) +'a';
        } else if(c>='0' && c<='9'){
            result += char(int(c - '0' + s) % 10) + '0';
        } else{
            result += c;
        }
    }
    return result;
}
 string decrypt(string text, int s){
    string result = "";
    for( char c : text){
        if (c>='A' && c<= 'Z'){
            result += char(int(c -'A' - s + 26) %26) + 'A';
        } else if(c>='a' && c<='z'){
            result += char(int(c - 'a' - s + 26) %26) +'a';
        } else if(c>='0' && c<='9'){
            result += char(int(c - '0' - s + 10) % 10) + '0';
        } else{
            result += c;
        }
 }
    return result;
}
int main(){
    cout<< "Enter the text to encrypt: ";
    string text;
    getline(cin, text);
    cout<< "Enter the shift value: ";
    int s;
    cin>> s;
    string encrypted_text = encrypt(text, s);
    string decrypted_text = decrypt(encrypted_text, s);
    cout<< "Encrypted text: " << encrypted_text << endl;
    cout<< "Decrypted text: " << decrypted_text << endl;
    return 0;
}