/*
 * https://leetcode.com/problems/substring-with-concatenation-of-all-words/
 * 题目：给定一个字符串数组 words，里面每个字符串的长度相同。 在字符串s中找出所有由 words 中所有字符串组成子串。
 *      比如 words = [ab,cd,ef], 则需要从 s 中找出所有子串 abcdef/abefcd/cdabef/cdefab/efabcd/efcdab 的位置
 * 思路：详见思路1
 *
 */
#include <iostream>
#include <string_view>
using namespace std;

#define TEST(a, b) ((a == b) ? "pass" : "fail")

//Accepted 930 ms Beats 22.69%
// 思路1 借鉴 28题 find-the-index-of-the-first-occurrence-in-a-string 中的hash算法
// 1. 先对 words 生成一个 hash 值，这个 hash 值和 words 中元素有关，与元素位置无关
// 2. 然后 遍历 s，判断 hash 值，如果hash值不相等，则继续匹配下一个字符；如果hash值相等，则进入3
// 3. 判断 子串 sub 是否包含了 words 中所有元素
// 备注：使用 string_view 提高效率
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        int RADIX = 26;      // 26 个字母，radix >= 26 即可
        int MOD = 1000000033;// 一个大的质数

        // 将 words 转换为 string_view 数组，统一处理
        vector<string_view> wordsCpy;
        std::copy(words.begin(), words.end(), std::back_inserter(wordsCpy));
        std::sort(wordsCpy.begin(), wordsCpy.end()); // 排序，方便后续的比较

        vector<int> results;
        int hashWords = hashVec(wordsCpy, RADIX, MOD);
        int wordLen = words[0].size();    // words 中每个元素的长度，words 的长度保证为：1 <= words.length <= 5000，所以可以直接使用 words[0]
        int wordCnt = words.size();       // words 中元素的个数
        int charsCnt = wordCnt * wordLen; // words 中所有字符的总数
        string_view  sv(s);               // 将 string 转换为 string_view，提高后续的substr效率
        for(int i = 0; i < sv.size() - charsCnt + 1; i++){
            // 计算 sv[i, i + charsCnt] 子串的hash值 [分割成 wordCnt 个 wordLen 长度的子串来计算]
            string_view sub = sv.substr(i, charsCnt);
            vector<string_view> vec;
            for(int j = 0; j < wordCnt; j ++) {
                vec.push_back(sub.substr(j * wordLen, wordLen));
            }
            int h = hashVec(vec, RADIX, MOD);

            // 如果 sv[i, i + charsCnt] 和 words 的hash相同，则可能是一个满足条件的子串，需要再逐项对比，来最终确认
            if(h == hashWords){
                if(compareVec(vec, wordsCpy)){ // 比较两个 vector，检查其元素是否完全相同，不关系元素位置
                    results.push_back(i);
                }
            }
        }

        return results;
    }

    // 比较 subs 和 words，检查两个数组中的元素是否完全相同（元素位置无所谓）
    bool compareVec(vector<string_view>& subs, const vector<string_view>& words) {
        if(subs.size() != words.size()) return false;
        std::sort(subs.begin(), subs.end()); // subs 排序， words 已经排过序
        for(int i = 0; i < subs.size(); i++){
            if(subs[i] != words[i]) return false;
        }
        return true;
    }

    int hashVec(const vector<string_view>& words, int RADIX, int MOD) {
        int h = 0;
        for(auto word : words){
            h = (h + hashValue(word, RADIX, MOD)) % MOD;
        }
        return h;
    }

    int hashValue(string_view str, int RADIX, int MOD) {
        long ans = 0;
        long factor = 1;
        for(auto c:str){
            ans += ((long) (c - 'a') * factor) % MOD;
            factor = (factor * RADIX) % MOD;
        }
        return ans % MOD;
    }
};


// 相比思路1 效率更高
// 思路2  使用 hashmap 记录 words 中每个字符串出现的次数 （因为 words 中可能有相同的字符串），然后遍历过程中，也使用 hashmap 记录遍历的字符串出现次数，来防止重复字符串问题
// From: https://leetcode.com/problems/substring-with-concatenation-of-all-words/solutions/13658/easy-two-map-solution-c-java/
//       其实和官方的思路类似，都是使用 hashmap 来判断存在和出现次数
// 如：s = "barfoothefoobarman", words = {"foo","bar"}
//    (1) 使用 counts 记录 words 每个字符串的出现次数， 得到 counts["foo"] = 1, counts["bar"] = 1
//    (2) 遍历 s，每次取 2 个子串 (即 words.size())，每个子串长度为 3 (即 words[0].size())
//        使用 found 来记录遍历时子串出现的次数，如果子串不在words中 或者 子串出现的次数比 counts 中多，则跳到下一个位置，重新遍历
//        如果 2个子串都遍历完成，则说明找到一个解。
class Solution2 {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        // 计算 words 中每个字符串出现的次数，记录在 counts 中
        std::unordered_map<string, int> counts;
        for (auto word : words) {
            counts[word]++;
        }

        vector<int> results;
        int wordLen = words[0].size();    // words 中每个元素的长度，words 的长度保证为：1 <= words.length <= 5000，所以可以直接使用 words[0]
        int wordCnt = words.size();       // words 中元素的个数
        int charsCnt = wordCnt * wordLen; // words 中所有字符的总数
        for(int i = 0; i < s.size() - charsCnt + 1; i++){
            std::unordered_map<string, int> found; // 记录 i 位置开始的串中，每个子串出现的次数
            int j = 0;
            for(; j < wordCnt; j++){
                string word = s.substr(i + j * wordLen, wordLen);
                if(counts.find(word) == counts.end()) break; // 子串不存在，则直接跳过
                found[word] ++;
                if(found[word] > counts[word]) break; // 出现的次数比 words 中多，则匹配失败，跳过
            }

            if (j == wordCnt) {
                results.push_back(i);
            }
        }
        return results;
    }
};

