#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// structure declaration
typedef struct {
    char county[128];
    char state[3];
    float Education_Bachelors_Degree_or_Higher;
    float Education_High_School_or_Higher;
    float Ethnicities_American_Indian_and_Alaska_Native_Alone;
    float Ethnicities_Asian_Alone;
    float Ethnicities_Black_Alone;
    float Ethnicities_Hispanic_or_Latino;
    float Ethnicities_Native_Hawaiian_and_Other_Pacific_Islander_Alone;
    float Ethnicities_Two_or_More_Races;
    float Ethnicities_White_Alone;
    float Ethnicities_White_Alone_not_Hispanic_or_Latino;
    int Income_Median_Household_Income;
    int Income_Per_Capita_Income;
    float Income_Persons_Below_Poverty_Level;
    int Population_2014_Population;
} CountyEntity;

// function declarations
int process_csv(FILE *csv_file, CountyEntity entries[]);
CountyEntity process_line(char *line);
void process_op(FILE *op_file, CountyEntity entries[], int num_entries);
void display(CountyEntity entries[], int num_entries);
int population_total(CountyEntity entries[], int num_entries);
float population_field(CountyEntity entries[], int num_entries, char *field);
float percent_field(CountyEntity entries[], int num_entries, char *field);
int filter_state(CountyEntity entries[], int num_entries, char *state, int entries_remaining);
int filter_field_ge_le_number(CountyEntity entries[], int num_entries, int entries_remaining, char *field, char *ge_le, float number);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("ERROR: Invalid arguments.\n");
        return 1;
    }

    FILE *csv_file = fopen(argv[1], "r");
    if (csv_file == NULL) {
        printf("ERROR: Invalid CSV file.\n");
        return 1;
    }

    FILE *op_file = fopen(argv[2], "r");
    if (op_file == NULL) {
        printf("ERROR: Invalid operations file.\n");
        return 1;
    }

    // process CSV file and print number of entries loaded
    CountyEntity entries[3143];
    int num_entries = process_csv(csv_file, entries);
    printf("%d records loaded\n", num_entries);

    // process OP file
    process_op(op_file, entries, num_entries);

    fclose(csv_file);
    fclose(op_file);
    return 0;
}

int process_csv(FILE *csv_file, CountyEntity entries[]) {
    char line[2048];
    int entities = 0;

    // skip header line
    fgets(line, sizeof(line), csv_file);

    // parse each line of CSV file until reaching EOF
    while (fgets(line, sizeof(line), csv_file) != NULL) {
        // create new_entry from processed line
        CountyEntity new_entry;
        new_entry = process_line(line);

        // add new_entry to entities list
        entries[entities] = new_entry;

        // increment number of entities
        entities++;
    }

    return entities;
}

