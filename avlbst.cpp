#include "avlbst.h"
#include "utility"


avlBST::avlBST() {

}

avlBST::~avlBST() {
    deleteAll();
}

avlBST::avlBST(const avlBST &other) {
    copy(other);
}

avlBST &avlBST::operator=(const avlBST &other) {
    if(this != &other) {
        deleteAll();
        copy(other);
    }
    return *this;
}

bool avlBST::empty() const {
    return !tree.size();
}

size_t avlBST::size() {
    return tree.size();
}



void avlBST::insert(const std::string &w, const size_t &pIdx, const size_t &lIdx, const size_t count) {  // Concerns : vector.push_back creates copy; replace if with function pointer
    node temp(w, pIdx, lIdx, count);
    if(empty()) {
        insertRoot(temp);
    }
    else {
        bool notBreak = true;
        bool useLog = true;
        bool createsNewDepth = false;
        int index = 0;
        std::vector<std::pair<size_t, int>> balanceLog;

        /* Iterates down the tree, along with changing the balance of the nodes accordingly */
        while(notBreak) {


            /* Case 1: Add to word count if character already exists */
            if(temp.word == tree[index].word) {
                ++tree[index];
                tree[index].paragraphIndex.push_back(pIdx);
                tree[index].lineIndex.push_back(lIdx);
                notBreak = false;
                useLog = false;
            }

            /* Case 2: Makes left children, which goes down until there is a -1 index */
            else if(temp.word < tree[index].word) {
                balanceLog.push_back(std::make_pair(index, -1));
                if(leftIdxs[index] == -1) {
                    if(rightIdxs[index] == -1)
                        createsNewDepth = true;
                    insertLeft(temp, index);
                    notBreak = false;
                }
                else
                    index = leftIdxs[index];
            }

            /* Case 3: Opposite of case 2 */
            else {
                balanceLog.push_back(std::make_pair(index, 1));
                if(rightIdxs[index] == -1) {
                    if(leftIdxs[index] == -1)
                        createsNewDepth = true;
                    insertRight(temp, index);
                    notBreak = false;
                }
                else
                    index = rightIdxs[index];
            }
         }

        /* Uses log to adjust the balances of the tree of each affected index */
        if(useLog && createsNewDepth) {
            for(size_t i=0; i < balanceLog.size() - 1; ++i) {
                std::cout << "Log entry: " << balanceLog[i].first << " " << balanceLog[i].second << std::endl;
                tree[balanceLog[i].first].balance += balanceLog[i].second;
            }
            //tree[balanceLog[balanceLog.size() - 1].first].balance += balanceLog[balanceLog.size() - 1].second;
            std::cout << "Asdf" << std::endl;
        }
        tree[balanceLog.back().first].balance += balanceLog.back().second;
    }

    //rebalance();

    for(size_t i = 0; i < tree.size(); ++i) {
        std::cout << tree[i] << "\t";
    }
    std::cout << std::endl;
    for(size_t i = 0; i < leftIdxs.size(); ++i) {
        std::cout << leftIdxs[i] << "\t";
    }
    std::cout << std::endl;
    for(size_t i = 0; i < rightIdxs.size(); ++i) {
        std::cout << rightIdxs[i] << "\t";
    }
    std::cout << std::endl;
    for(size_t i = 0; i < parentIdxs.size(); ++i) {
        std::cout << parentIdxs[i] << "\t";
    }
    std::cout << std::endl;

}


void avlBST::insertRoot(node &temp) {
    tree.push_back(temp);
    leftIdxs.push_back(-1);
    rightIdxs.push_back(-1);
    parentIdxs.push_back(-1);
}

void avlBST::insertLeft(node &temp, const int &index) {
    leftIdxs[index] = (tree.size()); // size refers to index of the inserted node
    leftIdxs.push_back(-1);
    rightIdxs.push_back(-1);
    parentIdxs.push_back(index);
    tree.push_back(temp);
}

void avlBST::insertRight(node &temp, const int &index) {
    rightIdxs[index] = (tree.size());
    leftIdxs.push_back(-1);
    rightIdxs.push_back(-1);
    parentIdxs.push_back(index);
    tree.push_back(temp);
}

void avlBST::rebalance() {
    std::cout << "REBALANCED CALLED" << std::endl;
    int risingIndex = tree.size() - 1;
    while(parentIdxs[risingIndex] != -1) {
        std::cout << "RISING Index is : " << risingIndex << std::endl;
        std::cout << " | | Balance is : " << tree[risingIndex].balance << std::endl;
        std::cout << "RIGHT IS ::: " << rightIdxs[risingIndex] << std::endl;
        //if(tree[risingIndex].balance <= -2 && tree[risingIndex].word > tree.at(rightIdxs[risingIndex]).word) {
        //    std::cout << "LEFT LEFT CASE!!!" << std::endl;
        //}

        risingIndex = parentIdxs[risingIndex];
    }
}

void avlBST::clear() {
    tree.clear();
    leftIdxs.clear();
    rightIdxs.clear();
    parentIdxs.clear();
}


void avlBST::copy(const avlBST &other) {
    tree = other.tree;
    leftIdxs = other.leftIdxs;
    rightIdxs = other.rightIdxs;
    parentIdxs = other.parentIdxs;
}

void avlBST::deleteAll() {
    tree.clear();
    leftIdxs.clear();
    rightIdxs.clear();
    parentIdxs.clear();
}
