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
void TaoChuoi(FILE*fp, wchar_t *&a){
	a = NULL;
	int i = 0;
	while (!feof(fp)){
		wchar_t ch = fgetwc(fp);
		a = (wchar_t*)realloc(a, (i + 1)*sizeof(wchar_t));
		a[i] = ch;
		i++;
	}
}
int TimViTriChuoiCon(wchar_t* ChuoiCha, wchar_t* ChuoiCon){
	int l1 = wcslen(ChuoiCha), l2 = wcslen(ChuoiCon);
	if (l2 > l1)
		return -1;
	else{
		int ViTri = 0;
		while (l1 - ViTri >= l2){
			int count = 0;
			for (int i = ViTri; i < l2 + ViTri; i++){
				if (ChuoiCha[i] != ChuoiCon[i - ViTri])
					break;
				else
					count++;
			}
			if (count == l2)
				return ViTri;
			ViTri++;
		}
		return -1;
	}
}
int DemSoLuongChuoiConTrongChuoiCha(wchar_t* ChuoiCha, wchar_t* ChuoiCon){
	int l1 = wcslen(ChuoiCha), l2 = wcslen(ChuoiCon);
	int value = 0;
	if (l2 > l1)
		return value;
	else{
		int ViTri = 0;
		while (l1 - ViTri >= l2){
			int count = 0;
			for (int i = ViTri; i < l2 + ViTri; i++){
				if (ChuoiCha[i] != ChuoiCon[i - ViTri])
					break;
				else
					count++;
			}
			if (count == l2)
				value++;
			ViTri++;
		}
		return value;
	}
}
void XoaChuoi(wchar_t* ChuoiCha, int ViTri, int SoLuong){
	int length = wcslen(ChuoiCha);
	if (ViTri + SoLuong >= length)
		SoLuong = length - ViTri;
	wcscpy(ChuoiCha + ViTri, ChuoiCha + ViTri + SoLuong);
}
void ChenChuoi(wchar_t* ChuoiCha, wchar_t* ChuoiCon, int ViTri){
	int l = wcslen(ChuoiCha);
	int l1 = wcslen(ChuoiCon);
	if (ViTri > l)
		ViTri = l;
	if (ViTri < l){
		wchar_t* temp = new wchar_t[l - ViTri + 1];
		wcscpy(temp, ChuoiCha + ViTri);
		wcscpy(ChuoiCha + ViTri, ChuoiCon);
		wcscpy(ChuoiCha + ViTri + l1, temp);
	}
	else
		wcscpy(ChuoiCha + ViTri, ChuoiCon);
}
void ThayThe(wchar_t *CanThay, wchar_t *ThayBoi, wchar_t *ChuoiCha){
	int l1 = wcslen(CanThay);//các hàm được gọi trong hàm này được chép từ bài thực hành sang
	int n = DemSoLuongChuoiConTrongChuoiCha(ChuoiCha, CanThay);//đếm sô lần xuất hiện chuỗi con trong chuỗi cha
	for (int i = 0; i < n; i++){
		int ViTri = TimViTriChuoiCon(ChuoiCha, CanThay);//tìm vị trí xuất hiện chuỗi con trong chuỗi cha
		XoaChuoi(ChuoiCha, ViTri, l1);//xóa chuỗi cha n1 phần tử từ "ViTri"
		ChenChuoi(ChuoiCha, ThayBoi, ViTri);//chèn chuỗi "ThayBoi" vào chuỗi "ChuoiCha" bắt đầu từ "ViTri"	
	}
}
void ThayTheChuoi(SINHVIEN sv, wchar_t *a){
	ThayThe(L"1212123", sv.mssv, a);
	ThayThe(L"Nguyễn Văn A", sv.hoten, a);
	ThayThe(L"NGUYỄN VĂN A", sv.hoten, a);
	ThayThe(L"Công nghệ thông tin", sv.khoa, a);
	ThayThe(L"CÔNG NGHỆ THÔNG TIN", wcsupr(sv.khoa), a);
	ThayThe(L"nva@gmail.com", sv.email, a);
	ThayThe(L"20/01/1994", sv.ngaysinh, a);
	ThayThe(L"HinhCaNhan.jpg", sv.anhcanhan, a);
	ThayThe(L"Tôi là một người rất thân thiện.", sv.mota, a);
	ThayThe(L"Âm nhạc: POP, Balad", sv.sothich_1, a);
	ThayThe(L"Ẩm thực: bún riêu, bún thịt nướng", sv.sothich_2, a);
	ThayThe(L"MSSV - Tên sinh viên thực hiện", L"1712878 - Nguyễn Thọ Tuấn", a);
}
void TaoFileHtml(SINHVIEN sv, wchar_t *a){
	wchar_t filename[30];
	wcscpy(filename, L"Website\\\\");
	wcscat(filename, sv.mssv);
	wcscat(filename, L".htm");
	FILE* fp = _wfopen(filename, L"wt, ccs=UTF-8");
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
	FILE* fpds = _wfopen(L"Website\\DSSV.csv", L"rt, ccs=UTF-8");
	FILE* fphtm = _wfopen(L"Website\\1212123.htm", L"rt,ccs=UTF-8");
	if (!fpds || !fphtm) {
		wprintf(L"Không thể đọc file \n");
		return;
	}
	else {
		DocDuLieu(fpds, sv, n);
		TaoChuoi(fphtm, a);
		for (int i = 0; i < n; i++)
			TaoFileHtml(sv[i], a);
		wprintf(L"Tạo thành công %d file html vào thư mục ../Website\n", n);
		//Hiển thị tiếng việt vào Defaults -> Font -> Consolas trên màn hình Console
	}
	free(sv);
	free(a);
	fcloseall();
}