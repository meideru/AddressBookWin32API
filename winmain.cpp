
// 住所録
// モードレスダイアログボックスを作成

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include <commctrl.h>
#include "resource.h"
#include "UserDataClass.h"

// ------------------- プロトタイプ宣言 -------------------- //

// メインとなるダイアログプロシージャ（モードレスダイアログボックス）
INT_PTR CALLBACK MyDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp);

// 編集フォームのダイアログプロシージャ（モーダルダイアログボックス）
INT_PTR CALLBACK MyDlgProc2(HWND hDlg2, UINT msg, WPARAM wp, LPARAM lp);

// ファイルが存在するかどうかの確認
bool CheckFiles();
// 実際にファイルが存在するかどうか確認
bool DoCheckFiles();

// -------- MyDlgProc -------- //

// ユーザリストを初期化する
bool InitUserList(HWND hDlg);
// 実際にユーザリストを初期化する
bool DoInitUserList(HWND hDlg);

// リストコントロールを設定する
bool InitListCtrl(HWND hDlg);
// 実際にリストコントロールを設定する
bool DoInitListCtrl(HWND hDlg);

// 登録ボタンが押されたときの処理
void PushAddButton(HWND hDlg);

// 編集ボタンが押されたときの処理
void PushEditButton(HWND hDlg);

// 検索ボタンが押されたときの処理
void PushSearchButton(HWND hDlg);

// 削除ボタンが押されたときの処理
void PushDeleteButton(HWND hDlg);

// リセットボタンが押されたときの処理
void PushResetButton(HWND hDlg);
// 実際にリセットを行う
bool DoResetText(HWND hDlg);

// ユーザリストを更新するとき
void UpdateUserList(HWND hDlg);
// 実際にユーザリストを更新する
bool DoUpdateUserList(HWND hDlg);

// -------- MyDlgProc2 -------- //

// エディットボックスを指定の文字列で初期化する
bool InitEditBox(HWND hDlg2);
// 実際にエディットボックスを指定の文字列で初期化する
bool DoInitEditBox(HWND hDlg2);

// 確定ボタンが押されたときの処理
void PushOkButton(HWND hDlg2);
// 実際に編集を行うときの処理
bool DoEditUserdata(HWND hDlg2);


// winmain関数
int WINAPI WinMain(HINSTANCE hCurInst, HINSTANCE hPrevInst,
	LPSTR lpsCmdLine, int nCmdShow)
{
	// メッセージに関する変数
	MSG msg;
	BOOL bRet;

	// ウィンドウハンドル
	HWND hDlg;

	// モードレスダイアログボックスを作成
	hDlg = CreateDialog(
		hCurInst,						// インスタンスハンドル
		MAKEINTRESOURCE(IDD_DIALOG1),	// リソース名
		NULL,							// 親ハンドル
		(DLGPROC)MyDlgProc);			// プロシージャ名
	
	// ダイアログボックスを表示
	ShowWindow(hDlg, nCmdShow);

	// メッセージ処理
	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		// メッセージの取得に失敗したとき
		if (bRet == -1){
			break;
		}
		else{	// メッセージの取得に成功したとき
			// ダイアログ宛のメッセージのとき
			if (!IsDialogMessage(hDlg, &msg)){
				TranslateMessage(&msg);		// メッセージを翻訳
				DispatchMessage(&msg);		// メッセージをプロシージャに転送
			}
		}
	}
}