CountyEntity process_line(char *line) {
    CountyEntity new_entry;
    char *token;
    int column = 1;

    // parse each column of line
    while ((token = strtok(line, ",")) != NULL) {
        line = NULL;

        // county
        if (column == 1) {
            // remove quotes
            strncpy((new_entry.county), token + 1, sizeof(new_entry.county) - 1);
            (new_entry.county)[strlen(new_entry.county) - 1] = '\0';
        }
        // state
        else if (column == 2) {
            // remove quotes
            strncpy((new_entry.state), token + 1, sizeof(new_entry.state) - 1);
            (new_entry.state)[strlen(new_entry.state)] = '\0';
        }
        // Education_Bachelors_Degree_or_Higher
        else if (column == 6) {
            // remove quotes before converting string to float
            char temp[strlen(token) - 1];
            strncpy(temp, token + 1, sizeof(token) - 2);
            temp[strlen(token) - 2] = '\0';
            (new_entry.Education_Bachelors_Degree_or_Higher) = atof(temp);
        }
        // Education_High_School_or_Higher
        else if (column == 7) {
            // remove quotes before converting string to float
            char temp[strlen(token) - 1];
            strncpy(temp, token + 1, sizeof(token) - 2);
            temp[strlen(token) - 2] = '\0';
            (new_entry.Education_High_School_or_Higher) = atof(temp);
        }
        // Ethnicities_American_Indian_and_Alaska_Native_Alone
        else if (column == 12) {
            // remove quotes before converting string to float
            char temp[strlen(token) - 1];
            strncpy(temp, token + 1, sizeof(token) - 2);
            temp[strlen(token) - 2] = '\0';
            (new_entry.Ethnicities_American_Indian_and_Alaska_Native_Alone) = atof(temp);
        }
        // Ethnicities_Asian_Alone
        else if (column == 13) {
            // remove quotes before converting string to float
            char temp[strlen(token) - 1];
            strncpy(temp, token + 1, sizeof(token) - 2);
            temp[strlen(token) - 2] = '\0';
            (new_entry.Ethnicities_Asian_Alone) = atof(temp);
        }
        // Ethnicities_Black_Alone
        else if (column == 14) {
            // remove quotes before converting string to float
            char temp[strlen(token) - 1];
            strncpy(temp, token + 1, sizeof(token) - 2);
            temp[strlen(token) - 2] = '\0';
            (new_entry.Ethnicities_Black_Alone) = atof(temp);
        }
        // Ethnicities_Hispanic_or_Latino
        else if (column == 15) {
            // remove quotes before converting string to float
            char temp[strlen(token) - 1];
            strncpy(temp, token + 1, sizeof(token) - 2);
            temp[strlen(token) - 2] = '\0';
            (new_entry.Ethnicities_Hispanic_or_Latino) = atof(temp);
        }
        // Ethnicities_Native_Hawaiian_and_Other_Pacific_Islander_Alone
        else if (column == 16) {
            // remove quotes before converting string to float
            char temp[strlen(token) - 1];
            strncpy(temp, token + 1, sizeof(token) - 2);
            temp[strlen(token) - 2] = '\0';
            (new_entry.Ethnicities_Native_Hawaiian_and_Other_Pacific_Islander_Alone) = atof(temp);
        }
        // Ethnicities_Two_or_More_Races
        else if (column == 17) {
            // remove quotes before converting string to float
            char temp[strlen(token) - 1];
            strncpy(temp, token + 1, sizeof(token) - 2);
            temp[strlen(token) - 2] = '\0';
            (new_entry.Ethnicities_Two_or_More_Races) = atof(temp);
        }
        // Ethnicities_White_Alone
        else if (column == 18) {
            // remove quotes before converting string to float
            char temp[strlen(token) - 1];
            strncpy(temp, token + 1, sizeof(token) - 2);
            temp[strlen(token) - 2] = '\0';
            (new_entry.Ethnicities_White_Alone) = atof(temp);
        }
        // Ethnicities_White_Alone_not_Hispanic_or_Latino
        else if (column == 19) {
            // remove quotes before converting string to float
            char temp[strlen(token) - 1];
            strncpy(temp, token + 1, sizeof(token) - 2);
            temp[strlen(token) - 2] = '\0';
            (new_entry.Ethnicities_White_Alone_not_Hispanic_or_Latino) = atof(temp);
        }
        // Income_Median_Household_Income
        else if (column == 26) {
            // remove quotes before converting string to int
            char temp[strlen(token) - 1];
            strncpy(temp, token + 1, sizeof(token) - 2);
            temp[strlen(token) - 2] = '\0';
            (new_entry.Income_Median_Household_Income) = atoi(temp);
        }
        // Income_Per_Capita_Income
        else if (column == 27) {
            // remove quotes before converting string to int
            char temp[strlen(token) - 1];
            strncpy(temp, token + 1, sizeof(token) - 2);
            temp[strlen(token) - 2] = '\0';
            (new_entry.Income_Per_Capita_Income) = atoi(temp);
        }
        // Income_Persons_Below_Poverty_Level
        else if (column == 28) {
            // remove quotes before converting string to float
            char temp[strlen(token) - 1];
            strncpy(temp, token + 1, sizeof(token) - 2);
            temp[strlen(token) - 2] = '\0';
            (new_entry.Income_Persons_Below_Poverty_Level) = atof(temp);
        }
        // Population_2014_Population
        else if (column == 39) {
            // remove quotes before converting string to int
            char temp[strlen(token) - 1];
            strncpy(temp, token + 1, sizeof(token) - 2);
            temp[strlen(token) - 2] = '\0';
            (new_entry.Population_2014_Population) = atoi(temp);
        }

        // increment column count
        column++;
    }
    
    return new_entry;
}

