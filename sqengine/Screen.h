#ifndef __GAME_SCREEN
#define __GAME_SCREEN

#include <d3d9.h>
#include <set>
#include <algorithm>

class Screen;

/**
 * �`��ΏۃI�u�W�F�N�g
 */
class ScreenObject { 
	friend class Screen;
public:
	ScreenObject(Screen *screen, int index);
	~ScreenObject();
	
	void setIndex(int index);

protected:
	Screen *screen;
	int index;
	bool visible;
	virtual void render(LPDIRECT3DDEVICE9 pD3DDevice) = 0;
};

/**
 * �`��x�[�X
 */
class Screen {

	friend class ScreenObject;
public:
	/**
	 * �R���X�g���N�^
	 */
	Screen();

	/**
	 * �f�X�g���N�^
	 */
	~Screen();

	/**
	 * ������
	 * @param hWnd �E�C���h�E�n���h��
	 * @return ���������� true
	 */
	bool init(HWND hWnd);

	/**
	 * ��ʃ����_�����O���s
	 */
	void render();
	
protected:
	LPDIRECT3D9 pD3D;
	LPDIRECT3DDEVICE9 pD3DDevice;

	typedef ScreenObject *OBJP;

	// ������r�֐�: index �Ń\�[�g����
	struct lessObj : std::binary_function <ScreenObject*,ScreenObject*,bool> {
		bool operator() (const OBJP &obj1, const OBJP &obj2) {
			return obj1->index < obj2->index;
		}
	};
	typedef std::multiset<OBJP,lessObj> ObjSet;
	// �I�u�W�F�N�g�o�^�p
	ObjSet all;

	void add(ScreenObject *obj);
	void remove(ScreenObject *obj);
};

#endif
