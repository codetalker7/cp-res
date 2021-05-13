
/*
	 template by: codetalker7
	 editor: sublime text 3
	 file name: TCTCTOE
	 date created: 2021-05-07 17:58:21
	 problem link: https://www.codechef.com/MAY21C/problems/TCTCTOE
*/
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<stack>
#include<unordered_set>
#include<cmath>
#include<numeric>
#include<iterator>
#include<set>
#include<unordered_map>
#include<map>
#include<queue>
#include<cstring>
#include<stdio.h>
#include<fstream>
#include<iomanip>
#include<functional>
#include<bitset>
#include<chrono>
#include<climits>
#include<assert.h>
using namespace std;

//type declarations
using ll = long long int;
using ull = unsigned long long int;
using vint = vector<int>;
using vll = vector<ll>;
using vch = vector<char>;
using vs = vector<string>;
using sll = set<ll>;
using msll = multiset<ll>;
using ldb = long double;

//constants
const ll MOD = 1000000007;
const ll INF = 1e18;
const int INFINT = 1e9 + 5;
const ldb PI = 3.14159265359;

//some useful algos
template <class T> T mceil(T a, T b){return (a % b == 0) ? a/b : a/b + 1;}
template <class T> T expo(T base , T exp , T mod){T res = 1;base = base % mod;while (exp > 0){if (exp & 1)res = (res*base) % mod;exp = exp>>1;base = (base*base) % mod;}return res;}
template <class T> ll maxpower(T a , T b){ll ans = 0;while(a > 0 && a % b == 0){ans++;a /= b;}return ans;}
template <class T> T extgcd(T a, T b , T &x , T &y) {x = 1, y = 0;T x1 = 0, y1 = 1, a1 = a, b1 = b; while (b1) { T q = a1 / b1; tie(x, x1) = make_tuple(x1, x - q * x1); tie(y, y1) = make_tuple(y1, y - q * y1); tie(a1, b1) = make_tuple(b1, a1 - q * b1);}return a1;}
template <class T> T modinv (T a , T m , T &x , T &y){T g = extgcd(a , m , x , y); if (g != 1) cerr << "Division by zero!"; else x = (x % m + m) % m; return x;}
template <class T> T signed_floor(T a , T b){if (a >= 0 && b >= 0) return a/b; else if (a < 0 & b < 0) return (-a)/(-b); else if (a < 0 & b >= 0){if (a % b == 0) return -((-a)/b); else return -((-a)/b) - 1;} else if (a >= 0 && b < 0){if(a % b == 0) return -(a/(-b)); else return -(a/(-b)) - 1;}}
template <class T> pair<T,T> log_base_2(T n){T temp = 1 , k = 0; while(temp <= n){temp <<= 1; k++;} temp >>= 1; k--; return {k , temp};}
//define global variables here

char g[4][4];

ll get_pairs(char x){
    ll temp = 0;

    //checking if rows are equal
    if (g[1][1] == x && g[1][1] == g[1][2] && g[1][2] == g[1][3]){
        temp++;
    }
    if (g[2][1] == x && g[2][1] == g[2][2] && g[2][2] == g[2][3]){
        temp++;
    }
    if (g[3][1] == x && g[3][1] == g[3][2] && g[3][2] == g[3][3]){
        temp++;
    }

    //checking if columns are equal
    if (g[1][1] == x && g[1][1] == g[2][1] && g[2][1] == g[3][1]){
        temp++;
    }
    if (g[1][2] == x && g[1][2] == g[2][2] && g[2][2] == g[3][2]){
        temp++;
    }
    if (g[1][3] == x && g[1][3] == g[2][3] && g[2][3] == g[3][3]){
        temp++;
    }

    //checking diagonals
    if (g[1][1] == x && g[1][1] == g[2][2] && g[2][2] == g[3][3]){
        temp++;
    }
    if (g[3][1] == x && g[3][1] == g[2][2] && g[2][2] == g[1][3]){
        temp++;
    }
    return temp;
}

