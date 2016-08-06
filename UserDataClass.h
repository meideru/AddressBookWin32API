
// ユーザデータクラスのヘッダ

#include <Windows.h>

// 保存パス
extern char* userPath;		// ユーザデータの保存パス
extern char* userPath2;		// ユーザデータのコピー先の保存パス
extern char* userPath3;		// ユーザデータの検索結果の保存パス

// ユーザデータ構造体
struct USERDATA
{
	long number;		// 番号（プライマリキー）
	char group[256];	// グループ名
	char name[256];		// 名前
	char address[256];	// 住所
	char tel[256];		// 電話番号
};

// グループデータ構造体
struct GROUPDATA
{
	long number;		// 番号（プライマリキー）
	char group[256];	// グループ名
};

// データのクラス
class DATA
{
	// コンストラクタ・デストラクタ
public:
	DATA();		// コンストラクタ
	~DATA();	// デストラクタ

	// 非公開メソッド
private:
	long MakeNumber();			// 自動で番号を作成（エラーは-1を返却）

	// 構造体に関するゲッタ
public:
	// ファイルから番号（上から）を指定してUSERDATAを取得（失敗時はnumber = -1）（一番上はindex = 0）
	USERDATA GetUserDataIndex(int index);
	// ファイルから番号を（プライマリキー）を指定してUSERDATAを取得（失敗時はnumber = -1)
	USERDATA GetUserDataNumber(int number);

	// 表示に関して
public:
	// ユーザデータをリストに表示する
	bool ShowUserList(HWND hList);
	// ユーザデータの検索結果を外部ファイルを参照してリストに表示する
	bool ShowUserSearchList(HWND hList);
	
	// 削除に関して
public:
	// userPath3のファイルを削除する
	bool DeleteSearchFile();

	// ファイルのサイズ・個数に関するゲッタ
public:
	// ユーザデータのファイルサイズを取得する
	size_t GetUserFileSize();
	// ユーザデータファイルの件数を取得する
	long GetUserFileCount();
	// 番号（プライマリキー）からインデックスを取得（上はindex = 0）（失敗時はindex = -1）
	long GetUserFileIndex(long number);
	// ユーザデータのファイルサイズを取得する
	size_t GetUserSearchFileSize();
	// ユーザデータの検索用ファイルから件数を取得する
	long GetUserSearchFileCount();


	// 登録・編集・検索・削除
public:
	// ユーザデータを追加する
	bool UserAdd(
		char* group, 
		char* name,
		char* address, 
		char* tel);
	// ユーザデータを編集する（引数の構造体の番号（プライマリキー）は一意である必要があります）
	bool UserEdit(USERDATA userdata);
	// ユーザデータを検索する（引数は検索キー）
	bool UserSearch(char* group, char* name, char* address, char* tel);
	// ユーザデータを削除する（引数はリストコントロールの先頭からの番号）
	bool UserDelete(long number);
};

