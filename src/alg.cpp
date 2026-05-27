// Copyright 2021 NNTU-CS
#include <cstdint>
#include "alg.h"

int countPairs1(int *arr, int len, int value) {
  int res = 0;
  for (int i = 0; i < len; i++) {
    for (int j = i + 1; j < len; j++) {
      if (arr[i] + arr[j] == value) {
        res++;
      }
    }
  }
  return res;
}

int countPairs2(int *arr, int len, int value) {
  int res = 0;
  int lo = 0;
  int hi = len - 1;

  while (lo < hi) {
    int cur = arr[lo] + arr[hi];

    if (cur == value) {
      if (arr[lo] == arr[hi]) {
        int k = hi - lo + 1;
        res += k * (k - 1) / 2;
        break;
      } else {
        int cntL = 1;
        int cntR = 1;

        while (lo + cntL < hi && arr[lo] == arr[lo + cntL]) {
          cntL++;
        }

        while (hi - cntR > lo && arr[hi] == arr[hi - cntR]) {
          cntR++;
        }

        res += cntL * cntR;
        lo += cntL;
        hi -= cntR;
      }
    } else if (cur < value) {
      lo++;
    } else {
      hi--;
    }
  }

  return res;
}

static int lowerBound(int *arr, int l, int r, int x) {
  int ans = -1;
  while (l <= r) {
    int m = l + (r - l) / 2;
    if (arr[m] == x) {
      ans = m;
      r = m - 1;
    } else if (arr[m] < x) {
      l = m + 1;
    } else {
      r = m - 1;
    }
  }
  return ans;
}

static int upperBound(int *arr, int l, int r, int x) {
  int ans = -1;
  while (l <= r) {
    int m = l + (r - l) / 2;
    if (arr[m] == x) {
      ans = m;
      l = m + 1;
    } else if (arr[m] < x) {
      l = m + 1;
    } else {
      r = m - 1;
    }
  }
  return ans;
}

int countPairs3(int *arr, int len, int value) {
  int res = 0;

  for (int i = 0; i < len; i++) {
    if (i > 0 && arr[i] == arr[i - 1]) {
      continue;
    }

    int need = value - arr[i];

    if (need < arr[i]) {
      break;
    }

    if (need == arr[i]) {
      int last = upperBound(arr, i, len - 1, arr[i]);
      int cnt = last - i + 1;
      res += cnt * (cnt - 1) / 2;
    } else {
      int first = lowerBound(arr, i + 1, len - 1, need);
      if (first == -1) {
        continue;
      }
      int last = upperBound(arr, i + 1, len - 1, need);

      int lastI = upperBound(arr, i, len - 1, arr[i]);
      int cntI = lastI - i + 1;

      res += cntI * (last - first + 1);
    }
  }

  return res;
}




