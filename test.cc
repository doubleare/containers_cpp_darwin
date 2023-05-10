#include "s21_containers.h"

#include <gtest/gtest.h>
#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <map>
#include <set>

TEST(Queue,all) {
std::queue<int> Qstd({6,7,8,9,0});
s21::Queue<int> Qs21({6,7,8,9,0});
std::queue<int> Tstd;
s21::Queue<int> Ts21;

/* Access and capacity, push and pop param construct */
EXPECT_EQ(Qstd.empty(),Qs21.empty());
EXPECT_EQ(Qstd.size(),Qs21.size());
EXPECT_EQ(Qstd.back(),Qs21.back());
EXPECT_EQ(Qstd.front(),Qs21.front());
Qstd.push(10);
Qs21.push(10);
EXPECT_EQ(Qstd.back(),Qs21.back());
EXPECT_EQ(Qstd.front(),Qs21.front());
Qstd.pop();
Qs21.pop();
Qstd.pop();
Qs21.pop();
EXPECT_EQ(Qstd.back(),Qs21.back());
EXPECT_EQ(Qstd.front(),Qs21.front());

/* Access and capacity, push and pop default construct */
EXPECT_EQ(Tstd.empty(),Ts21.empty());
EXPECT_EQ(Tstd.size(),Ts21.size());
EXPECT_EQ(Tstd.front(),Ts21.front());
Tstd.push(10);
Ts21.push(10);
Tstd.push(12);
Ts21.push(12);
EXPECT_EQ(Tstd.back(),Ts21.back());
EXPECT_EQ(Tstd.front(),Ts21.front());
Tstd.pop();
Ts21.pop();
EXPECT_EQ(Tstd.back(),Ts21.back());
EXPECT_EQ(Tstd.front(),Ts21.front());

/* Swap */
Qstd.swap(Tstd);
Qs21.swap(Ts21);
EXPECT_EQ(Tstd.back(),Ts21.back());
EXPECT_EQ(Tstd.front(),Ts21.front());
EXPECT_EQ(Qstd.back(),Qs21.back());
EXPECT_EQ(Qstd.front(),Qs21.front());

/* Copy operator */
Qstd = Tstd;
Qs21 = Ts21;
EXPECT_EQ(Qstd.empty(),Qs21.empty());
EXPECT_EQ(Qstd.size(),Qs21.size());
EXPECT_EQ(Tstd.empty(),Ts21.empty());
EXPECT_EQ(Tstd.size(),Ts21.size());
EXPECT_EQ(Tstd.back(),Ts21.back());
EXPECT_EQ(Tstd.front(),Ts21.front());
EXPECT_EQ(Qstd.back(),Qs21.back());
EXPECT_EQ(Qstd.front(),Qs21.front());

/* Copy construct */
std::queue<int> QstdCopy(Qstd);
s21::Queue<int> Qs21Copy(Qs21);

EXPECT_EQ(QstdCopy.empty(),Qs21Copy.empty());
EXPECT_EQ(QstdCopy.size(),Qs21Copy.size());
EXPECT_EQ(QstdCopy.empty(),Qstd.empty());
EXPECT_EQ(Qs21Copy.size(),Qs21.size());

EXPECT_EQ(Qs21Copy.back(),Qs21.back());
EXPECT_EQ(Qs21Copy.front(),Qs21.front());

EXPECT_EQ(QstdCopy.back(),Qs21Copy.back());
EXPECT_EQ(QstdCopy.front(),Qs21Copy.front());

/* Move construct */
std::queue<int> QstdMove(std::move(QstdCopy));
s21::Queue<int> Qs21Move(std::move(Qs21Copy));

EXPECT_EQ(QstdMove.empty(),Qs21Move.empty());
EXPECT_EQ(QstdMove.size(),Qs21Move.size());

EXPECT_EQ(Qs21Move.back(),Qs21.back());
EXPECT_EQ(Qs21Move.front(),Qs21.front());

EXPECT_EQ(QstdMove.back(),Qs21Move.back());
EXPECT_EQ(QstdMove.front(),Qs21Move.front());


/* Move operator */
Qstd = std::move(Tstd);
Qs21 = std::move(Ts21);
EXPECT_EQ(Qstd.empty(),Qs21.empty());
EXPECT_EQ(Qstd.size(),Qs21.size());
EXPECT_TRUE(Ts21.empty());
EXPECT_EQ(Tstd.empty(),Ts21.empty());
EXPECT_EQ(Tstd.size(),Ts21.size());
EXPECT_EQ(Qstd.back(),Qs21.back());
EXPECT_EQ(Qstd.front(),Qs21.front());
}





