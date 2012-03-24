#include <windows.h>
#include <tchar.h>

#define SCWIDTH  640
#define SCHEIGHT 480
#define INITFILE _SC("init.nut")

#include <sqobject/sqthread.h>

/**
 * squirrel ���O�o�͗p
 * @param v Squirrel VM
 * @param format �����w��
 */
static void PrintFunc(HSQUIRRELVM v, const SQChar* format, ...)
{
	va_list args;
	va_start(args, format);
	SQChar msg[1024];
	DWORD len = _vsntprintf(msg, 1024, format, args);
	::WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), msg, len, &len, NULL);
	va_end(args);
}

/**
 * �E�C���h�E�v���V�[�W��
 */
static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

#include "Screen.h"
#include "GameObject.h"
#include "GameRect.h"
#include "GamePad.h"

#include <sqobject/sqratfunc.h>
#include "GameTest.h"

Screen *screen = NULL;

static void printAll(const sqobject::ObjectInfo &key, const sqobject::ObjectInfo &value, void *userData)
{
	HSQUIRRELVM v = (HSQUIRRELVM)userData;
	PrintFunc(v, _SC("key:%s value:%s\n"), key.toString().c_str(), value.toString().c_str());
}

static void test(HSQUIRRELVM v)
{
	sqobject::ObjectInfo table = sqobject::ObjectInfo::createTable();

	table[2] = 1;
	table[_SC("a")] = 2;
	table[1] = _SC("test1");
	table[_SC("b")] = _SC("test2");

	int a = table[2];
	int b = table[_SC("a")];
	const SQChar *c = table[1];
	const SQChar *d = table[_SC("b")];
	sqobject::ObjectInfo e = table[1];
	
	PrintFunc(v, _SC("a:%d b:%d c:%s d:%s e:%s\n"), a, b, c, d, (const SQChar*)e);
	PrintFunc(v, _SC("\"a\" in table:%d \"c\" in table:%d\n"), table.has(_SC("a")) ? 1 : 0 , table.has(_SC("c")) ? 1 : 0);

	PrintFunc(v, _SC("iterator test: function\n"));
	table.foreach(printAll, (void*)v);

	PrintFunc(v, _SC("iterator test: function object\n"));
	struct {
		HSQUIRRELVM v;
		void operator()(sqobject::ObjectInfo &key, sqobject::ObjectInfo &value) {
			PrintFunc(v, _SC("key:%s value:%s\n"), key.toString().c_str(), value.toString().c_str());
		}
	} func = {v};
	table.foreach(func);
	
	sqobject::ObjectInfo array = sqobject::ObjectInfo::createArray();
	array.append(1);
	array.append(_SC("abc"));
	array.append(2);
	array.append(_SC("test"));
	array.append(_SC("test"));
	array.append(_SC("test2"));
	array.append(_SC("test2"));
	array.append((void*)NULL);

	array.removeValue(2);
	array.removeValue(_SC("test"), true);
	array.removeValue(_SC("test2"), false);

	struct {
		void operator()(int idx, sqobject::ObjectInfo &value) {
			sqobject::printf(_SC("idx:%d value:%s\n"), idx, value);
		}
	} afunc;
	array.foreach(afunc);
}

static SQRESULT throwfunc(HSQUIRRELVM v)
{
	sqobject::StackInfo stack(v);
	return sq_throwerror(v, stack.getArg(0));
}

static SQRESULT testfunc(HSQUIRRELVM v)
{
	sqobject::StackInfo stack(v);

#if 0
	sqobject::ObjectInfo engine = stack.getArg(0);
#if 1
	sqobject::ObjectInfo mapTrigger = engine.get(_SC("mapTrigger"));
	mapTrigger.create(_SC("test"), 10);
	mapTrigger.create(_SC("test2"), _SC("hoge"));
#else
	sqobject::ObjectInfo mapTrigger;
	mapTrigger.initTable();
	mapTrigger.create(_SC("test"),  20);
	mapTrigger.create(_SC("test2"), _SC("huga"));
	engine.set(_SC("mapTrigger"), mapTrigger);
#endif
#else
	stack[0][_SC("mapTrigger")][_SC("test")] = 30;
	stack[0][_SC("mapTrigger")][_SC("test2")] = _SC("moge");
#endif
	return 0;
}

