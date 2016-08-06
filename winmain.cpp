
// �Z���^
// ���[�h���X�_�C�A���O�{�b�N�X���쐬

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include <commctrl.h>
#include "resource.h"
#include "UserDataClass.h"

// ------------------- �v���g�^�C�v�錾 -------------------- //

// ���C���ƂȂ�_�C�A���O�v���V�[�W���i���[�h���X�_�C�A���O�{�b�N�X�j
INT_PTR CALLBACK MyDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);

// �ҏW�t�H�[���̃_�C�A���O�v���V�[�W���i���[�_���_�C�A���O�{�b�N�X�j
INT_PTR CALLBACK MyDlgProc2(HWND hDlg2, UINT msg, WPARAM wp, LPARAM lp);

// �t�@�C�������݂��邩�ǂ����̊m�F
bool CheckFiles();
// ���ۂɃt�@�C�������݂��邩�ǂ����m�F
bool DoCheckFiles();

// -------- MyDlgProc -------- //

// ���[�U���X�g������������
bool InitUserList(HWND hDlg);
// ���ۂɃ��[�U���X�g������������
bool DoInitUserList(HWND hDlg);

// ���X�g�R���g���[����ݒ肷��
bool InitListCtrl(HWND hDlg);
// ���ۂɃ��X�g�R���g���[����ݒ肷��
bool DoInitListCtrl(HWND hDlg);

// �o�^�{�^���������ꂽ�Ƃ��̏���
void PushAddButton(HWND hDlg);

// �ҏW�{�^���������ꂽ�Ƃ��̏���
void PushEditButton(HWND hDlg);

// �����{�^���������ꂽ�Ƃ��̏���
void PushSearchButton(HWND hDlg);

// �폜�{�^���������ꂽ�Ƃ��̏���
void PushDeleteButton(HWND hDlg);

// ���Z�b�g�{�^���������ꂽ�Ƃ��̏���
void PushResetButton(HWND hDlg);
// ���ۂɃ��Z�b�g���s��
bool DoResetText(HWND hDlg);

// ���[�U���X�g���X�V����Ƃ�
void UpdateUserList(HWND hDlg);
// ���ۂɃ��[�U���X�g���X�V����
bool DoUpdateUserList(HWND hDlg);

// -------- MyDlgProc2 -------- //

// �G�f�B�b�g�{�b�N�X���w��̕�����ŏ���������
bool InitEditBox(HWND hDlg2);
// ���ۂɃG�f�B�b�g�{�b�N�X���w��̕�����ŏ���������
bool DoInitEditBox(HWND hDlg2);

// �m��{�^���������ꂽ�Ƃ��̏���
void PushOkButton(HWND hDlg2);
// ���ۂɕҏW���s���Ƃ��̏���
bool DoEditUserdata(HWND hDlg2);


// winmain�֐�
int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
	LPSTR lpsCmdLine, int nCmdShow)
{
	// ���b�Z�[�W�Ɋւ���ϐ�
	MSG msg;
	BOOL bRet;

	// �E�B���h�E�n���h��
	HWND hDlg;

	// ���[�h���X�_�C�A���O�{�b�N�X���쐬
	hDlg = CreateDialog(
		hCurInst,						// �C���X�^���X�n���h��
		MAKEINTRESOURCE(IDD_DIALOG1),	// ���\�[�X��
		NULL,							// �e�n���h��
		(DLGPROC)MyDlgProc);			// �v���V�[�W����
	
	// �_�C�A���O�{�b�N�X��\��
	ShowWindow(hDlg, nCmdShow);

	// ���b�Z�[�W����
	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		// ���b�Z�[�W�̎擾�Ɏ��s�����Ƃ�
		if (bRet == -1){
			break;
		}
		else{	// ���b�Z�[�W�̎擾�ɐ��������Ƃ�
			// �_�C�A���O���̃��b�Z�[�W�̂Ƃ�
			if (!IsDialogMessage(hDlg, &msg)){
				TranslateMessage(&msg);		// ���b�Z�[�W��|��
				DispatchMessage(&msg);		// ���b�Z�[�W���v���V�[�W���ɓ]��
			}
		}
	}
}


