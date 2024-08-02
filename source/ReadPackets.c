#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include "ReadPackets.h"

#define MAX_LINE_LENGTH 2048
#define MAX_KEY_LENGTH 256
#define MAX_VALUE_LENGTH 2048
#define MAX_SECTION_LENGTH 256

// Typ dla wskaźników do pól w strukturze TranslationConfig
typedef struct {
    wchar_t *field;
    const wchar_t *key;
} FieldMapping;

static void trim_whitespace(wchar_t *str) {
    wchar_t *end;

    while (iswspace(*str)) str++;
    if (*str == L'\0') return;

    end = str + wcslen(str) - 1;
    while (end > str && iswspace(*end)) end--;
    *(end + 1) = L'\0';
}

static void unescape_newlines(wchar_t *value) {
    wchar_t *src = value;
    wchar_t *dst = value;

    while (*src) {
        if (src[0] == L'\\' && src[1] == L'n') {
            *dst++ = L'\n';
            src += 2;
        } else {
            *dst++ = *src++;
        }
    }
    *dst = L'\0';
}

static int parse_line(const wchar_t *line, wchar_t *key, wchar_t *value) {
    const wchar_t *equals_sign = wcschr(line, L'=');
    if (equals_sign == NULL) return -1;

    size_t key_length = equals_sign - line;
    size_t value_length = wcslen(line) - key_length - 1;

    wcsncpy(key, line, key_length);
    key[key_length] = L'\0';

    wcsncpy(value, equals_sign + 1, value_length);
    value[value_length] = L'\0';

    trim_whitespace(key);
    trim_whitespace(value);

    unescape_newlines(value);

    // Remove quotes from value if they exist
    if (value[0] == L'"') {
        memmove(value, value + 1, wcslen(value) * sizeof(wchar_t));
        value[wcslen(value) - 1] = L'\0';
    }

    return 0;
}

static int is_section_allowed(const wchar_t *section, const wchar_t *allowed_sections[], int num_sections) {
    for (int i = 0; i < num_sections; i++) {
        if (wcscmp(section, allowed_sections[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int read_ini_file(const wchar_t *filename, const wchar_t *allowed_sections[], int num_sections, TranslationConfig *config) {
    FILE *file = _wfopen(filename, L"r, ccs=UTF-8");
    if (file == NULL) {
        perror("Unable to open file");
        return -1;
    }

    wchar_t line[MAX_LINE_LENGTH];
    wchar_t key[MAX_KEY_LENGTH];
    wchar_t value[MAX_VALUE_LENGTH];
    wchar_t current_section[MAX_SECTION_LENGTH] = L"";

    // Mapowanie kluczy do odpowiednich pól w strukturze TranslationConfig
    FieldMapping field_map[] = {
        { config->about_dialog_title, L"about_dialog_title" },
        { config->about_dialog_caption, L"about_dialog_caption" },
        { config->pause_dialog_title, L"Pause_dialog_title" },
        { config->pause_dialog_caption, L"Pause_dialog_caption" },
        { config->points_scored_caption, L"Points_scored_caption" },
        { config->points_scored_title, L"Points_scored_title" }
    };
    int field_map_size = sizeof(field_map) / sizeof(field_map[0]);

    int in_allowed_section = 0;

    while (fgetws(line, sizeof(line) / sizeof(line[0]), file)) {
        trim_whitespace(line);

        if (line[0] == L'[') {
            // Handle section headers
            wchar_t *end_bracket = wcschr(line, L']');
            if (end_bracket) {
                size_t section_length = end_bracket - line - 1;
                wcsncpy(current_section, line + 1, section_length);
                current_section[section_length] = L'\0';

                // Check if the current section is allowed
                in_allowed_section = is_section_allowed(current_section, allowed_sections, num_sections);
            }
        } else if (line[0] != L'\0' && line[0] != L';' && line[0] != L'#' && in_allowed_section) {
            // Handle key-value pairs if in an allowed section
            if (parse_line(line, key, value) == 0) {
                for (int i = 0; i < field_map_size; i++) {
                    if (wcscmp(key, field_map[i].key) == 0) {
                        wcsncpy(field_map[i].field, value, MAX_VALUE_LENGTH - 1);
                        break;
                    }
                }
            }
        } else if (line[0] == L'[' && !in_allowed_section) {
            // Skip the section if not allowed
            while (fgetws(line, sizeof(line) / sizeof(line[0]), file) && line[0] != L'[') {
                // Do nothing, just skip lines until the next section header
            }
            if (line[0] == L'[') {
                fseek(file, -wcslen(line) * sizeof(wchar_t), SEEK_CUR); // Go back one line
            }
        }
    }

    fclose(file);
    return 0;
}
