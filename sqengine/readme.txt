Title: Squirrel�g�ݍ��݃G���W���T���v��
Author: �n粍�(go@wamsoft.jp)
Date: 2010/2/23

������͂ȂɁH

Squirrel (http://squirrel-lang.org/) ��g�ݍ���
�Q�[���G���W���̊T�O�T���v���R�[�h�ł�

Squirrel �͑g�ݍ��ݗp�I�u�W�F�N�g�w������ł��B
���@�I�ɂ� C ���ꕗ�ŁA�N���[�W���⋦���X���b�h�i�R���[�`���j��
�T�|�[�g���Ă���A�X�N���v�g�̎��s������C�ӂ̃^�C�~���O�Œ��f
�ł��邽�߁A�V�[���J�ڂȂǂ̐��䃍�W�b�N��g�ނ̂ɓK���Ă��܂��B

���̃T���v���G���W���ł͕`��n�ȂǁA�K�v�ȃ��W���[���� C++ 
�ŏ����N�����A����̐���� squirrel�X�N���v�g�ɂ܂�����
�X�^�C���ł���ł���܂��B

�X�N���v�g�́A�S�ăR���[�`����ԂŎ��s����邽�߁A�C�ӂ�
�^�C�~���O�Œ��f�\�ŁA���f�����^�C�~���O�ŉ�ʕ`���
�G���W�����̃C�x���g�������s���邱�ƂɂȂ�܂��B
���C�����[�v�I�\�������R�ɔz�u�\�Ȃ̂��R���[�`������̓����ł�

���V�X�e���T�v

�E�����

�@�f�t�H���g�� unicode �łŃR���p�C�����Ă���܂��B
�@���{����g���ꍇ�� BOM��UTF-8 �� UCS���g���K�v������܂�

�E�G���W���\��

 Direct3D �x�[�X�� Window 1�O��ō\�z���Ă���܂�
 �T���v���Ƃ��Ĉȉ��̊�{�I�u�W�F�N�g���g���܂�

  GamePad  �㉺���E�J�[�\�� + ENTER/ESC �̂ݑΉ���������n
�@GameRect ��`�`��p�I�u�W�F�N�g

 �܂����O�\���̂��߃R���\�[���������ŊJ���Ă܂��B

�E�ϐ����

  squirrel �̃O���[�o����Ԃ͂P�������݂��܂��B
�@Squirrel �p�̃X�N���v�g�̎��s�͂��̃O���[�o����ԏ�ł����Ȃ��A
�@��`���ꂽ�t�@���N�V������N���X�����̃O���[�o����Ԃɓo�^����Ă����܂��B

�E�^���X���b�h����

  squirrel�ɂ�镡���̃X���b�h�̕�����s��������������Ă��܂��B
  ���̂��߂ɗ��p�ł�������N���X Object / Thread ����`����Ă��܂��B
  �ڍׂ� squirrel/sqobject/manual.nut ���Q�Ƃ��Ă��������B

�E�X�N���v�g���s

�@�N�����ɃJ�����g�ɂ��� init.nut ��ǂݍ���Ŏ��s���܂��B
  �E�C���h�E�������ŕ��邱�ƂŃV�X�e���̎��s���I�����܂��B

���g���|�C���g

�E���Ԍo�ߏ�����Ǝ�����

�@���̃T���v���ł͎����Ԃ� ms �P�ʂő��肵�āA����� sqthread ��
�@����̊���ԂƂ��Ă���܂��B

�@�t���[���P�ʓ���ɂ������ꍇ�́A���C�����[�v����

  GameObject::updateTick(diff);

�@�̕����́Adiff �� 1 �ŌŒ肵�܂��B���킹�� sqobject �� wait() �ł�
�@�҂����Ԏw��Ȃǂ̒P�ʂ������̂Œ��ӂ��K�v�ł��B

�E���O�o�͏�����Ǝ�����

  print() �̌��ʂ�G���[�\���̏o�͂́Asq_setprintfunc() ��
�@�o�^���ꂽ�o�͐�t�@���N�V�����ɑ΂��čs���܂��B
�@���̕��������O�̃G���W���̃��O������A�R���\�[��������
�@���킹�Ď������܂�

�E�t�@�C���ǂݍ��ݏ�����Ǝ�����

  sqobject::Thread �́Afork() �Ȃǂ̃X�N���v�g�t�@�C���̓ǂݍ��݂ɂ�
�@�ȉ��̔񓯊��t�@�C���ǂݍ��݃��\�b�h���Ăяo���Ă��܂��B
�@����������̃G���W���ɂ��킹�Ď������Ȃ����܂��B

-----------------------------------------------------------------------------
void *sqobjOpenFile(const SQChar *filename, bool binary);
bool sqobjCheckFile(void *handler, const char **dataAddr, int *dataSize);
void sqobjCloseFile(void *handler)
-----------------------------------------------------------------------------

�@�f�t�H���g�̎����� sqobject/sqfile.cpp �ŁAsqstdio ���g���Ď������Ă܂�
�@��sqstdio �͓����I�ɂ� stdio ���g���Ă܂�

�E�Ǝ��N���X���쐬���� squirrel �Ƀo�C���h

  sqobject::Object ���p�����Ă����ƂȂɂ��ƕ֗��ł����A
�@���ꎩ�͕̂K�{�ł͂���܂���B�Ǝ��̕����A�Ǝ��̃o�C���_�œo�^�\�ł��B

  ���̃T���v���ł̓o�C���h�� sqrat ���g���Ă܂��B
  sqobject ���̃o�C���h��͂ق��Ɉȉ��̂��̂�����̂ŎQ�l�ɂ��Ă��������B

�@�@���O�o�^��: sqfunc.cpp

  ��sqobject �@�\�́A�������� Object::initSelf(), 
�@�@�j������ Object::destructor() ���Ă΂Ȃ��ƃ}�j���A���ʂ��
�@�@�@�\�͓��삵�Ȃ��Ȃ��Ă��܂��̂ł����ӂ��������B

  GameObject �́Asqobject::Object ���p��������ŁA
�@�Q�[���œT�^�I�ȃ^�X�N�X�^�C���̏������������Ă���܂��B
�@(�X�N���v�g���s�̑O��ŃI�u�W�F�N�g���Ȃ߂ŏ�ԍX�V���\�b�h������܂�)

�E���̑��Q�l

  sqobject::Object �ɂ́AC++ ����o�C���h����Ă��� squirrel �I�u�W�F�N�g��
�@�����o���Ăяo�����߂� callEvent() ������܂��B
�@�G���W�����ŏ�ԍX�V���ɃC�x���g���������̂ɕ֗��ł��B

�@sqobject �g���ׂ̍����@�\�ɂ��ẮA
  sqobject/readme.txt �� sqobject/manual.nut ��
�@�Q�Ƃ��Ă��������B

�����C�Z���X

squirrel ���l zlib���C�Z���X�ɏ]���ė��p���Ă��������B

/*
 * copyright (c)2010 Go Watanabe go@wamsoft.jp
 * zlib license
 */
