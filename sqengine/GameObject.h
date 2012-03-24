#ifndef __INCLUDE_GAMEOBJ__
#define __INCLUDE_GAMEOBJ__

#include <set>
#include <sqobject/sqobjectclass.h>

/**
 * �Q�[���p�I�u�W�F�N�g���N���X
 */
class GameObject : public sqobject::Object {

public:
	/// �R���X�g���N�^
	GameObject();
	/// �f�X�g���N�^
	virtual ~GameObject();

	/**
	 * ��Ԃ��X�V
	 * @param diff �o�ߎ���
	 */
	static void updateTick(int diff);

	/**
	 * �X�N���v�g���s�O�X�V����
	 */
	static void updateBefore();

	/**
	 * �X�N���v�g���s��X�V����
	 */
	static void updateAfter();

	/**
	 * @return �I�u�W�F�N�g��
	 */
	static int getCount();

protected:
	static unsigned int currentTick; //< ���݂� tick�l�L�^�p
	typedef std::set<GameObject*> GameObjectSet; //< �I�u�W�F�N�g�ꗗ
	static GameObjectSet objects; //< �I�u�W�F�N�g�ꗗ
	static void add(GameObject *obj); //< �I�u�W�F�N�g�ǉ�
	static void remove(GameObject *obj); //< �I�u�W�F�N�g�폜

	/**
	 * ��Ԃ��X�V
	 */
	virtual void before(){};
	virtual void after(){};
};

#endif
