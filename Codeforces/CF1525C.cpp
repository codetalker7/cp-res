/*
     template by: codetalker7
     editor: sublime text 3
     file name: CF1525C
     date created: 2021-05-16 14:02:17
     problem link: https://codeforces.com/contest/1525/problem/C
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

#define ssz(x) (int)x.size()

//some useful algos
template <class T> T mceil(T a, T b){return (a % b == 0) ? a/b : a/b + 1;}
template <class T> T expo(T base , T exp , T mod){T res = 1;base = base % mod;while (exp > 0){if (exp & 1)res = (res*base) % mod;exp = exp>>1;base = (base*base) % mod;}return res;}
template <class T> ll maxpower(T a , T b){ll ans = 0;while(a > 0 && a % b == 0){ans++;a /= b;}return ans;}
template <class T> T extgcd(T a, T b , T &x , T &y) {x = 1, y = 0;T x1 = 0, y1 = 1, a1 = a, b1 = b; while (b1) { T q = a1 / b1; tie(x, x1) = make_tuple(x1, x - q * x1); tie(y, y1) = make_tuple(y1, y - q * y1); tie(a1, b1) = make_tuple(b1, a1 - q * b1);}return a1;}
template <class T> T modinv (T a , T m , T &x , T &y){T g = extgcd(a , m , x , y); if (g != 1) cerr << "Division by zero!"; else x = (x % m + m) % m; return x;}
template <class T> T signed_floor(T a , T b){if (a >= 0 && b >= 0) return a/b; else if (a < 0 & b < 0) return (-a)/(-b); else if (a < 0 & b >= 0){if (a % b == 0) return -((-a)/b); else return -((-a)/b) - 1;} else if (a >= 0 && b < 0){if(a % b == 0) return -(a/(-b)); else return -(a/(-b)) - 1;}}
template <class T> pair<T,T> log_base_2(T n){T temp = 1 , k = 0; while(temp <= n){temp <<= 1; k++;} temp >>= 1; k--; return {k , temp};}
//define global variables here

void handle_lists(ll n , ll m , vector <pair<ll , ll> > &list , vll &start_pos , vll &final , vll &direction){
    if (list.empty())
        return;
    vll stack1 , stack2;
    for (ll i = 0; i < ssz(list); i++){
        if (direction[list[i].second] == 1)
            stack1.push_back(list[i].second);
        else{
            if (!stack1.empty()){
                //match the current robot with robot at the top of stack1
                ll u = stack1[stack1.size() - 1] , v = list[i].second;
                //it is true that start_pos[u] < start_pos[v]
                final[u] = (start_pos[v] - start_pos[u])/2;
                final[v] = final[u];
                stack1.pop_back();
            }
            else 
                stack2.push_back(list[i].second);
        }
    }

    ll i = 0;
    while(i < ssz(stack2)){
        if (i + 1 < stack2.size()){
            //the vertices u,v will meet and die
            ll u = stack2[i] , v = stack2[i + 1];
            final[u] = start_pos[v] - (start_pos[v] - start_pos[u])/2;
            final[v] = final[u];
            i += 2;
        }
        else
            break;
    }

    ll j = ssz(stack1) - 1;
    while(j >= 0){
        if (j - 1 >= 0){
            //the vertices u,v will meet and die
            ll u = stack1[j - 1] , v = stack1[j];
            final[u] = (2*m + start_pos[u] - start_pos[v])/2 - start_pos[u];
            final[v] = final[u];
            j = j - 2;
        }
        else
            break;
    }

    if (i == ssz(stack2) - 1 && j == 0){
        //u,v will meet and die
        ll u = stack2[i] , v = stack1[j];
        final[u] = start_pos[u] + (2*m - start_pos[u] - start_pos[v])/2;
        final[v] = final[u];
    }
}   

void solve(ll mcase){
    ll n , m;
    cin >> n >> m;

    char c;

    vll start_pos(n + 1 , (ll)0);
    vll final(n + 1 , (ll)-1);
    vll direction(n + 1 , (ll)-1);

    vector <pair<ll , ll> > even_list;
    vector <pair<ll , ll> > odd_list;

    for (ll i = 1; i <= n; i++){
        cin >> start_pos[i];
        if (start_pos[i] % 2 == 0)
            even_list.push_back({start_pos[i] , i});    
        else
            odd_list.push_back({start_pos[i] , i});
    }
    for (ll i = 1; i <= n; i++){
        cin >> c;   
        if (c == 'L')
            direction[i] = 0;
        else 
            direction[i] = 1;
    }

    sort(even_list.begin() , even_list.end());
    sort(odd_list.begin() , odd_list.end());

    
    handle_lists(n , m , even_list , start_pos , final , direction);
    handle_lists(n , m , odd_list , start_pos , final , direction);

    for(ll i = 1; i <= n; i++)
        cout << final[i] << " ";
    cout << "\n";
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
   
    return 0;
}