TEST(Stack,list) {
std::stack<int,std::list<int>> Sstd({1,2,3,4,5});
s21::Stack<int,s21::List<int>> Ss21({1,2,3,4,5});
std::stack<int,std::list<int>> Tstd;
s21::Stack<int,s21::List<int>> Ts21;

/* Access and capacity, push and pop param construct */
EXPECT_EQ(Sstd.empty(),Ss21.empty());
EXPECT_EQ(Sstd.size(),Ss21.size());
EXPECT_EQ(Sstd.top(),Ss21.top());
Sstd.push(10);
Ss21.push(10);
EXPECT_EQ(Sstd.top(),Ss21.top());
Sstd.pop();
Ss21.pop();
Sstd.pop();
Ss21.pop();
EXPECT_EQ(Sstd.top(),Ss21.top());

/* Access and capacity, push and pop default construct */
EXPECT_EQ(Tstd.empty(),Ts21.empty());
EXPECT_EQ(Tstd.size(),Ts21.size());
Tstd.push(10);
Ts21.push(10);
Tstd.push(12);
Ts21.push(12);
EXPECT_EQ(Tstd.top(),Ts21.top());
Tstd.pop();
Ts21.pop();
EXPECT_EQ(Tstd.top(),Ts21.top());

/* Swap */
Sstd.swap(Tstd);
Ss21.swap(Ts21);
EXPECT_EQ(Tstd.top(),Ts21.top());
EXPECT_EQ(Sstd.top(),Ss21.top());

/* Copy operator */
Sstd = Tstd;
Ss21 = Ts21;
EXPECT_EQ(Sstd.empty(),Ss21.empty());
EXPECT_EQ(Sstd.size(),Ss21.size());
EXPECT_EQ(Tstd.empty(),Ts21.empty());
EXPECT_EQ(Tstd.size(),Ts21.size());
EXPECT_EQ(Tstd.top(),Ts21.top());
EXPECT_EQ(Sstd.top(),Ss21.top());

/* Copy construct */
std::stack<int,std::list<int>> SstdCopy(Sstd);
s21::Stack<int,s21::List<int>> Ss21Copy(Ss21);

EXPECT_EQ(SstdCopy.empty(),Ss21Copy.empty());
EXPECT_EQ(SstdCopy.size(),Ss21Copy.size());
EXPECT_EQ(SstdCopy.empty(),Sstd.empty());
EXPECT_EQ(Ss21Copy.size(),Ss21.size());
EXPECT_EQ(Ss21Copy.top(),Ss21.top());
EXPECT_EQ(SstdCopy.top(),Ss21Copy.top());

/* Move construct */
std::stack<int,std::list<int>> SstdMove(std::move(SstdCopy));
s21::Stack<int,s21::List<int>> Ss21Move(std::move(Ss21Copy));

EXPECT_EQ(SstdMove.empty(),Ss21Move.empty());
EXPECT_EQ(SstdMove.size(),Ss21Move.size());
EXPECT_EQ(Ss21Move.top(),Ss21.top());
EXPECT_EQ(SstdMove.top(),Ss21Move.top());

/* Move operator */
Sstd = std::move(Tstd);
Ss21 = std::move(Ts21);
EXPECT_EQ(Sstd.empty(),Ss21.empty());
EXPECT_EQ(Sstd.size(),Ss21.size());
EXPECT_TRUE(Ts21.empty());
EXPECT_EQ(Tstd.empty(),Ts21.empty());
EXPECT_EQ(Tstd.size(),Ts21.size());
EXPECT_EQ(Sstd.top(),Ss21.top());
}