ll handle_special_cases(){
    string str1 , str2 , str3;
    str1.push_back(g[1][1]); str1.push_back(g[1][2]); str1.push_back(g[1][3]);
    str2.push_back(g[2][1]); str2.push_back(g[2][2]); str2.push_back(g[2][3]);
    str3.push_back(g[3][1]); str3.push_back(g[3][2]); str3.push_back(g[3][3]);

    //special case 1
    if (str1.compare("XXX") == 0 &&
        str2.compare("OXO") == 0 && 
        str3.compare("OXO") == 0
        )
        return 1;
    //special case 2
    if (str1.compare("XXX") == 0 &&
        str2.compare("XOO") == 0 && 
        str3.compare("XOO") == 0
        )
        return 1;
    //special case 3
    if (str1.compare("XXX") == 0 &&
        str2.compare("OOX") == 0 && 
        str3.compare("OOX") == 0
        )
        return 1;
    //special case 4
    if (str1.compare("XOO") == 0 &&
        str2.compare("XXX") == 0 && 
        str2.compare("XOO") == 0
        )
        return 1;
    //special case 5
    if (str1.compare("OXO") == 0 &&
        str2.compare("XXX") == 0 && 
        str3.compare("OXO") == 0
        )
        return 1;
    //special case 6
    if (str1.compare("OOX") == 0 &&
        str2.compare("XXX") == 0 && 
        str3.compare("OOX") == 0
        )
        return 1;
    //special case 7
    if (str1.compare("XOO") == 0 &&
        str2.compare("XOO") == 0 && 
        str3.compare("XXX") == 0
        )
        return 1;
    //special case 8
    if (str1.compare("OXO") == 0 &&
        str2.compare("OXO") == 0 && 
        str3.compare("XXX") == 0
        )
        return 1;
    //special case 9
    if (str1.compare("OOX") == 0 &&
        str2.compare("OOX") == 0 && 
        str3.compare("XXX") == 0
        )
        return 1;
    //special case 10
    if (str1.compare("XOX") == 0 &&
        str2.compare("OXO") == 0 && 
        str3.compare("XOX") == 0
        )
        return 1;
    //special case 11
    if (str1.compare("XXX") == 0 &&
        str2.compare("OXO") == 0 && 
        str3.compare("OOX") == 0
        )
        return 1;
    //special case 12
    if (str1.compare("XXX") == 0 &&
        str2.compare("OXO") == 0 && 
        str3.compare("XOO") == 0
        )
        return 1;
    //special case 13
    if (str1.compare("OOX") == 0 &&
        str2.compare("XXX") == 0 && 
        str3.compare("XOO") == 0
        )
        return 1;
    //special case 14
    if (str1.compare("XOO") == 0 &&
        str2.compare("XXX") == 0 && 
        str3.compare("OOX") == 0
        )
        return 1;
    //special case 15
    if (str1.compare("XOO") == 0 &&
        str2.compare("OXO") == 0 && 
        str3.compare("XXX") == 0
        )
        return 1;
    //special case 16
    if (str1.compare("OOX") == 0 &&
        str2.compare("OXO") == 0 && 
        str3.compare("XXX") == 0
        )
        return 1;
    //special case 17
    if (str1.compare("XOO") == 0 &&
        str2.compare("XXO") == 0 && 
        str3.compare("XOX") == 0
        )
        return 1;
    //special case 18
    if (str1.compare("XOX") == 0 &&
        str2.compare("XXO") == 0 && 
        str3.compare("XOO") == 0
        )
        return 1;
    //special case 19
    if (str1.compare("OXX") == 0 &&
        str2.compare("OXO") == 0 && 
        str3.compare("XXO") == 0
        )
        return 1;
    //special case 20
    if (str1.compare("XXO") == 0 &&
        str2.compare("OXO") == 0 && 
        str3.compare("OXX") == 0
        )
        return 1;
    //special case 21
    if (str1.compare("XOX") == 0 &&
        str2.compare("OXX") == 0 && 
        str3.compare("OOX") == 0
        )
        return 1;
    //special case 22
    if (str1.compare("OOX") == 0 &&
        str2.compare("OXX") == 0 && 
        str3.compare("XOX") == 0
        )
        return 1;
    return 0;
}

void solve(ll mcase){
    ll X = 0 , O = 0;

    //taking the input 
    for (ll i = 1; i <= 3; i++){
        for(ll j = 1; j <= 3; j++){
            cin >> g[i][j];
            if (g[i][j] == 'X')
                X++;
            else if (g[i][j] == 'O')
                O++;
        }
    }

    //handling the 12 special cases
    if (handle_special_cases()){
        cout << 1 << "\n";
        return;
    }


    ll win_X = get_pairs('X') , win_O = get_pairs('O');

    //grid is reachable if and only if X == O or X == O + 1
    if (X < O || X > O + 1){\
        cout << 3 << "\n";
        return;
    }
    if (win_X + win_O > 2){
        cout << 3 << "\n";
        return;
    }

    //checking whether a player has won already
    if (win_X + win_O == 1){
        if (win_O == 1 && X > O){
            cout << 3 << "\n";
            return;
        }
        else if (win_X == 1 && X == O){
            cout << 3 << "\n";
            return;   
        }
        cout << 1 << "\n";
        return;
    }
    if (win_X + win_O == 2){
        if (win_X == 0 || win_X == 1){
            cout << 3 << "\n";
            return;
        }
        cout << 1 << "\n";
        return;
    }

    //otherwise checking if X + O == 9 to see if there's a draw
    if (X + O == 9){
        cout << 1 << "\n";
        return;
    }
    //else the game must continue
    else {
        cout << 2 << "\n";
        return;
    }
}

//main function
int main(){
    //faster io
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

/*
    if there is an online judge, we use the
    standard io streams. Otherwise, we use custom
    io files.
*/
#ifndef ONLINE_JUDGE
    //works in codechef and codeforces
    FILE* inp = freopen("input.txt", "r" , stdin);
    FILE* err = freopen("error.txt", "w" , stderr);
    FILE* out = freopen("output.txt", "w" , stdout);
#endif

    //for testcases, use the below format
    
    ll t , mcase = 1; //testcases
    cin >> t;
    while(t > 0){
    	solve(mcase); //write a separate solve function
    	t--;
    	mcase++;
    }
    
    cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << "seconds" << "\n";
    return 0;
}