// メインとなるダイアログプロシージャ（モードレスダイアログボックス）
INT_PTR CALLBACK MyDlgProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
	// メッセージを処理
	switch (msg)
	{

	// ダイアログが呼び出されるとき
	case WM_INITDIALOG:
		
		// ファイルが存在するか確認
		if (!CheckFiles()){
			DestroyWindow(hDlg);	// ダイアログを閉じる
			PostQuitMessage(0);		// メッセージキューに0を送る
		}

		// ユーザリストを初期化
		if (!InitUserList(hDlg))
		{
			DestroyWindow(hDlg);	// ダイアログを閉じる
			PostQuitMessage(0);		// メッセージキューに0を送る
		}

		// リストコントロールを設定
		if (!InitListCtrl(hDlg))
		{
			DestroyWindow(hDlg);	// ダイアログを閉じる
			PostQuitMessage(0);		// メッセージキューに0を送る
		}

		// ユーザリストを更新する
		UpdateUserList(hDlg);

		return TRUE;

	// ボタンが押されたとき
	case WM_COMMAND:

		// コマンドを取得
		switch (LOWORD(wp))
		{

		// グループ名が入力された
		case IDC_EDIT_GROUP:
			return TRUE;
		
		// 名前が入力された
		case IDC_EDIT_NAME:
			return TRUE;

		// 住所が入力された
		case IDC_EDIT_ADDRESS:
			return TRUE;

		// 電話番号が入力された
		case IDC_EDIT_TEL:
			return TRUE;

		// 名簿が選択された
		case IDC_LIST_NAMELIST:
			return TRUE;

		// 登録ボタンが押された
		case IDC_BUTTON_ADD:
			// 登録を行う
			PushAddButton(hDlg);
			return TRUE;

		// 編集ボタンが押された
		case IDC_BUTTON_EDIT:
			// 編集ボタンが押されたとき
			PushEditButton(hDlg);
			return TRUE;

		// 検索ボタンが押された
		case IDC_BUTTON_SEARCH:
			// 検索ボタンが押されたとき
			PushSearchButton(hDlg);
			return TRUE;

		// 削除ボタンが押された
		case IDC_BUTTON_DELETE:
			// 登録を行う
			PushDeleteButton(hDlg);
			return TRUE;

		// リセットボタンが押された
		case IDC_BUTTON_RESET:
			// リセットボタンが押されたとき
			PushResetButton(hDlg);
			return TRUE;

		// メニューの終了が押された
		case ID_END:
			DestroyWindow(hDlg);	// ダイアログを閉じる
			PostQuitMessage(0);		// メッセージキューに0を送る
			return TRUE;

		// 想定外の処理
		default:
			return TRUE;
		}

	// 閉じるボタンが押された
	case WM_CLOSE:
		DestroyWindow(hDlg);	// ダイアログを閉じる
		PostQuitMessage(0);		// メッセージキューに0を送る
		return TRUE;

	// デフォルトプロシージャ
	default:
		return FALSE;
	}

	return FALSE;
}


// 編集フォームのダイアログプロシージャ（モーダルダイアログボックス）
INT_PTR CALLBACK MyDlgProc2(HWND hDlg2, UINT msg, WPARAM wp, LPARAM lp)
{
	// メッセージを処理
	switch (msg)
	{

	// ダイアログが呼び出されるとき
	case WM_INITDIALOG:

		// エディットボックスを指定の文字列で初期化する
		InitEditBox(hDlg2);

		return TRUE;

	// ボタンが押されたとき
	case WM_COMMAND:

		// コマンドを取得
		switch (LOWORD(wp))
		{

		// 確定ボタンが押されたとき
		case IDOK:

			// 確定ボタンが押されたときの処理
			PushOkButton(hDlg2);

			return TRUE;

		// キャンセルボタンが押されたとき
		case IDC_BUTTON_CANCEL2:
			EndDialog(hDlg2, TRUE);
			return TRUE;

		// 想定外の処理
		default:
			return TRUE;
		}

	// 閉じるボタンが押された
	case WM_CLOSE:
		EndDialog(hDlg2, TRUE);
		return TRUE;

	// デフォルトプロシージャ
	default:
		return FALSE;
	}

	return FALSE;
}


