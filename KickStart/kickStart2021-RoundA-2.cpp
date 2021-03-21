/*
    template-by: codetalker7
    editor: sublime text 3
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
//define global variables here
vector <vll> grid;
vector <vector <vll> > max_contiguous;
vector <vll> blank1;
vll blank;


ll get_for_vertex(ll R , ll C , ll i , ll j){
    // will store the final answer
    ll ans = 0;
    ll up = max_contiguous[i][j][0];
    ll down = max_contiguous[i][j][1];
    ll left = max_contiguous[i][j][2];
    ll right = max_contiguous[i][j][3];

    //from up and left
    if (left > 1){
        ll temp = min(left , up/2);
        ans += max(ll(0) , temp - 1);
    }
    if (up > 1){
        ll temp = min(left/2 , up);
        ans += max(ll(0) , temp - 1);
    }

    //from up and right
    if (right > 1){
        ll temp = min(right , up/2);
        ans += max(ll(0) , temp - 1);
    }
    if (up > 1){
        ll temp = min(right/2 , up);
        ans += max(ll(0) , temp - 1);
    }

    //from down and left
    if (left > 1){
        ll temp = min(left , down/2);
        ans += max(ll(0) , temp - 1);
    }
    if (down > 1){
        ll temp = min(left/2 , down);
        ans += max(ll(0) , temp - 1);
    }

    //from down and right
    if (right > 1){
        ll temp = min(right , down/2);
        ans += max(ll(0), temp - 1);
    }
    if (down > 1){
        ll temp = min(right/2 , down);
        ans += max(ll(0) , temp - 1);
    }
    return ans;
}
/*
    max_contiguous[0] -> up
    max_contiguous[1] -> down
    max_contiguous[2] -> left
    max_contiguous[3] -> right
*/
void calc_max_contiguous(ll R , ll C){
    //calculating right and left for each row
    for (ll i = 1; i <= R; i++){
        //currently in row i

        //calculating left for each vertex
        for (ll j = 1; j <= C; j++){
            if (j == 1){
                if (grid[i][j] == 0)
                    max_contiguous[i][j][2] = 0;
                else
                    max_contiguous[i][j][2] = 1;
            }
            else{
                if (grid[i][j] == 0)
                    max_contiguous[i][j][2] = 0;
                else
                    max_contiguous[i][j][2] = 1 + max_contiguous[i][j - 1][2];
            }
        }

        //calculating right for each vertex
        for (ll j = C; j >= 1; j--){
            if (j == C){
                if (grid[i][j] == 0)
                    max_contiguous[i][j][3] = 0;
                else
                    max_contiguous[i][j][3] = 1;
            }
            else{
                if (grid[i][j] == 0)
                    max_contiguous[i][j][3] = 0;
                else
                    max_contiguous[i][j][3] = 1 + max_contiguous[i][j + 1][3];
            }
        }
    }

    //calculating up and down for each vertex
    for (ll j = 1; j <= C; j++){
        //currently in column i

        //calculating up for each vertex
        for (ll i = 1; i <= R; i++){
            if (i == 1){
                if (grid[i][j] == 0){
                    max_contiguous[i][j][0] = 0;
                }
                else{
                    max_contiguous[i][j][0] = 1;
                }
            }
            else{
                if (grid[i][j] == 0)
                    max_contiguous[i][j][0] = 0;
                else
                    max_contiguous[i][j][0] = 1 + max_contiguous[i - 1][j][0];
            }
        }

        //calculating down for each vertex
        for (ll i = R; i >= 1; i--){
            if (i == R){
                if (grid[i][j] == 0)
                    max_contiguous[i][j][1] = 0;
                else
                    max_contiguous[i][j][1] = 1;
            }
            else{
                if (grid[i][j] == 0)
                    max_contiguous[i][j][1] = 0;
                else
                    max_contiguous[i][j][1] = 1 + max_contiguous[i + 1][j][1];
            }
        }
    }

}

void solve(ll mcase){
    ll R , C;
    cin >> R >> C;

    //taking the input
    for (ll i = 1; i <= R; i++)
        for (ll j = 1; j <= C; j++)
            cin >> grid[i][j];

    //counting max_contigious
    calc_max_contiguous(R , C);

    ll mcount = 0;
    //doing the main computation
    for (ll i = 1; i <= R; i++){
        for (ll j = 1; j <= C; j++){
            if (grid[i][j] == 1)
                mcount += get_for_vertex(R , C , i , j);
        }
    }
    cout << "Case #" << mcase << ": " << mcount << "\n";
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

    //initialising the grid
    //indexing starts at 1
    max_contiguous.push_back(blank1);
    grid.push_back(blank);

    for (ll i = 1; i <= 1000; i++){
        grid.push_back(blank);
        max_contiguous.push_back(blank1);

        grid[i].push_back(-1);
        max_contiguous[i].push_back(blank);

        for (ll j = 1; j <= 1000; j++){
            grid[i].push_back(-1);
            max_contiguous[i].push_back(blank);

            //at this point, max_contiguous[i][j] is a blank vector
            max_contiguous[i][j].assign(4 , 0);
        }
    }

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

