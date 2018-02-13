#include<bits/stdc++.h>
using namespace std;

bool suffixfunction(string pattern, int lengthprefix, int lengthtest, char added,int lengthpattern){
    string prefix=pattern.substr(0,lengthprefix);
    string testing=pattern.substr(0,lengthtest)+added;
    cout<<"TESTING is: "<<testing<<endl;
    if(lengthprefix<lengthpattern){
        testing=testing.substr(0,lengthprefix);
    }
    else{
        testing=testing.substr(1,lengthprefix);
    }
    cout<<"TESTING (trimmed) is: "<<testing<<endl;
    cout<<"PREFIX is: "<<prefix<<endl;
    if(prefix.compare(testing)==0){
        return true;
    }
    else{
        return false;
    }
}

void createtransition(map <pair<int,char>,char> hashtransition,string pattern,int lengthpattern,vector<char> alphabet, int lengthalphabet){
    for(int i=0;i<lengthpattern+1;i++){
        for(int j=0;j<lengthalphabet;j++){
            int k=min(i+1,lengthpattern);
            while(!suffixfunction(pattern,k,i,alphabet[j],lengthpattern)){
                k--;
                //cout<<k<<endl;
            }
            pair<int,char> transition = {i,alphabet[j]};
            cout<<"SIGMA("<<transition.first<<","<<transition.second<<")="<<k<<endl;
            hashtransition.insert({transition,k});
        }
    }
}

int main(){
    string pattern;
    string reading;
    string completealphabet;
    cin>>completealphabet;
    cin>>pattern;
    cin>>reading;
    int lengthpattern=pattern.length();
    int lengthreading=reading.length();
    int lengthalphabet=completealphabet.length();
    vector<char> alphabet;
    for(int i=0;i<lengthalphabet;i++){
        alphabet.push_back(completealphabet.at(i));
    }
    map <pair<int,char>,char> hashtransition;
    createtransition(hashtransition,pattern,lengthpattern,alphabet,lengthalphabet);
    cout<<"EVERYTHING CORRECT";
    for(int i=0;i<lengthpattern+1;i++){
        //cout<<hashtransition.at({i,'a'})<<endl;
        //cout<<hashtransition.at({i,'b'})<<endl;
    }
    return 0;
}
