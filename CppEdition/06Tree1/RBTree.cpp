/*
P3369
题目描述
您需要写一种数据结构（可参考题目标题），来维护一些数，其中需要提供以下操作：
1、插入 x 数
2、删除 x 数(若有多个相同的数，应只删除一个)
3、查询 x 数的排名(排名定义为比当前数小的数的个数 + 1)
4、查询排名为 x 的数
5、求 x 的前驱(前驱定义为小于 x，且最大的数)
6、求 x 的后继(后继定义为大于 x，且最小的数)

输入格式
第一行为 n，表示操作的个数,下面 n 行每行有两个数 opt 和 x，opt 表示操作的序号(1 ≤ opt ≤ 6)

输出格式
对于操作 3, 4, 5, 6 每行输出一个数，表示对应答案
*/

#include<bits/stdc++.h>
using namespace std;

//#define __REDBLACK_DEBUG

#define bro(x) (((x)->ftr->lc == (x)) ? ((x)->ftr->rc) : ((x)->ftr->lc))
#define islc(x) ((x) != NULL && (x)->ftr->lc == (x))
#define isrc(x) ((x) != NULL && (x)->ftr->rc == (x))

template<typename T>
class redblacktree {
	protected:
		struct Node {
	        T val;  // 节点信息
	        bool RBc;  // 节点颜色，若为true，则节点为Red;否则节点为Black.
	        Node* ftr;  // 父亲
	        Node* lc;  // 左儿子
	        Node* rc;  // 右儿子
	        int s;  // 域

	        Node(T v = T(), bool RB = true, Node* f = NULL, Node* l = NULL, Node* r = NULL ,int ss = 1):
            val(v), RBc(RB), ftr(f), lc(l), rc(r), s(ss) {}

	        Node* succ() {  // 删除节点时用到的替代节点
		        Node* ptn = rc;
		        while(ptn -> lc != NULL) {
			        --(ptn -> s);
			        ptn = ptn -> lc;
		        }
		        return ptn;
	        }

	        Node* left_node() {  // 直接前驱
		        Node* ptn = this;
		        if (!lc) {
			        while (ptn -> ftr && ptn -> ftr -> lc == ptn) ptn = ptn -> ftr;
			        ptn = ptn -> ftr;
		        } else {
			        ptn = ptn -> lc;
			        while (ptn -> rc) ptn = ptn -> rc;
		        }
		        return ptn;
	        }

	        Node* right_node() {  // 直接后继
		        Node* ptn = this;
		        if (!rc) {
			        while(ptn -> ftr && ptn -> ftr -> rc == ptn)
				        ptn = ptn -> ftr;
			        ptn = ptn -> ftr;
		        } else {
			        ptn = ptn -> rc;
			        while (ptn -> lc) ptn = ptn -> lc;
			    }
		        return ptn;
	        }

	        void maintain() {  // 维护域s
		        s = 1;
		        if(lc) s += lc -> s;
		        if(rc) s += rc -> s;
	        }
        };

		Node* _root;  // 根节点位置
		Node* _hot;  // 临时维护的节点

		void init(T v) {
	        _root = new Node(v, false, NULL, NULL, NULL, 1);
        #ifdef __REDBLACK_DEBUG
	        ++blackheight;
        #endif
}

        // 统一重平衡
		void connect34(Node* nroot, Node* nlc, Node* nrc, Node* ntree1, Node* ntree2, Node* ntree3, Node* ntree4) {
            nlc->lc = ntree1;
            if(ntree1 != NULL) ntree1->ftr = nlc;
            nlc->rc = ntree2;
            if(ntree2 != NULL) ntree2->ftr = nlc;
            nrc->lc = ntree3;
            if(ntree3 != NULL) ntree3->ftr = nrc;
            nrc->rc = ntree4;
            if(ntree4 != NULL) ntree4->ftr = nrc;
            nroot->lc = nlc;
            nlc->ftr = nroot;
            nroot->rc = nrc;
            nrc->ftr = nroot;
            nlc->maintain();
            nrc->maintain();
            nroot->maintain();
        }