/**
 * ���C��
 */
int
WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE, LPTSTR, INT)
{
	//�E�C���h�E�N���X�̓o�^
	WNDCLASSEX wc = {
		sizeof wc,
		CS_CLASSDC,
		WndProc, 0, 0,
		GetModuleHandle(NULL), 0, 0, 0, 0,
		_T("WindowClassName"), 0
		};
	if (FAILED(RegisterClassEx(&wc))) {
		return -1;
	}

	// �e�X�g�\���p�ɃR���\�[�����蓖��
	::AllocConsole();

	// �E�C���h�E�𐶐�
	RECT rect = {0,0,SCWIDTH,SCHEIGHT};
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	int width  = rect.right-rect.left;
	int height = rect.bottom-rect.top;
	HWND hWnd = CreateWindow(wc.lpszClassName,
							 _T("TEST PROGRAM"),
							 WS_OVERLAPPEDWINDOW,
							 CW_USEDEFAULT, CW_USEDEFAULT, width, height,
							 NULL, NULL, wc.hInstance, NULL);
	int ret = 0;
	if (hWnd) {
		
		screen = new Screen();
		if (screen->init(hWnd)) {
			
			// squirrel ������
			HSQUIRRELVM v = sqobject::init();
			
			// print �̓o�^
			sq_setprintfunc(v, PrintFunc);

			{
				test(v);
				sqobject::ObjectInfo root = sqobject::ObjectInfo::getRoot();
				root[_SC("testfunc")] = testfunc;
				root[_SC("throwfunc")] = throwfunc;
			}

			// squirrel �g�ݍ��݃N���X�o�^
			sqobject::Object::registerClass();
			sqobject::Thread::registerClass();
			sqobject::Thread::registerGlobal();

			// XXX ���O�̃N���X�o�^�͂����ɒǉ�
			GameRect::registerClass();
			GamePad::registerClass();
			GameTest::registerClass();
			
			// squirrel �X���b�h����������
			sqobject::Thread::init();
			
			// �N���X�N���v�g�����s
			sqobject::Thread::fork(INITFILE);
			
			// ��ʕ\���J�n
			ShowWindow(hWnd,SW_SHOWDEFAULT);
			UpdateWindow(hWnd);
			
			// ���C�����[�v
			DWORD prevTick = ::GetTickCount();
			bool working = true;
			while (working) {
				MSG msg;
				if (PeekMessage(&msg,0,0,0,PM_REMOVE)) {
					// �E�C���h�E���b�Z�[�W�̏���
					TranslateMessage(&msg);
					DispatchMessage(&msg);
					if (msg.message == WM_QUIT) {
						working = false;
					}
				} else {

					// ���ԍX�V
					DWORD tick = ::GetTickCount();
					int diff = tick - prevTick;
					prevTick = tick;

					// �p�b�h�X�V
					GamePad::update();
					
					// �I�u�W�F�N�g��ԍX�V
					GameObject::updateTick(diff);
					GameObject::updateBefore();
					
					// squirrel �X���b�h�X�V
					sqobject::Thread::update(diff);
					if (sqobject::Thread::main() == 0) {
						//�I�������r��
						//working = false;
					}

					// �I�u�W�F�N�g��ԍX�V
					GameObject::updateAfter();
					
					// ��ʍX�V
					screen->render();
				}
			}
			
			// squirrel �X���b�h�����I��
			sqobject::Thread::done();
			// squirrel �I��
			sqobject::done();

			delete screen;
			screen = NULL;
		} else {
			DestroyWindow(hWnd);
			ret = -1;
		}
	} else {
		ret = -1;
	}

	::FreeConsole();
	// �E�C���h�E�N���X���
	UnregisterClass(wc.lpszClassName, wc.hInstance);
	
	return ret;
}
