#include <stdio.h>

#define MAX_LEN 64

int bi_search(int *bs, int len, int curr) {
    int left = 0, right = len - 1;
    int mid;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (bs[mid] > curr)
            right = mid - 1;
        else if (bs[mid] < curr)
            left = mid + 1;
        else 
            return mid;
    }
    return left;
}

int longest_inc_sub_seq(int array[], int bs[], int n) {
    int len = 1;
    bs[0] = array[0];

    for(int i = 1; i < n; i++)
        if(array[i] > bs[len-1])
            bs[len++] = array[i];
        else
            bs[bi_search(bs, len, array[i])] = array[i];

    return len;
}

int main(int argc, char *argv[]) {
    int array[MAX_LEN];
    int bs[MAX_LEN];
    int n = 0;
#ifdef DEBUG
    freopen("input", "r", stdin);
#endif
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d", &array[i]);
#ifdef DEBUG
    fclose(stdin);
#endif
    int lis = longest_inc_sub_seq(array, bs, n);

    printf("LIS : %d\n", lis);
    for(int i = 0; i < lis; i++)
        printf("%d%c", bs[i], i == lis - 1 ? '\n' : ' ');

    return 0;
}
