#include <bits/stdc++.h>


namespace combinatorics {
    int64_t mod = 1000000007;

    int64_t fac64(int64_t x) {
        static const int64_t table[] = { // all factorials that fit into int64
                1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600, 6227020800, 87178291200,
                1307674368000, 20922789888000, 355687428096000, 6402373705728000, 121645100408832000,
                2432902008176640000
        };
        assert(x >= 0);
        assert(x <= 20);
        return table[x];
    }

    int64_t fac32(int64_t x) { // factorials mod 1000000007 (from 0! to 200!)
        static const int64_t table[] = {
                1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600, 227020758, 178290591,
                674358851, 789741546, 425606191, 660911389, 557316307, 146326063, 72847302, 602640637, 860734560,
                657629300, 440732388, 459042011, 394134213, 35757887, 36978716, 109361473, 390205642, 486580460,
                57155068, 943272305, 14530444, 523095984, 354551275, 472948359, 444985875, 799434881, 776829897,
                626855450, 954784168, 10503098, 472639410, 741412713, 846397273, 627068824, 726372166, 318608048,
                249010336, 948537388, 272481214, 713985458, 269199917, 75195247, 286129051, 595484846, 133605669,
                16340084, 996745124, 798197261, 286427093, 331333826, 536698543, 422103593, 280940535, 103956247,
                172980994, 108669496, 715534167, 518459667, 847555432, 719101534, 932614679, 878715114, 661063309,
                562937745, 472081547, 766523501, 88403147, 249058005, 671814275, 432398708, 753889928, 834533360,
                604401816, 187359437, 674989781, 749079870, 166267694, 296627743, 586379910, 119711155, 372559648,
                765725963, 275417893, 990953332, 104379182, 437918130, 229730822, 432543683, 551999041, 407899865,
                829485531, 925465677, 24826746, 681288554, 260451868, 649705284, 117286020, 136034149, 371858732,
                391895154, 67942395, 881317771, 114178486, 473061257, 294289191, 314702675, 79023409, 640855835,
                825267159, 333127002, 640874963, 750244778, 281086141, 979025803, 294327705, 262601384, 400781066,
                903100348, 112345444, 54289391, 329067736, 753211788, 190014235, 221964248, 853030262, 424235847,
                817254014, 50069176, 159892119, 24464975, 547421354, 923517131, 757017312, 38561392, 745647373,
                847105173, 912880234, 757794602, 942573301, 156287339, 224537377, 27830567, 369398991, 365040172,
                41386942, 621910678, 127618458, 674190056, 892978365, 448450838, 994387759, 68366839, 417262036,
                100021558, 903643190, 619341229, 907349424, 64099836, 89271551, 533249769, 318708924, 92770232,
                420330952, 818908938, 584698880, 245797665, 489377057, 66623751, 192146349, 354927971, 661674180,
                71396619, 351167662, 19519994, 689278845, 962979640, 929109959, 389110882, 98399701, 89541861,
                460662776, 289903466, 110982403, 974515647, 928612402, 722479105
        };
        assert(x >= 0);
        assert(x <= 200);
        return table[x];
    }

    int64_t pow(int64_t a, int64_t b) { // fast pow
        assert(b >= 0);
        if (!b) { return 1; }
        int64_t m = pow(a, b >> 1);
        m = (m * m) % mod;
        if (b & 1) { m = (m * a) % mod; }
        return m;
    }

    int64_t inv(int64_t x) { // multiply invariant
        return pow(x, mod - 2);
    }

    int64_t nCr(int64_t n, int64_t r) { // number if combinations
        assert(n >= r);
        int64_t n1 = fac32(n), d1 = inv(fac32(n - r)), d2 = inv(fac32(r));
        d1 = (d1 * d2) % mod;
        return (n1 * d1) % mod;
    }
}
