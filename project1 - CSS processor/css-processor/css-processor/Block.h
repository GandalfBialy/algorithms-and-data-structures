#pragma once


#include "Section.h"


template<size_t N>
class Block {
private:
    //std::array<Section, N> sections;
    Section* sections = new Section[N];
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

		//return count;
	}


	// operator
	Section& operator[](int index) {
		return sections[index];
	}
};
