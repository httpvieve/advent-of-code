#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_REPORT_DATA 1000
#define MAX_LEVEL_COUNT 100
#define NEWLINE '\n'

typedef struct {
  int data[MAX_LEVEL_COUNT];
  int count;
} Report;

bool checkLevelState (Report *report) {
  bool state = true, is_increasing = true, is_decreasing = true;
  int key = 1, difference;
  while (key < report->count) {
    difference = report->data[key] - report->data[key - 1]; 
    if (difference == 0 || abs(difference) > 3) return false;
    if (difference < 0) is_increasing = false;
    if (difference > 0) is_decreasing = false;
    if (!is_increasing && !is_decreasing) return false;
    key++;
  }
  return state;
}

int main() {
  FILE *dataset;
  int i = 0, totalReports = 0, safeReportsCount = 0;
  Report reportData[MAX_REPORT_DATA];

  dataset = fopen ("input.txt", "r");
  while (totalReports < MAX_REPORT_DATA){
    Report *current = &reportData[totalReports];
    current->count = 0;
    while (fscanf(dataset, "%d", &current->data[current->count]) == 1){
      current->count++;
      char ch = getc(dataset);
      if (ch == NEWLINE || ch == EOF) {
        totalReports++;
        break;
    }
    ungetc (ch, dataset);
    }
    if (feof(dataset)) break;
  }

  fclose (dataset);
  while (i < totalReports) {
    if (checkLevelState(&reportData[i])) safeReportsCount++;
    i++;
  }
  printf ("Safe Reports: %d ", safeReportsCount);
  return 0;
}
