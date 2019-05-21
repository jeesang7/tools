function makeEnertalkCheckSum(serialNumber) {
    let checkSum = '';
    if (!serialNumber || serialNumber.length != 8) return checkSum;
    let sum = 0;
    for (let i = 0; i < 8; i = i + 2) {
      sum += parseInt(serialNumber.substr(i, 2), 16);
    }
    checkSum = padZero(2, Number(256 - (sum % 256)).toString(16));
    return checkSum.toUpperCase();
}

function getChecksum(sn){
	let arr = convStr2Arr(sn, 2);
	let sum = 0;
	let max = parseInt('0x400', 16);
	let checksum = '';
	for(let i=0; i<arr.length; i++){
		sum = sum + parseInt(arr[i], 16);
	}
	checksum = padZero(2, (max - sum).toString(16).toUpperCase().slice(-2));
	return checksum;
}

function convStr2Arr(str, len) {
    let bufferLen = Math.ceil(str.length/len);
    let arrBuffer = new Array(bufferLen);
    let idx = 0;
    for(let i=0; i<str.length; i++){
        idx = Math.floor(i/len);
        arrBuffer[idx] = (arrBuffer[idx]||'').toString() + str.charAt(i).toString();
    }
    return arrBuffer;
}

function padZero(count, value = '') {
	const lackSpace = count - value.toString().length;
  
	if (lackSpace > 0) {
	  return `${new Array(lackSpace + 1).join('0')}${value}`;
	}
  
	return value.toString();
}


// console.log(makeEnertalkCheckSum('F30100e2'));
// console.log(getChecksum('F30100e2'));
// console.log(makeEnertalkCheckSum('F7FFFFFF'));
// console.log(getChecksum('F7FFFFFF'));
const C_KIND = {
  NUMBER: 0,
  HEX: 1
}
const kind = process.argv[2]; // 0: number, 1: hex
const sn = process.argv[3];

// console.log('PARAM:', process.argv);
let snHex = '';
let ret = '';
if (kind == C_KIND.NUMBER) {
  snHex = Number(sn).toString(16);
} else {
  snHex = sn;
}
ret = getChecksum(snHex);
let full = snHex + "" + ret;
console.log('param:', kind, sn, '  FULL:', full.toLowerCase(), full.toUpperCase());


// usage: $ node testSnChecksum.js  0 4127195126