// ���C���ƂȂ�_�C�A���O�v���V�[�W���i���[�h���X�_�C�A���O�{�b�N�X�j
INT_PTR CALLBACK MyDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
	// ���b�Z�[�W������
	switch (msg)
	{

	// �_�C�A���O���Ăяo�����Ƃ�
	case WM_INITDIALOG:
		
		// �t�@�C�������݂��邩�m�F
		if (!CheckFiles()){
			DestroyWindow(hDlg);	// �_�C�A���O�����
			PostQuitMessage(0);		// ���b�Z�[�W�L���[��0�𑗂�
		}

		// ���[�U���X�g��������
		if (!InitUserList(hDlg))
		{
			DestroyWindow(hDlg);	// �_�C�A���O�����
			PostQuitMessage(0);		// ���b�Z�[�W�L���[��0�𑗂�
		}

		// ���X�g�R���g���[����ݒ�
		if (!InitListCtrl(hDlg))
		{
			DestroyWindow(hDlg);	// �_�C�A���O�����
			PostQuitMessage(0);		// ���b�Z�[�W�L���[��0�𑗂�
		}

		// ���[�U���X�g���X�V����
		UpdateUserList(hDlg);

		return TRUE;

	// �{�^���������ꂽ�Ƃ�
	case WM_COMMAND:

		// �R�}���h���擾
		switch (LOWORD(wp))
		{

		// �O���[�v�������͂��ꂽ
		case IDC_EDIT_GROUP:
			return TRUE;
		
		// ���O�����͂��ꂽ
		case IDC_EDIT_NAME:
			return TRUE;

		// �Z�������͂��ꂽ
		case IDC_EDIT_ADDRESS:
			return TRUE;

		// �d�b�ԍ������͂��ꂽ
		case IDC_EDIT_TEL:
			return TRUE;

		// ���낪�I�����ꂽ
		case IDC_LIST_NAMELIST:
			return TRUE;

		// �o�^�{�^���������ꂽ
		case IDC_BUTTON_ADD:
			// �o�^���s��
			PushAddButton(hDlg);
			return TRUE;

		// �ҏW�{�^���������ꂽ
		case IDC_BUTTON_EDIT:
			// �ҏW�{�^���������ꂽ�Ƃ�
			PushEditButton(hDlg);
			return TRUE;

		// �����{�^���������ꂽ
		case IDC_BUTTON_SEARCH:
			// �����{�^���������ꂽ�Ƃ�
			PushSearchButton(hDlg);
			return TRUE;

		// �폜�{�^���������ꂽ
		case IDC_BUTTON_DELETE:
			// �o�^���s��
			PushDeleteButton(hDlg);
			return TRUE;

		// ���Z�b�g�{�^���������ꂽ
		case IDC_BUTTON_RESET:
			// ���Z�b�g�{�^���������ꂽ�Ƃ�
			PushResetButton(hDlg);
			return TRUE;

		// ���j���[�̏I���������ꂽ
		case ID_END:
			DestroyWindow(hDlg);	// �_�C�A���O�����
			PostQuitMessage(0);		// ���b�Z�[�W�L���[��0�𑗂�
			return TRUE;

		// �z��O�̏���
		default:
			return TRUE;
		}

	// ����{�^���������ꂽ
	case WM_CLOSE:
		DestroyWindow(hDlg);	// �_�C�A���O�����
		PostQuitMessage(0);		// ���b�Z�[�W�L���[��0�𑗂�
		return TRUE;

	// �f�t�H���g�v���V�[�W��
	default:
		return FALSE;
	}

	return FALSE;
}


