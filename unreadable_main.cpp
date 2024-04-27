#ifndef UwU
#pragma GCC optimize ("Ofast,unroll-loops")
#endif

#include <bits/stdc++.h>

#define timer(func,...){auto(start_time)=std::\
chrono::steady_clock::now();func(__VA_ARGS__);\
auto(end_time)=std::chrono::steady_clock::now(\
);auto(elapsed_ns)=std::chrono::duration_cast<\
std::chrono::milliseconds>(end_time-start_time\
);std::cout<<"Time elapsed: "<<elapsed_ns.coun\
t()<<" ms\n";}
#define fast std::cin.tie(0);std::cout.tie(0);\
std::ios_base::sync_with_stdio(0);
#define out std::cout
#define arng(var,from,to)for(int(var)=from;var\
<to;++var)
#define rng(var,to)arng(var,0,to)
#define test(test_count,func,...){rng(i,test_c\
ount){timer(func,__VA_ARGS__);}}
#define ifout(statement,ok_msg,other_msg){if(s\
tatement){std::cout<<ok_msg<<' ';}else{std::co\
ut<<other_msg<<' ';}}
#define solve_t(func){int(t);in>>t;rng(i,t){fu\
nc();}}
#define mp std::make_pair
#define mrng(vara,varb,ind1,ind2)rng(vara,ind1\
)rng(varb,ind2)
#define iter(var,list)for(auto&(var):list)
#define asrng(var,from,to,step)for(int(var)=fr\
om;(-1+2*int(step>0))*var<(-1+2*int(step>0))*t\
o;var+=step)
#define cauto const auto&
#define srng(var,to,step)for(int var=0;(-1+2*i\
nt(step > 0))*var<(-1+2*int(step>0))*to;var+=s\
tep)
#define pb push_back
#define in std::cin
#define print(list)iter(var,list){std::cout<<v\
ar<<' ';}std::cout<<std::endl;
#define prints(list,ostream)iter(var,list){ost\
ream<<var<<' ';}ostream<<std::endl;
#define clr(list,size)std::memset(&list,0,size\
of(list[0])*size);
#define inputs(list,istream)iter(var,list){ist\
ream>>var;}
#define retn std::cout<<std::endl;return;
#define all(list)list.begin(),list.end()
#define rsort_(list)std::sort(list.rbegin(),li\
st.rend())
#define lcm(x,y)(x * y / std::__gcd(x, y))
#define gcd(x,y)std::__gcd(x, y)
#define input(list)iter(var,list){std::cin>>va\
r;}
#define eb emplace_back
#define sw(a,b)std::swap(a, b);
#define sort_(list)std::sort(list.begin(),list\
.end())
#define writef(filename)freopen(filename,"w",s\
tdout);
#define nl std::endl
#define readf(filename)freopen(filename,"r",st\
din);
#define ret(x)std::cout<<x<<std::endl;return;
#define precision(n)std::fixed<<std::setprecis\
ion(n)
#define rall(list)list.rbegin(),list.rend()
template<class T>bool(set_max)(T&a,T(b)){{if(a\
>=b)return(false);}{a=b;return(true);}}templat\
e<class T>bool(set_min)(T&a,T(b)){{if(a<=b)ret\
urn(false);}{a=b;return(true);}}template<class\
 T,class U>T(ceil)(T(x),U(y)){return(x>0?(x+y-\
1)/y:x/y);}template<class T,class U>T(floor)(T\
(x),U(y)){return(x>0?x/y:(x-y+1)/y);}int(topbi\
t)(int(x)){return(x==0?-1:31-__builtin_clz(x))\
;}int(lowbit)(int(x)){return(x==0?-1:__builtin\
_ctz(x));}int(popcnt)(int(x)){return __builtin\
_popcount(x);}template<class T,class U>using u\
mtt=std::unordered_map<T,U>;template<class T>u\
sing vvt=std::vector<std::vector<T>>;template<\
class T,class U>using ptt=std::pair<T,U>;templ\
ate<class T>using umt=std::unordered_map<T,T>;\
template<class T>using mst=std::multiset<T>;te\
mplate<class T>using pt=std::pair<T,T>;templat\
e<class T>using vt=std::vector<T>;template<cla\
ss T>using stk=std::stack<T>;template<class T>\
using qt=std::queue<T>;template<class T>using \
st=std::set<T>;typedef std::string(str);typede\
f vt<pt<int>>(vpi);typedef vvt<int>(vvi);typed\
ef vt<int>(vi);typedef pt<int>(pi);void(read)(\
){};template<class T>void(read_)(T&value){std:\
:cin>>value;}template<class T,class...U>void(r\
ead)(T&head,U&...tail){read_(head);read(tail..\
.);}void(write)(){std::cout<<std::endl;};templ\
ate<class T> void(write_)(T(value)){std::cout<\
<value<<' ';}template<class T,class...U>void(w\
rite)(T(head),U...tail){write_(head);write(tai\
l...);}template<class T>void(set_)(int(n),T(va\
lue)){};template<class T,class U>void(_set)(in\
t(n),T(value),U&list){list.assign(n,value);};t\
emplate<class T,class U,class...W>void(set_)(i\
nt(n),T(value),U&head,W&...tail){_set(n,value,\
head);set_(n,value,tail...);};

// ------------------ SOLVE ------------------


void solve() {
    /* ?w? */
}


signed main() {
    fast;

#ifdef UwU
    readf("input.in");
//    writef("output.out");
    test(6969, solve);
#else
//    readf("rmq.in");
//    writef("rmq.out");
    solve();
#endif
//    solve_t(solve);

    return 0;
}