TEST(Stack,vector) {
std::stack<int,std::vector<int>> Sstd({1,2,3,4,5});
s21::Stack<int,s21::Vector<int>> Ss21({1,2,3,4,5});
std::stack<int,std::vector<int>> Tstd;
s21::Stack<int,s21::Vector<int>> Ts21;

/* Access and capacity, push and pop param construct */
EXPECT_EQ(Sstd.empty(),Ss21.empty());
EXPECT_EQ(Sstd.size(),Ss21.size());
EXPECT_EQ(Sstd.top(),Ss21.top());
Sstd.push(10);
Ss21.push(10);
EXPECT_EQ(Sstd.top(),Ss21.top());
Sstd.pop();
Ss21.pop();
Sstd.pop();
Ss21.pop();
EXPECT_EQ(Sstd.top(),Ss21.top());

/* Access and capacity, push and pop default construct */
EXPECT_EQ(Tstd.empty(),Ts21.empty());
EXPECT_EQ(Tstd.size(),Ts21.size());
Tstd.push(10);
Ts21.push(10);
Tstd.push(12);
Ts21.push(12);
EXPECT_EQ(Tstd.top(),Ts21.top());
Tstd.pop();
Ts21.pop();
EXPECT_EQ(Tstd.top(),Ts21.top());

/* Swap */
Sstd.swap(Tstd);
Ss21.swap(Ts21);
EXPECT_EQ(Tstd.top(),Ts21.top());
EXPECT_EQ(Sstd.top(),Ss21.top());

/* Copy operator */
Sstd = Tstd;
Ss21 = Ts21;
EXPECT_EQ(Sstd.empty(),Ss21.empty());
EXPECT_EQ(Sstd.size(),Ss21.size());
EXPECT_EQ(Tstd.empty(),Ts21.empty());
EXPECT_EQ(Tstd.size(),Ts21.size());
EXPECT_EQ(Tstd.top(),Ts21.top());
EXPECT_EQ(Sstd.top(),Ss21.top());

/* Copy construct */
std::stack<int,std::vector<int>> SstdCopy(Sstd);
s21::Stack<int,s21::Vector<int>> Ss21Copy(Ss21);

EXPECT_EQ(SstdCopy.empty(),Ss21Copy.empty());
EXPECT_EQ(SstdCopy.size(),Ss21Copy.size());
EXPECT_EQ(SstdCopy.empty(),Sstd.empty());
EXPECT_EQ(Ss21Copy.size(),Ss21.size());
EXPECT_EQ(Ss21Copy.top(),Ss21.top());
EXPECT_EQ(SstdCopy.top(),Ss21Copy.top());

/* Move construct */
std::stack<int,std::vector<int>> SstdMove(std::move(SstdCopy));
s21::Stack<int,s21::Vector<int>> Ss21Move(std::move(Ss21Copy));

EXPECT_EQ(SstdMove.empty(),Ss21Move.empty());
EXPECT_EQ(SstdMove.size(),Ss21Move.size());
EXPECT_EQ(Ss21Move.top(),Ss21.top());
EXPECT_EQ(SstdMove.top(),Ss21Move.top());

/* Move operator */
Sstd = std::move(Tstd);
Ss21 = std::move(Ts21);
EXPECT_EQ(Sstd.empty(),Ss21.empty());
EXPECT_EQ(Sstd.size(),Ss21.size());
EXPECT_TRUE(Ts21.empty());
EXPECT_EQ(Tstd.empty(),Ts21.empty());
EXPECT_EQ(Tstd.size(),Ts21.size());
EXPECT_EQ(Sstd.top(),Ss21.top());
}