// �ҏW�t�H�[���̃_�C�A���O�v���V�[�W���i���[�_���_�C�A���O�{�b�N�X�j
INT_PTR CALLBACK MyDlgProc2(HWND hDlg2, UINT msg, WPARAM wp, LPARAM lp)
{
	// ���b�Z�[�W������
	switch (msg)
	{

	// �_�C�A���O���Ăяo�����Ƃ�
	case WM_INITDIALOG:

		// �G�f�B�b�g�{�b�N�X���w��̕�����ŏ���������
		InitEditBox(hDlg2);

		return TRUE;

	// �{�^���������ꂽ�Ƃ�
	case WM_COMMAND:

		// �R�}���h���擾
		switch (LOWORD(wp))
		{

		// �m��{�^���������ꂽ�Ƃ�
		case IDOK:

			// �m��{�^���������ꂽ�Ƃ��̏���
			PushOkButton(hDlg2);

			return TRUE;

		// �L�����Z���{�^���������ꂽ�Ƃ�
		case IDC_BUTTON_CANCEL2:
			EndDialog(hDlg2, TRUE);
			return TRUE;

		// �z��O�̏���
		default:
			return TRUE;
		}

	// ����{�^���������ꂽ
	case WM_CLOSE:
		EndDialog(hDlg2, TRUE);
		return TRUE;

	// �f�t�H���g�v���V�[�W��
	default:
		return FALSE;
	}

	return FALSE;
}


// �t�@�C�������݂��邩�ǂ������m�F����
bool CheckFiles()
{
	// �t�@�C�������݂����A���t�@�C���̍쐬�Ɏ��s
	if (!(DoCheckFiles()))
	{
		// �t�@�C���쐬���s�Ɋւ��郁�b�Z�[�W
		MessageBox(
			NULL,
			TEXT("�t�@�C���̍쐬�Ɏ��s���܂����B"),
			TEXT("�G���["),
			MB_ICONINFORMATION | MB_OK);
	}

	return true;
}


// ���ۂɃt�@�C�������݂��邩�ǂ����m�F
bool DoCheckFiles()
{
	// �t�@�C���|�C���^
	FILE *fp;

	// ���[�U���̕ۑ��p�X���t�@�C���I�[�v���i�ǂݍ��݃��[�h�j
	if ((fp = fopen(userPath, "rb")) == NULL)
	{
		// �t�@�C�������݂��Ȃ��̂ō쐬����
		if ((fp = fopen(userPath, "wb")) == NULL){
			return false;
		}

		// �t�@�C���쐬�����Ɋւ��郁�b�Z�[�W�{�b�N�X
		MessageBox(
			NULL,
			TEXT("���[�U�f�[�^�����݂��Ȃ��̂Ńt�@�C�����쐬���܂����B"),
			TEXT("�쐬���܂���"),
			MB_ICONINFORMATION | MB_OK);
	}

	// �t�@�C���N���[�Y
	fclose(fp);

	return true;
}


// ���[�U���X�g������������
bool InitUserList(HWND hDlg)
{
	// ���s�����Ƃ�
	if (!(DoInitUserList(hDlg)))
	{
		// ���X�g�X�V�Ɏ��s�����Ƃ��̃��b�Z�[�W�{�b�N�X
		MessageBox(
			hDlg,
			TEXT("���[�U���X�g�̃J�����̏������Ɏ��s���܂����B"),
			TEXT("�G���["),
			MB_ICONEXCLAMATION | MB_OK);

		return false;
	}

	return true;
}

// ���ۂɃ��[�U���X�g������������
bool DoInitUserList(HWND hDlg)
{
	// ���X�g�R���g���[���̃n���h�����擾
	HWND hList = GetDlgItem(hDlg, IDC_LIST_NAMELIST);

	// �J����
	LV_COLUMN lvcol;

	// �ԍ��i�J�����j
	lvcol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvcol.fmt = LVCFMT_LEFT;
	lvcol.cx = 80;
	lvcol.pszText = TEXT("�ԍ�");
	ListView_InsertColumn(hList, 0, &lvcol);

	// �O���[�v�i�J�����j
	lvcol.cx = 150;
	lvcol.pszText = TEXT("�O���[�v");
	ListView_InsertColumn(hList, 1, &lvcol);

	// ���O�i�J�����j
	lvcol.cx = 140;
	lvcol.pszText = TEXT("���O");
	ListView_InsertColumn(hList, 2, &lvcol);

	// �Z���i�J�����j
	lvcol.cx = 270;
	lvcol.pszText = TEXT("�Z��");
	ListView_InsertColumn(hList, 3, &lvcol);

	// �d�b�ԍ��i�J�����j
	lvcol.cx = 170;
	lvcol.pszText = TEXT("�d�b�ԍ�");
	ListView_InsertColumn(hList, 4, &lvcol);

	return true;
}


