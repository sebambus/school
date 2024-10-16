#include <iostream>
#include <cstdio>
#include <ctype.h>
using namespace std;

//This program gets up to 10 scores from a students, calculates the average and final grade
//Security: NO INPUT SANITIZATION, TYPE CHECKING AT ALL


int main()
{
  //------DO NOT CHANGE THESE------
  int scores[10];
  char name[100] = "abc";
  char id[10] = "";
  int number_of_score = 0;
  double average = 0;
  int sum = 0;
  char grade = 'X';
  char comments[5] = "NONE";
  
  //------------------------------

  cout << "\n---------------------------------------\n";
  cout << "Welcome to the scoring system!" <<endl;
  cout << "Enter student's name: " ; 
  fgets(name, 99, stdin);

  // read student id
  cout << "\nPlease enter student ID: ";
  for(int i = 0; i < 10; i++) {
    char c = getchar();
    if(isalpha(c) && i < 3 ||
       isdigit(c) && i > 3  && i < 9 ||
       c == '-' && i == 3 || 
       c == '\n' && i == 9)
      id[i] = c;
    else {
      if(c != '\n')
        while(getchar() != '\n');
      cout << "Invalid Student ID\nPlease enter student ID: ";
      i = -1;
      continue;
    }
  }
  id[9] = '\0';

  
  // read exam scores
  cout << "Enter up to 10 student's scores (0-100) (if done, enter -1 to stop): ";  //DIVIDE BY ZERO PROBLEM
  cout << endl;
  for (int i = 0; i < 10; i++) {
    cout << "Score " << i+1 << ": ";
    char score[4] = "\0\0\0";
    for(int i = 0; i < 3; i++) {
      char c = getchar();
      if(isdigit(c) || (i == 0 && c == '-'))
        score[i] = c;
      else if(c == '\n')
        break;
      else {
	score[i] = c;
        score[0] = 'X';
      }
    }

    // discard entries that are too long
    if(score[2] != '\0')
      if(getchar() != '\n') {
	while(getchar() != '\n');
        cout << "Invalid Score!" << endl;
        i--;
        continue;
      }
    // discard entries that were marked as having invalid characters
    if(score[0] == 'X'){
      cout << "Invalid Score!" << endl;
      i--;
      continue;
    }

    int temp = atoi(score);
    // finish if entry is -1
    if(temp == -1){
      if(i == 0){
        cout << "Input at least 1 score" << endl;
	i--;
	continue;
      }
      else break;
    }
    // discard entries outside of 0-100
    if(temp > 100 || temp < 0){
      cout << "Invalid Score!" << endl;
      i--;
      continue;
    }

    // add the entry to the gradebook
    scores[i] = temp;
    number_of_score++;
    sum += temp;
  }
  
  // calculate average
  average = sum / number_of_score;
  cout << "Student's name is: " << name << endl;
  cout << "Student has " << number_of_score << " scores, sum is " << sum <<", and the average score is " << average << endl;

  // figure out the final grade, A, B, C, D, or F
  if( average >= 90)
    grade = 'A';
  if(average < 90 and average >= 80)
    grade = 'B';
  if (average < 80 and average >= 70)
    grade = 'C';
  if (average < 70 and average >= 60)
    grade = 'D';
  if (average < 60 and average >= 0)
    grade = 'F';
  cout << "Based on the average score, final grade is: " << grade << endl;

  // ask for verification
  while(true) {
    cout << "looks good? (Yes or No): ";
    char c = getchar();
    if(c == 'Y' || c == 'y') {
      comments[0] = c;
      char c = getchar();
      if(c == '\n'){
        comments[1] = '\0';
	break;
      }
      else if(c == 'E' || c == 'e') {
        comments[1] = c;
        char c = getchar();
	if(c == 'S' || c == 's') {
	  comments[2] = c;
         char c = getchar();
	  if(c == '\n') {
	    comments[3] = '\0';
            break;
	  }
	}
      }
    }
    else if(c == 'N' || c == 'n') {
      comments[0] = c;
      char c = getchar();
      if(c == '\n'){
        comments[1] = '\0';
	break;
      }
      else if(c == 'O' || c == 'o') {
        comments[1] = c;
        char c = getchar();
	if(c == '\n') {
	  comments[2] = '\0';
          break;
        }
      }
    }
    while(getchar() != '\n');
    cout << "Please answer with yes or no" << endl;
  }

  cout << "Comments - Looks good? - " << comments << endl << endl;
  cout << "Student name: " << name << endl;
  cout << "Student ID: " << id <<endl;
  cout << "Final grade is: " << grade << endl <<endl;

  cout << "Program exits successfully..." <<endl;

}