// ファイルが存在するかどうかを確認する
bool CheckFiles()
{
	// ファイルが存在せず、かつファイルの作成に失敗
	if (!(DoCheckFiles()))
	{
		// ファイル作成失敗に関するメッセージ
		MessageBox(
			NULL,
			TEXT("ファイルの作成に失敗しました。"),
			TEXT("エラー"),
			MB_ICONINFORMATION | MB_OK);
	}

	return true;
}


// 実際にファイルが存在するかどうか確認
bool DoCheckFiles()
{
	// ファイルポインタ
	FILE *fp;

	// ユーザ名の保存パスをファイルオープン（読み込みモード）
	if ((fp = fopen(userPath, "rb")) == NULL)
	{
		// ファイルが存在しないので作成する
		if ((fp = fopen(userPath, "wb")) == NULL){
			return false;
		}

		// ファイル作成成功に関するメッセージボックス
		MessageBox(
			NULL,
			TEXT("ユーザデータが存在しないのでファイルを作成しました。"),
			TEXT("作成しました"),
			MB_ICONINFORMATION | MB_OK);
	}

	// ファイルクローズ
	fclose(fp);

	return true;
}


// ユーザリストを初期化する
bool InitUserList(HWND hDlg)
{
	// 失敗したとき
	if (!(DoInitUserList(hDlg)))
	{
		// リスト更新に失敗したときのメッセージボックス
		MessageBox(
			hDlg,
			TEXT("ユーザリストのカラムの初期化に失敗しました。"),
			TEXT("エラー"),
			MB_ICONEXCLAMATION | MB_OK);

		return false;
	}

	return true;
}

// 実際にユーザリストを初期化する
bool DoInitUserList(HWND hDlg)
{
	// リストコントロールのハンドルを取得
	HWND hList = GetDlgItem(hDlg, IDC_LIST_NAMELIST);

	// カラム
	LV_COLUMN lvcol;

	// 番号（カラム）
	lvcol.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvcol.fmt = LVCFMT_LEFT;
	lvcol.cx = 80;
	lvcol.pszText = TEXT("番号");
	ListView_InsertColumn(hList, 0, &lvcol);

	// グループ（カラム）
	lvcol.cx = 150;
	lvcol.pszText = TEXT("グループ");
	ListView_InsertColumn(hList, 1, &lvcol);

	// 名前（カラム）
	lvcol.cx = 140;
	lvcol.pszText = TEXT("名前");
	ListView_InsertColumn(hList, 2, &lvcol);

	// 住所（カラム）
	lvcol.cx = 270;
	lvcol.pszText = TEXT("住所");
	ListView_InsertColumn(hList, 3, &lvcol);

	// 電話番号（カラム）
	lvcol.cx = 170;
	lvcol.pszText = TEXT("電話番号");
	ListView_InsertColumn(hList, 4, &lvcol);

	return true;
}


// リストコントロールを設定する
bool InitListCtrl(HWND hDlg)
{
	// 失敗したとき
	if (!(DoInitListCtrl(hDlg)))
	{
		// リスト更新に失敗したときのメッセージボックス
		MessageBox(
			hDlg,
			TEXT("リストコントロールの設定に失敗しました。"),
			TEXT("エラー"),
			MB_ICONEXCLAMATION | MB_OK);

		return false;
	}

	return true;
}


