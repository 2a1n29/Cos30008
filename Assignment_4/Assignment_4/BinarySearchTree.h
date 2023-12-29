#pragma once

#include "BinaryTreeNode.h"
#include <stdexcept>

template<typename T>
class BinarySearchTreeIterator;

template<typename T>
class BinarySearchTree {
private:
    using BNode = BinaryTreeNode<T>;
    using BTreeNode = BNode*;
    BTreeNode fRoot;

public:
    BinarySearchTree() : fRoot(&BNode::NIL) {};

    ~BinarySearchTree() {
        if (!fRoot->empty()) {
            delete fRoot;
        }
    };

    bool empty() const {
        return fRoot->empty();
    };

    size_t height() const {
        if (empty()) {
            throw domain_error("Empty tree has no height");
        }
        else if (!empty()) {
            return fRoot->height();
        }
        else {
            return 0;
        }
    };

    bool insert(const T& aKey) {
        if (!empty()) {
            fRoot->insert(aKey);
        }
        else {
            fRoot = new BNode(aKey);
            return true;
        }
    };

    bool remove(const T& aKey) {
        if (fRoot->leaf()) {
            if (fRoot->key == aKey) {
                fRoot = &BNode::NIL;
                return true;
            }
            else {
                return false;
            }
        }
        else if (empty()) {
            throw domain_error("Unable to remove an empty tree");
            return false;
        }
        else {
            fRoot->remove(aKey, &BNode::NIL);
        }
    };

    using Iterator = BinarySearchTreeIterator<T>;

    friend class BinarySearchTreeIterator<T>;

    Iterator begin() const {
        Iterator iterator(*this);
        return iterator.begin();
    };

    Iterator end() const {
        Iterator iterator(*this);
        return iterator.end();
    };
};
