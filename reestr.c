#include "reestr.h"
#include "consts.h"

typedef struct {
  int month;
  int year;
} Date;

typedef struct {
	char short_name[21];
  Date begin_date;
  Date end_date;
  int  price;
  int  students_count;
  int  group_count;
} ReestrEntry;

typedef struct {
  int entry_count;
  ReestrEntry* entries;
} Reestr;

Reestr* reestr = NULL;

int initReestr()
{
  if (reestr) {
		return -1;
	}

	reestr = (Reestr*)malloc(sizeof(Reestr));

	FILE* reestr_file = fopen(REESTR_FILE, FILES_ACCESS);

	if (!reestr_file) {
		return -1;
	}

  int read = fscanf(reestr_file, "%d\n", reestr->entry_count);

  if (1 != read) {
    return -1;
  }

  ReestrEntry* entries_ptr = reestr->entries;

  for (int i = 0; i < reestr->entry_count; i++) {
    fscanf(reestr_file, "%s %d.%d %d.%d %d %d %d",
            entries_ptr[i].short_name,
            entries_ptr[i].begin_date.month,
            entries_ptr[i].begin_date.year,
            entries_ptr[i].end_date.month,
            entries_ptr[i].end_date.month,
            entries_ptr[i].price,
            entries_ptr[i].students_count,
            entries_ptr[i].group_count
            );
  }

  fclose(reestr_file);
}
