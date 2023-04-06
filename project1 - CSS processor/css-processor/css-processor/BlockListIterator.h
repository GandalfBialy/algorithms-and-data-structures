#pragma once


//template <int N>
//class BlockListIterator {
//public:
//    BlockListIterator(BlockList<N>& blockList, int index)
//        : m_blockList(blockList), m_index(index) {}
//
//    bool operator!=(const BlockListIterator<N>& other) const {
//        return m_index != other.m_index;
//    }
//
//    Block<N>& operator*() {
//        return m_blockList[m_index];
//    }
//
//    BlockListIterator<N>& operator++() {
//        m_index++;
//        return *this;
//    }
//
//private:
//    BlockList<N>& m_blockList;
//    int m_index;
//};
