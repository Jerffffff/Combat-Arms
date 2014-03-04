#ifndef _LTMODEL_
#define _LTMODEL_

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#include "Structs.h"

class cLTModel
{
public:
	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();
	virtual unsigned int GetBoneNode(int* Obj, const char* nodeName, unsigned int Node);
	virtual unsigned int GetNodeName(int* Obj, unsigned int Node, char* name, int maxlen);
	virtual void Function15();
	virtual unsigned int GetNodeTransform(int* Obj, unsigned int hNode, Transform* trans, char bWorldSpace);
	virtual unsigned int GetModelNextNode(int* Obj, unsigned int Node, unsigned int &Next);
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual void Function21();
	virtual unsigned int GetNumNodes(int* Obj, unsigned int &num);
};

#endif