
// ユーザデータクラスのソースファイル

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "resource.h"
#include "UserDataClass.h"

// ↓各自書き換える
// ユーザデータ保存パス
char* userPath = "C:\\";
// ユーザデータのコピー先の保存パス
char* userPath2 = "C:\\";
// ユーザデータの検索結果の保存パス
char* userPath3 = "C:\\";
// ↑各自書き換える

// コンストラクタ
DATA::DATA()
{

}

// デストラクタ
DATA::~DATA()
{

}


// 自動で番号を作成（エラーは-1を返却）
long DATA::MakeNumber()
{
	// ファイルポインタ
	FILE *fp;

	// 番号（プライマリキー）の最大値
	long max = 1;

	// 返却する番号
	long primaryNumber = 1;

	// データの個数を求める
	long dataCount = GetUserFileCount();

	// ファイルオープン
	if ((fp = fopen(userPath, "rb")) == NULL){
		return -1;
	}

	// 登録件数が0のとき
	if (dataCount == 0)
	{
		// ファイルクローズ
		fclose(fp);
		// 番号は1を返却
		return 1;
	}

	// ユーザデータの番号（プライマリキー）の最大値を取得する
	for (long count = 1; count <= dataCount; count++)
	{
		// USDRDATA構造体
		USERDATA userdata;

		// sizeof(DATA)分のメモリを読み出す
		fread(&userdata, sizeof(USERDATA), 1, fp);

		// 最大値と比較する
		if (max < userdata.number){
			max = userdata.number;
		}
	}

	// ユーザデータの番号（プライマリキー）が1~maxまで
	// すべて埋まっていたとき
	if (dataCount == max)
	{
		// ファイルクローズ
		fclose(fp);
		// (max + 1)を返却
		return max + 1;
	}

	// シークを先頭に戻す
	fseek(fp, 0, SEEK_SET);

	// 重複しない番号（プライマリキー）を取得する
	// 候補の番号を動かす（候補は1~max）
	for (long count = 1; count <= max; count++)
	{
		// 登録してある番号（プライマリキー）と重複しないか確認する
		for (long count2 = 1; count <= dataCount; count2++)
		{
			// USDRDATA構造体
			USERDATA userdata;

			// count番目のからsizeof(DATA)分のメモリを読み出す
			fread(&userdata, sizeof(USERDATA), 1, fp);

			// 候補の番号が存在したとき
			if (count == userdata.number){
				goto CORRECT;
			}

			// 候補の番号が最後まで存在しなかったとき
			if (count2 == dataCount){
				primaryNumber = count;
				goto END;
			}
		}

		// 候補の番号が存在したとき
		CORRECT:

		// シークを先頭に戻す
		fseek(fp, 0, SEEK_SET);
	}

	// 候補の番号が最後まで存在しなかったとき
	END:

	// ファイルクローズ
	fclose(fp);

	return primaryNumber;
}


// ファイルから番号（上から）を指定してUSERDATAを取得（失敗時はnumber = -1）（一番上はindex = 0）
USERDATA DATA::GetUserDataIndex(int index)
{
	// ファイルポインタ
	FILE *fp;

	// 返却するUSERDATA構造体
	USERDATA userdata;

	// ファイルオープン
	if ((fp = fopen(userPath, "rb")) == NULL){
		//userdataを初期化
		userdata.number = -1;
		return userdata;
	}

	// シークを指定のindexに移動
	fseek(fp, sizeof(USERDATA) * index, SEEK_SET);

	// バッファにデータを移す
	fread(&userdata, sizeof(USERDATA), 1, fp);

	// ファイルクローズ
	fclose(fp);

	return userdata;
}


// ファイルから番号（プライマリキー）を指定してUSERDATAを取得（失敗時はnumber = -1)
USERDATA DATA::GetUserDataNumber(int number)
{
	// ファイルポインタ
	FILE *fp;
	// USERDATA構造体
	USERDATA userdata;
	// ユーザデータの登録件数
	long userCount = GetUserFileCount();

	// ファイルオープン
	if ((fp = fopen(userPath, "rb")) == NULL)
	{
		// 失敗したとき
		userdata.number = -1;
		return userdata;
	}

	// 番号（プライマリキー）のファイルを取得する
	for (long count = 1; count <= userCount; count++)
	{
		// USERDATA構造体を初期化
		userdata.number = -1;
		memset(userdata.group, '\0', sizeof(userdata.group));
		memset(userdata.name, '\0', sizeof(userdata.name));
		memset(userdata.address, '\0', sizeof(userdata.address));
		memset(userdata.tel, '\0', sizeof(userdata.tel));

		// USERDATA構造体を取得
		fread(&userdata, sizeof(USERDATA), 1, fp);

		// プライマリキーと一致したとき
		if (userdata.number == number){
			fclose(fp);
			return userdata;
		}
	}

	// ファイルクローズ
	fclose(fp);

	// どれとも一致しなかったとき
	userdata.number = -1;
	return userdata;
}


