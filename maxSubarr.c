#include <stdio.h>
#include <limits.h>
typedef struct {
int low;
int high;
int sum;
} Result;
Result maxCrossingSum(int arr[], int low, int mid, int high) {
int left_sum = INT_MIN;
int sum = 0;
int max_left = mid;
for (int i = mid; i >= low; i--) {
sum += arr[i];
if (sum > left_sum) {
left_sum = sum;
max_left = i;
}
}
int right_sum = INT_MIN;
sum = 0;
int max_right = mid + 1;
for (int i = mid + 1; i <= high; i++) {
sum += arr[i];

if (sum > right_sum) {
right_sum = sum;
max_right = i;
}
}
Result res = {max_left, max_right, left_sum + right_sum};
return res;
}
Result maxSubArraySum(int arr[], int low, int high) {
if (low == high) {
Result res = {low, high, arr[low]};
return res;
}
int mid = (low + high) / 2;
Result left_res = maxSubArraySum(arr, low, mid);
Result right_res = maxSubArraySum(arr, mid + 1, high);
Result cross_res = maxCrossingSum(arr, low, mid, high);
if (left_res.sum >= right_res.sum && left_res.sum >= cross_res.sum)
return left_res;
else if (right_res.sum >= left_res.sum && right_res.sum >= cross_res.sum)
return right_res;
else
return cross_res;
}
void printBestSubarrays(int arr[], int n, int constraint) {
int max_sum = 0;
int found = 0;
for (int i = 0; i < n; i++) {
int sum = 0;
for (int j = i; j < n; j++) {
sum += arr[j];
if (sum <= constraint && sum > max_sum) {
max_sum = sum;
}
}
}
for (int i = 0; i < n; i++) {
int sum = 0;
for (int j = i; j < n; j++) {
sum += arr[j];
if (sum == max_sum && sum <= constraint) {
for (int k = i; k <= j; k++) printf("%d ", arr[k]);

printf("Sum = %d\n", sum);
found = 1;
}
}
}
if (!found) printf("No feasible subarray under constraint.\n");
}
int main() {
int resources[] = {2, 1, 3, 4};
int n = sizeof(resources) / sizeof(resources[0]);
int constraint = 5;
Result res = maxSubArraySum(resources, 0, n - 1);
printf("Divide and conquer result: Left=%d Right=%d Sum=%d\n", res.low, res.high, res.sum);
printBestSubarrays(resources, n, constraint);
return 0;
}