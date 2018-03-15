 #include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int maxnode = 1000005;
const int nodesize = 26;

struct Aho_corasick
{
    int ch[maxnode][nodesize];
    int val[maxnode];
    int f[maxnode];
    int last[maxnode];
    bool vis[maxnode];
    int sz;
    int ans;

    void init()
    {
        sz = 1;
        memset(vis, false, sizeof(vis));
        memset(ch[0], 0, sizeof(ch[0]));
        memset(val, 0, sizeof(val));
    }

    int id(char c)
    {
        return c - 'a';
    }

    void Insert(const char *s)
    {
        int u = 0;
        int len = strlen(s);
        for(int i = 0; i < len; i++)
        {
            int c = id(s[i]);
            if(!ch[u][c])
            {
                memset(ch[sz], 0, sizeof(ch[sz]));
                ch[u][c] = sz++;//这里不能加上val[u] = 0,因为有可能有的模式串是该模式串的前缀
            }
            u = ch[u][c];
        }
        val[u]++;
    }

    void getFail()
    {
        queue<int> q;
        for(int c = 0; c < nodesize; c++)
        {
            int u = ch[0][c];
            if(u)
            {
                f[u] = 0;
                q.push(u);
                last[u] = 0;
            }
        }

        while(!q.empty())
        {
            int r = q.front();
            q.pop();
            for(int c = 0; c < nodesize; c++)
            {
                int u = ch[r][c];
                if(!u) continue;
                q.push(u);
                int v = f[r];
                while(v && !ch[v][c]) v = f[v];
                f[u] = ch[v][c];
                last[u] = val[f[u]] ? f[u] : last[f[u]];
            }
        }
    }

    int getans(int j)
    {
        if(j && vis[j] == false)//vis数组的作用是对于第二组样例的，如果该模式串已经被用过，那么下次再在文本串匹配到不应再用
        {
            vis[j] = true;//j能进到这个说明存在j这个节点，要继续找它的后缀链接，但它不一定是单词节点，所以val[j]可能为0
            return getans(last[j]) + val[j];
        }
        else return 0;
    }

    void Find(const char *s)
    {
        ans = 0;
        int len = strlen(s);
        int j = 0;
        for(int i = 0; i < len; i++)
        {
            int c = id(s[i]);
            while(j && !ch[j][c]) j = f[j];
            j = ch[j][c];
            if(val[j]) ans += getans(j);//说明此时j为单词节点，即trie根节点编号，所以匹配成功
            else if(last[j]) ans += getans(j);//此时j不是单词节点，但也找到它的后缀链接
        }
    }
};

Aho_corasick ac;
char T[1000005];

int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        ac.init();
        char s[60];
        int n;
        scanf("%d", &n);
        for(int i = 0; i < n; i++)
        {
            scanf("%s", s);
            ac.Insert(s);
        }
        ac.getFail();
        scanf("%s", T);
        ac.Find(T);
        printf("%d\n", ac.ans);
    }
    return 0 ;
}

