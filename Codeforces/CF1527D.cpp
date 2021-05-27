
/*
	 template by: codetalker7
	 editor: sublime text 3
	 file name: CF1527D
	 date created: 2021-05-27 13:02:20
	 problem link: https://codeforces.com/problemset/problem/1527/D
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

//macros
/*
	ssz refers to the signed size of an STL structure, because .size() function
	returns an unsigned integer
*/
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
ll ans_for_0;
vll blank;
vll child_of_0;
vll subtree;
vll discovery;
vll finishing;
vector <vll> adj;

bool is_ancestor(ll u , ll v){
	return (discovery[u] < discovery[v] && finishing[u] > finishing[v]);
}

bool is_descendant(ll u , ll v){
	return (discovery[u] > discovery[v] && finishing[u] < finishing[v]);
}

void dfs(ll s , ll &time){
	//setting the discovery time
	discovery[s] = time;
	time++;	

	for (auto u : adj[s]){
		//if the vertex is undiscovered
		if(discovery[u] == -1){
			if (s == 0)
				child_of_0[u] = u;
			else 
				child_of_0[u] = child_of_0[s];
			dfs(u , time);
			
			//getting subtree values
			subtree[s] += subtree[u];
			if (s == 0)
				ans_for_0 += subtree[u]*(subtree[u] - 1)/2;
		}
	}
	//finishing up
	subtree[s]++;
	finishing[s] = time;
	time++;
}

void solve(ll mcase){
	ll n;
	cin >> n;
		
	child_of_0.assign(n , -1);
	subtree.assign(n , 0);
	finishing.assign(n , -1);
	discovery.assign(n , -1);
	adj.assign(n , blank);

	//taking the input
	for (ll i = 1; i <= n - 1; i++){
		ll u , v;
		cin >> u >> v;

		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	ll time = 1;
	ans_for_0 = 0;
	dfs(0 , time);
	
	//printing the answer for k = 0
	cout << ans_for_0 << " ";

	//getting the rest of the answers
	ll one_path = 1 , form = 0 , extreme0 = 0 , extreme1 = 0;
	for (ll i = 1; i < n; i++){
		if (one_path == 0){
			cout << 0 << " ";
			continue;
		}

		//checking the form
		if (form == 0){
			if (is_ancestor(i , extreme0)){
				cout << 0 << " ";
				continue;
			}
			else if (is_descendant(i , extreme0)){
				if (extreme0 == 0)
					cout << (n*(n - 1)/2 - ans_for_0) - subtree[i]*(subtree[0] - subtree[child_of_0[i]]) << " ";
				else 
					cout << subtree[extreme0]*(subtree[0] - subtree[child_of_0[extreme0]]) - subtree[i]*(subtree[0] - subtree[child_of_0[extreme0]]) << " ";	
				extreme0 = i;
				continue;
			}
			else if (child_of_0[i] == child_of_0[extreme0]){
				cout << subtree[extreme0]*(subtree[0] - subtree[child_of_0[extreme0]]) << " ";
				one_path = 0;
				continue;
			}
			//i belongs to a different subtree
			else {
				cout << subtree[extreme0]*(subtree[0] - subtree[child_of_0[extreme0]] - subtree[i]) << " ";
				extreme1 = i;
				form = 1;
				continue;
			}
		}
		//else the form must be 0
		else {
			//check if i is an ancestor of either extreme0 or extreme1
			if (is_ancestor(i , extreme0)){
				cout << 0 << " ";
				continue;
			}
			else if (is_ancestor(i , extreme1)){
				cout << 0 << " ";
				continue;
			}

			//check if i is a descendent
			if (is_descendant(i , extreme0)){
				cout << subtree[extreme1]*(subtree[extreme0] - subtree[i]) << " ";
				extreme0 = i;
				continue;
			}
			else if (is_descendant(i , extreme1)){
				cout << subtree[extreme0]*(subtree[extreme1] - subtree[i]) << " ";
				extreme1 = i;
				continue;
			}
			//otherwise set one_path to 0 and find the answer
			one_path = 0;
			cout <<  subtree[extreme0] * subtree[extreme1] << " ";
		}
	}
	//figuring out the answer for n
	if (one_path == 0)
		cout << 0 << "\n";
	else 
		cout << 1 << "\n";	
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


/*child_of_0[V]
one_path = 1 (0 or 1)

form = 0 (0 or 1)
extreme0 = 0 , extreme1 = 0

answer_for_0 = sum_{u child of 0} subtree[u]*(subtree[u] - 1)/2

for i = 1 to n - 1
	if (one_path == 0){
		ans_for_i = 0;
		continue;
	}
	//so 0,...,i - 1 all belong to a single path
	//if one end of the path is the root 0
	if (form == 0){
		if (i is an ancestor of extreme0){
			ans_for_i = 0;
			continue;
		}
		else if (i is a descendent of extreme0){
			ans_for_i = subtree[extreme0]*(subtree[0] - subtree[child_of_0[extreme0]]) - subtree[i]*(subtree[0] - subtree[child_of_0[extreme0]]);
			extreme0 = i;
			continue;
		}
		else if (child_of_0[i] == child_of_0[extreme0]){
			ans_for_i = subtree[extreme0]*(subtree[0] - subtree[child_of_0[extreme0]]);
			one_path = 0;
			continue;
		}
		//i belongs to a different subtree
		else {
			ans_for_i = subtree[extreme0]*(subtree[0] - subtree[child_of_0[extreme0]] - subtree[i]);
			extreme1 = i;
			form = 1;
			continue;
		}
	}
	//else the form is 1
	else {
		//check if i is an ancestor of either extreme0 or extreme1
		if (i is an ancestor of extreme0){
			ans_for_i = 0;
			continue;
		}
		else if (i is an ancestor of extreme1){
			ans_for_i = 0;
			continue;
		}

		//check if i is a descendent
		if (i is a descendent of extreme0){
			ans_for_i = subtree[extreme1]*(subtree[extreme0] - subtree[i]);
			extreme0 = i;
			continue
		}
		else if (i is a descendent of extreme1){
			ans_for_i = subtree[extreme0]*(subtree[extreme1] - subtree[i]);
			extreme1 = i;
			continue;
		}
		//otherwise set one_path to 0 and find the answer
		one_path = 0;
		ans_for_i = subtree[extreme0] * subtree[extreme1];
	}
	
	//figuring out the answer for n
	if (one_path == 0)
		ans_for_n = 0;
	else 
		ans_for_n = 1;

	*/