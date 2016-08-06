
// ���[�U�f�[�^�N���X�̃\�[�X�t�@�C��

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "resource.h"
#include "UserDataClass.h"

// ���e������������
// ���[�U�f�[�^�ۑ��p�X
char* userPath = "C:\\";
// ���[�U�f�[�^�̃R�s�[��̕ۑ��p�X
char* userPath2 = "C:\\";
// ���[�U�f�[�^�̌������ʂ̕ۑ��p�X
char* userPath3 = "C:\\";
// ���e������������

// �R���X�g���N�^
DATA::DATA()
{

}

// �f�X�g���N�^
DATA::~DATA()
{

}


// �����Ŕԍ����쐬�i�G���[��-1��ԋp�j
long DATA::MakeNumber()
{
	// �t�@�C���|�C���^
	FILE *fp;

	// �ԍ��i�v���C�}���L�[�j�̍ő�l
	long max = 1;

	// �ԋp����ԍ�
	long primaryNumber = 1;

	// �f�[�^�̌������߂�
	long dataCount = GetUserFileCount();

	// �t�@�C���I�[�v��
	if ((fp = fopen(userPath, "rb")) == NULL){
		return -1;
	}

	// �o�^������0�̂Ƃ�
	if (dataCount == 0)
	{
		// �t�@�C���N���[�Y
		fclose(fp);
		// �ԍ���1��ԋp
		return 1;
	}

	// ���[�U�f�[�^�̔ԍ��i�v���C�}���L�[�j�̍ő�l���擾����
	for (long count = 1; count <= dataCount; count++)
	{
		// USDRDATA�\����
		USERDATA userdata;

		// sizeof(DATA)���̃�������ǂݏo��
		fread(&userdata, sizeof(USERDATA), 1, fp);

		// �ő�l�Ɣ�r����
		if (max < userdata.number){
			max = userdata.number;
		}
	}

	// ���[�U�f�[�^�̔ԍ��i�v���C�}���L�[�j��1~max�܂�
	// ���ׂĖ��܂��Ă����Ƃ�
	if (dataCount == max)
	{
		// �t�@�C���N���[�Y
		fclose(fp);
		// (max + 1)��ԋp
		return max + 1;
	}

	// �V�[�N��擪�ɖ߂�
	fseek(fp, 0, SEEK_SET);

	// �d�����Ȃ��ԍ��i�v���C�}���L�[�j���擾����
	// ���̔ԍ��𓮂����i����1~max�j
	for (long count = 1; count <= max; count++)
	{
		// �o�^���Ă���ԍ��i�v���C�}���L�[�j�Əd�����Ȃ����m�F����
		for (long count2 = 1; count <= dataCount; count2++)
		{
			// USDRDATA�\����
			USERDATA userdata;

			// count�Ԗڂ̂���sizeof(DATA)���̃�������ǂݏo��
			fread(&userdata, sizeof(USERDATA), 1, fp);

			// ���̔ԍ������݂����Ƃ�
			if (count == userdata.number){
				goto CORRECT;
			}

			// ���̔ԍ����Ō�܂ő��݂��Ȃ������Ƃ�
			if (count2 == dataCount){
				primaryNumber = count;
				goto END;
			}
		}

		// ���̔ԍ������݂����Ƃ�
		CORRECT:

		// �V�[�N��擪�ɖ߂�
		fseek(fp, 0, SEEK_SET);
	}

	// ���̔ԍ����Ō�܂ő��݂��Ȃ������Ƃ�
	END:

	// �t�@�C���N���[�Y
	fclose(fp);

	return primaryNumber;
}


// �t�@�C������ԍ��i�ォ��j���w�肵��USERDATA���擾�i���s����number = -1�j�i��ԏ��index = 0�j
USERDATA DATA::GetUserDataIndex(int index)
{
	// �t�@�C���|�C���^
	FILE *fp;

	// �ԋp����USERDATA�\����
	USERDATA userdata;

	// �t�@�C���I�[�v��
	if ((fp = fopen(userPath, "rb")) == NULL){
		//userdata��������
		userdata.number = -1;
		return userdata;
	}

	// �V�[�N���w���index�Ɉړ�
	fseek(fp, sizeof(USERDATA) * index, SEEK_SET);

	// �o�b�t�@�Ƀf�[�^���ڂ�
	fread(&userdata, sizeof(USERDATA), 1, fp);

	// �t�@�C���N���[�Y
	fclose(fp);

	return userdata;
}