// userPath3のファイルを削除する
bool DATA::DeleteSearchFile()
{
	// 【方針】
	// ・セキュリティに注意する
	// ・ファイルを削除するときは、ファイルが存在するのを確認してからすること

	// ファイルポインタ
	FILE *fp;

	// ファイルが存在しないとき（ファイルオープンに失敗したとき）
	if ((fp = fopen(userPath3, "rb")) == NULL){
		return true;
	}

	// ファイルクローズ
	fclose(fp);

	// ファイルを削除する
	if (remove(userPath3)){
		return false;
	}

	return true;
}


// ユーザデータを表示する
bool DATA::ShowUserList(HWND hList)
{
	// ファイルポインタ
	FILE *fp;
	// ユーザデータのファイルの件数を取得
	long userCount = GetUserFileCount();

	// ファイルオープン
	if ((fp = fopen(userPath, "rb")) == NULL){
		return false;
	}

	// アイテムをすべて削除する
	if (!(ListView_DeleteAllItems(hList))){
		return false;
	}

	// 表示する
	for (long count = 0; count < userCount; count++)
	{
		// USERDATAのバッファ
		USERDATA userdata;
		// アイテムの変数
		LV_ITEM item;

		// バッファに読み出す
		fread(&userdata, sizeof(USERDATA), 1, fp);

		// 番号を追加
		item.mask = LVIF_TEXT;
		char number[4];
		_itoa(userdata.number, number, 10);
		item.pszText = number;
		item.iItem = count;
		item.iSubItem = 0;
		ListView_InsertItem(hList, &item);	// アイテムを挿入する

		// グループを追加
		item.pszText = userdata.group;
		item.iItem = count;
		item.iSubItem = 1;
		ListView_SetItem(hList, &item);	// アイテムをセットする

		// 名前を追加
		item.pszText = userdata.name;
		item.iItem = count;
		item.iSubItem = 2;
		ListView_SetItem(hList, &item);	// アイテムをセットする

		// 住所を追加
		item.pszText = userdata.address;
		item.iItem = count;
		item.iSubItem = 3;
		ListView_SetItem(hList, &item);	// アイテムをセットする

		// 電話番号を追加
		item.pszText = userdata.tel;
		item.iItem = count;
		item.iSubItem = 4;
		ListView_SetItem(hList, &item);	// アイテムをセットする
	}

	// ファイルクローズ
	fclose(fp);

	return true;
}


// ユーザデータの検索結果を外部ファイルを参照してリストに表示する
bool DATA::ShowUserSearchList(HWND hList)
{
	// 【方針】
	// ・userPath3のファイル内容を引数のハンドルのリストコントロールに表示します。
	// ファイルポインタ
	FILE *fp;
	// ユーザデータのファイルの件数を取得
	long userCount = GetUserSearchFileCount();

	// ファイルオープン
	if ((fp = fopen(userPath3, "rb")) == NULL){
		return false;
	}

	// アイテムをすべて削除する
	if (!(ListView_DeleteAllItems(hList))){
		return false;
	}

	// 表示する
	for (long count = 0; count < userCount; count++)
	{
		// USERDATAのバッファ
		USERDATA userdata;
		// アイテムの変数
		LV_ITEM item;

		// バッファに読み出す
		fread(&userdata, sizeof(USERDATA), 1, fp);

		// 番号を追加
		item.mask = LVIF_TEXT;
		char number[4];
		_itoa(userdata.number, number, 10);
		item.pszText = number;
		item.iItem = count;
		item.iSubItem = 0;
		ListView_InsertItem(hList, &item);	// アイテムを挿入する

		// グループを追加
		item.pszText = userdata.group;
		item.iItem = count;
		item.iSubItem = 1;
		ListView_SetItem(hList, &item);	// アイテムをセットする

		// 名前を追加
		item.pszText = userdata.name;
		item.iItem = count;
		item.iSubItem = 2;
		ListView_SetItem(hList, &item);	// アイテムをセットする

		// 住所を追加
		item.pszText = userdata.address;
		item.iItem = count;
		item.iSubItem = 3;
		ListView_SetItem(hList, &item);	// アイテムをセットする

		// 電話番号を追加
		item.pszText = userdata.tel;
		item.iItem = count;
		item.iSubItem = 4;
		ListView_SetItem(hList, &item);	// アイテムをセットする
	}

	// ファイルクローズ
	fclose(fp);

	return true;
}


