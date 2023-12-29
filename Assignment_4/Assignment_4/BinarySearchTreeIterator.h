#pragma once

#include "BinarySearchTree.h"
#include <stack>

template<typename T>
class BinarySearchTreeIterator
{
private:
    using BSTree = BinarySearchTree<T>;
    using BNode = BinaryTreeNode<T>;
    using BTreeNode = BNode*;
    using BTNStack = std::stack<BTreeNode>;

    const BSTree& fBSTree;
    BTNStack fStack;

    void pushLeft(BTreeNode aNode)
    {
        if (!aNode->empty()) {
            fStack.push(aNode);
            pushLeft(aNode->left);
        }
    }

public:
    using Iterator = BinarySearchTreeIterator<T>;

    BinarySearchTreeIterator(const BSTree& aBSTree) : fBSTree(aBSTree), fStack() { pushLeft(aBSTree.fRoot); };

    const T& operator*() const { return fStack.top()->key; }

    Iterator& operator++()
    {
        BTreeNode b = fStack.top();
        fStack.pop();
        pushLeft(b->right);
        return *this;
    }

    Iterator operator++(int)
    {
        Iterator i = new Iterator(*this);
        i++;
        return i;
    }

    bool operator==(const Iterator& aOtherIter) const
    {
        if (aOtherIter.fStack == fStack && &aOtherIter.fBSTree == &fBSTree) {
            return true;
        }
        else {
            return false;
        }
    }

    bool operator!=(const Iterator& aOtherIter) const
    {
        if (!(aOtherIter.fStack == fStack && &aOtherIter.fBSTree == &fBSTree)) {
            return true;
        }
        else {
            return false;
        }
    }

    Iterator begin() const
    {
        Iterator i = Iterator(*this);
        i.fStack = BTNStack();
        BTreeNode ifBSTreefRoot = i.fBSTree.fRoot;
        i.pushLeft(ifBSTreefRoot);
        return i;
    }

    Iterator end() const
    {
        Iterator i = Iterator(*this);
        i.fStack = BTNStack();
        return i;
    }
};
