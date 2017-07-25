/**
 * @Author Nicholas Corrente
 * @date May 4th, 2017
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "graph_lib.h"
#include "graph.h"
#include "parser.h"

static void time_format(double speed, double distance, char* output){
    double hour = 0;
    double min = 0;
    double sec = 0;

    double t = distance/speed*60;
    while (t >= 60){
        hour++;
        t -= 60.0;
    }
    while (t >= 1) {
        min ++;
        t -= 1.0;
    }
    sec = t * 60;

    if (hour > 0){
        sprintf(output, "%.1f hr %1.f min %.1f sec", hour, min, sec);
    } else if (min > 0) {
        sprintf(output, "%1.f min %.1f sec", min, sec);
    }else if (sec > 0) {
        sprintf(output, "%.1f sec", sec);
    } else {
        sprintf(output, " ");
    }
}

// Here is an example of how you will be working with the output of the parser.
int main() {
    FILE* file = fopen("data/sample.txt", "r");
    file_record fr = parse_file(file);
    fclose(file);

    //create the graph using the data
    graph* map = graph_create(fr.location_count, true);
    for (size_t i = 0; i < fr.road_count; i++) {
        // add of the edges to the graph
        graph_add_edge(map, fr.roads[i].start, fr.roads[i].end);
    }
    // if map is disconnected, print statement and end program
    if (!graph_is_connected(map)){
        printf("Disconnected Map");
        return EXIT_SUCCESS;
    }

    for (size_t i = 0; i<fr.trip_count; i++){
        if (fr.trips[i].type == 'D'){
            // create the edge length matrix
            double **edge_length = (double**)malloc(sizeof (double*) * fr.location_count);
            if (edge_length)
            {
                for (int i = 0; i < (int)fr.location_count; i++)
                {
                    edge_length[i] = (double*)malloc(sizeof (double) * fr.location_count);
                }
            }
            for (int i = 0; i < (int)fr.road_count; i++){
                // fill matrix with road distances
                edge_length[(int)fr.roads[i].start][(int)fr.roads[i].end] = (double)fr.roads[i].distance;
            }

            vertex_t parent[fr.location_count];
            graph_dijkstras(map, fr.trips[i].start, parent, edge_length);

            vertex_t path[fr.location_count];
            int path_size = 0;
            graph_traverse_parents(parent, fr.trips[i].start, fr.trips[i].end, path, &path_size);

            printf("Shortest distance from %s to %s\n", fr.locations[fr.trips[i].start].name, fr.locations[fr.trips[i].end].name);
            printf("    Begin at %s\n", fr.locations[path[0]].name);
            double total_distance = 0.0;
            for (int j = 1; j < path_size; j++){
                total_distance += edge_length[path[j-1]][path[j]];
                printf("    Continue to %s (%.1f miles)\n", fr.locations[path[j]].name, edge_length[path[j-1]][path[j]]);
            }
            printf("Total distance: %.1f miles\n\n", total_distance);


            for(int k=0;k<(int)fr.location_count;k++){
                free(edge_length[k]);
            }
            free(edge_length);

        } else {
            // create edge length matrix
            double **edge_length = (double**)malloc(sizeof (double*) * fr.location_count);
            if (edge_length)
            {
                for (int i = 0; i < (int)fr.location_count; i++)
                {
                    edge_length[i] = (double*)malloc(sizeof (double) * fr.location_count);
                }
            }
            for (int i = 0; i < (int)fr.road_count; i++){
                // fill matrix with road distances
                edge_length[(int)fr.roads[i].start][(int)fr.roads[i].end] = (double)fr.roads[i].distance;
            }

            //create edge speed matrix
            double **edge_speed = (double**)malloc(sizeof (double*) * fr.location_count);
            if (edge_speed)
            {
                for (int i = 0; i < (int)fr.location_count; i++)
                {
                    edge_speed[i] = (double*)malloc(sizeof (double) * fr.location_count);
                }
            }
            for (int i = 0; i < (int)fr.road_count; i++){
                // fill matrix with road speeds
                edge_speed[(int)fr.roads[i].start][(int)fr.roads[i].end] = (double)fr.roads[i].speed;
            }

            vertex_t parent[fr.location_count];
            graph_dijkstras(map, fr.trips[i].start, parent, edge_length);

            vertex_t path[fr.location_count];
            int path_size = 0;
            graph_traverse_parents(parent, fr.trips[i].start, fr.trips[i].end, path, &path_size);

            printf("Shortest distance from %s to %s\n", fr.locations[fr.trips[i].start].name, fr.locations[fr.trips[i].end].name);
            printf("    Begin at %s\n", fr.locations[path[0]].name);
            double total_time = 0.0;
            double total_distance = 0.0;
            char time_output[100];
            for (int j = 1; j < path_size; j++){
                total_time += edge_length[path[j-1]][path[j]]/edge_speed[path[j-1]][path[j]]*60;
                total_distance += edge_length[path[j-1]][path[j]];
                time_format(edge_speed[path[j-1]][path[j]], edge_length[path[j-1]][path[j]], time_output);
                printf("    Continue to %s (%.1f miles @ %.1f mph = %s)\n", fr.locations[path[j]].name,
                edge_length[path[j-1]][path[j]], edge_speed[path[j-1]][path[j]], time_output);
            }
            time_format(total_time, total_distance, time_output);
            printf("Total time: %s \n\n", time_output);


            for(int k=0;k<(int)fr.location_count;k++){
                free(edge_length[k]);
                free(edge_speed[k]);
            }
            free(edge_length);
            free(edge_speed);
        }
    }


    graph_destroy(map);
    file_record_destroy(fr);

    return EXIT_SUCCESS;
}

/*
// Example of working with file_record
printf("There are %zu locations.\n", fr.location_count);
printf("The locations are named:\n");
for (size_t i = 0; i < fr.location_count; i++) {
printf("    %zu: %s\n", i, fr.locations[i].name);
}

printf("\nThere are %zu roads.\n", fr.road_count);
printf("The roads have the following information:\n");
for (size_t i = 0; i < fr.road_count; i++) {
printf("    start = %zu; end = %zu; dist = %f; speed = %f\n",
fr.roads[i].start, fr.roads[i].end,
fr.roads[i].distance, fr.roads[i].speed);
}

printf("\nThere are %zu requested trips\n", fr.trip_count);
printf("The trips have the following information:\n");
for (size_t i = 0; i < fr.trip_count; i++) {
printf("    start = %zu; end = %zu; type = %c\n",
fr.trips[i].start, fr.trips[i].end, fr.trips[i].type);
}
*/
