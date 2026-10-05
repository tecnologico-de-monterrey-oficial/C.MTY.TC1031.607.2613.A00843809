#pragma once

template <typename T>

struct NodeD {
    T data;
    NodeD* next;
    NodeD* prev;

    NodeD(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    NodeD(const T& value, NodeD* nextNode, NodeD* prevNode) : data(value), next(nextNode), prev(prevNode) {}
};