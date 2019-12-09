#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
const int maxNum = 100 + 5;
LL a, b, maxd;
// ��ǰ������ս�
LL v[maxNum], ans[maxNum];

// �������� 1/c <= a/b ����Сc
inline int get_first(LL a, LL b) {
    return b / a + 1;
}

// ŷ������㷨
LL gcd(LL a, LL b) {
    return b == 0 ? a : gcd(b, a % b);
}

// �����ǰ��v�����Ž�ans���ţ�����ans
bool better(int d) {
    for(int i = d; i >= 0; i--) {
        if(v[i] != ans[i]) {
            return ans[i] == -1 || v[i] < ans[i];
        }
    }
    return false;
}

// ��ǰ���Ϊd,��ĸ����С��from,����֮��ǡ��Ϊaa/bb
bool dfs(int d, int from, LL aa, LL bb) {
    if(d == maxd) {
        // aa/bb�����ǰ�������
        if(bb % aa) {
            return false;
        }
        // ���Ϊdʱ�ķ�ĸ
        v[d] = bb / aa;
        if(better(d)) {
            memcpy(ans, v, sizeof(LL) * (d + 1));
        }
        return true;
    }
    bool ok = false;
    // ö�ٵ����
    from = max(from, get_first(aa, bb));
    for(int i = from; ; i++) {
        // ��֦�����ʣ�µ�max+1-d������ȫ������1/i,
        // ��������Ȼ������aa/bb�����޽�
        if(bb * (maxd + 1 - d) <= i * aa) {
            break;
        }
        v[d] = i;

        // ����aa/bb - 1/i������Ϊa2/b2
        LL b2 = bb * i;
        LL a2 = aa * i - bb;
        // ��ȡ���Լ��
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
        // ��������
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
