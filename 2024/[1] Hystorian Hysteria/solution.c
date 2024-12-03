#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000


int compare(const void *a, const void *b);
int getCount (int number, int *array, int length);
int computeTotalDistance(int *a, int *b, int length);
int computeSimilarityScore (int *a, int *b, int length);
int main () {

/* TODO: 
 * [1] read input & sort the two arrays
 * [2] initialize total_difference = 0
 * [3] for loop logic:  i = 0; i < array length; i++ -> total_difference += |arr_a[i] - arr_b[i]|
 * [4] return total_difference
 * */  
  
  FILE *dataset = NULL;
  int total_distance, similarity_score, count = 0, left_array[MAX], right_array[MAX];

  dataset = fopen ("input.txt", "r");
  
  if (dataset == NULL) printf("File not found!");
  while (fscanf(dataset, "%d %d", &left_array[count], &right_array[count]) == 2) {
    count++;
  }
  fclose(dataset);
  total_distance = computeTotalDistance (left_array, right_array, count);
  similarity_score = computeSimilarityScore (left_array, right_array, count);
  printf ("Distance: %d\n", total_distance);
  printf ("Similarity Score: %d", similarity_score);
  return 0;
}
int compare(const void *a, const void *b) {
  return (*(int*)a - *(int*)b);
}
int computeTotalDistance (int *a, int *b, int length) {
  
  int i, total = 0;

  qsort(a, length, sizeof(int), compare);
  qsort(b, length, sizeof(int), compare);
  
  for (i = 0; i < length; i++) {
    total += abs (a[i] - b[i]);
  }

  return total;
}

int computeSimilarityScore (int *a, int *b, int length) {

  int i, score = 0;

  for (i = 0; i < length; i++) {
    score += a[i] * getCount(a[i], b, length); 
  }

  return score;
}
int getCount (int number, int *array, int length) {
  
  int i, counter = 0;

  for (i = 0; i < length; i++) {
    if (array[i] == number) counter++;
  }

  return counter;
}