        // 双红修正
		void SolveDoubleRed(Node* nn) {
            while((!(nn->ftr)) || nn->ftr->RBc) {
                if(nn == _root) {
                    _root->RBc = false;
        #ifdef __REDBLACK_DEBUG
                    ++blackheight;
        #endif
                    return;
                }
                Node* pftr = nn->ftr;
                if(!(pftr->RBc)) return;			// No double-red
                Node* uncle = bro(nn->ftr);
                Node* grdftr = nn->ftr->ftr;
                if(uncle != NULL && uncle->RBc) {	// RR-2
                    grdftr->RBc = true;
                    uncle->RBc = false;
                    pftr->RBc = false;
                    nn = grdftr;
                } else {							// RR-1
                    if(islc(pftr)) {
                        if(islc(nn)) {
                            pftr->ftr = grdftr->ftr;
                            if(grdftr == _root) _root = pftr;
                            else if(grdftr->ftr->lc == grdftr) grdftr->ftr->lc = pftr;
                            else grdftr->ftr->rc = pftr;
                            connect34(pftr, nn, grdftr, nn->lc, nn->rc, pftr->rc, uncle);
                            pftr->RBc = false;
                            grdftr->RBc = true;
                        } else {
                            nn->ftr = grdftr->ftr;
                            if(grdftr == _root) _root = nn;
                            else if(grdftr->ftr->lc == grdftr) grdftr->ftr->lc = nn;
                            else grdftr->ftr->rc = nn;
                            connect34(nn, pftr, grdftr, pftr->lc, nn->lc, nn->rc, uncle);
                            nn->RBc = false;
                            grdftr->RBc = true;
                        }
                    } else {
                        if(islc(nn)) {
                            nn->ftr = grdftr->ftr;
                            if(grdftr == _root) _root = nn;
                            else if(grdftr->ftr->lc == grdftr) grdftr->ftr->lc = nn;
                            else grdftr->ftr->rc = nn;
                            connect34(nn, grdftr, pftr, uncle, nn->lc, nn->rc, pftr->rc);
                            nn->RBc = false;
                            grdftr->RBc = true;
                        } else {
                            pftr->ftr = grdftr->ftr;
                            if(grdftr == _root) _root = pftr;
                            else if(grdftr->ftr->lc == grdftr) grdftr->ftr->lc = pftr;
                            else grdftr->ftr->rc = pftr;
                            connect34(pftr, grdftr, nn, uncle, pftr->lc, nn->lc, nn->rc);
                            pftr->RBc = false;
                            grdftr->RBc = true;
                        }
                    }
                    return;
                }
            }
        }

        // 双黑修正
		void SolveDoubleBlack(Node* nn) {
            while(nn != _root) {
                Node* pftr = nn->ftr;
                Node* bthr = bro(nn);
                if(bthr->RBc) {					////BB-1
                    bthr->RBc = false;
                    pftr->RBc = true;
                    if(_root == pftr) _root = bthr;
                    if(pftr->ftr) {
                        if(pftr->ftr->lc == pftr)
                            pftr->ftr->lc = bthr;
                        else
                            pftr->ftr->rc = bthr;
                    }
                    bthr->ftr = pftr->ftr;
                    if(islc(nn)) {
                        connect34(bthr, pftr, bthr->rc, nn, bthr->lc, bthr->rc->lc, bthr->rc->rc);
                    } else {
                        connect34(bthr, bthr->lc, pftr, bthr->lc->lc, bthr->lc->rc, bthr->rc, nn);
                    }
                    bthr = bro(nn);
                    pftr = nn->ftr;
                }
                if(bthr->lc && bthr->lc->RBc) {	////BB-3
                    bool oldRBc = pftr->RBc;
                    pftr->RBc = false;
                    if(pftr->lc == nn) {
                        if(pftr->ftr) {
                            if(pftr->ftr->lc == pftr)
                                pftr->ftr->lc = bthr->lc;
                            else
                                pftr->ftr->rc = bthr->lc;
                        }
                        bthr->lc->ftr = pftr->ftr;
                        if(_root == pftr) _root = bthr->lc;
                        connect34(bthr->lc, pftr, bthr, pftr->lc, bthr->lc->lc, bthr->lc->rc, bthr->rc);
                    } else {
                        bthr->lc->RBc = false;
                        if(pftr->ftr) {
                            if(pftr->ftr->lc == pftr)
                                pftr->ftr->lc = bthr;
                            else
                                pftr->ftr->rc = bthr;
                        }
                        bthr->ftr = pftr->ftr;
                        if(_root == pftr) _root = bthr;
                        connect34(bthr, bthr->lc, pftr, bthr->lc->lc, bthr->lc->rc, bthr->rc, pftr->rc);
                    }
                    pftr->ftr->RBc = oldRBc;
                    return;
                } else if(bthr->rc && bthr->rc->RBc) {	////BB-3
                    bool oldRBc = pftr->RBc;
                    pftr->RBc = false;
                    if(pftr->lc == nn) {
                        bthr->rc->RBc = false;
                        if(pftr->ftr) {
                            if(pftr->ftr->lc == pftr)
                                pftr->ftr->lc = bthr;
                            else
                                pftr->ftr->rc = bthr;
                        }
                        bthr->ftr = pftr->ftr;
                        if(_root == pftr) _root = bthr;
                        connect34(bthr, pftr, bthr->rc, pftr->lc, bthr->lc, bthr->rc->lc, bthr->rc->rc);
                    } else {
                        if(pftr->ftr) {
                            if(pftr->ftr->lc == pftr)
                                pftr->ftr->lc = bthr->rc;
                            else
                                pftr->ftr->rc = bthr->rc;
                        }
                        bthr->rc->ftr = pftr->ftr;
                        if(_root == pftr) _root = bthr->rc;
                        connect34(bthr->rc, bthr, pftr, bthr->lc, bthr->rc->lc, bthr->rc->rc, pftr->rc);
                    }
                    pftr->ftr->RBc = oldRBc;
                    return;
                }
                if(pftr->RBc) {					////BB-2R
                    pftr->RBc = false;
                    bthr->RBc = true;
                    return;
                } else {						////BB-2B
                    bthr->RBc = true;
                    nn = pftr;
                }
            }
        #ifdef __REDBLACK_DEBUG
            --blackheight;
        #endif
        } 

