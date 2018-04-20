#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <stdlib.h>
#include <memory.h>
#pragma pack(1)
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
		memset(sv + n, 0, sizeof(SINHVIEN));
		fgetws(a, sizeof(SINHVIEN), fp);

		wcscpy(sv[n].mssv, wcstok(a, L","));
		wcscpy(sv[n].hoten, wcstok(NULL, L","));
		wcscpy(sv[n].khoa, wcstok(NULL, L","));
		wcscpy(sv[n].email, wcstok(NULL, L","));
		wcscpy(sv[n].khoatuyen, wcstok(NULL, L","));
		wcscpy(sv[n].ngaysinh, wcstok(NULL, L","));
		wcscpy(sv[n].anhcanhan, wcstok(NULL, L","));
		wcscpy(sv[n].mota, wcstok(NULL, L","));
		wchar_t *t = wcstok(NULL, L",");
		if (t != NULL){
			wcscpy(sv[n].sothich_1, t);
			t = wcstok(NULL, L",");
			if (t != NULL){
				wcscpy(sv[n].sothich_2, t);
			}
		}
		n++;
	}
	free(a);
}
int TaoChuoi(FILE*fp, wchar_t *&a){
	a = NULL;
	int i = 0;
	while (!feof(fp)){
		wchar_t ch = fgetwc(fp);
		a = (wchar_t*)realloc(a, (i + 1)*sizeof(wchar_t));
		a[i] = ch;
		i++;
	}
	return i;
}
int FindSubString(wchar_t* Dest, wchar_t* Src, int startPos = 0){
	int l1 = wcslen(Dest), l2 = wcslen(Src);
	if (l2 > l1 - startPos)
		return -1;
	else{
		int run = startPos;
		while (l1 - run >= l2){
			int count = 0;
			for (int i = run; i < l2 + run; i++){
				if (*(Dest + i) != *(Src + i - run))
					break;
				else
					count++;
			}
			if (count == l2){
				return run;
				break;
			}
			run++;
		}
		return -1;
	}
}
int CountMatches(wchar_t* Dest, wchar_t* Src){
	int l1 = wcslen(Dest), l2 = wcslen(Src);
	int value = 0;
	if (l2 > l1)
		return value;
	else{
		int run = 0;
		while (l1 - run >= l2){
			int count = 0;
			for (int i = run; i < l2 + run; i++){
				if (*(Dest + i) != *(Src + i - run))
					break;
				else
					count++;
			}
			if (count == l2){
				value++;
			}
			run++;
		}
		return value;
	}
}
void XoaChuoi(wchar_t* Dest, int startPos, int numChars){
	int length = wcslen(Dest);
	wcscpy(Dest + startPos, Dest + startPos + numChars);
}
void ChenChuoi(wchar_t* chuoicha, wchar_t* chuoicon, int vitri){
	int l = wcslen(chuoicha);
	int l1 = wcslen(chuoicon);
	wchar_t* temp = new wchar_t[l - vitri + 1];
	wcscpy(temp, chuoicha + vitri);
	wcscpy(chuoicha + vitri, chuoicon);
	wcscpy(chuoicha + vitri + l1, temp);
}
void ThayThe(wchar_t *canthay, wchar_t *thayboi, wchar_t *chuoicha){
	int l1 = wcslen(canthay);//các hàm được gọi trong hàm này được chép từ bài thực hành sang
	int n = CountMatches(chuoicha, canthay);//đếm sô lần xuất hiện chuỗi con trong chuỗi cha
	for (int i = 0; i < n; i++){
		int vitri = FindSubString(chuoicha, canthay);//tìm vị trí xuất hiện chuỗi con trong chuỗi cha
		XoaChuoi(chuoicha, vitri, l1);//xoa chuỗi cha n1 phần tử từ "vitri"
		ChenChuoi(chuoicha, thayboi, vitri);//chèn chuỗi "thayboi" vào chuỗi "chuoicha" bắt đầu từ "vitri"	
	}
}
void ThayTheChuoi(SINHVIEN sv, wchar_t *a){
	/*wchar_t *s[] = { L"Nguyễn Văn A", L"1212123", L"nva@gmail.com", L"HinhCaNhan.jpg", L"Âm nhạc: POP, Balad",
	L"Ẩm thực: bún riêu, bún thịt nướng", L"Tôi là một người rất thân thiện." };*/
	ThayThe(L"Nguyễn Văn A", sv.hoten, a);
	ThayThe(L"NGUYỄN VĂN A", sv.hoten, a);
	ThayThe(L"1212123", sv.mssv, a);
	ThayThe(L"nva@gmail.com", sv.email, a);
	ThayThe(L"Công nghệ thông tin", sv.khoa, a);
	ThayThe(L"CÔNG NGHỆ THÔNG TIN", wcsupr(sv.khoa), a);
	ThayThe(L"20/01/1994", sv.ngaysinh, a);
	ThayThe(L"HinhCaNhan.jpg", sv.anhcanhan, a);
	ThayThe(L"Âm nhạc: POP, Balad", sv.sothich_1, a);
	ThayThe(L"Ẩm thực: bún riêu, bún thịt nướng", sv.sothich_2, a);
	ThayThe(L"Tôi là một người rất thân thiện.", sv.mota, a);
	ThayThe(L"MSSV - Tên sinh viên thực hiện", L"1712878 - Nguyễn Thọ Tuấn", a);
}
void TaoFileHtml(SINHVIEN sv, wchar_t *a){
	wchar_t filename[16];
	wcscpy(filename, sv.mssv);
	wcscat(filename, L".html");
	FILE* fp = _wfopen(filename, L"w, ccs=UTF-8");
	wchar_t* b = wcsdup(a);
	ThayTheChuoi(sv, b);
	fputws(b, fp);
	fclose(fp);
}
void wmain()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	SINHVIEN *sv = NULL;
	wchar_t *a = NULL;
	int n;
	FILE* fpds = _wfopen(L"DSSV.csv", L"r, ccs=UTF-8");
	FILE* fphtml = _wfopen(L"1212123.htm", L"r,ccs=UTF-8");
	if (!fpds || !fphtml) {
		wprintf(L"Không thể đọc file \n");
		return;
	}
	else {
		DocDuLieu(fpds, sv, n);
		wprintf(L"Danh sách chứa %d sinh viên\n", n);
		TaoChuoi(fphtml, a);
		for (int i = 0; i < n; i++)
			TaoFileHtml(sv[i], a);
	}
	free(sv);
	free(a);
	fcloseall();
}