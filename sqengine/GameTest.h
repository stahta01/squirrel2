#ifndef __GAMETEST_H_
#define __GAMETEST_H_

#include "GameObject.h"
#include <vector>
#include <map>

/**
 * �e�X�g�p
 */	
class GameTest : public GameObject {

	friend class Screen;
public:

	static void registerClass() {
		SQCLASSOBJ(GameTest, _SC("GameTest"));
		SQFUNC(GameTest, printValue);
		SQFUNC(GameTest, printVector);
		SQFUNC(GameTest, printMap);
	}

	// �R���X�g���N�^
	GameTest() {
	}

	// ObjectInfo �������ɂƂ�e�X�g
	void printValue(const sqobject::ObjectInfo &obj) {
		sqobject::printf(_SC("value type:%x:%s\n"), obj.type(), obj);
	}
	
	// �x�N�^�������ɂƂ�e�X�g
	typedef std::vector<int> V;
	void printVector(const V &value) {
		if (value.size() > 0) {
			V::const_iterator it = value.begin();
			while (it != value.end()) {
				sqobject::printf(_SC("vector %d\n"), *it);
				it++;
			}
		} else {
			sqobject::printf(_SC("vector empty\n"));
		}
	}

	// map�������ɂƂ�e�X�g
	typedef std::map<sqobject::sqstring, int> M;
	void printMap(const M &value) {
		if (value.size() > 0) {
			M::const_iterator it = value.begin();
			while (it != value.end()) {
				sqobject::printf(_SC("map %s:%d\n"), it->first, it->second);
				it++;
			}
		} else {
			sqobject::printf(_SC("map empty\n"));
		}
	}
};
#endif
