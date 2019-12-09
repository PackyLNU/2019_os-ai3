#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
const int maxNum = 100 + 5;
LL a, b, maxd;
// 当前解和最终解
LL v[maxNum], ans[maxNum];

// 返回满足 1/c <= a/b 的最小c
inline int get_first(LL a, LL b) {
    return b / a + 1;
}

// 欧几里得算法
LL gcd(LL a, LL b) {
    return b == 0 ? a : gcd(b, a % b);
}

// 如果当前解v比最优解ans更优，更新ans
bool better(int d) {
    for(int i = d; i >= 0; i--) {
        if(v[i] != ans[i]) {
            return ans[i] == -1 || v[i] < ans[i];
        }
    }
    return false;
}

// 当前深度为d,分母不能小于from,分数之和恰好为aa/bb
bool dfs(int d, int from, LL aa, LL bb) {
    if(d == maxd) {
        // aa/bb必须是埃及分数
        if(bb % aa) {
            return false;
        }
        // 深度为d时的分母
        v[d] = bb / aa;
        if(better(d)) {
            memcpy(ans, v, sizeof(LL) * (d + 1));
        }
        return true;
    }
    bool ok = false;
    // 枚举的起点
    from = max(from, get_first(aa, bb));
    for(int i = from; ; i++) {
        // 剪枝：如果剩下的max+1-d个分数全部都是1/i,
        // 加起来仍然不超过aa/bb，则无解
        if(bb * (maxd + 1 - d) <= i * aa) {
            break;
        }
        v[d] = i;

        // 计算aa/bb - 1/i，设结果为a2/b2
        LL b2 = bb * i;
        LL a2 = aa * i - bb;
        // 获取最大公约数
        LL g = gcd(a2, b2);
        if(dfs(d + 1, i + 1, a2 / g, b2 / g)) {
            ok = true;
        }
    }
    return ok;
}

int main() {
    int kase = 0;
    while(cin >> a >> b) {
        int ok = 1;
        // 迭代加深
        for(maxd = 1; maxd <= 100; maxd++) {
            memset(ans, -1, sizeof(ans));
            if(dfs(0, get_first(a, b), a, b)) {
                ok = 1;
                break;
            }
        }
        cout << "Case " << ++kase << ": ";
        if(ok) {
            cout << a << "/" << b << "=";
            for(int i = 0; i < maxd; i++) {
                cout << "1/" << ans[i] << "+";
            }
            cout << "1/" << ans[maxd] << endl;
        } else {
            cout << "No solution." << endl;
        }
    }
    return 0;
}