// ���X�g�R���g���[����ݒ肷��
bool InitListCtrl(HWND hDlg)
{
	// ���s�����Ƃ�
	if (!(DoInitListCtrl(hDlg)))
	{
		// ���X�g�X�V�Ɏ��s�����Ƃ��̃��b�Z�[�W�{�b�N�X
		MessageBox(
			hDlg,
			TEXT("���X�g�R���g���[���̐ݒ�Ɏ��s���܂����B"),
			TEXT("�G���["),
			MB_ICONEXCLAMATION | MB_OK);

		return false;
	}

	return true;
}


// ���ۂɃ��X�g�R���g���[����ݒ肷��
bool DoInitListCtrl(HWND hDlg)
{
	// ���X�g�R���g���[���̃n���h�����擾
	HWND hList = GetDlgItem(hDlg, IDC_LIST_NAMELIST);

	// ��s�I���\�E�O���b�h����\��
	ListView_SetExtendedListViewStyle(
		hList,
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return true;
}


// ���[�U���X�g���X�V����Ƃ�
void UpdateUserList(HWND hDlg)
{
	// ���s�����Ƃ�
	if (!(DoUpdateUserList(hDlg)))
	{
		// ���X�g�X�V�Ɏ��s�����Ƃ��̃��b�Z�[�W�{�b�N�X
		MessageBox(
			hDlg,
			TEXT("���[�U���X�g�̍X�V�Ɏ��s���܂����B"),
			TEXT("�G���["),
			MB_ICONEXCLAMATION | MB_OK);

		return;
	}
}

// ���ۂɃ��[�U���X�g���X�V����
bool DoUpdateUserList(HWND hDlg)
{
	// ���X�g�R���g���[���̃n���h�����擾
	HWND hList = GetDlgItem(hDlg, IDC_LIST_NAMELIST);

	// �f�[�^�N���X�̃C���X�^���X
	DATA data;

	// �X�V����
	if (!(data.ShowUserList(hList))){
		return false;
	}

	return true;
}


// �o�^�{�^���������ꂽ�Ƃ��̏���
void PushAddButton(HWND hDlg)
{
	// �o�b�t�@
	char group[256];	// �O���[�v��
	char name[256];		// ���O
	char address[256];	// �Z��
	char tel[256];		// �d�b�ԍ�

	// ���͕������擾
	GetDlgItemText(hDlg, IDC_EDIT_GROUP, group, sizeof(group));		// �O���[�v��
	GetDlgItemText(hDlg, IDC_EDIT_NAME, name, sizeof(name));			// ���O
	GetDlgItemText(hDlg, IDC_EDIT_ADDRESS, address, sizeof(address));	// �Z��
	GetDlgItemText(hDlg, IDC_EDIT_TEL, tel, sizeof(tel));				// �d�b�ԍ�

	// �G�f�B�b�g�R���g���[���ɂ����ăO���[�v���ȊO�̋󗓂��P�ł�����Ƃ�
	if ((strcmp(name, "") == 0) || (strcmp(address, "") == 0) || (strcmp(tel, "") == 0))
	{
		// �P�ł����͂���Ă��Ȃ��Ƃ��̃��b�Z�[�W
		MessageBox(
			hDlg,
			TEXT("���͂���Ă��Ȃ����ڂ�����܂��B"),
			TEXT("�G���["),
			MB_ICONEXCLAMATION | MB_OK);

		return;
	}

	// DATA�N���X�̃C���X�^���X
	DATA userdata;

	// �ǉ�
	if (userdata.UserAdd(group, name, address, tel))
	{
		// ���[�U���X�g���X�V����
		UpdateUserList(hDlg);

		// �o�^�����̃��b�Z�[�W�{�b�N�X��\��
		MessageBox(
			hDlg,
			TEXT("�o�^���������܂����B"),
			TEXT("�o�^����"),
			MB_ICONINFORMATION | MB_OK);

		// ���̓t�H�[�������Z�b�g����
		PushResetButton(hDlg);
	}
	else
	{
		// ���[�U���X�g���X�V����
		UpdateUserList(hDlg);

		// �o�^���s�̃��b�Z�[�W�{�b�N�X��\��
		MessageBox(
			hDlg,
			TEXT("�o�^�Ɏ��s���܂����B"),
			TEXT("�G���["),
			MB_ICONEXCLAMATION | MB_OK);
	}
}


// �ҏW�{�^���������ꂽ�Ƃ��̏���
void PushEditButton(HWND hDlg)
{
	// �y���j�z
	// �E�ҏW�{�^�����������ƃ_�C�A���O�{�b�N�X��\������
	// �E�_�C�A���O�{�b�N�X�ɂĕҏW���s��

	// �e�E�B���h�E�̃C���X�^���X�n���h��
	HINSTANCE hInst;
	// ���X�g�R���g���[���̃n���h��
	HWND hList;
	// ���X�g�R���g���[���őI������Ă��鍀�ڂ̔ԍ�
	int index;

	// ���X�g�R���g���[���̃n���h���E�e�E�B���h�E�̃E�B���h�E�n���h�����擾
	if (((hList = GetDlgItem(hDlg, IDC_LIST_NAMELIST)) == NULL)
		|| ((hInst = (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE)) == NULL))
	{
		// ���s�����Ƃ��̃��b�Z�[�W
		MessageBox(
			hDlg,
			TEXT("�������Ɏ��s���܂����B"),
			TEXT("�G���["),
			MB_ICONEXCLAMATION | MB_OK);

		return;
	}

	// ���X�g�R���g���[���őI�𒆂̃A�C�e�����擾
	if ((index = ListView_GetNextItem(hList, -1, LVNI_ALL | LVNI_SELECTED)) == -1)
	{
		// �I�����Ă��Ȃ��Ƃ��̃��b�Z�[�W
		MessageBox(
			hDlg,
			TEXT("�ҏW���鍀�ڂ�I�����Ă��������B"),
			TEXT("�G���["),
			MB_ICONEXCLAMATION | MB_OK);
		
		return;
	}

	// �ҏW�t�H�[���̃_�C�A���O�{�b�N�X��\������
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hDlg, MyDlgProc2);
}


