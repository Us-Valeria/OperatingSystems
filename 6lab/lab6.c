#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* get_section_name(Elf64_Ehdr* header, Elf64_Shdr* shdr, int index, FILE* file) {
  Elf64_Shdr shstrtab;
  char* section_names;

  // Находим раздел .shstrtab по индексу, хранящемуся в e_shstrndx
  fseek(file, header->e_shoff + header->e_shstrndx * header->e_shentsize, SEEK_SET);
  fread(&shstrtab, sizeof(Elf64_Shdr), 1, file);

  // Выделяем память для хранения имен разделов
  section_names = malloc(shstrtab.sh_size);
  fseek(file, shstrtab.sh_offset, SEEK_SET);
  fread(section_names, shstrtab.sh_size, 1, file);
  
  // Возвращаем имя раздела по индексу
  return section_names + shdr[index].sh_name;
}
char* array[30];

void sect(int argc, char **argv) {
  const char* elfFile = argv[1];
  Elf64_Ehdr header;
  Elf64_Shdr* sections;
  int i;
  FILE* file = fopen(elfFile, "rb");

  fread(&header, sizeof(Elf64_Ehdr), 1, file);

  // Выделение памяти для хранения информации о разделах
  sections = malloc(sizeof(Elf64_Shdr) * header.e_shnum);

  // Чтение информации о разделах
  fseek(file, header.e_shoff, SEEK_SET);
  fread(sections, sizeof(Elf64_Shdr), header.e_shnum, file);

  for (i = 0; i < header.e_shnum; i++) {
    char* section_name = get_section_name(&header, sections, i, file);
    array[i] = section_name;
    //printf("%d\t%s\n", i, section_name);
  }

  // Освобождение памяти и закрытие файла
  free(sections);
  fclose(file);
}



int main(int argc, char **argv) {
  const char *elfFile = argv[1];
  Elf64_Ehdr header;
  Elf64_Shdr sheader;
  Elf64_Shdr symtab;
  Elf64_Shdr strtab;
  Elf64_Shdr shstrtab;
  Elf64_Sym sym;
  char sname[32];
  int i;
  sect(0, argv); 
  FILE *file = fopen(elfFile, "rb");
  fread(&header, sizeof(header), 1, file);
  fseek(file, header.e_shoff, SEEK_SET);
  fread(&sheader, sizeof(sheader), 1, file);
  // Find the section header string table
  fseek(file, header.e_shoff + header.e_shentsize * header.e_shstrndx, SEEK_SET);
  fread(&shstrtab, sizeof(shstrtab), 1, file);
  for (i = 0; i < header.e_shnum; i++) {
    fseek(file, header.e_shoff + header.e_shentsize * i, SEEK_SET);
    fread(&sheader, sizeof(sheader), 1, file);     
    fseek(file, shstrtab.sh_offset + sheader.sh_name, SEEK_SET);
    fread(sname, 1, 32, file);
    if (strcmp(sname, ".symtab") == 0)
      symtab = (Elf64_Shdr)sheader;
    if (strcmp(sname, ".strtab") == 0)
      strtab = (Elf64_Shdr)sheader;
  }
  char array_sname[30][32];
  for (int i = 0; i < 30; i++) {
    fseek(file, symtab.sh_offset + symtab.sh_entsize * i, SEEK_SET);
    fread(&sym, sizeof(sym), 1, file);
    fseek(file, strtab.sh_offset + sym.st_name, SEEK_SET);
    fgets(sname, sizeof(sname), file);
    strcpy(array_sname[i], sname);
    if (i != 0) fprintf(stdout, "%-20s %s\n", array[i], array_sname[i]);
  }
  
  
  while(1) {
    char str[20];
    printf("Enter section_name\n");
    fgets(str, sizeof(str), stdin);
    if (str[strlen(str) - 1] == '\n')str[strlen(str) - 1] = '\0';
    for (int i = 0; i < 30; i++) 
    {
      if (strcmp(str, array[i]) == 0) {fprintf(stdout, "FIND OVERLAP FOR %s  %d: %s\n", array[i],  i, array_sname[i]); break;}
    }

  }
   
  return 0;
}