// 実際にリストコントロールを設定する
bool DoInitListCtrl(HWND hDlg)
{
	// リストコントロールのハンドルを取得
	HWND hList = GetDlgItem(hDlg, IDC_LIST_NAMELIST);

	// 一行選択可能・グリッド線を表示
	ListView_SetExtendedListViewStyle(
		hList,
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return true;
}


// ユーザリストを更新するとき
void UpdateUserList(HWND hDlg)
{
	// 失敗したとき
	if (!(DoUpdateUserList(hDlg)))
	{
		// リスト更新に失敗したときのメッセージボックス
		MessageBox(
			hDlg,
			TEXT("ユーザリストの更新に失敗しました。"),
			TEXT("エラー"),
			MB_ICONEXCLAMATION | MB_OK);

		return;
	}
}

// 実際にユーザリストを更新する
bool DoUpdateUserList(HWND hDlg)
{
	// リストコントロールのハンドルを取得
	HWND hList = GetDlgItem(hDlg, IDC_LIST_NAMELIST);

	// データクラスのインスタンス
	DATA data;

	// 更新する
	if (!(data.ShowUserList(hList))){
		return false;
	}

	return true;
}


// 登録ボタンが押されたときの処理
void PushAddButton(HWND hDlg)
{
	// バッファ
	char group[256];	// グループ名
	char name[256];		// 名前
	char address[256];	// 住所
	char tel[256];		// 電話番号

	// 入力文字を取得
	GetDlgItemText(hDlg, IDC_EDIT_GROUP, group, sizeof(group));		// グループ名
	GetDlgItemText(hDlg, IDC_EDIT_NAME, name, sizeof(name));			// 名前
	GetDlgItemText(hDlg, IDC_EDIT_ADDRESS, address, sizeof(address));	// 住所
	GetDlgItemText(hDlg, IDC_EDIT_TEL, tel, sizeof(tel));				// 電話番号

	// エディットコントロールにおいてグループ名以外の空欄が１つでもあるとき
	if ((strcmp(name, "") == 0) || (strcmp(address, "") == 0) || (strcmp(tel, "") == 0))
	{
		// １つでも入力されていないときのメッセージ
		MessageBox(
			hDlg,
			TEXT("入力されていない項目があります。"),
			TEXT("エラー"),
			MB_ICONEXCLAMATION | MB_OK);

		return;
	}

	// DATAクラスのインスタンス
	DATA userdata;

	// 追加
	if (userdata.UserAdd(group, name, address, tel))
	{
		// ユーザリストを更新する
		UpdateUserList(hDlg);

		// 登録成功のメッセージボックスを表示
		MessageBox(
			hDlg,
			TEXT("登録が完了しました。"),
			TEXT("登録完了"),
			MB_ICONINFORMATION | MB_OK);

		// 入力フォームをリセットする
		PushResetButton(hDlg);
	}
	else
	{
		// ユーザリストを更新する
		UpdateUserList(hDlg);

		// 登録失敗のメッセージボックスを表示
		MessageBox(
			hDlg,
			TEXT("登録に失敗しました。"),
			TEXT("エラー"),
			MB_ICONEXCLAMATION | MB_OK);
	}
}


// 編集ボタンが押されたときの処理
void PushEditButton(HWND hDlg)
{
	// 【方針】
	// ・編集ボタンが押されるとダイアログボックスを表示する
	// ・ダイアログボックスにて編集を行う

	// 親ウィンドウのインスタンスハンドル
	HINSTANCE hInst;
	// リストコントロールのハンドル
	HWND hList;
	// リストコントロールで選択されている項目の番号
	int index;

	// リストコントロールのハンドル・親ウィンドウのウィンドウハンドルを取得
	if (((hList = GetDlgItem(hDlg, IDC_LIST_NAMELIST)) == NULL)
		|| ((hInst = (HINSTANCE)GetWindowLong(hDlg, GWL_HINSTANCE)) == NULL))
	{
		// 失敗したときのメッセージ
		MessageBox(
			hDlg,
			TEXT("初期化に失敗しました。"),
			TEXT("エラー"),
			MB_ICONEXCLAMATION | MB_OK);

		return;
	}

	// リストコントロールで選択中のアイテムを取得
	if ((index = ListView_GetNextItem(hList, -1, LVNI_ALL | LVNI_SELECTED)) == -1)
	{
		// 選択していないときのメッセージ
		MessageBox(
			hDlg,
			TEXT("編集する項目を選択してください。"),
			TEXT("エラー"),
			MB_ICONEXCLAMATION | MB_OK);
		
		return;
	}

	// 編集フォームのダイアログボックスを表示する
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hDlg, MyDlgProc2);
}