void process_op(FILE *op_file, CountyEntity entries[], int num_entries) {
    char line[2048];
    char *field;
    char *state;
    char *ge_le;
    float number;
    int entries_remaining = num_entries;

    // parse each line of OP file until reaching EOF
    while (fgets(line, sizeof(line), op_file) != NULL) {
        // display
        if ((strncmp(line, "display", 7) == 0)) {
            display(entries, num_entries);
        }
        // population-total
        else if ((strncmp(line, "population-total", 16) == 0)) {
            int total_population = population_total(entries, num_entries);
            printf("2014 population: %d\n", total_population);
        }
        // population:<field>
        else if (strncmp(line, "population:", 11) == 0) {
            field = strtok(line + 11, ":");
            if (field[strlen(field) - 1] == '\n') {
                field[strlen(field) - 1] = '\0';
            }
            float sub_population = population_field(entries, num_entries, field);
            printf("2014 %s population: %f\n", field, sub_population);
        }
        // percent:<field>
        else if (strncmp(line, "percent:", 7) == 0) {
            field = strtok(line + 7, ":");
            if (field[strlen(field) - 1] == '\n') {
                field[strlen(field) - 1] = '\0';
            }
            float percentage = percent_field(entries, num_entries, field);
            printf("2014 %s percentage: %f\n", field, percentage);
        }
        // filter-state:<state abbreviation>
        else if (strncmp(line, "filter-state:", 13) == 0) {
            state = strtok(line + 13, ":");
            if (state[strlen(state) - 1] == '\n') {
                state[strlen(state) - 1] = '\0';
            }
            entries_remaining = filter_state(entries, num_entries, state, entries_remaining);
            printf("Filter: state == %s (%d entries)\n", state, entries_remaining);
        }
        // filter:<field>:<ge/le>:<number>
        else if (strncmp(line, "filter:", 7) == 0) {
            field = strtok(line + 7, ":");
            ge_le = strtok(NULL, ":");
            number = atof(strtok(NULL, ";"));
            entries_remaining = filter_field_ge_le_number(entries, num_entries, entries_remaining, field, ge_le, number);
            printf("Filter: %s %s %f (%d entries)\n", field, ge_le, number, entries_remaining);
        }
    }
}

void display(CountyEntity entries[], int num_entries) {
    for (int i = 0; i < num_entries; i++) {
        if (strcmp(entries[i].county, "NULL") != 0) {
            printf("%s, %s\n", entries[i].county, entries[i].state);
            printf("    Population: %d\n", entries[i].Population_2014_Population);
            printf("    Education\n");
            printf("        >= High School: %f%%\n", entries[i].Education_High_School_or_Higher);
            printf("        >= Bachelor's: %f%%\n", entries[i].Education_Bachelors_Degree_or_Higher);
            printf("    Ethnicity Percentages\n");
            printf("        American Indian and Alaska Native Alone: %f%%\n", entries[i].Ethnicities_American_Indian_and_Alaska_Native_Alone);
            printf("        Asian Alone: %f%%\n", entries[i].Ethnicities_Asian_Alone);
            printf("        Black Alone: %f%%\n", entries[i].Ethnicities_Black_Alone);
            printf("        Hispanic or Latino: %f%%\n", entries[i].Ethnicities_Hispanic_or_Latino);
            printf("        Native Hawaiian and Other Pacific Islander Alone: %f%%\n", entries[i].Ethnicities_Native_Hawaiian_and_Other_Pacific_Islander_Alone);
            printf("        Two or More Races: %f%%\n", entries[i].Ethnicities_Two_or_More_Races);
            printf("        White Alone: %f%%\n", entries[i].Ethnicities_White_Alone);
            printf("        White Alone, not Hispanic or Latino: %f%%\n", entries[i].Ethnicities_White_Alone_not_Hispanic_or_Latino);
            printf("    Income\n");
            printf("        Median Household: %d\n", entries[i].Income_Median_Household_Income);
            printf("        Per Capita: %d\n", entries[i].Income_Per_Capita_Income);
            printf("        Below Poverty Level: %f%%\n", entries[i].Income_Persons_Below_Poverty_Level);
        }
    }
}