// �t�@�C������ԍ��i�v���C�}���L�[�j���w�肵��USERDATA���擾�i���s����number = -1)
USERDATA DATA::GetUserDataNumber(int number)
{
	// �t�@�C���|�C���^
	FILE *fp;
	// USERDATA�\����
	USERDATA userdata;
	// ���[�U�f�[�^�̓o�^����
	long userCount = GetUserFileCount();

	// �t�@�C���I�[�v��
	if ((fp = fopen(userPath, "rb")) == NULL)
	{
		// ���s�����Ƃ�
		userdata.number = -1;
		return userdata;
	}

	// �ԍ��i�v���C�}���L�[�j�̃t�@�C�����擾����
	for (long count = 1; count <= userCount; count++)
	{
		// USERDATA�\���̂�������
		userdata.number = -1;
		memset(userdata.group, '\0', sizeof(userdata.group));
		memset(userdata.name, '\0', sizeof(userdata.name));
		memset(userdata.address, '\0', sizeof(userdata.address));
		memset(userdata.tel, '\0', sizeof(userdata.tel));

		// USERDATA�\���̂��擾
		fread(&userdata, sizeof(USERDATA), 1, fp);

		// �v���C�}���L�[�ƈ�v�����Ƃ�
		if (userdata.number == number){
			fclose(fp);
			return userdata;
		}
	}

	// �t�@�C���N���[�Y
	fclose(fp);

	// �ǂ�Ƃ���v���Ȃ������Ƃ�
	userdata.number = -1;
	return userdata;
}


// userPath3�̃t�@�C�����폜����
bool DATA::DeleteSearchFile()
{
	// �y���j�z
	// �E�Z�L�����e�B�ɒ��ӂ���
	// �E�t�@�C�����폜����Ƃ��́A�t�@�C�������݂���̂��m�F���Ă��炷�邱��

	// �t�@�C���|�C���^
	FILE *fp;

	// �t�@�C�������݂��Ȃ��Ƃ��i�t�@�C���I�[�v���Ɏ��s�����Ƃ��j
	if ((fp = fopen(userPath3, "rb")) == NULL){
		return true;
	}

	// �t�@�C���N���[�Y
	fclose(fp);

	// �t�@�C�����폜����
	if (remove(userPath3)){
		return false;
	}

	return true;
}


// ���[�U�f�[�^��\������
bool DATA::ShowUserList(HWND hList)
{
	// �t�@�C���|�C���^
	FILE *fp;
	// ���[�U�f�[�^�̃t�@�C���̌������擾
	long userCount = GetUserFileCount();

	// �t�@�C���I�[�v��
	if ((fp = fopen(userPath, "rb")) == NULL){
		return false;
	}

	// �A�C�e�������ׂč폜����
	if (!(ListView_DeleteAllItems(hList))){
		return false;
	}

	// �\������
	for (long count = 0; count < userCount; count++)
	{
		// USERDATA�̃o�b�t�@
		USERDATA userdata;
		// �A�C�e���̕ϐ�
		LV_ITEM item;

		// �o�b�t�@�ɓǂݏo��
		fread(&userdata, sizeof(USERDATA), 1, fp);

		// �ԍ���ǉ�
		item.mask = LVIF_TEXT;
		char number[4];
		_itoa(userdata.number, number, 10);
		item.pszText = number;
		item.iItem = count;
		item.iSubItem = 0;
		ListView_InsertItem(hList, &item);	// �A�C�e����}������

		// �O���[�v��ǉ�
		item.pszText = userdata.group;
		item.iItem = count;
		item.iSubItem = 1;
		ListView_SetItem(hList, &item);	// �A�C�e�����Z�b�g����

		// ���O��ǉ�
		item.pszText = userdata.name;
		item.iItem = count;
		item.iSubItem = 2;
		ListView_SetItem(hList, &item);	// �A�C�e�����Z�b�g����

		// �Z����ǉ�
		item.pszText = userdata.address;
		item.iItem = count;
		item.iSubItem = 3;
		ListView_SetItem(hList, &item);	// �A�C�e�����Z�b�g����

		// �d�b�ԍ���ǉ�
		item.pszText = userdata.tel;
		item.iItem = count;
		item.iSubItem = 4;
		ListView_SetItem(hList, &item);	// �A�C�e�����Z�b�g����
	}

	// �t�@�C���N���[�Y
	fclose(fp);

	return true;
}


