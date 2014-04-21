/*
* Author: Isachenko
* Date: 2012-03-16 (Mon, 16 March 2014)
***************************************************************/

#ifdef _MSC_VER
#pragma once
#endif

#ifndef OGDF_AVLTREE_H
#define OGDF_AVLTREE_H

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <ogdf/basic/Stack.h>

template<class K_TYPE, class HEIGHT_TYPE=unsigned char>
class AVLNode
{
private:
    template <class T> friend class AVLTree;

    K_TYPE m_key;
    AVLNode *m_left;
    AVLNode *m_right;
    HEIGHT_TYPE m_height;

    static HEIGHT_TYPE getHeight(AVLNode* avlNode){
        return avlNode?avlNode->m_height:0;
    }

    char balnceValue() const {
        if (!this) return 0;
        return (getHeight(m_right) - getHeight(m_left));
    }

    void fixHeight() {
        HEIGHT_TYPE hl = getHeight(m_left);
        HEIGHT_TYPE hr = getHeight(m_right);
        m_height = (hl>hr?hl:hr) + 1;
    }

public:
    AVLNode() : m_key(0), m_left(nullptr), m_right(nullptr), m_height(1) {}
    AVLNode(K_TYPE key) : m_key(key), m_left(nullptr), m_right(nullptr), m_height(1){}
    K_TYPE key() const { return m_key; }
    bool operator <(const AVLNode<K_TYPE>& avlNode) const { return m_key<avlNode.m_key; }
    bool operator <=(const AVLNode<K_TYPE>& avlNode) const { return m_key<=avlNode.m_key; }
    bool operator >(const AVLNode<K_TYPE>& avlNode) const { return m_key>avlNode.m_key; }
    bool operator >=(const AVLNode<K_TYPE>& avlNode) const { return m_key>=avlNode.m_key; }
    bool operator ==(const AVLNode<K_TYPE>& avlNode) const { return m_key==avlNode.m_key; }
    bool operator !=(const AVLNode<K_TYPE>& avlNode) const { return m_key!=avlNode.m_key; }

};

template<class T=double>
class AVLTree
{
private:
    AVLNode<T> *m_rootNode;

    AVLNode<T> *rotateright(AVLNode<T> *u){
        AVLNode<T> *v = u->m_left;
        u->m_left = v->m_right;
        v->m_right = u;
        u->fixHeight();
        v->fixHeight();
        return v;
    }

    AVLNode<T>* rotateleft(AVLNode<T> *u){
        AVLNode<T> *v = u->m_right;
        u->m_right = v->m_left;
        v->m_left = u;
        u->fixHeight();
        v->fixHeight();
        return v;
    }

    AVLNode<T>* balance(AVLNode<T> *u){
        u->fixHeight();
        if(u->balnceValue()==2) {
            if( u->m_right->balnceValue() < 0 )
                u->m_right = rotateright(u->m_right);
            return rotateleft(u);
        }
        if(u->balnceValue()==-2) {
            if( u->m_left->balnceValue() > 0  )
                u->m_left = rotateleft(u->m_left);
            return rotateright(u);
        }
        return u; // needs no balancing
    }

    AVLNode<T> *findmin(AVLNode<T> *u)
    {
        return u->m_left?findmin(u->m_left):u;
    }

    AVLNode<T> *removemin(AVLNode<T> *u)
    {
        if( u->m_left == nullptr )
            return u->m_right;
        u->m_left = removemin(u->m_left);
        return balance(u);
    }

    // remove key from tree rooted in u.
    AVLNode<T>* removeFromNode(AVLNode<T>* u, const T &key)
    {
        if( !u ) return 0;
        if( key < u->m_key )
            u->m_left = removeFromNode(u->m_left,key);
        else if( key > u->m_key )
            u->m_right = removeFromNode(u->m_right,key);
        else //  key == u->key
        {
            AVLNode<T>* l = u->m_left;
            AVLNode<T>* r = u->m_right;
            delete u;
            if( !r ) return l;
            AVLNode<T>* min = findmin(r);
            min->m_right = removemin(r);
            min->m_left = l;
            return balance(min);
        }
        return balance(u);
    }

    void deleteSubTree(AVLNode<T>* v) {
        if (v->m_left) {
            deleteSubTree(v->m_left);
        }
        if (v->m_right) {
            deleteSubTree(v->m_right);
        }
        delete v;
    }

public:
    AVLTree() : m_rootNode(nullptr){}

    //not recursive
    AVLNode<T> *insert(const T &key) {
        ogdf::Stack<AVLNode<T>*> stack;
        AVLNode<T> *curNode = m_rootNode;
        AVLNode<T> *newNode;
        while(curNode){
            // key alredy exist
            if (key == curNode->m_key){
                return curNode;
            }
            stack.push(curNode);
            if(key < curNode->m_key)
                curNode = curNode->m_left;
            else
                curNode = curNode->m_right;
        }
        newNode = new AVLNode<T>(key);
        curNode = newNode;
        // balancing
        AVLNode<T>* parent = !stack.empty()?stack.pop():nullptr;
        while (parent) {
            curNode = balance(curNode);
            if (curNode->m_key < parent->m_key){
                parent->m_left = curNode;
            } else {
                parent->m_right = curNode;
            }
            curNode = parent;
            parent = !stack.empty()?stack.pop():nullptr;
        }
        m_rootNode = balance(curNode);
        return newNode;
    }

    AVLNode<T> *lookup(const T &key) {
        AVLNode<T> *curNode = m_rootNode;
        while(curNode){
            if (key == curNode->m_key){
                return curNode;
            }
            if (key < curNode->m_key) {
                curNode = curNode->m_left;
            } else {
                curNode = curNode->m_right;
            }
        }
        return nullptr;
    }

    void remove(const T &key){
        m_rootNode = removeFromNode(m_rootNode, key);
    }

    void removeAll() {
        deleteSubTree(m_rootNode);
        m_rootNode = nullptr;
    }

    bool isEmpty() {
        return m_rootNode == nullptr;
    }

    ~AVLTree() {
        removeAll();
    }
};

#endif