// �����{�^���������ꂽ�Ƃ��̏���
void PushSearchButton(HWND hDlg)
{
	//DATA�N���X�̃C���X�^���X
	DATA data;
	// ���X�g�R���g���[���̃n���h��
	HWND hList;

	// �t�@�C���̌������ʂ̌���
	long searchCount;
	
	// �����L�[��ۑ�����o�b�t�@
	char group[256];	// �O���[�v��
	char name[256];		// ���O
	char address[256];	// �Z��
	char tel[256];		// �d�b�ԍ�

	// ���X�g�R���g���[���̃n���h�����擾
	if ((hList = GetDlgItem(hDlg, IDC_LIST_NAMELIST)) == NULL)
	{
		// �����Ɏ��s�����Ƃ��̃��b�Z�[�W
		MessageBox(
			hDlg,
			TEXT("�����Ɏ��s���܂����B"),
			TEXT("�G���["),
			MB_ICONEXCLAMATION | MB_OK);

		return;
	}
	
	// ���͕������擾
	GetDlgItemText(hDlg, IDC_EDIT_GROUP, group, sizeof(group));		// �O���[�v��
	GetDlgItemText(hDlg, IDC_EDIT_NAME, name, sizeof(name));			// ���O
	GetDlgItemText(hDlg, IDC_EDIT_ADDRESS, address, sizeof(address));	// �Z��
	GetDlgItemText(hDlg, IDC_EDIT_TEL, tel, sizeof(tel));				// �d�b�ԍ�

	// �����L�[���P�����͂���Ă��Ȃ��Ƃ�
	if ((strcmp(group, "") == 0) && (strcmp(name, "") == 0)
		&& (strcmp(address, "") == 0) && (strcmp(tel, "") == 0))
	{
		// �����L�[���P�����͂���Ă��Ȃ��Ƃ��̃��b�Z�[�W
		MessageBox(
			hDlg,
			TEXT("�����L�[����͂��Ă��������B"),
			TEXT("�G���["),
			MB_ICONEXCLAMATION | MB_OK);

		return;
	}

	// �������s��
	if (!data.UserSearch(group, name, address, tel))
	{
		// �����Ɏ��s�����Ƃ��̃��b�Z�[�W
		MessageBox(
			hDlg,
			TEXT("�����Ɏ��s���܂����B"),
			TEXT("�G���["),
			MB_ICONEXCLAMATION | MB_OK);

		return;
	}

	// ���X�g�R���g���[���ɕ\������
	data.ShowUserSearchList(hList);

	// �������ʂ̌������擾����
	searchCount = data.GetUserSearchFileCount();

	// �������ʂ̌��������b�Z�[�W�{�b�N�X�ŕ\������
	if (searchCount == 0)
	{
		// ��v������̂�������Ȃ������Ƃ�
		MessageBox(
			hDlg,
			TEXT("��v������̂�������܂���ł����B"),
			TEXT("��������"),
			MB_ICONINFORMATION | MB_OK);
	}
	else
	{
		// ��v������̂����������Ƃ�
		char lpText[256];		// ���b�Z�[�W�{�b�N�X���̃e�L�X�g
		char countText[4];		// long�^��char�^�ɕϊ���������

		// long�^��char�^�ɕϊ�����
		sprintf(countText, "%d", searchCount);

		// lpText�ɃR�s�[����
		strcpy(lpText, countText);				// �������R�s�[
		strcat(lpText, "��������܂����B");	// �������A��	

		// ���b�Z�[�W�{�b�N�X��\��
		MessageBox(
			hDlg,
			lpText,
			TEXT("��������"),
			MB_ICONINFORMATION | MB_OK);
	}

	// userPath3�̃t�@�C�����폜����
	data.DeleteSearchFile();
}


