// Copyright 2021 NNTU-CS
#include <cstdint>
#include "alg.h"

int findMatches1(int* data, int size, int target) {
    int result = 0;
    for (int idx = 0; idx < size; ++idx) {
        for (int jdx = idx + 1; jdx < size; ++jdx) {
            if (data[idx] + data[jdx] == target) {
                ++result;
            }
        }
    }
    return result;
}

int findMatches2(int* data, int size, int target) {
    int result = 0;
    int start = 0;
    int finish = size - 1;

    while (start < finish) {
        int current = data[start] + data[finish];

        if (current == target) {
            if (data[start] == data[finish]) {
                int length = finish - start + 1;
                result += length * (length - 1) / 2;
                break;
            }
            else {
                int repeatStart = 1;
                int repeatFinish = 1;

                while (start + repeatStart < finish && data[start] == data[start + repeatStart]) {
                    ++repeatStart;
                }

                while (finish - repeatFinish > start && data[finish] == data[finish - repeatFinish]) {
                    ++repeatFinish;
                }

                result += repeatStart * repeatFinish;
                start += repeatStart;
                finish -= repeatFinish;
            }
        }
        else if (current < target) {
            ++start;
        }
        else {
            --finish;
        }
    }

    return result;
}

int getFirstPos(int* data, int leftPos, int rightPos, int val) {
    int answer = -1;
    while (leftPos <= rightPos) {
        int middle = leftPos + (rightPos - leftPos) / 2;
        if (data[middle] == val) {
            answer = middle;
            rightPos = middle - 1;
        }
        else if (data[middle] < val) {
            leftPos = middle + 1;
        }
        else {
            rightPos = middle - 1;
        }
    }
    return answer;
}

int getLastPos(int* data, int leftPos, int rightPos, int val) {
    int answer = -1;
    while (leftPos <= rightPos) {
        int middle = leftPos + (rightPos - leftPos) / 2;
        if (data[middle] == val) {
            answer = middle;
            leftPos = middle + 1;
        }
        else if (data[middle] < val) {
            leftPos = middle + 1;
        }
        else {
            rightPos = middle - 1;
        }
    }
    return answer;
}

int findMatches3(int* data, int size, int target) {
    int result = 0;

    for (int pos = 0; pos < size; ++pos) {
        if (pos > 0 && data[pos] == data[pos - 1]) {
            continue;
        }

        int need = target - data[pos];

        if (need < data[pos]) {
            break;
        }

        if (need == data[pos]) {
            int lastOccurrence = getLastPos(data, pos, size - 1, data[pos]);
            int cnt = lastOccurrence - pos + 1;
            result += cnt * (cnt - 1) / 2;
        }
        else {
            int firstOccurrence = getFirstPos(data, pos + 1, size - 1, need);
            if (firstOccurrence == -1) {
                continue;
            }
            int lastOccurrence = getLastPos(data, pos + 1, size - 1, need);

            int lastPosCurrent = getLastPos(data, pos, size - 1, data[pos]);
            int cntCurrent = lastPosCurrent - pos + 1;

            result += cntCurrent * (lastOccurrence - firstOccurrence + 1);
        }
    }

    return result;
}



