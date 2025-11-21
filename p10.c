#include <stdio.h>
#include <omp.h>
void blur() {
    printf("Blurring the image...\n");
    for (int i = 0; i < 100000000; i++);  
    printf("Blur complete.\n");
}
void sharpen() {
    printf("Sharpening the image...\n");
    for (int i = 0; i < 100000000; i++);  
    printf("Sharpen complete.\n");
}
void contrast() {
    printf("Adjusting contrast...\n");
    for (int i = 0; i < 100000000; i++);  
    printf("Contrast adjustment complete.\n");
}
void resize_img() {
    printf("Resizing the image...\n");
    for (int i = 0; i < 100000000; i++);  
    printf("Resize complete.\n");
}
int main() {
    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task
            blur();
            #pragma omp task
            sharpen();
            #pragma omp task
            contrast();
            #pragma omp task
            resize_img();
        }
    }
    return 0;
}