// �폜�{�^���������ꂽ�Ƃ��̏���
void PushDeleteButton(HWND hDlg)
{
	// ���X�g�R���g���[���̃n���h�����擾
	HWND hList = GetDlgItem(hDlg, IDC_LIST_NAMELIST);

	// DATA�N���X�̃C���X�^���X
	DATA userdata;

	// �폜���郆�[�U�f�[�^�̔ԍ��i�v���C�}���L�[�j
	long number = ListView_GetNextItem(hList, -1, LVNI_ALL | LVNI_SELECTED);

	// �폜
	if (number == -1)
	{
		// �����I������Ă��Ȃ��Ƃ��̃��b�Z�[�W�{�b�N�X
		MessageBox(
			hDlg,
			TEXT("�폜���鍀�ڂ�I�����Ă��������B"),
			TEXT("�G���["),
			MB_ICONEXCLAMATION | MB_OK);
	}
	else if (userdata.UserDelete(number))
	{
		// ���[�U���X�g���X�V����
		UpdateUserList(hDlg);

		// �폜�����̃��b�Z�[�W�{�b�N�X��\��
		MessageBox(
			hDlg,
			TEXT("�폜���������܂����B"),
			TEXT("�폜����"),
			MB_ICONINFORMATION | MB_OK);
	}
	else
	{
		// ���[�U���X�g���X�V����
		UpdateUserList(hDlg);

		// �폜���s�̃��b�Z�[�W�{�b�N�X��\��
		MessageBox(
			hDlg,
			TEXT("�폜�Ɏ��s���܂����B"),
			TEXT("�G���["),
			MB_ICONEXCLAMATION | MB_OK);
	}
}