void PrintVector(const vector<int>& vec)
{
    cout << "[";
    for(int i = 0; i < vec.size(); i++){
        cout << vec[i];
        if(i < vec.size() - 1) cout << ", ";
    }
    cout <<"]"<<endl;
}

int main()
{
//    std::string_view s1 = "abc\0\0def";
//    std::string_view s2 = "abc\0\0def"sv;
//    std::cout << "s1: " << s1.size() << " \"" << s1 << "\"\n"; // 3, abc
//    std::cout << "s2: " << s2.size() << " \"" << s2 << "\"\n"; // 8, abcdef

    auto start = chrono::steady_clock::now();

    Solution s;

//    // case 1
    string s1 = "barfoothefoobarman";
    vector<string> words1 = {"foo","bar"};
    auto result1 = s.findSubstring(s1,words1);
    PrintVector(result1); // expect [0, 9]

    // case 2
    string s2 = "dlmogiklbqfggokuonfgugiyammwvwhbjvrqgdbjtipcwzwmobtjjdhmpvknrsqbpjtvmwfifukbwgokjjvvmeheatttljwdupygofotcywygmksvipkmyqmrjifueiouiukoldqlzquocojkdvzdlnuuvbqajewubgiolazmsvaujmfohervtorppipbolvrtdfefhqxcrrofycmewjykbnzjeazrxrkayohfgekzwyewctbyczidokoskojihvkflslryxruvxrzquytvgyjsndddmnkhzrstclsbeowchwsbwnwemhxbkcgwpqfqjzmmlenpumrckmdgzcmnjjqulwscoytyxhkklzahntjzfphhruwadnwpjptypmwovizijzqzuzycogjhahkdugugxoemccbymagvbyuxytzobkwbsigoobuoraatedrqfamiyigydhpeslhmvoajrxzixabcfvslxgvvpbwujlzdygptureloetogxslsmyrtuokxkeivflvmcoiutwkzryfoqsidtzypqkmaqxywktknisjdoteisjykdhpyipnyzcbqzzolsyycsjfjdjrxupjayzyhqohqqiirjyccwdgoomxtxqqugcwedwntkxlcfvvrtatpfbgtnfnnwfjchfikdwgotrsanorgqmyvoeqdldshldlsiufoslencwprmhyevwzlcqrpvlzgpkbzggnytrnxqdpekpjhnivraogwzfeoqfoynbzgvmelpvpbkyjxjgojuwhtcmkurysfbrnwerjvozxazixionukkbfonpihpcorwbpcvzxjaukzejksxeejhkxxzhgpjuihvxjqyhaydmaivkcuqhdztcyulelvyteutokrxmscasmwepswyyxrawnmazjbsnvndhfcwzfwrruxinvilsbnopbroksiapwfydkwcptvipstepbphffyugrktlsvaqaatkxxbssmhmhmbidjpijjravklofnghnaumxvesjoeqcibhtqsccjextpnaeuhtwdgvbknkaubccemvuezyndwiujkyftrbxxzykmkkilpkrdhohgmwjigduqdbjvdgueggqrtbeknwnvkubysnjysdowgztjipnowghpjmbwkorwkvuckfaciqaprvazlqqjyxahlbdxpxvzusdexfiivlzogbotrgerfeathgqydmxzgcddhnleykthmjcfphzwnzpvfgtkutjavoffcrjcdejrpoxevydkxsffabruwbwtrcytvkyyqhqgvpmsnpdmiktinlflmdffffzcrxbigtqeicyxudlcofmdqtpexwjebkhtjidsdtwlvwkpavtqaitsbkyagifiumdewgwzzumwqyoqtjgwrcqvmpvtzadtogxmmvnlrzjixxathjpylhvzwruvtxpkdowrmkedlonjloeuxtvkcqjzjeuddlnhalamvfrhvfsitwdsryetqnu";
    vector<string> words2 = {"pbolvrtdfefhqxcrrofyc","mewjykbnzjeazrxrkayoh","fgekzwyewctbyczidokos","kojihvkflslryxruvxrzq","uytvgyjsndddmnkhzrstc","lsbeowchwsbwnwemhxbkc","gwpqfqjzmmlenpumrckmd","gzcmnjjqulwscoytyxhkk","lzahntjzfphhruwadnwpj","ptypmwovizijzqzuzycog","jhahkdugugxoemccbymag","vbyuxytzobkwbsigoobuo","raatedrqfamiyigydhpes","lhmvoajrxzixabcfvslxg","vvpbwujlzdygptureloet","ogxslsmyrtuokxkeivflv","mcoiutwkzryfoqsidtzyp","qkmaqxywktknisjdoteis","jykdhpyipnyzcbqzzolsy","ycsjfjdjrxupjayzyhqoh","qqiirjyccwdgoomxtxqqu","gcwedwntkxlcfvvrtatpf","bgtnfnnwfjchfikdwgotr","sanorgqmyvoeqdldshldl","siufoslencwprmhyevwzl","cqrpvlzgpkbzggnytrnxq"};
    auto result2 = s.findSubstring(s2,words2);
    PrintVector(result2); // expect [187]

    auto end = chrono::steady_clock::now();
    cout<< "cost:" << chrono::duration_cast<chrono::milliseconds>(end-start).count() <<endl;
    return 0;
}