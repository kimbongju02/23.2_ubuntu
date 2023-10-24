#include <stdio.h>
#include <stdlib.h>

struct Student {
    char name[50];
    float midterm_score;
    float final_score;
    struct Student* left;
    struct Student* right;
};

struct Student* createStudent(const char* name, float midterm_score, float final_score) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    strcpy(newStudent->name, name);
    newStudent->midterm_score = midterm_score;
    newStudent->final_score = final_score;
    newStudent->left = NULL;
    newStudent->right = NULL;
    return newStudent;
}

struct Student* insertStudent(struct Student* root, const char* name, 
float midterm_score, float final_score) {
    if (root == NULL) {
        return createStudent(name, midterm_score, final_score);
    }

    if (strcmp(name, root->name) < 0) {
        root->left = insertStudent(root->left, name, midterm_score, final_score);
    } else {
        root->right = insertStudent(root->right, name, midterm_score, final_score);
    }

    return root;
}

void inOrderTraversal(struct Student* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("name: %s, middle_score: %.2f, final_score: %.2f\n", 
        root->name, root->midterm_score, root->final_score);
        inOrderTraversal(root->right);
    }
}

int main() {
    int num_students;
    printf("student number : ");
    scanf("%d", &num_students);

    struct Student* root = NULL;

    for (int i = 0; i < num_students; i++) {
        char name[50];
        float midterm_score, final_score;

        printf("name: ");
        scanf("%s", name);
        printf("middle_score: ");
        scanf("%f", &midterm_score);
        printf("final_score: ");
        scanf("%f", &final_score);

        root = insertStudent(root, name, midterm_score, final_score);
    }

    inOrderTraversal(root);

    return 0;
}

