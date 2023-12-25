function fastFind(arr: Array<number>) {
  const desiredNumber = 8;
  let lowerBound = 0;
  let upperBound = arr.length;

  while (upperBound !== lowerBound) {
    //no Ints >> floor
    let idx = lowerBound + Math.floor((upperBound - lowerBound) / 2);

    console.log(`Asked for idx ${idx} and got ${arr[idx]}`);

    if (arr[idx] === desiredNumber) {
      return true;
    } else if (arr[idx] < desiredNumber) {
      lowerBound = idx;
    } else {
      upperBound = idx;
    }
  }

  return false;
}

const result = fastFind([1, 2, 3, 4, 5, 6, 7, 8, 9]);