// ���[�U�f�[�^�̌������ʂ��O���t�@�C�����Q�Ƃ��ă��X�g�ɕ\������
bool DATA::ShowUserSearchList(HWND hList)
{
	// �y���j�z
	// �EuserPath3�̃t�@�C�����e�������̃n���h���̃��X�g�R���g���[���ɕ\�����܂��B
	// �t�@�C���|�C���^
	FILE *fp;
	// ���[�U�f�[�^�̃t�@�C���̌������擾
	long userCount = GetUserSearchFileCount();

	// �t�@�C���I�[�v��
	if ((fp = fopen(userPath3, "rb")) == NULL){
		return false;
	}

	// �A�C�e�������ׂč폜����
	if (!(ListView_DeleteAllItems(hList))){
		return false;
	}

	// �\������
	for (long count = 0; count < userCount; count++)
	{
		// USERDATA�̃o�b�t�@
		USERDATA userdata;
		// �A�C�e���̕ϐ�
		LV_ITEM item;

		// �o�b�t�@�ɓǂݏo��
		fread(&userdata, sizeof(USERDATA), 1, fp);

		// �ԍ���ǉ�
		item.mask = LVIF_TEXT;
		char number[4];
		_itoa(userdata.number, number, 10);
		item.pszText = number;
		item.iItem = count;
		item.iSubItem = 0;
		ListView_InsertItem(hList, &item);	// �A�C�e����}������

		// �O���[�v��ǉ�
		item.pszText = userdata.group;
		item.iItem = count;
		item.iSubItem = 1;
		ListView_SetItem(hList, &item);	// �A�C�e�����Z�b�g����

		// ���O��ǉ�
		item.pszText = userdata.name;
		item.iItem = count;
		item.iSubItem = 2;
		ListView_SetItem(hList, &item);	// �A�C�e�����Z�b�g����

		// �Z����ǉ�
		item.pszText = userdata.address;
		item.iItem = count;
		item.iSubItem = 3;
		ListView_SetItem(hList, &item);	// �A�C�e�����Z�b�g����

		// �d�b�ԍ���ǉ�
		item.pszText = userdata.tel;
		item.iItem = count;
		item.iSubItem = 4;
		ListView_SetItem(hList, &item);	// �A�C�e�����Z�b�g����
	}

	// �t�@�C���N���[�Y
	fclose(fp);

	return true;
}


// ���[�U�f�[�^�̃t�@�C���T�C�Y���擾����
size_t DATA::GetUserFileSize()
{
	// �t�@�C���|�C���^
	FILE *fp;

	// �t�@�C���I�[�v��
	if ((fp = fopen(userPath, "rb")) == NULL){
		// ���s�����Ƃ�
		return 0;
	}

	// �V�[�N���ړ�
	fseek(fp, 0, SEEK_END);

	// �t�@�C���̃T�C�Y���v�Z
	size_t fileSize = ftell(fp);

	// �t�@�C���N���[�Y
	fclose(fp);

	return fileSize;
}


// ���[�U�f�[�^�t�@�C���̌������擾����
long DATA::GetUserFileCount()
{
	return GetUserFileSize() / sizeof(USERDATA);
}


// �ԍ��i�v���C�}���L�[�j����C���f�b�N�X���擾�i���index = 0�j�i���s����index = -1�j
long DATA::GetUserFileIndex(long number)
{
	// �t�@�C���|�C���^
	FILE *fp;
	// USERDATA�\����
	USERDATA userdata;
	// �o�^����
	long userCount = GetUserFileCount();

	// �t�@�C���I�[�v��
	if ((fp = fopen(userPath, "rb")) == NULL){
		return -1;
	}

	// ��������
	for (long index = 0; index < userCount; index++)
	{
		// USERDATA�\���̂�������
		userdata.number = -1;
		memset(userdata.group, '\0', sizeof(userdata.group));
		memset(userdata.name, '\0', sizeof(userdata.name));
		memset(userdata.address, '\0', sizeof(userdata.address));
		memset(userdata.tel, '\0', sizeof(userdata.tel));

		// USERDATA�\���̂��擾
		fread(&userdata, sizeof(USERDATA), 1, fp);

		// �ԍ��ƈ�v�����Ƃ�
		if (userdata.number == number){
			fclose(fp);
			return index;
		}
	}

	// �t�@�C���N���[�Y
	fclose(fp);

	return -1;
}


