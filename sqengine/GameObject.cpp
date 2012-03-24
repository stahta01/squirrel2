#include "GameObject.h"

GameObject::GameObjectSet GameObject::objects;
unsigned int GameObject::currentTick;

/**
 * @return �I�u�W�F�N�g��
 */
int
GameObject::getCount()
{
	return objects.size();
}

/// �I�u�W�F�N�g�ǉ�
void
GameObject::add(GameObject *object)
{
	objects.insert(object);
}

/// �I�u�W�F�N�g�폜
void
GameObject::remove(GameObject *object)
{
	objects.erase(object);
}

/// �R���X�g���N�^
GameObject::GameObject()
{
	add(this);
}

/// �f�X�g���N�^
GameObject::~GameObject()
{
	remove(this);
}

/**
 * ��Ԃ��X�V
 * @param diff �o�ߎ���
 */
void
GameObject::updateTick(int diff)
{
	currentTick += diff;
}

/**
 * �X�N���v�g���s�O�X�V����
 */
void
GameObject::updateBefore()
{
	// XXX �K�v�Ȃ�I�u�W�F�N�g�N���X���̏����������������ŌĂяo��
	GameObjectSet::iterator i = objects.begin();
	while (i != objects.end()) {
		(*i)->before();
		i++;
	}
}

/**
 * �X�N���v�g���s��X�V����
 */
void
GameObject::updateAfter()
{
	GameObjectSet::iterator i = objects.begin();
	while (i != objects.end()) {
		(*i)->after();
		i++;
	}
}

