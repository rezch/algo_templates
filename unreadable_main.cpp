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
 T,class U>T(ceil)(T(x),U(y)){return((x)>(0)?(\
x+y-1)/(y):(x)/y);}template<class T,class U>T(\
floor)(T(x),U(y)){return(x>0?x/y:(x-y+1)/y);}i\
nt(topbit)(int(x)){return(x==0?-1:(31)-__built\
in_clz(x));}int(lowbit)(int(x)){return(x==0?-1\
:__builtin_ctz(x));}int(popcnt)(int(x)){return\
(__builtin_popcount(x));}template<class T,clas\
s U>using umtt=std::unordered_map<T,U>;templat\
e<class T>using vvt=std::vector<std::vector<T>\
>;template<class T,class U>using ptt=std::pair\
<T,U>;template<class T>using umt=std::unordere\
d_map<T,T>;template<class T>using mst=std::mul\
tiset<T>;template<class T>using pt=std::pair<T\
,T>;template<class T>using vt=std::vector<T>;t\
emplate<class T>using stk=std::stack<T>;templa\
te<class T>using qt=std::queue<T>;template<cla\
ss T>using st=std::set<T>;typedef std::string(\
str);typedef vt<pt<int>>(vpi);typedef vvt<int>\
(vvi);typedef vt<int>(vi);typedef pt<int>(pi);\
void(read)(){ };template<class T>void(read_)(T\
&(value)){std::cin>>value;}template<class T,cl\
ass...U>void(read)(T&head,U&...tail){read_(hea\
d);read(tail...);}void(write)( ){std::cout<<st\
d::endl;};template<class T> void(write_)(T(val\
ue)){std::cout<<value<<' ';}template<class T,c\
lass...U>void(write)(T(head),U...tail){write_(\
head);write(tail...);}template<class T>void(se\
t_)(int(n),T(value)){ };template<class T,class\
 U>void(_set)(int(n),T(value),U&list){list.ass\
ign(n,value);};template<class T,class U,class.\
..W>void(set_)(int(n),T(value),U&head,W&...tai\
l){_set(n,value,head);set_(n,value,tail...);};\

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
