# Problem 54: Poker hands

> https://projecteuler.net/problem=54

![](https://blog-1252824460.cos.ap-nanjing.myqcloud.com/project_euler_54_1.png)

[download poker.txt](https://projecteuler.net/project/resources/p054_poker.txt)

## 分析

扑克游戏

扑克游戏中，一手牌包括5张卡牌，并且等级(rank)从低到高排序如下：

- 高牌，即大散牌(High Card): Highest value card.
- 一对(One Pair)
- 两对(Two Pairs)
- 三条(Three of a Kind)
- 顺子(Straight)
- 同花(Flush)
- 葫芦，即三条+一对(Full House)
- 四条(Four of a Kind)
- 同花顺(Straight Flush)
- 皇家同花顺(Royal Flush) : 10, J, Q, K, A 的同花顺


卡牌的数值是：2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace.

如果两个玩家的手牌等级一样，则数值更高的玩家获胜，如 一对八 赢 一对五。 如果玩家的手牌等级打平，比如都有一对 Q，那么则比较散牌中的最大值，如果散牌最大值相等，则继续比较次大值，依次类推。

题中给出了一些手牌和比较的结果。

[poker.txt](https://projecteuler.net/project/resources/p054_poker.txt) 中包含了1000手随机的两个玩家的手牌，文件中每一行包含10张牌，以空格分割，前5个是玩家1的手牌，后5个是玩家2的手牌。保证所有的手牌都是有效的(没有无效的字符或者重复的卡牌)。

每个玩家的手牌没有特定的顺序，每手牌都有一个明显的赢家。

求： 玩家1 赢的次数

## 方法

题目比较简单，只是实现的代码较多。封装了两个类，**Card** 和 **Hand** 分别表示一张牌和一手牌。 依次读取文件的每一行，分成两手牌 player1 和 player2, 比较两手牌的大小即可。

手牌的比较，实现在 **Hand.Compare()** 中。

```cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// 一张牌
class Card{
public:

    Card(char value, char suit){
        m_value = traslateCardValue(value);
        m_suit = suit;
    }

    Card(const Card& c){
        m_value = c.GetValue();
        m_suit = c.GetSuit();
    }

    Card(){}
    ~Card(){}

    int GetValue() const {
        return m_value;
    }

    char GetSuit() const {
        return m_suit;
    }

    // 比较两张牌的大小，只比较面值，不比较花色。
    // 返回：1 表示比c大，0 表示和c相等，-1 表示比c小 
    int Compare(const Card& c) const {
        if(m_value > c.GetValue()) return 1;
        if(m_value == c.GetValue()) return 0;
        return -1;
    }

private:
    int traslateCardValue(char c){
        if(c == '2') return 2;
        if(c == '3') return 3;
        if(c == '4') return 4;
        if(c == '5') return 5;
        if(c == '6') return 6;
        if(c == '7') return 7;
        if(c == '8') return 8;
        if(c == '9') return 9;
        if(c == 'T') return 10;
        if(c == 'J') return 11;
        if(c == 'Q') return 12;
        if(c == 'K') return 13;
        if(c == 'A') return 14;

        return 0;
    }

    int m_value; // 卡牌的面值，2, 3, 4, 5, 6, 7, 8, 9, 10(Ten), 11(Jack), 12(Queen), 13(King), 14(Ace)
    char m_suit; // 卡牌的花色，C/D/H/S, C 梅花 clubs (♣), D 方片 diamonds (♦), H 红桃 hearts (♥) and S 黑桃 spades (♠)
};

// 一手牌
class Hand{
public:
    Hand(const std::vector<Card>& cards){
        for(int i = 0; i < 5; i++){
            m_cards[i] = cards[i];
        }

        // 将手牌从小到大排序，便于后面的比较
        std::sort(m_cards, m_cards+5, cardCompare);

        // 计算手牌的等级
        m_rank = calcRank();
    }

    // 1, 高牌，即大散牌(High Card)
    // 2, 一对(One Pair)
    // 3, 两对(Two Pairs)
    // 4, 三条(Three of a Kind)
    // 5, 顺子(Straight)
    // 6, 同花(Flush)
    // 7, 葫芦，即三条+一对(Full House)
    // 8, 四条(Four of a Kind)
    // 9, 同花顺(Straight Flush)
    // 10, 皇家同花顺(Royal Flush) : 10, J, Q, K, A 的同花顺
    int GetRank() const {
        return m_rank;
    }

    Card GetCardAt(int i) const {
        return m_cards[i];
    }

    // 如果是四条，返回四条的起始手牌位置
    int GetFourCardsIndex() const {
        return m_fourCardsIndex;
    }

    // 如果是葫芦或三条，返回三条的起始手牌位置
    int GetThreeCardsIndex() const {
        return m_threeCardsIndex;
    }

    // 葫芦时，一对的起始手牌位置，两对时，较大的对子的起始手牌位置，一对时，对子的起始手牌位置
    int GetPairIndex() const {
        return m_pairIndex;
    }

    // 如果是两对，返回较小对子的起始手牌位置
    int GetSmallerPairIndex() const {
        return m_smallerPairIndex;
    }

    // 比较两手牌的大小，不比较花色(即花色之间无大小区分)
    // 返回：1 表示比c大，0 表示和c相等，-1 表示比c小 
    int Compare(const Hand& h) const {
        // (1) 比较等级
        if( m_rank > h.GetRank() ) return 1;
        if( m_rank < h.GetRank() ) return -1;

        // (2) 同等级，比较牌面值

        // 都是皇家同花顺，相等
        if( m_rank == 10 ) return 0;

        // 都是同花顺，比较面值
        if( m_rank == 9 ){
            return m_cards[0].Compare( h.GetCardAt(0) );
        }

        // 都是四条，先比较四条，如果四条相等，再比较单牌
        if( m_rank == 8 ){

            // 比较四条
            int cmp = m_cards[m_fourCardsIndex].Compare( h.GetCardAt(h.GetFourCardsIndex()) );
            if(cmp != 0) return cmp;

            // 四条也相等，比较单牌
            int ownHighCardIndex = (m_fourCardsIndex == 0) ? 4 : 0;       // 自己手牌的单张位置
            int peerHighCardIndex = (h.GetFourCardsIndex() == 0) ? 4 : 0; // 对手手牌的单张位置

            return m_cards[ownHighCardIndex].Compare(h.GetCardAt(peerHighCardIndex));
        }

        // 都是葫芦，先比较三条，再比较对子
        if( m_rank == 7 ){

            // 先比较三条
            int cmp = m_cards[m_threeCardsIndex].Compare( h.GetCardAt(h.GetThreeCardsIndex()) );
            if(cmp != 0) return cmp;

            // 再比较对子
            return m_cards[m_pairIndex].Compare(h.GetCardAt(h.GetPairIndex()));
        }

        // 都是同花，从高到低依次比较
        if( m_rank == 6 ){
            for(int i = 4; i >= 0; i--){
                int cmp = m_cards[i].Compare(h.GetCardAt(i));
                if(cmp != 0) return cmp;
            }
            return 0;
        }

        // 都是顺子，直接比较
        if( m_rank == 5 ){
            return m_cards[0].Compare(h.GetCardAt(0));
        }

        // 都是三条，先比较三条，再比较剩下的两个单牌
        if( m_rank == 4 ){

            // 先比较三条
            int cmp = m_cards[m_threeCardsIndex].Compare( h.GetCardAt(h.GetThreeCardsIndex()) );
            if(cmp != 0) return cmp;

            // 再比较剩下的两个单牌
            for(int i = 4; i >= 0; i--){
                if( i == m_threeCardsIndex || i == m_threeCardsIndex + 1 || i == m_threeCardsIndex + 2) continue; // 跳过三条

                for(int j = 4; j >= 0; j--){
                    if( j == h.GetThreeCardsIndex() || j == h.GetThreeCardsIndex() + 1 || j == h.GetThreeCardsIndex() + 2) continue; // 跳过三条

                    cmp = m_cards[i].Compare( h.GetCardAt(j) );
                    if(cmp != 0) return cmp;
                }
            }

            return 0;
        }

        // 都是两对，先比较两对，再比较单牌
        if ( m_rank == 3 ){

            // 先比较两对
            int cmp = m_cards[m_pairIndex].Compare( h.GetCardAt(h.GetPairIndex()) );
            if(cmp != 0) return cmp;

            cmp = m_cards[m_smallerPairIndex].Compare( h.GetCardAt(h.GetSmallerPairIndex()) );
            if(cmp != 0) return cmp;

            // 再比较单牌
            for(int i = 4; i >= 0; i--){
                // 跳过两对
                if( i == m_pairIndex || i == m_pairIndex + 1 || 
                    i == m_smallerPairIndex || i == m_smallerPairIndex + 1 
                ){
                    continue; 
                }

                for(int j = 4; j >= 0; j--){
                    // 跳过两对
                    if( j == h.GetPairIndex() || j == h.GetPairIndex() + 1 || 
                        j == h.GetSmallerPairIndex() || j == h.GetSmallerPairIndex() + 1 
                    ){
                        continue; 
                    }

                    cmp = m_cards[i].Compare( h.GetCardAt(j) );
                    if(cmp != 0) return cmp;
                }
            }

            return 0;
        }

        // 都是一对，先比较一对，再比较单牌
        if( m_rank == 2 ){

            // 先比较一对
            int cmp = m_cards[m_pairIndex].Compare( h.GetCardAt(h.GetPairIndex()) );
            if(cmp != 0) return cmp;

            // 再比较单牌
            for(int i = 4; i >= 0; i-- ){ 
                if( i == m_pairIndex || i == m_pairIndex + 1) continue; // 跳过对子

                for(int j = 4; j >= 0; j-- ){
                    if( j == h.GetPairIndex() || j == h.GetPairIndex() + 1) continue; // 跳过对子

                    cmp = m_cards[i].Compare( h.GetCardAt(j) );
                    if(cmp != 0) return cmp;
                }
            }

            return 0;
        }

        // 都是高牌，即散牌，从高到低比较
        for(int i = 4; i >= 0; i-- ){ 
            for(int j = 4; j >= 0; j-- ){
                int cmp = m_cards[i].Compare( h.GetCardAt(j) );
                if(cmp != 0) return cmp;
            }
        }

        return 0;
    }

private:
    static bool cardCompare (Card c1, Card c2) { 
        return c1.Compare(c2) < 0 ;
    }

    // 计算手牌的等级
    int calcRank(){
        if(hasRoyalFlush()) return 10;
        if(hasStraightFlush()) return 9;
        if(hasFourOfAKind()) return 8;
        if(hasFullHouse()) return 7;
        if(hasFlush()) return 6;
        if(hasStraight()) return 5;
        if(hasThreeOfAKind()) return 4;
        if(hasTwoPairs()) return 3;
        if(hasOnePair()) return 2;
        return 1;
    }

    // [手牌已从小到大排序] 检查是否有一对
    bool hasOnePair(){
        for(int i = 0; i < 4; i++){
            if( m_cards[i].GetValue() == m_cards[i+1].GetValue()){
                m_pairIndex = i;
                return true;
            }
        }
        return false;
    }

    // [手牌已从小到大排序] 检查是否有两对
    bool hasTwoPairs(){

        int firstIndex = -1;
        for(int i = 0; i < 4; i++){
            if( m_cards[i].GetValue() == m_cards[i+1].GetValue()){ // 找到一对
                if(firstIndex == -1 ) { // 第一对
                    firstIndex = i;
                    i++;
                }else{ // 第二对 
                    m_smallerPairIndex = firstIndex;
                    m_pairIndex = i;
                    return true;
                }
            }
        }

        return false;
    }

    // [手牌已从小到大排序] 检查是否有三条
    bool hasThreeOfAKind(){
        for(int i = 0; i < 3; i++){
            if( m_cards[i].GetValue() == m_cards[i+1].GetValue() &&
                m_cards[i].GetValue() == m_cards[i+2].GetValue()
            ){
                m_threeCardsIndex = i;
                return true;
            }
        }
        return false;
    }

    // [手牌已从小到大排序] 检查是否有顺子
    bool hasStraight(){
        if( m_cards[1].GetValue() == m_cards[0].GetValue() + 1 &&
            m_cards[2].GetValue() == m_cards[0].GetValue() + 2 &&
            m_cards[3].GetValue() == m_cards[0].GetValue() + 3 &&
            m_cards[4].GetValue() == m_cards[0].GetValue() + 4
        ){
            return true;
        }
        return false;
    }

    // [手牌已从小到大排序] 检查是否有同花
    bool hasFlush()
    {
        // 花色相同
        if( m_cards[1].GetSuit() == m_cards[0].GetSuit() &&
            m_cards[2].GetSuit() == m_cards[0].GetSuit() &&
            m_cards[3].GetSuit() == m_cards[0].GetSuit() &&
            m_cards[4].GetSuit() == m_cards[0].GetSuit()
        ){
            return true;
        }
        return false;
    }

    // [手牌已从小到大排序] 检查是否有葫芦
    bool hasFullHouse(){
        // aaabb
        if( m_cards[1].GetValue() == m_cards[0].GetValue() && 
            m_cards[2].GetValue() == m_cards[0].GetValue() && 
            m_cards[3].GetValue() == m_cards[4].GetValue() 
        ){ 
            m_threeCardsIndex = 0;
            m_pairIndex = 3;
            return true;
        }

        // aabbb
        if( m_cards[0].GetValue() == m_cards[1].GetValue() && 
            m_cards[3].GetValue() == m_cards[2].GetValue() && 
            m_cards[4].GetValue() == m_cards[2].GetValue() 
        ){ 
            m_threeCardsIndex = 2;
            m_pairIndex = 0;
            return true;
        }

        return false;
    }

    // [手牌已从小到大排序] 检查是否有四条
    bool hasFourOfAKind(){
        for(int i = 0; i < 2; i++){
            if( m_cards[i].GetValue() == m_cards[i+1].GetValue() &&
                m_cards[i].GetValue() == m_cards[i+2].GetValue() &&
                m_cards[i].GetValue() == m_cards[i+3].GetValue()
            ){
                m_fourCardsIndex = i;
                return true;
            }
        }
        return false;
    }

    // [手牌已从小到大排序] 检查是否有同花顺
    bool hasStraightFlush(){
        return hasStraight() && hasFlush();
    }

    // [手牌已从小到大排序] 检查是否有皇家同花顺
    bool hasRoyalFlush(){
        return (m_cards[0].GetValue() == 10) && hasStraightFlush();
    }

    Card m_cards[5]; // 一手牌包括五张牌
    int m_rank;      // 手牌的等级

    // 一些关键信息，用于比较，在判断等级时就记录，避免后续重复判断手牌
    int m_fourCardsIndex;   // 如果是四条，保存四条的起始手牌位置
    int m_threeCardsIndex;  // 葫芦和三条时，保存三条的起始手牌位置
    int m_pairIndex;        // 葫芦时，一对的起始手牌位置，两对时，较大的对子的起始手牌位置，一对时，对子的起始手牌位置
    int m_smallerPairIndex; // 两对时，较小对子的起始手牌位置
};

int main()
{
    int player1WinCnt = 0;

    // 从文件中读取每一行的两手牌
    std::ifstream f("poker.txt");   
    char line[64] = {0};
    while( f.getline(line, 64)){
        // 将每一行分割成 10 张牌，分别给 玩家1 和 玩家2
        std::vector<Card> cards1;
        std::vector<Card> cards2;

        std::string s = line;
        std::istringstream iss(s);
        std::string item;
        while (std::getline(iss, item, ' ')) {
            //std::cout << item << std::endl;   
            Card c(item[0], item[1]);
            if(cards1.size() < 5){ // 前 5 张牌给玩家1
                cards1.push_back(c);
            } else{                // 后 5 张牌给玩家2
                cards2.push_back(c);
            }
        }

        // 比较玩家1 和 玩家2 的手牌
        Hand player1(cards1);
        Hand player2(cards2);
        if(player1.Compare(player2) > 0){
            player1WinCnt ++;
        }
    }
    f.close();

    std::cout<<player1WinCnt<<std::endl;
    return 0;
}
```

## 答案

376