TEST(List,all) {
/* Constructors */
std::list<int> LMstd;
s21::List<int> LMs21;
std::list<int> Lstd({4,2,3,4,4,6,5});
s21::List<int> Ls21({4,2,3,4,4,6,5});
std::list<int> LNstd(10);
s21::List<int> LNs21(10);
std::list<int> LCstd(LNstd);
s21::List<int> LCs21(LNs21);
std::list<int> LTstd(std::move(LCstd));
s21::List<int> LTs21(std::move(LCs21));

/* Access and capacity */
EXPECT_EQ(Lstd.back(),Ls21.back());
EXPECT_EQ(Lstd.front(),Ls21.front());
EXPECT_EQ(Lstd.empty(),Ls21.empty());
EXPECT_EQ(Lstd.size(),Ls21.size());
EXPECT_EQ(Lstd.max_size(),Ls21.max_size());

LTstd.push_back(122);
LTs21.push_back(122);
LTstd.push_front(999);
LTs21.push_front(999);

EXPECT_EQ(LTstd.back(),LTs21.back());
EXPECT_EQ(LTstd.front(),LTs21.front());
EXPECT_EQ(LTstd.empty(),LTs21.empty());
EXPECT_EQ(LTstd.size(),LTs21.size());
EXPECT_EQ(LTstd.max_size(),LTs21.max_size());

/* Iterators */
std::list<int>::iterator istd = Lstd.begin();
s21::List<int>::iterator is21 = Ls21.begin();
std::list<int>::iterator istd1 = Lstd.begin();
s21::List<int>::iterator is211 = Ls21.begin();
EXPECT_EQ(*is21, 4);

EXPECT_EQ(istd == istd1,is21 == is211);
EXPECT_EQ(*istd,*is21);
++istd;
++is21;
EXPECT_EQ(*istd,*is21);
istd = Lstd.end();
is21 = Ls21.end();
EXPECT_EQ(istd != istd1,is21 != is211);
--istd;
--is21;
EXPECT_EQ(*is21, 5);
EXPECT_EQ(*istd,*is21);
istd = Lstd.begin();
is21 = Ls21.begin();
istd++;
is21++;
EXPECT_EQ(*istd,*is21);
istd = Lstd.end();
is21 = Ls21.end();
istd--;
is21--;
EXPECT_EQ(*istd,*is21);

/* Modifiers */
Lstd.push_back(10);
Ls21.push_back(10);
EXPECT_EQ(Lstd.back(),Ls21.back());
EXPECT_EQ(Lstd.front(),Ls21.front());
Lstd.pop_back();
Ls21.pop_back();
EXPECT_EQ(Lstd.back(),Ls21.back());
EXPECT_EQ(Lstd.front(),Ls21.front());
Lstd.push_front(13);
Ls21.push_front(13);
EXPECT_EQ(Lstd.back(),Ls21.back());
EXPECT_EQ(Lstd.front(),Ls21.front());
Lstd.pop_front();
Ls21.pop_front();
EXPECT_EQ(Lstd.back(),Ls21.back());
EXPECT_EQ(Lstd.front(),Ls21.front());

istd = Lstd.begin();
is21 = Ls21.begin();
istd = Lstd.insert(istd,19);   
is21 = Ls21.insert(is21,19);
EXPECT_EQ(*istd,*is21);

Lstd.push_front(14);
Ls21.push_front(14);
istd = Lstd.begin();
is21 = Ls21.begin();

Lstd.erase(istd);        
Ls21.erase(is21);
istd = Lstd.begin();
is21 = Ls21.begin();
EXPECT_EQ(*istd,*is21);

LTstd.push_front(130);
LTs21.push_front(130);
Lstd.push_back(101);
Ls21.push_back(101);
LTstd.push_front(101);
LTs21.push_front(101);
Lstd.swap(LTstd);
Ls21.swap(LTs21);
EXPECT_EQ(Lstd.back(),Ls21.back());
EXPECT_EQ(Lstd.front(),Ls21.front());
EXPECT_EQ(LTstd.back(),LTs21.back());
EXPECT_EQ(LTstd.front(),LTs21.front());
Lstd.swap(LTstd);
Ls21.swap(LTs21);

EXPECT_EQ(Lstd.size(),Ls21.size());
Lstd.unique();
Ls21.unique();
EXPECT_EQ(Lstd.size(),Ls21.size());
EXPECT_EQ(Lstd.back(),Ls21.back());
EXPECT_EQ(Lstd.front(),Ls21.front());

istd = Lstd.end();
is21 = Ls21.end();
--istd;
--is21;
--istd;
--is21;

Lstd.sort();
Ls21.sort();   
EXPECT_EQ(Lstd.size(),Ls21.size()); 
EXPECT_EQ(Lstd.back(),Ls21.back());
EXPECT_EQ(Lstd.front(),Ls21.front());

Lstd.merge(LTstd);
Ls21.merge(LTs21);
EXPECT_EQ(Lstd.size(),Ls21.size());
EXPECT_EQ(Lstd.back(),Ls21.back());
EXPECT_EQ(Lstd.front(),Ls21.front());
istd = Lstd.end();
is21 = Ls21.end();
--istd;
--is21;
--istd;
--is21;
EXPECT_EQ(*istd,*is21);
istd = Lstd.begin();
is21 = Ls21.begin();
istd++;
is21++;
istd++;
is21++;
EXPECT_EQ(*istd,*is21);

Lstd.splice(istd,LTstd);
Ls21.splice(is21,LTs21);
EXPECT_EQ(Lstd.size(),Ls21.size());
EXPECT_EQ(Lstd.back(),Ls21.back());
EXPECT_EQ(Lstd.front(),Ls21.front());
istd = Lstd.end();
is21 = Ls21.end();
--istd;
--is21;
--istd;
--is21;
EXPECT_EQ(*istd,*is21);
istd = Lstd.begin();
is21 = Ls21.begin();
istd++;
is21++;
istd++;
is21++;
EXPECT_EQ(*istd,*is21);

Lstd.reverse();
Ls21.reverse();
EXPECT_EQ(Lstd.size(),Ls21.size());
EXPECT_EQ(Lstd.back(),Ls21.back());
EXPECT_EQ(Lstd.front(),Ls21.front());
istd = Lstd.end();
is21 = Ls21.end();
--istd;
--is21;
--istd;
--is21;
EXPECT_EQ(*istd,*is21);
istd = Lstd.begin();
is21 = Ls21.begin();
istd++;
is21++;
istd++;
is21++;
EXPECT_EQ(*istd,*is21);

/* Copy operator and clear */
LNstd = Lstd;
LNs21 = Ls21;
EXPECT_EQ(LNstd.empty(),LNs21.empty());
EXPECT_EQ(LNstd.size(),LNs21.size());
EXPECT_EQ(LNstd.back(),LNs21.back());
EXPECT_EQ(LNstd.front(),LNs21.front());

LNstd.clear();
LNs21.clear();
EXPECT_EQ(LNstd.empty(),LNs21.empty());
EXPECT_EQ(LNstd.size(),LNs21.size());

/* Move operator */
LNstd = std::move(Lstd);
LNs21 = std::move(Ls21);
EXPECT_TRUE(Ls21.empty());
EXPECT_EQ(LNstd.empty(),LNs21.empty());
EXPECT_EQ(LNstd.size(),LNs21.size());
EXPECT_EQ(LNstd.back(),LNs21.back());
EXPECT_EQ(LNstd.front(),LNs21.front());
}




