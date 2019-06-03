#pragma once
#include "Exports.h"

class ENGINEDLL_API Component {
private:
	const char* m_name;

protected:
	void SetName(const char* name) { m_name = name; }

public:
	Component();
	~Component();

	virtual void Update() = 0;
	const char* GetName() { return m_name; }
};

