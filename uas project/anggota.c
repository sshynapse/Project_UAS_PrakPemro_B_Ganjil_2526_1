#include "perpustakaan.h"

void register_member(Anggota **members, int *count) {
    *members = realloc(*members, (*count + 1) * sizeof(Anggota));
    Anggota *new_member = &(*members)[*count];
    new_member->id = *count + 1;
    printf("Nama: ");
    fgets(new_member->nama, sizeof(new_member->nama), stdin);
    new_member->nama[strcspn(new_member->nama, "\n")] = 0;
    printf("Email: ");
    fgets(new_member->email, sizeof(new_member->email), stdin);
    new_member->email[strcspn(new_member->email, "\n")] = 0;
    (*count)++;
    save_members(*members, *count);
    printf("Anggota terdaftar.\n");
}

void view_members(Anggota *members, int count) {
    for (int i = 0; i < count; i++) {
        printf("ID: %d, Nama: %s, Email: %s\n", members[i].id, members[i].nama, members[i].email);
    }
}