#pragma once


#include "Section.h"
//#include "BlockIterator.h"


template<size_t N>
class Block {
private:
	Section sections[N];
	bool isFull = false;

public:
	void print() {
		for (int i = 0; i < N; i++) {
			std::cerr << "Section " << i << ": ";
			sections[i].print();
		}
	}

	
    void setSection(int index, Section section) {
        sections[index] = section;
    }

	
    Section getSection(int index) const {
        return sections[index];
    }
	
	
	bool getIsFull() const {
		return isFull;
	}

	
	void setIsFull(bool isFull) {
		this->isFull = isFull;
	}
	
	
	void removeSection(int index) {
		sections[index] = Section();
	}

	
	int getSectionsCount() const {
		int count = 0;

		//// use list methods to count the sections
		//Node<Section>* currentSection = sections.getHead();
		//	
		//// count the sections
		//while (currentSection != nullptr) {
		//	count++;
		//	currentSection = currentSection->next;
		//}

		return count;
	}


	Section& operator[](int index) {
		return sections[index];
	}
};
