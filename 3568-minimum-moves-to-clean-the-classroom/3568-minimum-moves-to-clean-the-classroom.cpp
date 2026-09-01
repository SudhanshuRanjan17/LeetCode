class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr = -1, sc = -1;
        vector<vector<int>> id(m, vector<int>(n, -1));

        int litter = 0;

        // Locate S and assign an index to every L.
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                }

                if (classroom[i][j] == 'L') {
                    id[i][j] = litter++;
                }
            }
        }

        // No litter to collect.
        if (litter == 0)
            return 0;

        int fullMask = (1 << litter) - 1;

        /*
            State:
            row, col, remaining energy, collected litter mask
        */
        struct State {
            int r, c, e, mask;
        };

        queue<State> q;

        /*
            visited[r][c][energy][mask]

            Maximum:
            20 * 20 * 51 * 1024 ~= 20 million states
        */
        int totalStates = m * n * (energy + 1) * (1 << litter);

        vector<char> visited(totalStates, false);

        auto encode = [&](int r, int c, int e, int mask) {
            return (((r * n + c) * (energy + 1) + e)
                    * (1 << litter) + mask);
        };

        q.push({sr, sc, energy, 0});
        visited[encode(sr, sc, energy, 0)] = true;

        int dist = 0;

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                auto [r, c, e, mask] = q.front();
                q.pop();

                if (mask == fullMask)
                    return dist;

                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    // Outside grid.
                    if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                        continue;

                    // Obstacle.
                    if (classroom[nr][nc] == 'X')
                        continue;

                    // Cannot make a move without energy.
                    if (e == 0)
                        continue;

                    int ne = e - 1;
                    int nmask = mask;

                    // Collect litter.
                    if (classroom[nr][nc] == 'L') {
                        int bit = id[nr][nc];
                        nmask |= (1 << bit);
                    }

                    // Reset energy on R.
                    if (classroom[nr][nc] == 'R') {
                        ne = energy;
                    }

                    int stateId = encode(nr, nc, ne, nmask);

                    if (!visited[stateId]) {
                        visited[stateId] = true;
                        q.push({nr, nc, ne, nmask});
                    }
                }
            }

            dist++;
        }

        return -1;
    }
};