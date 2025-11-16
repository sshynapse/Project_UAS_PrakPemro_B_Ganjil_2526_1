#include "perpustakaan.h"
#include <ctype.h> 

/* Ambil tanggal sekarang (DD-MM-YYYY) */
void getTanggalSekarang(char *buffer) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Baca durasi maksimal pinjam dari data/config.txt, default 7 hari */
int getMaxLoanDays() {
    FILE *f = fopen("data/config.txt", "r");
    if (!f) return 7;
    int days = 7;
    if (fscanf(f, "%d", &days) != 1) days = 7;
    fclose(f);
    return days;
}

/* Ubah durasi peminjaman (tulis ke config) */
void ubahDurasiPeminjaman() {
    int days;
    printf("Masukkan durasi peminjaman maksimal (hari): ");
    if (scanf("%d", &days) != 1) { clearBuffer(); printf("Input tidak valid.\n"); return; }
    FILE *f = fopen("data/config.txt", "w");
    if (!f) { printf("Gagal menulis config.\n"); return; }
    fprintf(f, "%d\n", days);
    fclose(f);
    printf("Durasi peminjaman diatur menjadi %d hari.\n", days);
}

int strncasecmp_portable(const char *s1, const char *s2, size_t n) {
    if (n == 0) return 0;
    size_t i;
    for (i = 0; i < n; ++i) {
        unsigned char c1 = (unsigned char)s1[i];
        unsigned char c2 = (unsigned char)s2[i];
        int lc1 = tolower(c1);
        int lc2 = tolower(c2);
        if (lc1 != lc2) return lc1 - lc2;
        if (c1 == '\0') return 0;
    }
    return 0;
}

#ifndef HAVE_STRNCASECMP
int strncasecmp(const char *s1, const char *s2, size_t n) {
    return strncasecmp_portable(s1, s2, n);
}
#endif

char *strcasestr(const char *haystack, const char *needle) {
    if (!haystack || !needle) return NULL;
    size_t len_h = strlen(haystack);
    size_t len_n = strlen(needle);
    if (len_n == 0) return (char *)haystack;
    for (size_t i = 0; i + len_n <= len_h; ++i) {
        if (strncasecmp(haystack + i, needle, len_n) == 0) return (char *)(haystack + i);
    }
    return NULL;
}
