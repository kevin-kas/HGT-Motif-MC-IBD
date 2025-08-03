#include <bits/stdc++.h>
#include <boost/unordered/unordered_flat_set.hpp>
#include <boost/unordered/unordered_flat_map.hpp>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

long long rand(long long l, long long r) {
	return uniform_int_distribution<long long>(l, r)(rng);
}

int K;
long long R;

int n;
boost::unordered_flat_map<string, int> taxon_id;
int tid[8005];
bool e[8005][8005];
vector<int> g[8005];
vector<pair<long long, int>> pre;
bool vis[8005];
boost::unordered_flat_set<__int128> s;
boost::unordered_flat_map<vector<int>, vector<pair<vector<int>, long long>>> motifs;

void read_taxon(const string taxonfile) {
	ifstream in(taxonfile);
	string s;
	for (getline(in, s); getline(in, s); ) {
		auto p = s.find(',') + 1;
		const int id = stoi(s.substr(p, s.find(',', p) - p));
		p = s.find(',', s.find(',', p) + 1) + 1;
		taxon_id[s.substr(p, s.find(',', p) - p)] = id;
	}
}

void read_data() {
	string s;
	getline(cin, s);
	for (size_t l = 1, r = min(s.find(',', l), s.length()); l < s.length(); l = r + 1, r = min(s.find(',', l), s.length())) {
		const string cur = s.substr(l, r - l);
		tid[++n] = taxon_id[cur];
	}
	for (int i = 1; i <= n; i++) {
		getline(cin, s);
		size_t p = s.find(',');
		for (int j = 1; j <= n; j++) {
			if (++p < s.length() && s[p] != ',') {
				e[i][j] = true, g[i].push_back(j);
				while (p < s.length() && isdigit(s[p]))
					p++;
				p += 2;
			}
		}
        pre.emplace_back(15LL * g[i].size() * g[i].size() * g[i].size(), i);
	}
    for (int i = 1; i < n; i++)
        pre[i].first += pre[i - 1].first;
}

bool check(const vector<int>& g1, const vector<int>& g2) {
	vector<int> p(K);
	iota(begin(p), end(p), 0);
	do {
		bool flag = true;
		for (int i = 0; i < K; i++)
			if (tid[g1[p[i]]] != tid[g2[i]])
				flag = false;
		for (int i = 0; i < K && flag; i++)
			for (int j = i + 1; j < K && flag; j++)
				if (e[g1[p[i]]][g1[p[j]]] != e[g2[i]][g2[j]])
					flag = false;
		if (flag)
			return true;
	} while (next_permutation(begin(p), end(p)));
	return false;
}

void add(const vector<int>& v) {
	vector<int> t;
	for (const auto& i : v)
		t.push_back(tid[i]);
	sort(begin(t), end(t));
	for (auto& [motif, cnt] : motifs[t]) {
		if (check(v, motif)) {
			cnt++;
			return;
		}
	}
	motifs[t].emplace_back(v, 1);
}

int main(int argc, char *argv[]) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	K = stoi(string(argv[1]));
	R = stoll(string(argv[2]));
	const string taxonfile(argv[3]);
	read_taxon(taxonfile);
	read_data();
    for (long long i = 1, _ = pre.back().first; i <= R; i++) {
        const int p = lower_bound(begin(pre), end(pre), pair<long long, int>{rand(1, _), 0})->second;
        vector<int> v{p}, adj;
        vis[p] = true;
        for (const auto& j : g[p])
            if (j != p)
                adj.push_back(j), vis[j] = true;
        for (int j = 1; j < K && !adj.empty(); j++) {
            auto it = begin(adj) + rand(0, adj.size() - 1);
            const int nxt = *it;
            adj.erase(it);
            v.push_back(nxt);
            for (const auto& k : g[nxt])
                if (!vis[k])
                    adj.push_back(k), vis[k] = true;
        }
        if (v.size() == K) {
            sort(begin(v), end(v));
            __int128 x = 0;
            for (const auto& j : v)
                x = x * (n + 1) + j;
            if (s.find(x) == end(s))
                s.insert(x), add(v);
        }
        for (const auto& j : v)
            vis[j] = false;
        for (const auto& j : adj)
            vis[j] = false;
    }
	long long tot = 0, sum = 0;
	for (const auto& [t, vm] : motifs) {
		tot += vm.size();
		for (const auto& [motif, cnt] : vm)
			sum += cnt;
	}
	cerr << "[Info] Found " << tot << " motif(s) of " << sum << " subgraph(s)." << endl;
	for (const auto& [t, vm] : motifs) {
		for (const auto& [motif, cnt] : vm) {
			cout << K << ' ';
			for (int i = 0; i < K; i++)
				cout << tid[motif[i]] << ' ';
			for (int i = 0; i < K; i++)
				for (int j = 0; j < K; j++)
					cout << e[motif[i]][motif[j]] << ' ';
			cout << cnt << '\n';
		}
	}
	return 0;
}
