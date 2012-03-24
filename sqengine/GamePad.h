#ifndef __GAMEPAD_H_
#define __GAMEPAD_H_

#include "GameObject.h"

enum {
	PAD_UP     = 1<<0,
	PAD_RIGHT  = 1<<1,
	PAD_DOWN   = 1<<2,
	PAD_LEFT   = 1<<3,
	PAD_SELECT = 1<<4,
	PAD_CANCEL = 1<<5,
};

/**
 * �L�[�p�b�h���N���X
 * �J�E���g����������
 */
class GamePad : public GameObject {

public:
	static void update();
	static void registerClass();

	/**
	 * �R���X�g���N�^
	 */
	GamePad();

	/**
	 * �f�X�g���N�^
	 */
	~GamePad();

	/**
	 * @param key �ΏۃL�[
	 * @return ������Ă��邩
	 */
	bool isPress(int key);

	/**
	 * @param key �ΏۃL�[
	 * @return �����ꂽ�u�Ԃ�
	 */
	bool isTrigger(int key);

	/**
	 * @param key �ΏۃL�[
	 * @return �����ꂽ�u�Ԃ�
	 */
	bool isRelease(int key);

	/**
	 * �����ꂽ�L�[���P�����Ԃ��i�D��x���j
	 * @return �����ꂽ�L�[
	 */
	int getKey();

	// �e�X�g�p
	static void testObject(const Object *obj);
	static void testGamePad(const GamePad *pad);

	SQRESULT testArgCount(HSQUIRRELVM v);
	static SQRESULT testArgCountStatic(HSQUIRRELVM v);
	
protected:
	static int state;
	static int prevState;
	static int tstate;
	static int rstate;
};

#endif
