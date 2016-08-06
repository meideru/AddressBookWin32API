
// ���[�U�f�[�^�N���X�̃w�b�_

#include <Windows.h>

// �ۑ��p�X
extern char* userPath;		// ���[�U�f�[�^�̕ۑ��p�X
extern char* userPath2;		// ���[�U�f�[�^�̃R�s�[��̕ۑ��p�X
extern char* userPath3;		// ���[�U�f�[�^�̌������ʂ̕ۑ��p�X

// ���[�U�f�[�^�\����
struct USERDATA
{
	long number;		// �ԍ��i�v���C�}���L�[�j
	char group[256];	// �O���[�v��
	char name[256];		// ���O
	char address[256];	// �Z��
	char tel[256];		// �d�b�ԍ�
};

// �O���[�v�f�[�^�\����
struct GROUPDATA
{
	long number;		// �ԍ��i�v���C�}���L�[�j
	char group[256];	// �O���[�v��
};

// �f�[�^�̃N���X
class DATA
{
	// �R���X�g���N�^�E�f�X�g���N�^
public:
	DATA();		// �R���X�g���N�^
	~DATA();	// �f�X�g���N�^

	// ����J���\�b�h
private:
	long MakeNumber();			// �����Ŕԍ����쐬�i�G���[��-1��ԋp�j

	// �\���̂Ɋւ���Q�b�^
public:
	// �t�@�C������ԍ��i�ォ��j���w�肵��USERDATA���擾�i���s����number = -1�j�i��ԏ��index = 0�j
	USERDATA GetUserDataIndex(int index);
	// �t�@�C������ԍ����i�v���C�}���L�[�j���w�肵��USERDATA���擾�i���s����number = -1)
	USERDATA GetUserDataNumber(int number);

	// �\���Ɋւ���
public:
	// ���[�U�f�[�^�����X�g�ɕ\������
	bool ShowUserList(HWND hList);
	// ���[�U�f�[�^�̌������ʂ��O���t�@�C�����Q�Ƃ��ă��X�g�ɕ\������
	bool ShowUserSearchList(HWND hList);
	
	// �폜�Ɋւ���
public:
	// userPath3�̃t�@�C�����폜����
	bool DeleteSearchFile();

	// �t�@�C���̃T�C�Y�E���Ɋւ���Q�b�^
public:
	// ���[�U�f�[�^�̃t�@�C���T�C�Y���擾����
	size_t GetUserFileSize();
	// ���[�U�f�[�^�t�@�C���̌������擾����
	long GetUserFileCount();
	// �ԍ��i�v���C�}���L�[�j����C���f�b�N�X���擾�i���index = 0�j�i���s����index = -1�j
	long GetUserFileIndex(long number);
	// ���[�U�f�[�^�̃t�@�C���T�C�Y���擾����
	size_t GetUserSearchFileSize();
	// ���[�U�f�[�^�̌����p�t�@�C�����猏�����擾����
	long GetUserSearchFileCount();


	// �o�^�E�ҏW�E�����E�폜
public:
	// ���[�U�f�[�^��ǉ�����
	bool UserAdd(
		char* group, 
		char* name,
		char* address, 
		char* tel);
	// ���[�U�f�[�^��ҏW����i�����̍\���̂̔ԍ��i�v���C�}���L�[�j�͈�ӂł���K�v������܂��j
	bool UserEdit(USERDATA userdata);
	// ���[�U�f�[�^����������i�����͌����L�[�j
	bool UserSearch(char* group, char* name, char* address, char* tel);
	// ���[�U�f�[�^���폜����i�����̓��X�g�R���g���[���̐擪����̔ԍ��j
	bool UserDelete(long number);
};

