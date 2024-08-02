#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include <wchar.h>

#define MAX_KEY_LENGTH 256
#define MAX_VALUE_LENGTH 2048
#define MAX_SECTION_LENGTH 256
#define MAX_ALLOWED_SECTIONS 10

typedef struct {
    wchar_t about_dialog_title[MAX_VALUE_LENGTH];
    wchar_t about_dialog_caption[MAX_VALUE_LENGTH];
    wchar_t pause_dialog_title[MAX_VALUE_LENGTH];
    wchar_t pause_dialog_caption[MAX_VALUE_LENGTH];
    wchar_t points_scored_caption[MAX_VALUE_LENGTH];
    wchar_t points_scored_title[MAX_VALUE_LENGTH];
} TranslationConfig;

/**
 * Funkcja odczytuje dane z pliku INI i zapisuje je w strukturze TranslationConfig.
 * @param filename Nazwa pliku INI do odczytu.
 * @param allowed_sections Tablica dozwolonych sekcji.
 * @param num_sections Liczba dozwolonych sekcji.
 * @param config Wskaźnik na strukturę TranslationConfig, do której zostaną zapisane dane.
 * @return 0 w przypadku sukcesu, lub -1 w przypadku błędu.
 */
int read_ini_file(const wchar_t *filename, const wchar_t *allowed_sections[], int num_sections, TranslationConfig *config);

#endif // CONFIG_READER_H