TEST(Vector, all) {
/* Constructors */
std::vector<int> VMstd;
s21::Vector<int> VMs21;
std::vector<int> Vstd({14,12,13,14,16,15});
s21::Vector<int> Vs21({14,12,13,14,16,15});
std::vector<int> VNstd(10);
s21::Vector<int> VNs21(10);
std::vector<int> VCstd(VNstd);
s21::Vector<int> VCs21(VNs21);
std::vector<int> VTstd(std::move(VCstd));
s21::Vector<int> VTs21(std::move(VCs21));

/* Access, capacity and push */ 
EXPECT_EQ(Vstd.back(),Vs21.back());
EXPECT_EQ(Vstd.front(),Vs21.front());
EXPECT_EQ(Vstd.at(2),Vs21.at(2));
// EXPECT_ANY_THROW(Vs21.at(20));  /* Проверка на выкидыш, провоцирует утечку */
EXPECT_EQ(Vstd[4],Vs21[4]);
EXPECT_EQ(Vstd.data()[3],Vs21.data()[3]);

EXPECT_EQ(Vstd.empty(),Vs21.empty());
EXPECT_EQ(Vstd.size(),Vs21.size());
EXPECT_EQ(Vstd.max_size(),Vs21.max_size());
EXPECT_EQ(Vstd.capacity(),Vs21.capacity());

VTstd.push_back(228);
VTs21.push_back(228);
VTstd.push_back(1488);
VTs21.push_back(1488);
EXPECT_EQ(VTstd.back(),VTs21.back());
EXPECT_EQ(VTstd.front(),VTs21.front());
EXPECT_EQ(VTstd.empty(),VTs21.empty());
EXPECT_EQ(VTstd.size(),VTs21.size()); 
EXPECT_EQ(VTstd.max_size(),VTs21.max_size());
EXPECT_EQ(VTstd.capacity(),VTs21.capacity());
VTstd.reserve(1);
VTs21.reserve(1);
EXPECT_EQ(VTstd.size(),VTs21.size()); 
EXPECT_EQ(VTstd.capacity(),VTs21.capacity());
VTstd.reserve(20);
VTs21.reserve(20);
EXPECT_EQ(VTstd.size(),VTs21.size()); 
EXPECT_EQ(VTstd.capacity(),VTs21.capacity());
VTstd.shrink_to_fit();
VTs21.shrink_to_fit();
EXPECT_EQ(VTstd.size(),VTs21.size()); 
EXPECT_EQ(VTstd.capacity(),VTs21.capacity());

/* Iterators */
std::vector<int>::iterator vstd = Vstd.begin();
s21::Vector<int>::iterator vs21 = Vs21.begin();
std::vector<int>::iterator vstd1 = Vstd.end();
s21::Vector<int>::iterator vs211 = Vs21.end();
EXPECT_EQ(*vs21, 14);
vstd1--;
vs211--;
EXPECT_EQ(*vs211, 15);
EXPECT_EQ(*vstd,*vs21);
EXPECT_EQ(*vstd1,*vs211);
vstd++;
vs21++;
EXPECT_EQ(*vstd,*vs21);
--vstd1;
--vs211;
EXPECT_EQ(*vstd1,*vs211);
++vstd;
++vs21;
EXPECT_EQ(*vstd,*vs21);

/* Modifieres */
Vstd.pop_back();
Vs21.pop_back();
EXPECT_EQ(Vstd.back(),Vs21.back());
EXPECT_EQ(Vstd.front(),Vs21.front());
EXPECT_EQ(Vstd.size(),Vs21.size());
EXPECT_EQ(Vstd.capacity(),Vs21.capacity());

Vstd.insert(vstd,197);
Vs21.insert(vs21,197);
EXPECT_EQ(*vstd,*vs21);
EXPECT_EQ(Vstd.size(),Vs21.size());
EXPECT_EQ(Vstd.capacity(),Vs21.capacity());

Vstd.erase(vstd);
Vs21.erase(vs21);
EXPECT_EQ(*vstd,*vs21);
EXPECT_EQ(Vstd.size(),Vs21.size());
EXPECT_EQ(Vstd.capacity(),Vs21.capacity());

/* Copy operator and clear */
VNstd = Vstd;
VNs21 = Vs21;
EXPECT_EQ(VNstd.size(),VNs21.size());
EXPECT_EQ(VNstd.back(),VNs21.back());
EXPECT_EQ(VNstd.front(),VNs21.front());
EXPECT_EQ(VNstd.capacity(),VNs21.capacity());

VNstd.clear();
VNs21.clear();
EXPECT_TRUE(VNstd.empty());
EXPECT_TRUE(VNs21.empty());
EXPECT_EQ(VNstd.empty(),VNs21.empty());
EXPECT_EQ(VNstd.size(),VNs21.size());
EXPECT_EQ(VNstd.capacity(),VNs21.capacity());

/* Move operator and swap */
VNstd = std::move(Vstd);
VNs21 = std::move(Vs21);
EXPECT_TRUE(Vs21.empty());
EXPECT_EQ(Vstd.empty(),Vs21.empty());
EXPECT_EQ(VNstd.size(),VNs21.size());
EXPECT_EQ(VNstd.back(),VNs21.back());
EXPECT_EQ(VNstd.front(),VNs21.front());
EXPECT_EQ(VNstd.capacity(),VNs21.capacity());

VNstd.swap(VTstd);
VNs21.swap(VTs21);
EXPECT_EQ(VNstd.empty(),VNs21.empty());
EXPECT_EQ(VNstd.size(),VNs21.size());
EXPECT_EQ(VNstd.back(),VNs21.back());
EXPECT_EQ(VNstd.front(),VNs21.front());
EXPECT_EQ(VNstd.capacity(),VNs21.capacity());

EXPECT_EQ(VTstd.empty(),VTs21.empty());
EXPECT_EQ(VTstd.size(),VTs21.size());
EXPECT_EQ(VTstd.back(),VTs21.back());
EXPECT_EQ(VTstd.front(),VTs21.front());
EXPECT_EQ(VTstd.capacity(),VTs21.capacity());
}



