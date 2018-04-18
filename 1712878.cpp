#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <stdlib.h>
#include <memory.h>
typedef struct{
	wchar_t mssv[11];
	wchar_t hoten[31];
	wchar_t khoa[31];
	wchar_t email[31];
	wchar_t khoatuyen[5];
	wchar_t ngaysinh[11];
	wchar_t anhcanhan[21];
	wchar_t mota[1001];
	wchar_t sothich_1[201];
	wchar_t sothich_2[201];
} SINHVIEN;
void DocDuLieu(FILE* fp, SINHVIEN *&sv, int &n){
	n = 0;
	wchar_t *a = (wchar_t*)malloc(sizeof(SINHVIEN));
	while (!feof(fp)){
		sv = (SINHVIEN*)realloc(sv, (n + 1)*sizeof(SINHVIEN));
		fgetws(a, sizeof(SINHVIEN), fp);
		wcscpy(sv[n].mssv, wcstok(a, L","));
		wcscpy(sv[n].hoten, wcstok(NULL, L","));
		wcscpy(sv[n].khoa, wcstok(NULL, L","));
		wcscpy(sv[n].email, wcstok(NULL, L","));
		wcscpy(sv[n].khoatuyen, wcstok(NULL, L","));
		wcscpy(sv[n].ngaysinh, wcstok(NULL, L","));
		wcscpy(sv[n].anhcanhan, wcstok(NULL, L","));
		wcscpy(sv[n].mota, wcstok(NULL, L","));
		wcscpy(sv[n].sothich_1, wcstok(NULL, L","));
		wcscpy(sv[n].sothich_2, wcstok(NULL, L"\n"));
		n++;
	}
	free(a);
}
void wmain()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	SINHVIEN *sv = NULL;
	int n;
	FILE* fp = _wfopen(L"DSSV.csv", L"r, ccs=UTF-8");
	if (!fp) {
		wprintf(L"Không thể đọc file \n");
		return;
	}
	else {
		DocDuLieu(fp, sv, n);
		wprintf(L"Danh sách chứa %d sinh viên\n", n);
		for (int i = 0; i < n; i++){
				wprintf(L"%ls\n", sv[i].sothich_2);
		}
	}
	if (sv != NULL)
		free(sv);
}