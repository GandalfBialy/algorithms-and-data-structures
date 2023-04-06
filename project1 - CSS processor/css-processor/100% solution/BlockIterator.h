#pragma once


#include "List.h"
#include "Block.h"
#include "BlockList.h"
#include "Section.h"

//template <int SECTIONS_PER_BLOCK>
//class BlockIterator {
//public:
//    BlockIterator(BlockList<SECTIONS_PER_BLOCK>& blockList) :
//        blockList{ blockList },
//        currentIndex{ 0 }
//    {}
//    typedef List<Block<SECTIONS_PER_BLOCK>> BlockList;
//    typedef typename BlockList::Iterator Iterator;
//
//    BlockIterator(BlockList* blocks) : blocks_(blocks), current_block_(nullptr), current_section_(0) {}
//
//    bool hasNext() const {
//        if (current_block_ == nullptr || current_section_ >= current_block_->getSize()) {
//            if (blocks_ == nullptr) {
//                return false;
//            }
//            if (current_block_ == nullptr) {
//                current_block_ = blocks_->first();
//            }
//            else {
//                ++current_block_;
//            }
//            current_section_ = 0;
//        }
//        return true;
//    }
//
//    Iterator& next() {
//        ++current_section_;
//        return *this;
//    }
//
//    typename List<Block<SECTIONS_PER_BLOCK>>::Iterator begin() {
//        return blockList.getBlocks().begin();
//    }
//
//    typename List<Block<SECTIONS_PER_BLOCK>>::Iterator end() {
//        return blockList.getBlocks().end();
//    }
//
//    Section<SECTIONS_PER_BLOCK>& get() {
//        return (*current_block_)[current_section_ - 1];
//    }
//
//private:
//    BlockList* blocks_;
//    typename BlockList::Iterator current_block_;
//    int current_section_;
//};