// ユーザデータのファイルサイズを取得する
size_t DATA::GetUserFileSize()
{
	// ファイルポインタ
	FILE *fp;

	// ファイルオープン
	if ((fp = fopen(userPath, "rb")) == NULL){
		// 失敗したとき
		return 0;
	}

	// シークを移動
	fseek(fp, 0, SEEK_END);

	// ファイルのサイズを計算
	size_t fileSize = ftell(fp);

	// ファイルクローズ
	fclose(fp);

	return fileSize;
}


// ユーザデータファイルの件数を取得する
long DATA::GetUserFileCount()
{
	return GetUserFileSize() / sizeof(USERDATA);
}


// 番号（プライマリキー）からインデックスを取得（上はindex = 0）（失敗時はindex = -1）
long DATA::GetUserFileIndex(long number)
{
	// ファイルポインタ
	FILE *fp;
	// USERDATA構造体
	USERDATA userdata;
	// 登録件数
	long userCount = GetUserFileCount();

	// ファイルオープン
	if ((fp = fopen(userPath, "rb")) == NULL){
		return -1;
	}

	// 検索する
	for (long index = 0; index < userCount; index++)
	{
		// USERDATA構造体を初期化
		userdata.number = -1;
		memset(userdata.group, '\0', sizeof(userdata.group));
		memset(userdata.name, '\0', sizeof(userdata.name));
		memset(userdata.address, '\0', sizeof(userdata.address));
		memset(userdata.tel, '\0', sizeof(userdata.tel));

		// USERDATA構造体を取得
		fread(&userdata, sizeof(USERDATA), 1, fp);

		// 番号と一致したとき
		if (userdata.number == number){
			fclose(fp);
			return index;
		}
	}

	// ファイルクローズ
	fclose(fp);

	return -1;
}


// ユーザデータのファイルサイズを取得する
size_t DATA::GetUserSearchFileSize()
{
	// ファイルポインタ
	FILE *fp;

	// ファイルオープン
	if ((fp = fopen(userPath3, "rb")) == NULL){
		// 失敗したとき
		return 0;
	}

	// シークを移動
	fseek(fp, 0, SEEK_END);

	// ファイルのサイズを計算
	size_t fileSize = ftell(fp);

	// ファイルクローズ
	fclose(fp);

	return fileSize;
}


// ユーザデータの検索用ファイルから件数を取得する
long DATA::GetUserSearchFileCount()
{
	return GetUserSearchFileSize() / sizeof(USERDATA);
}


// データを追加する
bool DATA::UserAdd(
	char* group,
	char* name,
	char* address,
	char* tel)
{
	// 文字列を構造体に移す
	USERDATA data;						// 構造体
	if ((data.number = MakeNumber()) == -1){	// 番号を設定
		return false;
	}
	strcpy(data.group, group);		// グループ名をコピー
	strcpy(data.name, name);		// 名前をコピー
	strcpy(data.address, address);	// 住所をコピー
	strcpy(data.tel, tel);			// 電話番号をコピー

	// ファイルポインタ
	FILE *fp;

	// ファイルオープン
	if ((fp = fopen(userPath, "ab")) == NULL){
		return false;
	}

	// ファイルを書き込む
	fwrite(&data, sizeof(USERDATA), 1, fp);

	// ファイルクローズ
	fclose(fp);

	return true;
}

// ユーザデータを編集する（引数の構造体の番号（プライマリキー）は一意である必要があります）
bool DATA::UserEdit(USERDATA userdata)
{
	// 【方針】
	// ・このメソッドにはバグがあります。
	// ・ファイルをabで開いたときは、シークは末尾に固定され
	//   fseekで移動することはできないようです。

	// ファイルポインタ
	FILE *fp, *fp2;
	// インデックスを取得
	long index = GetUserFileIndex(userdata.number);
	// 登録件数を取得
	long userCount = GetUserFileCount();

	// インデックスの取得に失敗したとき
	if (index == -1){
		return false;
	}

	// 登録件数の取得に失敗したとき
	if (userCount == -1){
		return false;
	}

	// ファイルオープン
	if ((fp = fopen(userPath, "rb")) == NULL){
		return false;
	}

	// ユーザデータのコピーを作成ファイルを作成
	if ((fp2 = fopen(userPath2, "wb")) == NULL){
		fclose(fp);
		return false;
	}

	// ユーザファイルをコピー先に書き込む（indexのときは引数を書き込む）
	for (long index2 = 0; index2 < userCount; index2++)
	{
		// 編集するファイルのとき
		if (index2 == index)
		{
			// 編集後のUSERDATA構造体を書き込む
			fwrite(&userdata, sizeof(USERDATA), 1, fp2);

			// 元ファイルのシークを移動する
			fseek(fp, sizeof(USERDATA), SEEK_CUR);
		}
		// 編集しないファイルのとき
		else
		{
			// USERDATA構造体のバッファ
			USERDATA userdata_buf;

			// 元ファイルよりバッファに移す
			fread(&userdata_buf, sizeof(USERDATA), 1, fp);

			// コピー先のファイルに書き込む
			fwrite(&userdata_buf, sizeof(USERDATA), 1, fp2);
		}
	}

	// ファイルクローズ
	fclose(fp);
	fclose(fp2);

	// userPathのファイルを削除
	if (remove(userPath)){
		return false;
	}

	// userPath2のファイル名をuserPathに変更
	if (rename(userPath2, userPath)){
		return false;
	}

	return true;
}


