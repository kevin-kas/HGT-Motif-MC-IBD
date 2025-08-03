#include <bits/stdc++.h>
#include <boost/unordered/unordered_flat_set.hpp>
#include <boost/unordered/unordered_flat_map.hpp>

using namespace std;

int K;

int n;
boost::unordered_flat_map<string, int> taxon_id;
int tid[8005];
bool e[8005][8005];
vector<int> g[8005];
size_t T;
bool vis[8005];
boost::unordered_flat_set<size_t> s;
boost::unordered_flat_map<vector<int>, vector<pair<vector<int>, long long>>> motifs;

int read_taxon(const string taxonfile) {
	ifstream in(taxonfile);
	string s;
	for (getline(in, s); getline(in, s); ) {
		auto p = s.find(',') + 1;
		const int id = stoi(s.substr(p, s.find(',', p) - p));
		p = s.find(',', p) + 1;
		p = s.find(',', p) + 1;
		const string ref = s.substr(p, s.find(',', p) - p);
		if (taxon_id.find(ref) != end(taxon_id))
			return 1;
		taxon_id[ref] = id;
	}
	// cerr << "[Brute-force] Read " << taxon_id.size() << " taxons." << endl;
	return 0;
}

int read_data() {
	string s;
	getline(cin, s);
	for (size_t l = 1, r = min(s.find(',', l), s.length()); l < s.length(); l = r + 1, r = min(s.find(',', l), s.length())) {
		const string cur = s.substr(l, r - l);
		tid[++n] = taxon_id[cur];
		// if (taxon_id.find(cur) == end(taxon_id)) {
			// cerr << "[Error] Unknown reference id " << cur << "." << endl;
			// return 1;
		// }
		// if (const size_t p = cur.find('.'), q = cur.find('_'); p == string::npos)
			// meta[++n] = {stoi(cur.substr(4, q - 4)), stoi(cur.substr(q + 1))};
		// else
			// meta[++n] = {stoi(cur.substr(4, p - 4)), stoi(cur.substr(p + 1, q - p - 1)) + 1};
	}
	// if (n > 5000) {
		// cerr << "[Error] Too many vertices (" << n << ")." << endl;
		// return 1;
	// }
	for (int i = 1; i <= n; i++) {
		getline(cin, s);
		size_t p = s.find(',');
		// if (meta[i].second != s.substr(0, p)) {
			// cerr << "[Error] Wrong adjacency matrix order " << s.substr(0, p) << "." << endl;
			// return 1;
		// }
		// if (const int cols = count(begin(s), end(s), ','); cols != n) {
			// cerr << "[Error] Need " << n << " columns but " << cols << endl;
			// return 1;
		// }
		for (int j = 1; j <= n; j++) {
			if (++p < s.length() && s[p] != ',') {
				e[i][j] = true, g[i].push_back(j);
				// if (s[p] == '0') {
					// cerr << "[Error] Wrong edge weight format: (" << i << ", " << j << ")." << endl;
					// return 1;
				// }
				while (p < s.length() && isdigit(s[p]))
					p++;
				// if (p + 1 >= s.length() || s[p] != '.' || s[p + 1] != '0') {
					// cerr << "[Error] Wrong edge weight format: (" << i << ", " << j << ")." << endl;
					// return 1;
				// }
				p += 2;
			}
		}
		// for (int j = 1; j <= n; j++)
			// if (s[p + (j * 2 - 1)] == '1')
				// e[i][j] = true, g[i].push_back(j);
	}
	// for (int i = 1; i <= n; i++) {
		// for (int j = 1; j <= n; j++) {
			// if (e[i][j] != e[j][i]) {
				// cerr << "[Error] Wrong reverse edge weight: (" << i << ", " << j << ")." << endl;
				// return 1;
			// }
		// }
	// }
	T = 1;
	for (int i = 1; i < K; i++)
		T *= n + 1;
	return 0;
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

int mn;

void dfs(size_t sum) {
	vector<int> v;
	for (; sum != 0; sum /= n + 1)
		v.push_back(sum % (n + 1));
	sort(begin(v), end(v));
	for (const auto& i : v)
		sum = sum * (n + 1) + i;
	if (s.find(sum) != end(s))
		return;
	s.insert(sum);
	if (sum >= T) {
		add(v);
		return;
	}
	for (const auto& i : v)
		for (const auto& j : g[i])
			if (!vis[j] && j > mn)
				vis[j] = true, dfs(sum * (n + 1) + j), vis[j] = false;
}

int main(int argc, char *argv[]) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	K = stoi(string(argv[1]));
	const string taxonfile(argv[2]);
	read_taxon(taxonfile);
	read_data();
	// if (read_taxon(taxonfile) != 0)
		// return 1;
	// if (read_data() != 0)
		// return 1;
	// queue<vector<int>> q;
	for (int i = 1; i <= n; i++)
		// q.push({i});
	// for (; !q.empty(); q.pop()) {
		// const auto& cur = q.front();
		// if (cur.size() == K) {
			// add(cur);
			// continue;
		// }
		// for (const auto& i : cur) {
			// for (const auto& j : g[i]) {
				// if (j > cur.front() && find(begin(cur), end(cur), j) == end(cur)) {
					// auto v = cur;
					// v.insert(lower_bound(begin(v), end(v), j), j);
					// q.emplace(move(v));
				// }
			// }
		// }
	// }
		s.clear(), vis[i] = true, dfs(mn = i), vis[i] = false;
	long long tot = 0;
	long long sum = 0;
	// vector<int> v;
	for (const auto& [t, vm] : motifs) {
		tot += vm.size();
		for (const auto& [motif, cnt] : vm)
			sum += cnt;
	}
	cerr << "[Info] Found " << tot << " motif(s) of " << sum << " subgraph(s)." << endl;
	// cout << tot << '\n';
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
	// vector<int> v;
	// for (const auto& [t, vm] : motifs)
		// for (const auto& [motif, cnt] : vm)
			// v.push_back(cnt);
	// cout << "Found " << v.size() << " motif(s)" << '\n';
	// sort(begin(v), end(v), greater<int>());
	// for (size_t i = 0, j = 0; i < v.size(); i = j) {
		// while (j < v.size() && v[i] == v[j])
			// j++;
		// cout << j - i << " motif(s) with " << v[i] << " appearance(s)" << '\n';
	// }
	return 0;
}