        // 允许重复的查找
		Node* find(T v, const int op) {
	        Node* ptn = _root;  // 从根节点开始查找
	        _hot = NULL;  // 维护父亲节点
	        while(ptn != NULL) {
		        _hot = ptn;
		        ptn->s += op;
		        if(ptn->val > v)
			        ptn = ptn->lc;
		        else
			        ptn = ptn->rc;
	        }
	        return ptn;
        }  

        // 不允许重复的查找
		Node* rfind(T v, const int op) {
	        Node* ptn = _root;
	        _hot = NULL;
	        while(ptn != NULL && ptn->val != v) {
		        _hot = ptn;
		        ptn->s += op;
		        if(ptn->val > v)
			        ptn = ptn->lc;
		        else
			        ptn = ptn->rc;
	        }
	        return ptn;
        }

		Node* findkth(int rank, Node* ptn) {
            if(!(ptn->lc)) {
                if(rank == 1) {
                    return ptn;
                } else {
                    return findkth(rank - 1, ptn->rc);
                }
            } else {
                if(ptn->lc->s == rank - 1) return ptn;
                else if(ptn->lc->s >= rank) return findkth(rank, ptn->lc);
                else return findkth(rank - (ptn->lc->s) - 1, ptn->rc);
            }
        }

		int find_rank(T v, Node* ptn) {
            if(!ptn) return 1;
            else if(ptn->val >= v) return find_rank(v, ptn->lc);
            else return (1 + ((ptn->lc) ? (ptn->lc->s) : 0) + find_rank(v, ptn->rc));
        }

    #ifdef __REDBLACK_DEBUG
        int blackheight(0);

		void checkconnect(Node* ptn) {
            if(!ptn) return;
            assert(ptn->s > 0);
            if(ptn->lc && ptn->lc->ftr != ptn) {
                printf("Oops! %d has a lc %d, but it failed to point its ftr!\n", ptn->val, ptn->lc->val);
            }
            if(ptn->rc && ptn->rc->ftr != ptn) {
                printf("Oops! %d has a rc %d, but it failed to point its ftr!\n", ptn->val, ptn->rc->val);
            }
            int sss = ptn->s;
            if(ptn->lc) sss -= ptn->lc->s;
            if(ptn->rc) sss -= ptn->rc->s;
            if(sss - 1) {
                printf("Damn! %d's size is %d, but the sum of its children's size is %d!\n", ptn->val, ptn->s, ptn->s - sss);
            }
            checkconnect(ptn->lc);
            checkconnect(ptn->rc);
        }

		void previs(Node* ptn, int cnt) {
            if(ptn == NULL) {
                if(blackheight == -1) blackheight = cnt;
                assert(blackheight == cnt);
                return;
            }
            printf("%d %s %d \n", ptn->val, ptn->RBc ? "Red" : "Black", ptn->s);
            if(!(ptn->RBc)) ++cnt;
            previs(ptn->lc, cnt);
            previs(ptn->rc, cnt);
        }

		void invis(Node* ptn, int cnt) {
            if(ptn == NULL) {
                if(blackheight == -1) blackheight = cnt;
                assert(blackheight == cnt);
                return;
            }
            if(!(ptn->RBc)) ++cnt;
            invis(ptn->lc, cnt);
            printf("%d %s %d \n", ptn->val, ptn->RBc ? "Red" : "Black", ptn->s);
            invis(ptn->rc, cnt);
        }