// ユーザデータを検索する（引数は検索キー）
bool DATA::UserSearch(char* group, char* name, char* address, char* tel)
{
	// 【方針】
	// ・引数の検索キーのファイルをuserPath3に外部ファイルとして書き出す
	// ・ShowUserSearchList関数でリストコントロールに検索結果を表示する
	// ・検索結果用の外部ファイルの使用が終わったらDeleteSearchFileメソッドで削除する

	// ファイルポインタ
	FILE *fp, *fp2;
	// ファイルの件数を取得
	long userCount = GetUserFileCount();
	
	// 検索フラッグ（検索キーが入力されている項目にフラッグを立てる）
	bool groupFlag = true;		// グループ名
	bool nameFlag = true;		// 名前
	bool addressFlag = true;	// 住所
	bool telFlag = true;		// 電話番号
	
	// userPath3のファイルを削除する
	if (!DeleteSearchFile()){
		return false;
	}

	// 検索キーのフラッグを立てる
	if (!strcmp(group, "")){	// グループ名が入力されていないとき
		groupFlag = false;
	}
	if (!strcmp(name, "")){		// 名前が入力されていないとき
		nameFlag = false;
	}
	if (!strcmp(address, "")){	// 住所が入力されていないとき
		addressFlag = false;
	}
	if (!strcmp(tel, "")){		// 電話番号が入力されていないとき
		telFlag = false;
	}

	// ファイルオープン（userPath）
	if ((fp = fopen(userPath, "rb")) == NULL){
		return false;
	}

	// userPath3のファイル作成（ファイルオープン）
	if ((fp2 = fopen(userPath3, "wb")) == NULL){
		fclose(fp);
		return false;
	}

	// userPath3に該当項目を書き込む
	for (long count = 0; count < userCount; count++)
	{
		// USERDATA構造体のバッファ
		USERDATA userdata;

		// バッファに読み出す
		fread(&userdata, sizeof(USERDATA), 1, fp);

		// 検索キーと一致したとき
		if (((strstr(userdata.group, group) != NULL) || !groupFlag)
			&& ((strstr(userdata.name, name) != NULL) || !nameFlag)
			&& ((strstr(userdata.address, address) != NULL) || !addressFlag)
			&& ((strstr(userdata.tel, tel) != NULL) || !telFlag))
		{
			// 検索用ファイルに書き込む
			fwrite(&userdata, sizeof(USERDATA), 1, fp2);
		}
	}

	// ファイルクローズ
	fclose(fp);
	fclose(fp2);

	return true;
}


// ユーザデータを削除する（引数はリストコントロールの先頭からの番号）
bool DATA::UserDelete(long number)
{
	// 【方針】
	// ・userPathの内容をsizeof(DATA)バイトずつuserPath2に書き込む
	// ・userPathのファイルを削除する
	// ・userPath2のファイル名をuserPathに変更する

	// userPathの件数を取得する
	long userCount = GetUserFileCount();

	// ファイルポインタ
	FILE *fp, *fp2;

	// ファイルオープン
	if ((fp = fopen(userPath, "rb")) == NULL){
		return false;
	}

	// ファイルオープン
	if ((fp2 = fopen(userPath2, "ab")) == NULL){
		fclose(fp);
		return false;
	}

	// size(DATA) バイトずつ読み出す
	for (long count = 0; count < userCount; count++)
	{
		// USERDATA構造体
		USERDATA userdata;

		// userPathのsizeof(DATA)分ををuserdataにコピー
		fread(&userdata, sizeof(USERDATA), 1, fp);

		// 削除する番号ではないとき
		if (count != number)
		{
			// userPath2にコピー
			fwrite(&userdata, sizeof(USERDATA), 1, fp2);
		}
	}

	// ファイルクローズ
	fclose(fp);
	fclose(fp2);

	// userPathのファイルを削除
	if (remove(userPath)){
		return false;
	}

	// userPath2のファイル名をuserPathに変更
	if (rename(userPath2, userPath)){
		return false;
	}
	
	return true;
}