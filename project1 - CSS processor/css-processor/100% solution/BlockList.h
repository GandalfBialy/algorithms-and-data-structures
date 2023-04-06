#pragma once


#include "Block.h"
#include "Section.h"


template<size_t N>
class BlockList {
private:
    List<Block<N>> blocks;

	
public:
	/*BlockListIterator<N> begin() {
		return BlockListIterator<N>(*this, 0);
	}

	BlockListIterator<N> end() {
		return BlockListIterator<N>(*this, m_blocks.getSize());
	}*/
	
    void append(Block<N> block) {
        blocks.append(block);
    }

	
	void appendSection(Section section) {
		if (blocks.isEmpty()) {
			Block<N> block;
			block.setSection(0, section);
			blocks.append(block);
		}
		else if (blocks[blocks.getSize() - 1].getIsFull()) {
			Block<N> block;
			block.setSection(0, section);
			blocks.append(block);
		}
		else {
			int lastBlockIndex = blocks.getSize() - 1;
			int lastSectionIndex = blocks[lastBlockIndex].getSectionsCount();

			blocks[lastBlockIndex].setSection(lastSectionIndex, section);
		}
	}


	void removeSection(int sectionIndex) {
		int blockIndex = sectionIndex / N;
		int sectionIndexInBlock = sectionIndex % N;

		blocks[blockIndex].removeSection(sectionIndexInBlock);

		/*if (blocks[blockIndex].getSectionsCount() == 0) {
			blocks.remove(blockIndex);
		}*/

		if (!blocks[blockIndex].getIsFull() && blockIndex != blocks.getSize() - 1) {
			int lastBlockIndex = blocks.getSize() - 1;
			int lastSectionIndex = blocks[lastBlockIndex].getSectionsCount() - 1;
			Section lastSection = blocks[lastBlockIndex].getSection(lastSectionIndex);

			blocks[blockIndex].setSection(sectionIndexInBlock, lastSection);
			blocks[lastBlockIndex].removeSection(lastSectionIndex);

			/*if (blocks[lastBlockIndex].getSectionsCount() == 0) {
				blocks.remove(lastBlockIndex);
			}*/
		}
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


	// get section l-value
	Section& getSection(int sectionIndex) {
		int blockIndex = sectionIndex / N;
		int sectionIndexInBlock = sectionIndex % N;

		return blocks[blockIndex].getSection(sectionIndexInBlock);
	}

	
	int getSize() const {
		return blocks.getSize();
	}

	
	Block<N> operator[](int index) const {
		return blocks[index];
	}


	Block<N>& operator[](int index) {
		return blocks[index];
	}

	
	bool isEmpty() const {
		return blocks.isEmpty();
	}

	
	bool isSectionEmpty(int sectionIndex) const {
		Section section = blocks[sectionIndex].getSection(sectionIndex);

		return section.getDeclarations().getSize() == 0 or
			section.getSelectors().getSize() == 0 or
			section.getSectionName() == "";
	}

	
	int getSectionsCount() const {
		int count = 0;

		for (int i = 0; i < blocks.getSize(); i++) {
			count += blocks[i].getSectionsCount();
		}

		return count;
	}
};