int population_total(CountyEntity entries[], int num_entries) {
    int total_population = 0;
    for (int i = 0; i < num_entries; i++) {
        if (strcmp(entries[i].county, "NULL") != 0) {
            total_population = total_population + entries[i].Population_2014_Population;
        }
    }
    return total_population;
}

float population_field(CountyEntity entries[], int num_entries, char *field) {
    float sub_population = 0;
    float percentage = 0;

    for (int i = 0; i < num_entries; i++) {
        if (strcmp(entries[i].county, "NULL") != 0) {
            if (strcmp(field, "Education.High School or Higher") == 0) {
                percentage = entries[i].Education_High_School_or_Higher;
            } 
            else if (strcmp(field, "Education.Bachelor's Degree or Higher") == 0) {
                percentage = entries[i].Education_Bachelors_Degree_or_Higher;
            }
            else if (strcmp(field, "Ethnicities.American Indian and Alaska Native Alone") == 0) {
                percentage = entries[i].Ethnicities_American_Indian_and_Alaska_Native_Alone;
            }
            else if (strcmp(field, "Ethnicities.Asian Alone") == 0) {
                percentage = entries[i].Ethnicities_Asian_Alone;
            }
            else if (strcmp(field, "Ethnicities.Black Alone") == 0) {
                percentage = entries[i].Ethnicities_Black_Alone;
            }
            else if (strcmp(field, "Ethnicities.Hispanic or Latino") == 0) {
                percentage = entries[i].Ethnicities_Hispanic_or_Latino;
            }
            else if (strcmp(field, "Ethnicities.Native Hawaiian and Other Pacific Islander Alone") == 0) {
                percentage = entries[i].Ethnicities_Native_Hawaiian_and_Other_Pacific_Islander_Alone;
            }
            else if(strcmp(field, "Ethnicities.Two or More Races") == 0) {
                percentage = entries[i].Ethnicities_Two_or_More_Races;
            }
            else if (strcmp(field, "Ethnicities.White Alone") == 0) {
                percentage = entries[i].Ethnicities_White_Alone;
            }
            else if (strcmp(field, "Ethnicities.White Alone, not Hispanic or Latino") == 0) {
                percentage = entries[i].Ethnicities_White_Alone_not_Hispanic_or_Latino;
            }
            else if (strcmp(field, "Income.Persons Below Poverty Level") == 0) {
                percentage = entries[i].Income_Persons_Below_Poverty_Level;
            }
            sub_population = sub_population + (entries[i].Population_2014_Population * (percentage / 100)); 
        }
    }
    return sub_population;
}

float percent_field(CountyEntity entries[], int num_entries, char *field) {
    float percentage = 0;
    int total_population = population_total(entries, num_entries);
    float sub_population = population_field(entries, num_entries, field);

    percentage = (sub_population / total_population) * 100;

    return percentage;
}

