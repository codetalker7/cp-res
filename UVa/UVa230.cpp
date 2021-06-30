
/*
	 template by: codetalker7
	 editor: sublime text 3
	 file name: UVa230
	 date created: 2021-06-29 02:37:23
	 problem link: 
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
#include<random>
using namespace std;

//debugging functions
//var_name is used to give the variable name
void debug(char x){cerr << x;}
void debug(int x){cerr << x;}
void debug(unsigned int x){cerr << x;}
void debug(long long x){cerr << x;}
void debug(unsigned long long x){cerr << x;}
void debug(long double x){cerr << x;}
void debug(double x){cerr << x;}
void debug(string x){cerr << x;}
void debug(float x){cerr << x;}

template <class T, class V> void debug(pair <T, V> x){cerr << "(" << x.first << "," << x.second << ")";}
template <class T> void debug(vector <T> v){cerr<<"[ ";for(T i: v){debug(i);cerr<<" ";}cerr << "]";}
template <class T> void debug(set <T> v){cerr<<"{ ";for(T i: v){debug(i);cerr<<" ";}cerr << "}";}
template <class T> void debug(multiset <T> v){cerr<<"{ ";for(T i: v){debug(i);cerr<<" ";}cerr << "}";}
template <class T, class V> void debug(map <T, V> v){cerr<<"[ ";for(auto i: v){debug(i);cerr<<" ";}cerr << "]";}
//debug with a new line at the end
#define debugln(x) debug(x); cerr << "\n"

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

//macros
/*
	ssz refers to the signed size of an STL structure, because .size() function
	returns an unsigned integer
*/
#define ssz(x) (int)x.size()

struct book{
    char bookTitle[81], bookAuthor[81];

    bool operator < (const book &p){
        //convert to string objects
        string this_author = bookAuthor, this_title = bookTitle;
        string p_author = p.bookAuthor, p_title = p.bookTitle;

        int by_author = p_author.compare(this_author);
        if (by_author == 0){
            int by_title = p_title.compare(this_title);
            if (by_title > 0){
                return 1;
            } 
            else{
                return 0;
            }
        }
        else if (by_author > 0){
            return 1;
        }
        else
            return 0;
    }
};

//some useful algos
template <class T> T mceil(T a, T b){return (a % b == 0) ? a/b : a/b + 1;}
template <class T> T expo(T base , T exp , T mod){T res = 1;base = base % mod;while (exp > 0){if (exp & 1)res = (res*base) % mod;exp = exp>>1;base = (base*base) % mod;}return res;}
template <class T> ll maxpower(T a , T b){ll ans = 0;while(a > 0 && a % b == 0){ans++;a /= b;}return ans;}
template <class T> T extgcd(T a, T b , T &x , T &y) {x = 1, y = 0;T x1 = 0, y1 = 1, a1 = a, b1 = b; while (b1) { T q = a1 / b1; tie(x, x1) = make_tuple(x1, x - q * x1); tie(y, y1) = make_tuple(y1, y - q * y1); tie(a1, b1) = make_tuple(b1, a1 - q * b1);}return a1;}
template <class T> T modinv (T a , T m , T &x , T &y){T g = extgcd(a , m , x , y); if (g != 1) cerr << "Division by zero!"; else x = (x % m + m) % m; return x;}
template <class T> T signed_floor(T a , T b){if (a >= 0 && b >= 0) return a/b; else if (a < 0 & b < 0) return (-a)/(-b); else if (a < 0 & b >= 0){if (a % b == 0) return -((-a)/b); else return -((-a)/b) - 1;} else if (a >= 0 && b < 0){if(a % b == 0) return -(a/(-b)); else return -(a/(-b)) - 1;}}
template <class T> pair<T,T> log_base_2(T n){T temp = 1 , k = 0; while(temp <= n){temp <<= 1; k++;} temp >>= 1; k--; return {k , temp};}
//define global variables here

void solve(ll mcase){
    //taking the library books
    char title[81], author[81];
    vector <book> library;

    char input[164];
    while(scanf("\"%[^\"]\" by %[^\n]\n", title, author) == 2){
        book new_book; 
        memcpy(new_book.bookTitle, title, 81);
        memcpy(new_book.bookAuthor, author, 81);
        library.push_back(new_book);
    }
    //read END
    scanf("%s\n", title);
    sort(library.begin(), library.end());
        
    //making a map
    map <string, ll> avail;
    for (ll i = 0; i < ssz(library); i++){
        string curr = library[i].bookTitle;
        avail[curr] = 1;
    }
    /*
        avail 1 -> on the shelf   
        avail 2 -> available, but not on the shelf
        avail 0 -> not available
    */ 

    //handling the queries
    char query[81];
    while (scanf("%s", query) == 1){
        string q = query;
        if (q.compare("END") == 0){
            break;
        }
        else if (q.compare("BORROW") == 0){
            scanf(" \"%[^\"]\"\n", title);
            q = title;  
            avail[q] = 0;
        }
        else if (q.compare("RETURN") == 0){
            scanf(" \"%[^\"]\"\n", title);
            q = title;
            avail[q] = 2;
        }
        // SHELVE
        else{
            ll last_shelf_index = -1;
            for (ll i = 0; i < ssz(library); i++){
                q = library[i].bookTitle;
                ll available = avail[q];

                if (available == 1){
                    last_shelf_index = i;
                }
                else if (available == 2){
                    avail[q] = 1;
                    if (last_shelf_index == -1){
                        last_shelf_index = i;
                        printf("Put \"%s\" first\n", library[i].bookTitle);
                    }
                    else{
                        printf("Put \"%s\" after \"%s\"\n", library[i].bookTitle, library[last_shelf_index].bookTitle);
                        last_shelf_index = i;
                    }
                }
            }
            printf("END\n");
        }
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
    /*
        Uncomment the next line to use the
        Mersenne Twister Random Number 
        Generator, with the current system 
        time as the seed. 
        The first line is for 32-bit
        Second line is for 64-bit
    */
    //mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    //mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());


    //for testcases, use the below format
    /*
    ll t , mcase = 1; //testcases
    cin >> t;
    while(t > 0){
    	solve(mcase); //write a separate solve function
    	t--;
    	mcase++;
    }
    */
    solve(1);
    cerr << "time taken : " << (float)clock() / CLOCKS_PER_SEC << "seconds" << "\n";
    return 0;
}
