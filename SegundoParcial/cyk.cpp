#include<iostream>
#include<cstring>
#include<algorithm>
#include<string>
#include<sstream>
#include<iomanip>
using namespace std;
#define MAX 100
#define for(i,a,b) for(i=a;i<b; i++)//For easier declarations

string gram[MAX][MAX];  //to store entered grammar
int np;       //np-> number of productions


inline string concat(string a, string b)   //concatenates unique non-terminals
{
    int i;
    string r=a;
    for(i,0,b.length())
        if(r.find(b[i]) > r.length())
            r+=b[i];
    return (r);
}
inline string search_prod(string p) //returns a concatenated string of variables which can produce string p
{
    int j,k;
    string r="";
    for(j,0,np)
    {
        k=1;
        while(gram[j][k] != "")
        {
            if(gram[j][k] == p)
            {
                r=concat(r,gram[j][0]);
            }
            k++;
        }
    }
    return r;
}

inline string gen_comb(string a, string b)  //creates every combination of variables from a and b . For eg: BA * AB = {BA, BB, AA, BB}
{
    int i,j;
    string pri=a,re="";
    for(i,0,a.length())
        for(j,0,b.length())
        {
            pri="";
            pri=pri+a[i]+b[j];
            re=re+search_prod(pri);     //searches if the generated productions can be created or not
        }
    return re;
}

int main(){
    int flagP=1,i=0,j,l,k,flag;
    // cout<<"hola mundo";
    string a,str,r,pr,start;
    string matrix[MAX][MAX],st;
    np=0;
    while(true){
        if(flagP){
            getline(cin,a);
            istringstream iss(a);
        }
        flag=1;
        if(a[0]>='A' && a[0]<='Z' && flagP){//Reads productions
            for(j,0,MAX){
                int sp=a.find(" ");
                if(sp!=-1){
                    gram[i][j]=a.substr(0,sp);
                    a=a.substr(sp+1,a.length());
                }
                else if(flag){
                    gram[i][j]=a;
                    a="";
                    flag=0;
                }
                else{
                    gram[i][j]="";
                }

            }

            np++;
        }
        else{
            if(flagP){
                start=gram[0][0];//Sets S
                flagP=0;
            }
            str=a;
            for(i,0,str.length())       //Assigns values to principal diagonal of matrix
            {
                r="";
                st = "";
                st+=str[i];
                for(j,0,np)
                {
                    k=1;
                    while(gram[j][k] != "")
                    {
                        if(gram[j][k] == st)
                        {
                            r=concat(r,gram[j][0]);
                        }
                        k++;
                    }
                }
                matrix[i][i]=r;
            }
            for(k,1,str.length())       //Assigns values to upper half of the matrix
            {
                for(j,k,str.length())
                {
                    r="";
                    for(l,j-k,j)
                    {
                        pr = gen_comb(matrix[j-k][l],matrix[l+1][j]);
                        r = concat(r,pr);
                    }
                    matrix[j-k][j] = r;
                }
            }

            // for(i,0,str.length())   //Prints the matrix
            // {
            //     k=0;
            //     l=str.length()-i-1;
            //     for(j,l,str.length())
            //     {
            //         cout<<setw(5)<<matrix[k++][j]<<" ";
            //     }
            //     cout<<endl;
            // }

            int f=0;
            for(i,0,start.length())            	 
                if(matrix[0][str.length()-1].find(start[i]) <= matrix[0][str.length()-1].length())  
                {//Checks if last element of first row contains a Start variable
                    cout<<"Accepted\n";
                }else{
                    cout<<"Rejected\n";
                }
            cin>>a;
            if(cin.eof()){
                return 0;//condition for break
            }

        }
        i++;

    }
    return 0;
}


