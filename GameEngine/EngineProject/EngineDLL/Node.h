#pragma once
#include "Exports.h"

class ENGINEDLL_API Node {
public:
	Node();
	~Node();

	virtual void Update() { }

	void DeleteFromMemory() { }
	void Destroy() { }
	void AddChild() { }
};
