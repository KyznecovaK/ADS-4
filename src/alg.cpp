// Copyright 2021 NNTU-CS
#include <cstdint>
#include "alg.h"

int countPairs1(int *arr, int len, int value) {
  int count = 0;
  for (int i = 0; i < len; i++) {
    for (int j = i + 1; j < len; j++) {
      if (arr[i] + arr[j] == value) {
        count++;
      }
    }
  }
  return count;
}

int countPairs2(int *arr, int len, int value) {
  int count = 0;
  int left = 0;
  int right = len - 1;

  while (left < right) {
    int sum = arr[left] + arr[right];

    if (sum == value) {
      if (arr[left] == arr[right]) {
        int total = right - left + 1;
        count += total * (total - 1) / 2;
        break;
      } else {
        int leftCount = 1;
        int rightCount = 1;

        while (left + leftCount < right &&
               arr[left] == arr[left + leftCount]) {
          leftCount++;
        }

        while (right - rightCount > left &&
               arr[right] == arr[right - rightCount]) {
          rightCount++;
        }

        count += leftCount * rightCount;

        left += leftCount;
        right -= rightCount;
      }
    } else if (sum < value) {
      left++;
    } else {
      right--;
    }
  }

  return count;
}

int lowerBound(int *arr, int left, int right, int target) {
  int result = -1;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (arr[mid] == target) {
      result = mid;
      right = mid - 1;
    } else if (arr[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return result;
}

int upperBound(int *arr, int left, int right, int target) {
  int result = -1;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (arr[mid] == target) {
      result = mid;
      left = mid + 1;
    } else if (arr[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return result;
}

int countPairs3(int *arr, int len, int value) {
  int count = 0;

  for (int i = 0; i < len; i++) {
    if (i > 0 && arr[i] == arr[i - 1]) {
      continue;
    }

    int target = value - arr[i];

    if (target < arr[i]) {
      break;
    }

    if (target == arr[i]) {
      int last = upperBound(arr, i, len - 1, arr[i]);
      int cnt = last - i + 1;
      count += cnt * (cnt - 1) / 2;
    } else {
      int first = lowerBound(arr, i + 1, len - 1, target);
      if (first == -1) {
        continue;
      }
      int last = upperBound(arr, i + 1, len - 1, target);

      int iLast = upperBound(arr, i, len - 1, arr[i]);
      int iCnt = iLast - i + 1;

      count += iCnt * (last - first + 1);
    }
  }

  return count;
}