// ���Z�b�g�{�^���������ꂽ�Ƃ��̏���
void PushResetButton(HWND hDlg)
{
	// ���Z�b�g�Ɏ��s�����Ƃ�
	if (!DoResetText(hDlg))
	{
		// �폜���s�̃��b�Z�[�W�{�b�N�X��\��
		MessageBox(
			hDlg,
			TEXT("���Z�b�g�Ɏ��s���܂����B"),
			TEXT("�G���["),
			MB_ICONEXCLAMATION | MB_OK);
	}
}

// ���ۂɃ��Z�b�g���s��
bool DoResetText(HWND hDlg)
{
	// ���ꂼ������Z�b�g
	if (!SetDlgItemText(hDlg, IDC_EDIT_GROUP, TEXT(""))
		|| !SetDlgItemText(hDlg, IDC_EDIT_NAME, TEXT(""))
		|| !SetDlgItemText(hDlg, IDC_EDIT_ADDRESS, TEXT(""))
		|| !SetDlgItemText(hDlg, IDC_EDIT_TEL, TEXT(""))){
		return false;
	}

	return true;
}


// �G�f�B�b�g�{�b�N�X���w��̕�����ŏ���������
bool InitEditBox(HWND hDlg2)
{
	// �������Ɏ��s�����Ƃ�
	if (!DoInitEditBox(hDlg2))
	{
		// ���������s�̃��b�Z�[�W�{�b�N�X��\��
		MessageBox(
			hDlg2,
			TEXT("�������Ɏ��s���܂����B"),
			TEXT("�G���["),
			MB_ICONEXCLAMATION | MB_OK);

		return false;
	}

	return true;
}

// ���ۂɃG�f�B�b�g�{�b�N�X���w��̕�����ŏ���������
bool DoInitEditBox(HWND hDlg2)
{
	// hDlg�i�e�E�B���h�E�j�̃E�B���h�E�n���h��
	HWND hDlg;
	// ���X�g�R���g���[���̃n���h��
	HWND hList;
	// ���X�g�R���g���[���őI������Ă��鍀�ڂ̔ԍ�
	int index;
	// �擾����USERDATA�\����
	USERDATA userdata;
	// �ԍ���int��char�ɕϊ�����������̃o�b�t�@
	char numStr[4];


	// �e�E�B���h�EhDlg�̃E�B���h�E�n���h�����擾
	if ((hDlg = GetWindow(hDlg2, GW_OWNER)) == NULL){
		return false;
	}

	// ���X�g�R���g���[���̃n���h�����擾
	if ((hList = GetDlgItem(hDlg, IDC_LIST_NAMELIST)) == NULL){
		return false;
	}

	// ���X�g�R���g���[���őI�𒆂̃A�C�e�����擾
	if ((index = ListView_GetNextItem(hList, -1,
		LVNI_ALL | LVNI_SELECTED)) == -1){
		return false;
	}

	// USERDATA�\���̂��擾
	DATA data;									// DATA�N���X�̃C���X�^���X
	userdata = data.GetUserDataIndex(index);	// �t�@�C������index�Ԗڂ̍\���̂��擾����

	// USERDATA�\���̂��������擾�ł��Ă��Ȃ��Ƃ�
	if (userdata.number == -1){
		return false;
	}

	// �ԍ���ݒ�
	_itoa(userdata.number, numStr, 10);	// �ԍ���int��char�ɕϊ�
	if (!SetDlgItemText(hDlg2, IDC_EDIT_NUMBER2, numStr)){
		return false;
	}

	// �O���[�v����ݒ�
	if (!SetDlgItemText(hDlg2, IDC_EDIT_GROUP2, userdata.group)){
		return false;
	}

	// ���O��ݒ�
	if (!SetDlgItemText(hDlg2, IDC_EDIT_NAME2, userdata.name)){
		return false;
	}

	// �Z����ݒ�
	if (!SetDlgItemText(hDlg2, IDC_EDIT_ADDRESS2, userdata.address)){
		return false;
	}

	// �d�b�ԍ���ݒ�
	if (!SetDlgItemText(hDlg2, IDC_EDIT_TEL2, userdata.tel)){
		return false;
	}

	return true;
}