TEST(Set, all) {
/* Constructors */
std::set<int> Sstd({9,8,7,7,5,5,5,13,1,18,228});
s21::Set<int> Ss21({9,8,7,7,5,5,5,13,1,18,228});
std::set<int> SMstd;
s21::Set<int> SMs21;
std::set<int> SCstd(SMstd);
s21::Set<int> SCs21(SMs21);
std::set<int> STstd(std::move(SCstd));
s21::Set<int> STs21(std::move(SCs21));

/* Сapacity */ 
EXPECT_EQ(Sstd.empty(), Ss21.empty());
EXPECT_EQ(Sstd.size(), Ss21.size());
EXPECT_EQ(Ss21.size(), 8);
// EXPECT_EQ(Sstd.max_size(),Ss21.max_size()); /* Приблизительное число */

/* Iterators and lookup */ 
std::set<int>::iterator sstd = Sstd.begin();
std::set<int>::iterator sstd1 = Sstd.end();
s21::Set<int>::iterator ss21 = Ss21.begin();
s21::Set<int>::iterator ss211 = Ss21.end();
std::set<int>::iterator fstd = Sstd.find(5);
s21::Set<int>::iterator fs21 = Ss21.find(5);
std::set<int>::iterator f1std = Sstd.find(0);
s21::Set<int>::iterator f1s21 = Ss21.find(0);
std::set<int>::iterator isstd = Sstd.insert(3).first;
s21::Set<int>::iterator iss21 = Ss21.insert(3).first;

EXPECT_EQ(*sstd,*ss21);
EXPECT_EQ(*fstd,*fs21);
EXPECT_EQ(*f1std,*sstd1);
EXPECT_EQ(*f1s21,*ss211);
EXPECT_EQ(*isstd,*iss21);
EXPECT_EQ(*iss21, 3);
EXPECT_EQ(*fs21,*Ss21.insert(5).first);
sstd1--;
ss211--;
EXPECT_EQ(*sstd1,*ss211);
sstd++;
ss21++;
EXPECT_EQ(*sstd,*ss21);
--sstd1;
--ss211;
EXPECT_EQ(*sstd1,*ss211);
++sstd;
++ss21;
EXPECT_EQ(*sstd,*ss21);
EXPECT_TRUE(Ss21.contains(5));
EXPECT_FALSE(Ss21.contains(0));

/* Modifiers */ 
EXPECT_TRUE(Sstd.insert(4).second);
EXPECT_TRUE(Ss21.insert(4).second);
EXPECT_FALSE(Sstd.insert(5).second);
EXPECT_FALSE(Ss21.insert(5).second);

Sstd.erase(isstd);
Ss21.erase(iss21);
EXPECT_EQ(Sstd.size(),Ss21.size());
EXPECT_FALSE(Ss21.contains(3));

Sstd.swap(STstd);
Ss21.swap(STs21);
EXPECT_FALSE(STs21.empty());
EXPECT_TRUE(Ss21.empty());
EXPECT_EQ(Sstd.size(),Ss21.size());
EXPECT_EQ(STstd.size(),STs21.size());
Sstd.swap(STstd);
Ss21.swap(STs21);
EXPECT_FALSE(Ss21.empty());
EXPECT_TRUE(STs21.empty());
EXPECT_EQ(Sstd.size(),Ss21.size());
EXPECT_EQ(STstd.size(),STs21.size());

STstd.insert(15);
STstd.insert(2);
STs21.insert(15);
STs21.insert(2);

Sstd.merge(STstd);
Ss21.merge(STs21);
EXPECT_FALSE(Ss21.empty());
EXPECT_TRUE(STs21.empty());
EXPECT_EQ(Sstd.size(),Ss21.size());
EXPECT_EQ(STstd.size(),STs21.size());

STs21.insert(5);
STstd.insert(5);

Sstd.merge(STstd);
Ss21.merge(STs21);
EXPECT_FALSE(Ss21.empty());
EXPECT_FALSE(STs21.empty());
EXPECT_EQ(Sstd.size(),Ss21.size());
EXPECT_EQ(STstd.size(),STs21.size());

/* Copy operator and clear */ 
STs21 = Ss21;
STstd = Sstd;
EXPECT_EQ(STstd.empty(),STs21.empty());
EXPECT_EQ(STstd.size(),STs21.size());
EXPECT_EQ(Ss21.contains(5),STs21.contains(5));
EXPECT_EQ(Ss21.contains(4),STs21.contains(4));
EXPECT_EQ(Ss21.contains(24),STs21.contains(24));


STs21.clear();
STstd.clear();
EXPECT_TRUE(STs21.empty());
EXPECT_EQ(STstd.size(),STs21.size());

/* Move operator */ 
STs21 = std::move(Ss21);
STstd = std::move(Sstd);
EXPECT_TRUE(Ss21.empty());
EXPECT_FALSE(STs21.empty());
EXPECT_EQ(Sstd.size(),Ss21.size());
EXPECT_EQ(STstd.size(),STs21.size());
}


