// Implementations of the declarations in parser.h.
#include "parser.h"

// Private function to test if a line is blank
bool is_empty(char* str)
{
    for (size_t i = 0; str[i] != '\0'; i++)
    {
        if (!isspace(str[i])) return false;
    }
    return true;
}

// Private function to test if a line is a comment
bool is_comment(char* str)
{
    return (str[0] == '#');
}

// Private function to get the next line that is not empty/comment.
void next_line(char* line, size_t line_len, FILE* stream)
{
    // Skip empty lines and comments
    while ((fgets(line, line_len, stream) != NULL)
                    && (is_empty(line) || is_comment(line)))
    {/* empty loop */}

    // Remove trailing newline
    size_t len = strlen(line);
    if (line[len-1] == '\n') line[len-1] = '\0';
}

// File parser
file_record parse_file(FILE* stream)
{
    file_record fr;
    char line[STRING_LEN+1];
    char* start = NULL;
    char* end = NULL;

    // Read in number of locations
    next_line(line, STRING_LEN+1, stream);
    fr.location_count = strtoul(line, &end, 10);
    assert(line != end);

    // Read in location names
    fr.locations = malloc(fr.location_count * sizeof(location_record));
    for (size_t i = 0; i < fr.location_count; i++)
    {
        next_line(line, STRING_LEN+1, stream);
        fr.locations[i].id = i;
        fr.locations[i].name = malloc((STRING_LEN+1) * sizeof(char));
        strcpy(fr.locations[i].name, line);
    }

    // Read in number of roads
    next_line(line, STRING_LEN+1, stream);
    fr.road_count = strtoul(line, &end, 10);
    assert(line != end);

    // Read in road information
    fr.roads = malloc(fr.road_count * sizeof(road_record));
    for (size_t i = 0; i < fr.road_count; i++)
    {
        next_line(line, STRING_LEN+1, stream);
        start = line;
        fr.roads[i].start = strtoul(start, &end, 10);
        assert(start != end);
        start = end;
        fr.roads[i].end = strtoul(start, &end, 10);
        assert(start != end);
        start = end;
        fr.roads[i].distance = strtod(start, &end);
        assert(start != end);
        start = end;
        fr.roads[i].speed = strtod(start, &end);
        assert(start != end);
    }

    // Read in number of trips
    next_line(line, STRING_LEN+1, stream);
    fr.trip_count = strtoul(line, &end, 10);
    assert(line != end);

    // Read in trip information
    fr.trips = malloc(fr.trip_count * sizeof(trip_record));
    for (size_t i = 0; i < fr.trip_count; i++)
    {
        next_line(line, STRING_LEN+1, stream);
        start = line;
        fr.trips[i].start = strtoul(start, &end, 10);
        assert(start != end);
        start = end;
        fr.trips[i].end = strtoul(start, &end, 10);
        assert(start != end);
        start = end;
        while (isspace(*start)) start++;
        fr.trips[i].type = *start;
        assert(fr.trips[i].type == 'D' || fr.trips[i].type == 'T');
    }

    return fr;
}

void file_record_destroy(file_record fr)
{
    for (size_t i = 0; i < fr.location_count; i++)
    {
        free(fr.locations[i].name);
    }
    free(fr.locations);
    free(fr.roads);
    free(fr.trips);
}