// ���[�U�f�[�^�̃t�@�C���T�C�Y���擾����
size_t DATA::GetUserSearchFileSize()
{
	// �t�@�C���|�C���^
	FILE *fp;

	// �t�@�C���I�[�v��
	if ((fp = fopen(userPath3, "rb")) == NULL){
		// ���s�����Ƃ�
		return 0;
	}

	// �V�[�N���ړ�
	fseek(fp, 0, SEEK_END);

	// �t�@�C���̃T�C�Y���v�Z
	size_t fileSize = ftell(fp);

	// �t�@�C���N���[�Y
	fclose(fp);

	return fileSize;
}


// ���[�U�f�[�^�̌����p�t�@�C�����猏�����擾����
long DATA::GetUserSearchFileCount()
{
	return GetUserSearchFileSize() / sizeof(USERDATA);
}


// �f�[�^��ǉ�����
bool DATA::UserAdd(
	char* group,
	char* name,
	char* address,
	char* tel)
{
	// ��������\���̂Ɉڂ�
	USERDATA data;						// �\����
	if ((data.number = MakeNumber()) == -1){	// �ԍ���ݒ�
		return false;
	}
	strcpy(data.group, group);		// �O���[�v�����R�s�[
	strcpy(data.name, name);		// ���O���R�s�[
	strcpy(data.address, address);	// �Z�����R�s�[
	strcpy(data.tel, tel);			// �d�b�ԍ����R�s�[

	// �t�@�C���|�C���^
	FILE *fp;

	// �t�@�C���I�[�v��
	if ((fp = fopen(userPath, "ab")) == NULL){
		return false;
	}

	// �t�@�C������������
	fwrite(&data, sizeof(USERDATA), 1, fp);

	// �t�@�C���N���[�Y
	fclose(fp);

	return true;
}

// ���[�U�f�[�^��ҏW����i�����̍\���̂̔ԍ��i�v���C�}���L�[�j�͈�ӂł���K�v������܂��j
bool DATA::UserEdit(USERDATA userdata)
{
	// �y���j�z
	// �E���̃��\�b�h�ɂ̓o�O������܂��B
	// �E�t�@�C����ab�ŊJ�����Ƃ��́A�V�[�N�͖����ɌŒ肳��
	//   fseek�ňړ����邱�Ƃ͂ł��Ȃ��悤�ł��B

	// �t�@�C���|�C���^
	FILE *fp, *fp2;
	// �C���f�b�N�X���擾
	long index = GetUserFileIndex(userdata.number);
	// �o�^�������擾
	long userCount = GetUserFileCount();

	// �C���f�b�N�X�̎擾�Ɏ��s�����Ƃ�
	if (index == -1){
		return false;
	}

	// �o�^�����̎擾�Ɏ��s�����Ƃ�
	if (userCount == -1){
		return false;
	}

	// �t�@�C���I�[�v��
	if ((fp = fopen(userPath, "rb")) == NULL){
		return false;
	}

	// ���[�U�f�[�^�̃R�s�[���쐬�t�@�C�����쐬
	if ((fp2 = fopen(userPath2, "wb")) == NULL){
		fclose(fp);
		return false;
	}

	// ���[�U�t�@�C�����R�s�[��ɏ������ށiindex�̂Ƃ��͈������������ށj
	for (long index2 = 0; index2 < userCount; index2++)
	{
		// �ҏW����t�@�C���̂Ƃ�
		if (index2 == index)
		{
			// �ҏW���USERDATA�\���̂���������
			fwrite(&userdata, sizeof(USERDATA), 1, fp2);

			// ���t�@�C���̃V�[�N���ړ�����
			fseek(fp, sizeof(USERDATA), SEEK_CUR);
		}
		// �ҏW���Ȃ��t�@�C���̂Ƃ�
		else
		{
			// USERDATA�\���̂̃o�b�t�@
			USERDATA userdata_buf;

			// ���t�@�C�����o�b�t�@�Ɉڂ�
			fread(&userdata_buf, sizeof(USERDATA), 1, fp);

			// �R�s�[��̃t�@�C���ɏ�������
			fwrite(&userdata_buf, sizeof(USERDATA), 1, fp2);
		}
	}

	// �t�@�C���N���[�Y
	fclose(fp);
	fclose(fp2);

	// userPath�̃t�@�C�����폜
	if (remove(userPath)){
		return false;
	}

	// userPath2�̃t�@�C������userPath�ɕύX
	if (rename(userPath2, userPath)){
		return false;
	}

	return true;
}