// 検索ボタンが押されたときの処理
void PushSearchButton(HWND hDlg)
{
	//DATAクラスのインスタンス
	DATA data;
	// リストコントロールのハンドル
	HWND hList;

	// ファイルの検索結果の件数
	long searchCount;
	
	// 検索キーを保存するバッファ
	char group[256];	// グループ名
	char name[256];		// 名前
	char address[256];	// 住所
	char tel[256];		// 電話番号

	// リストコントロールのハンドルを取得
	if ((hList = GetDlgItem(hDlg, IDC_LIST_NAMELIST)) == NULL)
	{
		// 検索に失敗したときのメッセージ
		MessageBox(
			hDlg,
			TEXT("検索に失敗しました。"),
			TEXT("エラー"),
			MB_ICONEXCLAMATION | MB_OK);

		return;
	}
	
	// 入力文字を取得
	GetDlgItemText(hDlg, IDC_EDIT_GROUP, group, sizeof(group));		// グループ名
	GetDlgItemText(hDlg, IDC_EDIT_NAME, name, sizeof(name));			// 名前
	GetDlgItemText(hDlg, IDC_EDIT_ADDRESS, address, sizeof(address));	// 住所
	GetDlgItemText(hDlg, IDC_EDIT_TEL, tel, sizeof(tel));				// 電話番号

	// 検索キーが１つも入力されていないとき
	if ((strcmp(group, "") == 0) && (strcmp(name, "") == 0)
		&& (strcmp(address, "") == 0) && (strcmp(tel, "") == 0))
	{
		// 検索キーが１つも入力されていないときのメッセージ
		MessageBox(
			hDlg,
			TEXT("検索キーを入力してください。"),
			TEXT("エラー"),
			MB_ICONEXCLAMATION | MB_OK);

		return;
	}

	// 検索を行う
	if (!data.UserSearch(group, name, address, tel))
	{
		// 検索に失敗したときのメッセージ
		MessageBox(
			hDlg,
			TEXT("検索に失敗しました。"),
			TEXT("エラー"),
			MB_ICONEXCLAMATION | MB_OK);

		return;
	}

	// リストコントロールに表示する
	data.ShowUserSearchList(hList);

	// 検索結果の件数を取得する
	searchCount = data.GetUserSearchFileCount();

	// 検索結果の件数をメッセージボックスで表示する
	if (searchCount == 0)
	{
		// 一致するものが見つからなかったとき
		MessageBox(
			hDlg,
			TEXT("一致するものが見つかりませんでした。"),
			TEXT("検索結果"),
			MB_ICONINFORMATION | MB_OK);
	}
	else
	{
		// 一致するものが見つかったとき
		char lpText[256];		// メッセージボックス内のテキスト
		char countText[4];		// long型をchar型に変換した件数

		// long型をchar型に変換する
		sprintf(countText, "%d", searchCount);

		// lpTextにコピーする
		strcpy(lpText, countText);				// 件数をコピー
		strcat(lpText, "件見つかりました。");	// 文字列を連結	

		// メッセージボックスを表示
		MessageBox(
			hDlg,
			lpText,
			TEXT("検索結果"),
			MB_ICONINFORMATION | MB_OK);
	}

	// userPath3のファイルを削除する
	data.DeleteSearchFile();
}