int filter_state(CountyEntity entries[], int num_entries, char *state, int entries_remaining) {

    for (int i = 0; i < num_entries; i++) {
        if (strcmp(entries[i].county, "NULL") != 0) {
            if (strcmp(entries[i].state, state) != 0) {
                entries[i].county[0] = 'N';
                entries[i].county[1] = 'U';
                entries[i].county[2] = 'L';
                entries[i].county[3] = 'L';
                entries[i].county[4] = '\0';
                entries_remaining--;
            }
        }
    }

    return entries_remaining;
}

int filter_field_ge_le_number(CountyEntity entries[], int num_entries, int entries_remaining, char *field, char *ge_le, float number) {

    for (int i = 0; i < num_entries; i++) {
        if (strcmp(entries[i].county, "NULL") != 0) {
            if (strcmp(ge_le, "ge") == 0) {
                if (strcmp(field, "Education.High School or Higher") == 0) {
                    if (entries[i].Education_High_School_or_Higher < number) {
                        entries[i].county[0] = 'N';
                        entries[i].county[1] = 'U';
                        entries[i].county[2] = 'L';
                        entries[i].county[3] = 'L';
                        entries[i].county[4] = '\0';
                        entries_remaining--;
                    }
                } 
                else if (strcmp(field, "Education.Bachelor's Degree or Higher") == 0) {
                    if (entries[i].Education_Bachelors_Degree_or_Higher < number) {
                        entries[i].county[0] = 'N';
                        entries[i].county[1] = 'U';
                        entries[i].county[2] = 'L';
                        entries[i].county[3] = 'L';
                        entries[i].county[4] = '\0';
                        entries_remaining--;
                    }
                } 
                else if (strcmp(field, "Ethnicities.American Indian and Alaska Native Alone") == 0) {
                    if (entries[i].Ethnicities_American_Indian_and_Alaska_Native_Alone < number) {
                        entries[i].county[0] = 'N';
                        entries[i].county[1] = 'U';
                        entries[i].county[2] = 'L';
                        entries[i].county[3] = 'L';
                        entries[i].county[4] = '\0';
                        entries_remaining--;
                    }
                } 
                else if (strcmp(field, "Ethnicities.Asian Alone") == 0) {
                    if (entries[i].Ethnicities_Asian_Alone < number) {
                        entries[i].county[0] = 'N';
                        entries[i].county[1] = 'U';
                        entries[i].county[2] = 'L';
                        entries[i].county[3] = 'L';
                        entries[i].county[4] = '\0';
                        entries_remaining--;
                    }
                }
                else if (strcmp(field, "Ethnicities.Black Alone") == 0) {
                    if (entries[i].Ethnicities_Black_Alone < number) {
                        entries[i].county[0] = 'N';
                        entries[i].county[1] = 'U';
                        entries[i].county[2] = 'L';
                        entries[i].county[3] = 'L';
                        entries[i].county[4] = '\0';
                        entries_remaining--;
                    }
                }
                else if (strcmp(field, "Ethnicities.Hispanic or Latino") == 0) {
                    if (entries[i].Ethnicities_Hispanic_or_Latino < number) {
                        entries[i].county[0] = 'N';
                        entries[i].county[1] = 'U';
                        entries[i].county[2] = 'L';
                        entries[i].county[3] = 'L';
                        entries[i].county[4] = '\0';
                        entries_remaining--;
                    }
                }
                else if (strcmp(field, "Ethnicities.Native Hawaiian and Other Pacific Islander Alone") == 0) {
                    if (entries[i].Ethnicities_Native_Hawaiian_and_Other_Pacific_Islander_Alone < number) {
                        entries[i].county[0] = 'N';
                        entries[i].county[1] = 'U';
                        entries[i].county[2] = 'L';
                        entries[i].county[3] = 'L';
                        entries[i].county[4] = '\0';
                        entries_remaining--;
                    }
                }
                else if (strcmp(field, "Ethnicities.Two or More Races") == 0) {
                    if (entries[i].Ethnicities_Two_or_More_Races < number) {
                        entries[i].county[0] = 'N';
                        entries[i].county[1] = 'U';
                        entries[i].county[2] = 'L';
                        entries[i].county[3] = 'L';
                        entries[i].county[4] = '\0';
                        entries_remaining--;
                    }
                }
                else if (strcmp(field, "Ethnicities.White Alone") == 0) {
                    if (entries[i].Ethnicities_White_Alone < number) {
                        entries[i].county[0] = 'N';
                        entries[i].county[1] = 'U';
                        entries[i].county[2] = 'L';
                        entries[i].county[3] = 'L';
                        entries[i].county[4] = '\0';
                        entries_remaining--;
                    }
                }
                else if (strcmp(field, "Ethnicities.White Alone not Hispanic or Latino") == 0) {
                    if (entries[i].Ethnicities_White_Alone_not_Hispanic_or_Latino < number) {
                        entries[i].county[0] = 'N';
                        entries[i].county[1] = 'U';
                        entries[i].county[2] = 'L';
                        entries[i].county[3] = 'L';
                        entries[i].county[4] = '\0';
                        entries_remaining--;
                    }
                }
                else if (strcmp(field, "Income.Median Household Income") == 0) {
                    if (entries[i].Income_Median_Household_Income < number) {
                        entries[i].county[0] = 'N';
                        entries[i].county[1] = 'U';
                        entries[i].county[2] = 'L';
                        entries[i].county[3] = 'L';
                        entries[i].county[4] = '\0';
                        entries_remaining--;
                    }
                }
                else if (strcmp(field, "Income.Per Capita Income") == 0) {
                    if (entries[i].Income_Per_Capita_Income < number) {
                        entries[i].county[0] = 'N';
                        entries[i].county[1] = 'U';
                        entries[i].county[2] = 'L';
                        entries[i].county[3] = 'L';
                        entries[i].county[4] = '\0';
                        entries_remaining--;
                    }
                }
                else if (strcmp(field, "Income.Persons Below Poverty Level") == 0) {
                    if (entries[i].Income_Persons_Below_Poverty_Level < number) {
                        entries[i].county[0] = 'N';
                        entries[i].county[1] = 'U';
                        entries[i].county[2] = 'L';
                        entries[i].county[3] = 'L';
                        entries[i].county[4] = '\0';
                        entries_remaining--;
                    }
                }
            }
            else if (strcmp(ge_le, "le") == 0) {
                if (strcmp(field, "Education.High School or Higher") == 0) {
                    if (entries[i].Education_High_School_or_Higher > number) {
                        entries[i].county[0] = 'N';
                        entries[i].county[1] = 'U';
                        entries[i].county[2] = 'L';
                        entries[i].county[3] = 'L';
                        entries[i].county[4] = '\0';
                        entries_remaining--;
                    }
                } 
                else if (strcmp(field, "Education.Bachelor's Degree or Higher") == 0) {
                    if (entries[i].Education_Bachelors_Degree_or_Higher > number) {
                        entries[i].county[0] = 'N';
                        entries[i].county[1] = 'U';
                        entries[i].county[2] = 'L';
                        entries[i].county[3] = 'L';
                        entries[i].county[4] = '\0';
                        entries_remaining--;
                    }
                } 
                else if (strcmp(field, "Ethnicities.American Indian and Alaska Native Alone") == 0) {
                    if (entries[i].Ethnicities_American_Indian_and_Alaska_Native_Alone > number) {
                        entries[i].county[0] = 'N';
                        entries[i].county[1] = 'U';
                        entries[i].county[2] = 'L';
                        entries[i].county[3] = 'L';
                        entries[i].county[4] = '\0';
                        entries_remaining--;
                    }
                } 
                else if (strcmp(field, "Ethnicities.Asian Alone") == 0) {
                    if (entries[i].Ethnicities_Asian_Alone > number) {
                        entries[i].county[0] = 'N';
                        entries[i].county[1] = 'U';
                        entries[i].county[2] = 'L';
                        entries[i].county[3] = 'L';
                        entries[i].county[4] = '\0';
                        entries_remaining--;
                    }
                }
                else if (strcmp(field, "Ethnicities.Black Alone") == 0) {
                    if (entries[i].Ethnicities_Black_Alone > number) {
                        entries[i].county[0] = 'N';
                        entries[i].county[1] = 'U';
                        entries[i].county[2] = 'L';
                        entries[i].county[3] = 'L';
                        entries[i].county[4] = '\0';
                        entries_remaining--;
                    }
                }
                else if (strcmp(field, "Ethnicities.Hispanic or Latino") == 0) {
                    if (entries[i].Ethnicities_Hispanic_or_Latino > number) {
                        entries[i].county[0] = 'N';
                        entries[i].county[1] = 'U';
                        entries[i].county[2] = 'L';
                        entries[i].county[3] = 'L';
                        entries[i].county[4] = '\0';
                        entries_remaining--;
                    }
                }
                else if (strcmp(field, "Ethnicities.Native Hawaiian and Other Pacific Islander Alone") == 0) {
                    if (entries[i].Ethnicities_Native_Hawaiian_and_Other_Pacific_Islander_Alone > number) {
                        entries[i].county[0] = 'N';
                        entries[i].county[1] = 'U';
                        entries[i].county[2] = 'L';
                        entries[i].county[3] = 'L';
                        entries[i].county[4] = '\0';
                        entries_remaining--;
                    }
                }
                else if (strcmp(field, "Ethnicities.Two or More Races") == 0) {
                    if (entries[i].Ethnicities_Two_or_More_Races > number) {
                        entries[i].county[0] = 'N';
                        entries[i].county[1] = 'U';
                        entries[i].county[2] = 'L';
                        entries[i].county[3] = 'L';
                        entries[i].county[4] = '\0';
                        entries_remaining--;
                    }
                }
                else if (strcmp(field, "Ethnicities.White Alone") == 0) {
                    if (entries[i].Ethnicities_White_Alone > number) {
                        entries[i].county[0] = 'N';
                        entries[i].county[1] = 'U';
                        entries[i].county[2] = 'L';
                        entries[i].county[3] = 'L';
                        entries[i].county[4] = '\0';
                        entries_remaining--;
                    }
                }
                else if (strcmp(field, "Ethnicities.White Alone not Hispanic or Latino") == 0) {
                    if (entries[i].Ethnicities_White_Alone_not_Hispanic_or_Latino > number) {
                        entries[i].county[0] = 'N';
                        entries[i].county[1] = 'U';
                        entries[i].county[2] = 'L';
                        entries[i].county[3] = 'L';
                        entries[i].county[4] = '\0';
                        entries_remaining--;
                    }
                }
                else if (strcmp(field, "Income.Median Household Income") == 0) {
                    if (entries[i].Income_Median_Household_Income > number) {
                        entries[i].county[0] = 'N';
                        entries[i].county[1] = 'U';
                        entries[i].county[2] = 'L';
                        entries[i].county[3] = 'L';
                        entries[i].county[4] = '\0';
                        entries_remaining--;
                    }
                }
                else if (strcmp(field, "Income.Per Capita Income") == 0) {
                    if (entries[i].Income_Per_Capita_Income > number) {
                        entries[i].county[0] = 'N';
                        entries[i].county[1] = 'U';
                        entries[i].county[2] = 'L';
                        entries[i].county[3] = 'L';
                        entries[i].county[4] = '\0';
                        entries_remaining--;
                    }
                }
                else if (strcmp(field, "Income.Persons Below Poverty Level") == 0) {
                    if (entries[i].Income_Persons_Below_Poverty_Level > number) {
                        entries[i].county[0] = 'N';
                        entries[i].county[1] = 'U';
                        entries[i].county[2] = 'L';
                        entries[i].county[3] = 'L';
                        entries[i].county[4] = '\0';
                        entries_remaining--;
                    }
                }
            }
        }
    }

    return entries_remaining;
}