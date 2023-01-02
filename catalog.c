#include "catalog.h"

const char* CATALOG_FILE = "Catalog.txt";
// const char* FILE_ACCESS = "r";

typedef struct {
	char short_name[21];
	int total_hours;
	int classroom_hours;
	char full_name[295];
} Subject;

typedef struct {
	int k_wage;
	int k_accrual;
	int k_sfedu;

	int program_count;

	Subject* subjects;
} Catalog;

static Catalog* catalog = NULL;

int initCatalog() {
	if (catalog) {
		return -1;
	}

	catalog = (Catalog*)malloc(sizeof(Catalog));

	FILE* catalog_file = fopen(CATALOG_FILE, "r");

	if (!catalog_file) {
		return -1;
	}

	int read = fscanf(catalog_file, "%d %d %d\n%d\n", 
											 						&catalog->k_wage, 
										   						&catalog->k_accrual, 
										   						&catalog->k_sfedu, 
										   						&catalog->program_count);

	if (4 != read) {
		return -1;
	}
	
	catalog->subjects = (Subject*)malloc(sizeof(Subject) * catalog->program_count);

	Subject* subjects_ptr = catalog->subjects;
	for (int i = 0; i < catalog->program_count; ++i) {
		fscanf(catalog_file, "%s %d %d ", 
												 &subjects_ptr[i].short_name, 
										  	 &subjects_ptr[i].total_hours, 
										  	 &subjects_ptr[i].classroom_hours);
		fgets(subjects_ptr[i].full_name, 295, catalog_file);
	}

	fclose(catalog_file);

	return 0;
}

int deinitCatalog() {
	if (catalog) {
		if (catalog->subjects) {
			free(catalog->subjects);
		}
		free(catalog);
	}
}