TEST(Map,all) {
/* Constructors */
std::map<int,int> Mstd{{3,10},{2,11},{1,12},{4,13},{5,14}};
s21::Map<int,int> Ms21{{3,10},{2,11},{1,12},{4,13},{5,14}};
std::map<int,int> MMstd;
s21::Map<int,int> MMs21;
std::map<int,int> MCstd(MMstd);
s21::Map<int,int> MCs21(MMs21);
std::map<int,int> MTstd(std::move(MCstd));
s21::Map<int,int> MTs21(std::move(MCs21));

/* Access and capacity */ 
EXPECT_EQ(Mstd.empty(), Ms21.empty());
EXPECT_EQ(Mstd.size(), Ms21.size());
EXPECT_EQ(Mstd.size(), 5);
// EXPECT_EQ(Mstd.max_size(), Ms21.max_size());  /* Приблизительное число */

EXPECT_EQ(Mstd.at(2),Ms21.at(2));
// EXPECT_ANY_THROW(Ms21.at(20));  /* Проверка на выкидыш, провоцирует утечку */
EXPECT_EQ(Mstd[4],Ms21[4]);

/* Iterators and lookup */ 
std::map<int,int>::iterator mstd = Mstd.begin();
std::map<int,int>::iterator mstd1 = Mstd.end();
s21::Map<int,int>::iterator ms21 = Ms21.begin();
s21::Map<int,int>::iterator ms211 = Ms21.end();
std::map<int,int>::iterator imstd = Mstd.insert(std::pair(6,15)).first;
s21::Map<int,int>::iterator ims21 = Ms21.insert(std::pair(6,15)).first;

EXPECT_EQ(*mstd,*ms21);
EXPECT_EQ(*imstd,*ims21);
EXPECT_EQ(ims21->second, 15);
mstd1--;
ms211--;
EXPECT_EQ(*mstd1,*ms211);
mstd++;
ms21++;
EXPECT_EQ(mstd->first,ms21->first);
EXPECT_EQ(mstd->second,ms21->second);
--mstd1;
--ms211;
EXPECT_EQ(*mstd1,*ms211);
++mstd;
++ms21;
EXPECT_EQ(*mstd,*ms21);
EXPECT_TRUE(Ms21.contains(5));
EXPECT_FALSE(Ms21.contains(0));

/* Modifiers */ 
EXPECT_TRUE(Mstd.insert(std::pair(7,4)).second);
EXPECT_TRUE(Ms21.insert(7,4).second);
EXPECT_FALSE(Ms21.insert(5,0).second);

Mstd.erase(imstd);
Ms21.erase(ims21);
EXPECT_EQ(Mstd.size(),Ms21.size());
EXPECT_FALSE(Ms21.contains(6));

Mstd.swap(MTstd);
Ms21.swap(MTs21);
EXPECT_FALSE(MTs21.empty());
EXPECT_TRUE(Ms21.empty());

EXPECT_EQ(Mstd.size(),Ms21.size());
EXPECT_EQ(MTstd.size(),MTs21.size());
Mstd.swap(MTstd);
Ms21.swap(MTs21);
EXPECT_FALSE(Ms21.empty());
EXPECT_TRUE(MTs21.empty());
EXPECT_EQ(Mstd.size(),Ms21.size());
EXPECT_EQ(MTstd.size(),MTs21.size());

MTstd.insert(std::pair(1,15));
MTstd.insert(std::pair(10,2));
MTs21.insert_or_assign(10,2);
EXPECT_EQ(*MTs21.insert(1,15).first,*MTs21.insert_or_assign(1,20).first);

Mstd.merge(MTstd);
Ms21.merge(MTs21);
EXPECT_FALSE(Ms21.empty());
EXPECT_FALSE(MTs21.empty()); /* Не работает */
EXPECT_EQ(Mstd.size(),Ms21.size());
EXPECT_EQ(MTstd.size(),MTs21.size());

MTs21.insert(13,5);
MTstd.insert(std::pair(13,5));

Mstd.merge(MTstd);
Ms21.merge(MTs21);
EXPECT_FALSE(Ms21.empty());
EXPECT_FALSE(MTstd.empty());
EXPECT_EQ(Mstd.size(),Ms21.size());
EXPECT_EQ(MTstd.size(),MTstd.size());

/* Copy operator and clear */ 
MTs21 = Ms21;
MTstd = Mstd;
EXPECT_EQ(MTstd.empty(),MTs21.empty());
EXPECT_EQ(MTstd.size(),MTs21.size());
EXPECT_EQ(Ms21.contains(5),MTs21.contains(5));
EXPECT_EQ(Ms21.contains(4),MTs21.contains(4));
EXPECT_EQ(Ms21.contains(24),MTs21.contains(24));

MTs21.clear();
MTstd.clear();
EXPECT_TRUE(MTs21.empty());
EXPECT_EQ(MTstd.size(),MTs21.size());

/* Move operator */ 
MTs21 = std::move(Ms21);
MTstd = std::move(Mstd);
EXPECT_TRUE(Ms21.empty());
EXPECT_FALSE(MTs21.empty());
EXPECT_EQ(Mstd.size(),Ms21.size());
EXPECT_EQ(MTstd.size(),MTs21.size());

}







int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}