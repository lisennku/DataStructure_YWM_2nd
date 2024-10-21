//
// Created by lisen on 24-10-21.
//
int largestAltitude(int* gain, int gainSize) {
    int sum = 0;
    int max_sum = 0;
    for(int i = 0; i < gainSize; i++) {
        sum += gain[i];
        if(max_sum < sum)
            max_sum = sum;
    }
    return max_sum;
}