		void postvis(Node* ptn, int cnt) {
            if(ptn == NULL) {
                if(blackheight == -1) blackheight = cnt;
                assert(blackheight == cnt);
                return;
            }
            if(!(ptn->RBc)) ++cnt;
            postvis(ptn->lc, cnt);
            postvis(ptn->rc, cnt);
            printf("%d %s %d \n", ptn->val, ptn->RBc ? "Red" : "Black", ptn->s);
        }
    #endif

	public:
		struct iterator {
	        private:
		        Node* _real__node;

	        public:
		        iterator& operator++() {
			        _real__node = _real__node->right_node();
			        return *this;
		        }

		        iterator& operator--() {
			        _real__node = _real__node->left_node();
			        return *this;
		        }

		        T operator*() {
			        return _real__node->val;
		        }

		        iterator(Node* node_nn = NULL) : _real__node(node_nn) {}
		        iterator(T const& val_vv) : _real__node(rfind(val_vv, 0)) {}
		        iterator(iterator const& iter) : _real__node(iter._real__node) {}
        };

		redblacktree() : _root(NULL), _hot(NULL) {}

		int get_rank(T v) {
            return find_rank(v, _root);
        }

		iterator insert(T v) {
	        Node* ptn = find(v, 1);
	        if(_hot == NULL) {
		        init(v);
		        return iterator(_root);
	        }
	        ptn = new Node(v, true, _hot, NULL, NULL, 1);
	        if(	_hot->val <= v	)
		        _hot->rc = ptn;
	        else
		        _hot->lc = ptn;
	        SolveDoubleRed(ptn);
	        return iterator(ptn);
        }

		bool remove(T v) {
            Node* ptn = rfind(v, -1);
            if(!ptn) return false;
            Node* node_suc;
            while(ptn->lc || ptn->rc) {	////迭代寻找真后继
                if(!(ptn->lc)) {
                    node_suc = ptn->rc;
                } else if(!(ptn->rc)) {
                    node_suc = ptn->lc;
                } else {
                    node_suc = ptn->succ();
                }
                --(ptn->s);
                ptn->val = node_suc->val;
                ptn = node_suc;
            }
            if(!(ptn->RBc)) {
                --(ptn->s);
                SolveDoubleBlack(ptn);
            }
            if(ptn == _root) {
                _root = NULL;
                delete ptn;
                return true;
            }
            if(ptn->ftr->lc == ptn)
                ptn->ftr->lc = NULL;
            else
                ptn->ftr->rc = NULL;
            delete ptn;
            return true;
        }

		int size() {
            return _root->s;
        }
        
        bool empty() {
            return !_root;
        }

		iterator kth(int rank) {
            return iterator(findkth(rank, _root));
        }

		iterator lower_bound(T v) {
            Node* ptn = _root;
            while(ptn) {
                _hot = ptn;
                if(ptn->val < v) {
                    ptn = ptn->rc;
                } else {
                    ptn = ptn->lc;
                }
            }
            if(_hot->val < v) {
                ptn = _hot;
            } else {
                ptn = _hot->left_node();
            }
            return iterator(ptn);
        }

		iterator upper_bound(T v) {
            Node* ptn = _root;
            while(ptn) {
                _hot = ptn;
                if(ptn->val > v) {
                    ptn = ptn->lc;
                } else {
                    ptn = ptn->rc;
                }
            }
            if(_hot->val > v) {
                ptn = _hot;
            } else {
                ptn = _hot->right_node();
            }
            return iterator(ptn);
        }

    #ifdef __REDBLACK_DEBUG
        void vis() {
            printf("BlackHeight:\t%d\n", blackheight);
            printf("------pre-vis------\n");
            previs(_root, 0);
            printf("------in-vis------\n");
            invis(_root, 0);
            printf("------post-vis------\n");
            postvis(_root, 0);
        }

		void correctlyconnected() {
            checkconnect(_root);
        }
    #endif
};


redblacktree<int> my_tree;
int tot, opt, x;

int main() {
	cin >> tot;
	redblacktree<int>::iterator it;
	for(register int i = 0; i < tot; ++i) {
		cin >> opt >> x;
		switch(opt) {
			case 1:
				my_tree.insert(x);
				break;
			case 2:
				my_tree.remove(x);
				break;
			case 3:
				printf("%d\n", my_tree.get_rank(x));
				break;
			case 4:
				it = my_tree.kth(x);
				printf("%d\n", *it);
				break;
			case 5:
				it = my_tree.lower_bound(x);
				printf("%d\n", *it);
				break;
			case 6:
				it = my_tree.upper_bound(x);
				printf("%d\n", *it);
				break;
			default:
				break;
		}
	}

	return 0;
}