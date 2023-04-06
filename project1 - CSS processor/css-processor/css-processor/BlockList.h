#pragma once


#include "Block.h"


template<size_t N>
class BlockList {
private:
    List<Block<N>> blocks;

public:
    void append(Block<N> block) {
        blocks.append(block);
    }

	void print() {
		for (int i = 0; i < blocks.getSize(); i++) {
			std::cerr << "Block " << i << ": ";
			blocks[i].print();
		}
	}


    List<Block<N>> getBlocks() const {
        return blocks;
    }

    
	Block<N> getBlock(int index) const {
		return blocks[index];
	}


	Section getSection(int blockIndex, int sectionIndex) const {
		return blocks[blockIndex].getSection(sectionIndex);
	}


	Section getSection(int sectionIndex) const {
		int blockIndex = sectionIndex / N;
		int sectionIndexInBlock = sectionIndex % N;

		return blocks[blockIndex].getSection(sectionIndexInBlock);
	}

	
	int getSize() const {
		return blocks.getSize();
	}

	
	/*int getSectionsCounter() const {
		return sectionsCounter;
	}*/

	
	// operator[]
	Block<N> operator[](int index) const {
		return blocks[index];
	}


	// operator
	Block<N>& operator[](int index) {
		return blocks[index];
	}

	
	int getSectionsCount() const {
		// count sections
		int sectionsCount = 0;
	
		// use list methods to count sections
		//Node<Block<N>>* currentBlock = blocks.getHead();
		
		// count sections
		/*while (currentBlock != nullptr) {
			sectionsCount += currentBlock->data.getSectionsCount();
			currentBlock = currentBlock->next;
		}*/

		return sectionsCount;
	}
};