// ���[�U�f�[�^����������i�����͌����L�[�j
bool DATA::UserSearch(char* group, char* name, char* address, char* tel)
{
	// �y���j�z
	// �E�����̌����L�[�̃t�@�C����userPath3�ɊO���t�@�C���Ƃ��ď����o��
	// �EShowUserSearchList�֐��Ń��X�g�R���g���[���Ɍ������ʂ�\������
	// �E�������ʗp�̊O���t�@�C���̎g�p���I�������DeleteSearchFile���\�b�h�ō폜����

	// �t�@�C���|�C���^
	FILE *fp, *fp2;
	// �t�@�C���̌������擾
	long userCount = GetUserFileCount();
	
	// �����t���b�O�i�����L�[�����͂���Ă��鍀�ڂɃt���b�O�𗧂Ă�j
	bool groupFlag = true;		// �O���[�v��
	bool nameFlag = true;		// ���O
	bool addressFlag = true;	// �Z��
	bool telFlag = true;		// �d�b�ԍ�
	
	// userPath3�̃t�@�C�����폜����
	if (!DeleteSearchFile()){
		return false;
	}

	// �����L�[�̃t���b�O�𗧂Ă�
	if (!strcmp(group, "")){	// �O���[�v�������͂���Ă��Ȃ��Ƃ�
		groupFlag = false;
	}
	if (!strcmp(name, "")){		// ���O�����͂���Ă��Ȃ��Ƃ�
		nameFlag = false;
	}
	if (!strcmp(address, "")){	// �Z�������͂���Ă��Ȃ��Ƃ�
		addressFlag = false;
	}
	if (!strcmp(tel, "")){		// �d�b�ԍ������͂���Ă��Ȃ��Ƃ�
		telFlag = false;
	}

	// �t�@�C���I�[�v���iuserPath�j
	if ((fp = fopen(userPath, "rb")) == NULL){
		return false;
	}

	// userPath3�̃t�@�C���쐬�i�t�@�C���I�[�v���j
	if ((fp2 = fopen(userPath3, "wb")) == NULL){
		fclose(fp);
		return false;
	}

	// userPath3�ɊY�����ڂ���������
	for (long count = 0; count < userCount; count++)
	{
		// USERDATA�\���̂̃o�b�t�@
		USERDATA userdata;

		// �o�b�t�@�ɓǂݏo��
		fread(&userdata, sizeof(USERDATA), 1, fp);

		// �����L�[�ƈ�v�����Ƃ�
		if (((strstr(userdata.group, group) != NULL) || !groupFlag)
			&& ((strstr(userdata.name, name) != NULL) || !nameFlag)
			&& ((strstr(userdata.address, address) != NULL) || !addressFlag)
			&& ((strstr(userdata.tel, tel) != NULL) || !telFlag))
		{
			// �����p�t�@�C���ɏ�������
			fwrite(&userdata, sizeof(USERDATA), 1, fp2);
		}
	}

	// �t�@�C���N���[�Y
	fclose(fp);
	fclose(fp2);

	return true;
}


// ���[�U�f�[�^���폜����i�����̓��X�g�R���g���[���̐擪����̔ԍ��j
bool DATA::UserDelete(long number)
{
	// �y���j�z
	// �EuserPath�̓��e��sizeof(DATA)�o�C�g����userPath2�ɏ�������
	// �EuserPath�̃t�@�C�����폜����
	// �EuserPath2�̃t�@�C������userPath�ɕύX����

	// userPath�̌������擾����
	long userCount = GetUserFileCount();

	// �t�@�C���|�C���^
	FILE *fp, *fp2;

	// �t�@�C���I�[�v��
	if ((fp = fopen(userPath, "rb")) == NULL){
		return false;
	}

	// �t�@�C���I�[�v��
	if ((fp2 = fopen(userPath2, "ab")) == NULL){
		fclose(fp);
		return false;
	}

	// size(DATA) �o�C�g���ǂݏo��
	for (long count = 0; count < userCount; count++)
	{
		// USERDATA�\����
		USERDATA userdata;

		// userPath��sizeof(DATA)������userdata�ɃR�s�[
		fread(&userdata, sizeof(USERDATA), 1, fp);

		// �폜����ԍ��ł͂Ȃ��Ƃ�
		if (count != number)
		{
			// userPath2�ɃR�s�[
			fwrite(&userdata, sizeof(USERDATA), 1, fp2);
		}
	}

	// �t�@�C���N���[�Y
	fclose(fp);
	fclose(fp2);

	// userPath�̃t�@�C�����폜
	if (remove(userPath)){
		return false;
	}

	// userPath2�̃t�@�C������userPath�ɕύX
	if (rename(userPath2, userPath)){
		return false;
	}
	
	return true;
}