// 削除ボタンが押されたときの処理
void PushDeleteButton(HWND hDlg)
{
	// リストコントロールのハンドルを取得
	HWND hList = GetDlgItem(hDlg, IDC_LIST_NAMELIST);

	// DATAクラスのインスタンス
	DATA userdata;

	// 削除するユーザデータの番号（プライマリキー）
	long number = ListView_GetNextItem(hList, -1, LVNI_ALL | LVNI_SELECTED);

	// 削除
	if (number == -1)
	{
		// 何も選択されていないときのメッセージボックス
		MessageBox(
			hDlg,
			TEXT("削除する項目を選択してください。"),
			TEXT("エラー"),
			MB_ICONEXCLAMATION | MB_OK);
	}
	else if (userdata.UserDelete(number))
	{
		// ユーザリストを更新する
		UpdateUserList(hDlg);

		// 削除成功のメッセージボックスを表示
		MessageBox(
			hDlg,
			TEXT("削除が完了しました。"),
			TEXT("削除完了"),
			MB_ICONINFORMATION | MB_OK);
	}
	else
	{
		// ユーザリストを更新する
		UpdateUserList(hDlg);

		// 削除失敗のメッセージボックスを表示
		MessageBox(
			hDlg,
			TEXT("削除に失敗しました。"),
			TEXT("エラー"),
			MB_ICONEXCLAMATION | MB_OK);
	}
}


// リセットボタンが押されたときの処理
void PushResetButton(HWND hDlg)
{
	// リセットに失敗したとき
	if (!DoResetText(hDlg))
	{
		// 削除失敗のメッセージボックスを表示
		MessageBox(
			hDlg,
			TEXT("リセットに失敗しました。"),
			TEXT("エラー"),
			MB_ICONEXCLAMATION | MB_OK);
	}
}

// 実際にリセットを行う
bool DoResetText(HWND hDlg)
{
	// それぞれをリセット
	if (!SetDlgItemText(hDlg, IDC_EDIT_GROUP, TEXT(""))
		|| !SetDlgItemText(hDlg, IDC_EDIT_NAME, TEXT(""))
		|| !SetDlgItemText(hDlg, IDC_EDIT_ADDRESS, TEXT(""))
		|| !SetDlgItemText(hDlg, IDC_EDIT_TEL, TEXT(""))){
		return false;
	}

	return true;
}


// エディットボックスを指定の文字列で初期化する
bool InitEditBox(HWND hDlg2)
{
	// 初期化に失敗したとき
	if (!DoInitEditBox(hDlg2))
	{
		// 初期化失敗のメッセージボックスを表示
		MessageBox(
			hDlg2,
			TEXT("初期化に失敗しました。"),
			TEXT("エラー"),
			MB_ICONEXCLAMATION | MB_OK);

		return false;
	}

	return true;
}

// 実際にエディットボックスを指定の文字列で初期化する
bool DoInitEditBox(HWND hDlg2)
{
	// hDlg（親ウィンドウ）のウィンドウハンドル
	HWND hDlg;
	// リストコントロールのハンドル
	HWND hList;
	// リストコントロールで選択されている項目の番号
	int index;
	// 取得したUSERDATA構造体
	USERDATA userdata;
	// 番号をint→charに変換した文字列のバッファ
	char numStr[4];


	// 親ウィンドウhDlgのウィンドウハンドルを取得
	if ((hDlg = GetWindow(hDlg2, GW_OWNER)) == NULL){
		return false;
	}

	// リストコントロールのハンドルを取得
	if ((hList = GetDlgItem(hDlg, IDC_LIST_NAMELIST)) == NULL){
		return false;
	}

	// リストコントロールで選択中のアイテムを取得
	if ((index = ListView_GetNextItem(hList, -1,
		LVNI_ALL | LVNI_SELECTED)) == -1){
		return false;
	}

	// USERDATA構造体を取得
	DATA data;									// DATAクラスのインスタンス
	userdata = data.GetUserDataIndex(index);	// ファイルからindex番目の構造体を取得する

	// USERDATA構造体が正しく取得できていないとき
	if (userdata.number == -1){
		return false;
	}

	// 番号を設定
	_itoa(userdata.number, numStr, 10);	// 番号をint→charに変換
	if (!SetDlgItemText(hDlg2, IDC_EDIT_NUMBER2, numStr)){
		return false;
	}

	// グループ名を設定
	if (!SetDlgItemText(hDlg2, IDC_EDIT_GROUP2, userdata.group)){
		return false;
	}

	// 名前を設定
	if (!SetDlgItemText(hDlg2, IDC_EDIT_NAME2, userdata.name)){
		return false;
	}

	// 住所を設定
	if (!SetDlgItemText(hDlg2, IDC_EDIT_ADDRESS2, userdata.address)){
		return false;
	}

	// 電話番号を設定
	if (!SetDlgItemText(hDlg2, IDC_EDIT_TEL2, userdata.tel)){
		return false;
	}

	return true;
}


