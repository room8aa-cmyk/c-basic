#include <stdio.h>
#include <stdlib.h>


#define max_dinh 100005
#define max_canh 200005

typedef struct nut
{
    int dinh;
    struct nut* tiep;
} nut;

nut* danh_sach_ke[max_dinh];
int bac[max_dinh];
int mau[max_dinh];
int da_tham[max_dinh];
int thu_tu[max_dinh];
int hang_doi[max_dinh];


int canh_u[max_canh];
int canh_v[max_canh];

const char* ten_mau[] = {
    "", "red", "green", "blue", "yellow",
    "orange", "purple", "cyan", "magenta", "brown", "pink"
};

void them_canh(int u, int v) {
    nut* nut1 = (nut*)malloc(sizeof(nut));
    nut1->dinh = v;
    nut1->tiep = danh_sach_ke[u];
    danh_sach_ke[u] = nut1;


    nut* nut2 = (nut*)malloc(sizeof(nut));
    nut2->dinh = u;
    nut2->tiep = danh_sach_ke[v];
    danh_sach_ke[v] = nut2; }

int main()
{
    FILE *tep_vao = fopen("dothi.txt", "r");
    FILE *tep_ra = fopen("dothitomau.dot", "w");

    if (tep_vao == NULL)
    {
        printf("khong mo duoc tep dothi.txt\n");
        return 0; }

    int so_dinh, so_canh;
    fscanf(tep_vao, "%d %d", &so_dinh, &so_canh);


    for (int i = 0; i < so_canh; i++) {
        fscanf(tep_vao, "%d %d", &canh_u[i], &canh_v[i]);
        them_canh(canh_u[i], canh_v[i]);
        bac[canh_u[i]]++;
        bac[canh_v[i]]++; }
    fclose(tep_vao);

    int bac_lon_nhat = 0;
    for (int i = 1; i <= so_dinh; i++)
    {
        if (bac[i] > bac_lon_nhat) {
            bac_lon_nhat = bac[i]; }
    }


    int dinh_goc = -1;
    for (int i = 1; i <= so_dinh; i++) {
        if (bac[i] < bac_lon_nhat)
        {
            dinh_goc = i;
            break; } }

    int so_luong_thu_tu = 0;

    if (dinh_goc != -1)
    {
        int dau = 0, cuoi = 0;
        hang_doi[cuoi++] = dinh_goc;
        da_tham[dinh_goc] = 1;


        while (dau < cuoi) {
            int u = hang_doi[dau++];
            thu_tu[so_luong_thu_tu++] = u;

            nut* hien_tai = danh_sach_ke[u];
            while (hien_tai != NULL)
            {
                int v = hien_tai->dinh;
                if (!da_tham[v]) { da_tham[v] = 1; hang_doi[cuoi++] = v; }
                hien_tai = hien_tai->tiep;
            } }


        for (int i = 0; i < so_luong_thu_tu / 2; i++) {
            int tam = thu_tu[i];
            thu_tu[i] = thu_tu[so_luong_thu_tu - 1 - i];
            thu_tu[so_luong_thu_tu - 1 - i] = tam; }
    }
    else {
        for (int i = 1; i <= so_dinh; i++)
        { thu_tu[so_luong_thu_tu++] = i; }
    }


    int *mau_da_dung = (int*)calloc(bac_lon_nhat + 3, sizeof(int));

    for (int i = 0; i < so_luong_thu_tu; i++)
    {
        int u = thu_tu[i];

        for (int j = 0; j <= bac_lon_nhat + 2; j++) { mau_da_dung[j] = 0; }


        nut* hien_tai = danh_sach_ke[u];
        while (hien_tai != NULL) {
            int v = hien_tai->dinh;
            if (mau[v] != 0)
            { mau_da_dung[mau[v]] = 1; }
            hien_tai = hien_tai->tiep; }

        for (int c = 1; c <= bac_lon_nhat + 2; c++) {
            if (mau_da_dung[c] == 0) {
                mau[u] = c;
                break; }
        }
    }

    free(mau_da_dung);


    fprintf(tep_ra, "graph dothi\n{\n");
    for (int i = 1; i <= so_dinh; i++)
    {
        const char* ten = (mau[i] <= 10) ? ten_mau[mau[i]] : "gray";
        fprintf(tep_ra, "  %d [fillcolor=%s, style=filled];\n", i, ten); }

    for (int i = 0; i < so_canh; i++) {
        fprintf(tep_ra, "  %d--%d;\n", canh_u[i], canh_v[i]); }
    fprintf(tep_ra, "}\n");
    fclose(tep_ra);

    return 0; }