// �m��{�^���������ꂽ�Ƃ��̏���
void PushOkButton(HWND hDlg2)
{
	// ���s�����Ƃ�
	if (!(DoEditUserdata(hDlg2)))
	{
		// �ҏW�ɂɎ��s�����Ƃ��̃��b�Z�[�W�{�b�N�X
		MessageBox(
			hDlg2,
			TEXT("�ҏW�Ɏ��s���܂����B"),
			TEXT("�G���["),
			MB_ICONEXCLAMATION | MB_OK);
	}
	else
	{
		// �폜�����̃��b�Z�[�W�{�b�N�X��\��
		MessageBox(
			hDlg2,
			TEXT("�ҏW���������܂����B"),
			TEXT("�ҏW����"),
			MB_ICONINFORMATION | MB_OK);
	
		// �ҏW�t�H�[���i�_�C�A���O�j�����
		EndDialog(hDlg2, TRUE);
	}
}

// ���ۂɕҏW���s���Ƃ��̏���
bool DoEditUserdata(HWND hDlg2)
{
	// DATA�N���X�̃C���X�^���X
	DATA data;
	// USERDATA�̍\���́iNew���ҏW��EOld���ҏW�O�j
	USERDATA userDataNew, userDataOld;
	// ������̔ԍ�
	char numStr[4];
	// hDlg�i�e�E�B���h�E�j�̃E�B���h�E�n���h��
	HWND hDlg;

	// �G�f�B�b�g�R���g���[������ԍ����擾����
	GetDlgItemText(hDlg2, IDC_EDIT_NUMBER2, numStr, sizeof(numStr));	// �o�b�t�@�ɕۑ�
	userDataNew.number = atol(numStr);									// long�ɕϊ�
	// �G�f�B�b�g�R���g���[������O���[�v�����擾
	GetDlgItemText(hDlg2, IDC_EDIT_GROUP2, userDataNew.group, sizeof(userDataNew.group));
	// �G�f�B�b�g�R���g���[�����疼�O���擾
	GetDlgItemText(hDlg2, IDC_EDIT_NAME2, userDataNew.name, sizeof(userDataNew.name));
	// �G�f�B�b�g�R���g���[������Z�����擾
	GetDlgItemText(hDlg2, IDC_EDIT_ADDRESS2, userDataNew.address, sizeof(userDataNew.address));
	// �G�f�B�b�g�R���g���[������d�b�ԍ����擾
	GetDlgItemText(hDlg2, IDC_EDIT_TEL2, userDataNew.tel, sizeof(userDataNew.tel));

	// �t�@�C������USERDATA�\���̂��擾����
	userDataOld = data.GetUserDataNumber(userDataNew.number);

	// �t�@�C������̎擾�Ɏ��s�����Ƃ�
	if (userDataOld.number == -1){
		return false;
	}

	// �ύX�O�ƕύX�オ�ς���Ă��Ȃ��Ƃ�
	if (!strcmp(userDataNew.group, userDataOld.group)			// �O���[�v�����r
		&& !strcmp(userDataNew.name, userDataOld.name)			// ���O���r
		&& !strcmp(userDataNew.address, userDataOld.address)	// �Z�����r
		&& !strcmp(userDataNew.tel, userDataOld.tel))			// �d�b�ԍ����r
	{
		// �ҏW�ӏ����Ȃ��Ƃ�
		MessageBox(
			hDlg2,
			TEXT("�ύX�ӏ�������܂���B"),
			TEXT("�G���["),
			MB_ICONEXCLAMATION | MB_OK);

		return false;
	}

	// �ҏW���s��
	if (!data.UserEdit(userDataNew)){
		return false;
	}

	// �e�E�B���h�EhDlg�̃E�B���h�E�n���h�����擾
	if ((hDlg = GetWindow(hDlg2, GW_OWNER)) == NULL){
		return false;
	}

	// ���[�U���X�g���X�V����
	UpdateUserList(hDlg);

	return true;
}