// 確定ボタンが押されたときの処理
void PushOkButton(HWND hDlg2)
{
	// 失敗したとき
	if (!(DoEditUserdata(hDlg2)))
	{
		// 編集にに失敗したときのメッセージボックス
		MessageBox(
			hDlg2,
			TEXT("編集に失敗しました。"),
			TEXT("エラー"),
			MB_ICONEXCLAMATION | MB_OK);
	}
	else
	{
		// 削除成功のメッセージボックスを表示
		MessageBox(
			hDlg2,
			TEXT("編集が完了しました。"),
			TEXT("編集完了"),
			MB_ICONINFORMATION | MB_OK);
	
		// 編集フォーム（ダイアログ）を閉じる
		EndDialog(hDlg2, TRUE);
	}
}

// 実際に編集を行うときの処理
bool DoEditUserdata(HWND hDlg2)
{
	// DATAクラスのインスタンス
	DATA data;
	// USERDATAの構造体（Newが編集後・Oldが編集前）
	USERDATA userDataNew, userDataOld;
	// 文字列の番号
	char numStr[4];
	// hDlg（親ウィンドウ）のウィンドウハンドル
	HWND hDlg;

	// エディットコントロールから番号を取得する
	GetDlgItemText(hDlg2, IDC_EDIT_NUMBER2, numStr, sizeof(numStr));	// バッファに保存
	userDataNew.number = atol(numStr);									// longに変換
	// エディットコントロールからグループ名を取得
	GetDlgItemText(hDlg2, IDC_EDIT_GROUP2, userDataNew.group, sizeof(userDataNew.group));
	// エディットコントロールから名前を取得
	GetDlgItemText(hDlg2, IDC_EDIT_NAME2, userDataNew.name, sizeof(userDataNew.name));
	// エディットコントロールから住所を取得
	GetDlgItemText(hDlg2, IDC_EDIT_ADDRESS2, userDataNew.address, sizeof(userDataNew.address));
	// エディットコントロールから電話番号を取得
	GetDlgItemText(hDlg2, IDC_EDIT_TEL2, userDataNew.tel, sizeof(userDataNew.tel));

	// ファイルからUSERDATA構造体を取得する
	userDataOld = data.GetUserDataNumber(userDataNew.number);

	// ファイルからの取得に失敗したとき
	if (userDataOld.number == -1){
		return false;
	}

	// 変更前と変更後が変わっていないとき
	if (!strcmp(userDataNew.group, userDataOld.group)			// グループ名を比較
		&& !strcmp(userDataNew.name, userDataOld.name)			// 名前を比較
		&& !strcmp(userDataNew.address, userDataOld.address)	// 住所を比較
		&& !strcmp(userDataNew.tel, userDataOld.tel))			// 電話番号を比較
	{
		// 編集箇所がないとき
		MessageBox(
			hDlg2,
			TEXT("変更箇所がありません。"),
			TEXT("エラー"),
			MB_ICONEXCLAMATION | MB_OK);

		return false;
	}

	// 編集を行う
	if (!data.UserEdit(userDataNew)){
		return false;
	}

	// 親ウィンドウhDlgのウィンドウハンドルを取得
	if ((hDlg = GetWindow(hDlg2, GW_OWNER)) == NULL){
		return false;
	}

	// ユーザリストを更新する
	UpdateUserList(hDlg);

	return true;
}