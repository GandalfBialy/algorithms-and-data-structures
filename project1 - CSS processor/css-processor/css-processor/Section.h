#pragma once


#include "List.h"
#include "Declaration.h"



class Section
{
private:
	List<String> selectors;
	List<Declaration> declarations;
};

