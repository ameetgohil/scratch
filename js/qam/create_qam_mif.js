const fs = require('fs');
const u = x => x >>> 0;
const neg = x => ~x + 1;
let qam16_mem = [0x30003000,
		 0x10003000,
		 0x30001000,
		 0x10001000,
		 u(neg(0x3000) << 16)|0x3000,
		 u(neg(0x1000) << 16)|0x3000,
		 u(neg(0x3000) << 16)|0x1000,
		 u(neg(0x1000) << 16)|0x1000,
		 (0x3000 << 16)|u(neg(0x3000) & 0xFFFF),
		 (0x1000 << 16)|u(neg(0x3000) & 0xFFFF),
		 (0x3000 << 16)|u(neg(0x1000) & 0xFFFF),
		 (0x1000 << 16)|u(neg(0x1000) & 0xFFFF),
		 u(neg(0x3000) << 16) | u(neg(0x3000) & 0xFFFF),
		 u(neg(0x1000) << 16) | u(neg(0x3000) & 0xFFFF),
		 u(neg(0x3000) << 16) | u(neg(0x1000) & 0xFFFF),
		 u(neg(0x3000) << 16) | u(neg(0x1000) & 0xFFFF)
		];

let qam16_string = '';
for(let i = 0; i< qam16_mem.length; i++)
    qam16_string += u(qam16_mem[i]).toString(16) + '\n';

let qam8_string = '';
for(let i = 0; i < 8; i++)
    qam8_string = i.toString(16) + '\n';

let qam32_string = '';
for(let i = 0; i < 32; i++)
    qam8_string = i.toString(16) + '\n';

let qam64_string = '';
for(let i = 0; i < 64; i++)
    qam8_string = i.toString(16) + '\n';


console.log(qam16_string);

fs.writeFile('qam16.mif', qam16_string, (err) => {
    if(err) {
	return console.log(err);
    }

    console.log("MIF file created");
});

fs.writeFile('qam8.mif', qam8_string, (err) => {
    if(err) {
	return console.log(err);
    }

    console.log("MIF file created");
});

fs.writeFile('qam32.mif', qam32_string, (err) => {
    if(err) {
	return console.log(err);
    }

    console.log("MIF file created");
});

fs.writeFile('qam64.mif', qam64_string, (err) => {
    if(err) {
	return console.log(err);
    }

    console.log("MIF file created");
});
