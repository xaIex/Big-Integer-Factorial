#include "BigInt.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Node {
    int val;
    Node* next;
};

template<class ItemType>
BigInt<ItemType>::BigInt() {
    head = nullptr;
}

template<class ItemType>
void BigInt<ItemType>::insert(ItemType item) {
    Node* newNode = new Node;
    newNode->val = item;
    newNode->next = head;
    head = newNode;
}

template<class ItemType>
BigInt<ItemType>::~BigInt() {
    Node* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }
    head = nullptr;
}

template<class ItemType>
void BigInt<ItemType>::multiplyNode(ItemType num) {
    if (num == 1 || num == 0) {
        insert(1);
        return;
    }

    insert(1); // start with 1
    for (int i = 2; i <= num; i++) {
        Node* curr = head;
        Node* prev = nullptr;
        int carry = 0;
        while (curr != nullptr) {
            int product = curr->val * i + carry; // multiply the current node with i + carry
            curr->val = product % 10; // removes the carry from the final value ex 32 % 10 = 2
            carry = product / 10; //extracts the carry from product ex 32 / 10 = 3

            prev = curr; // update prev and move to next node
            curr = curr->next;
        }
        //if a carry exists and create new node to add the digits
        while (carry != 0) {
            Node* newNode = new Node;
            newNode->val = (ItemType)carry % 10;
            newNode->next = nullptr;
            prev->next = newNode;

            carry /= 10;
            prev = prev->next;
        }
    }   
}

template<class ItemType>
void BigInt<ItemType>::print(ofstream& outFile) {
    Node* temp = head;
    string numStr;

    int digitCount = 0;
    while (temp != nullptr) {
        // Convert digit to character and insert at the beginning
        numStr.insert(numStr.begin(), '0' + temp->val); 
        digitCount++;
        // if there are 3 digits, we add a comma
        // temp->next != nullptr checks if its the last digit
        // ex. 479,001,006  9 % 3 == 0 is true but temp->next != nullptr is false which signifies,
        // it's the end of the linked list so we don't add a comma
        if (digitCount % 3 == 0 && temp->next != nullptr) {
            numStr.insert(numStr.begin(), ',');
        }
        temp = temp->next;
    }
    cout << numStr;
    outFile << numStr << endl;
}

template class BigInt<int>; // instaniate first, otherwise linking error LNK2019
      

