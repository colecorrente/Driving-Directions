/**
 * This header provides a parser to parse input files for driving directions.
 */
#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define STRING_LEN 100
typedef unsigned long vertex_t;

/**
 * A struct with the information for a location in the map.
 * Contains the associated vertex id and the location name.
 */
typedef struct location_record
{
    vertex_t id;
    char* name;
} location_record;

/**
 * A struct with the information for a road segment in the map.
 * Contains start and end vertices, and distance and current speed.
 */
typedef struct road_record
{
    vertex_t start;
    vertex_t end;
    double distance;
    double speed;
} road_record;

/**
 * A struct with the information of a trip your used would like to take.
 * Contains start and end vertices and a preference on what metric to use
 * for the trip planning. The value of type is either 'D' for distance or
 * 'T' for time.
 */
typedef struct trip_record
{
    vertex_t start;
    vertex_t end;
    char type;
} trip_record;

/**
 * This struct contains the complete parsed information contained in an
 * input file.
 */
typedef struct file_record
{
    size_t location_count;
    location_record* locations; // Array of locations
    size_t road_count;
    road_record* roads; // Array of roads
    size_t trip_count;
    trip_record* trips; // Array of trips
} file_record;

/**
 * Reads a valid input from stream
 *
 * Basic error checking is done with asserts.
 *
 * @param  stream input stream
 * @return        parsed output
 */
file_record parse_file(FILE* stream);

/**
 * Frees all memory associated with a file_record.
 *
 * @param fr the file record to be freed
 */
void file_record_destroy(file_record fr);

#endif//__PARSER_H__
