const fs = require('fs');
let i = 2;
let content = null;
const f =  () => {
    for(var j = 0; j<1000; j++) {
	i = i+j;
    }
    fs.readFile('./asyncawait.js', function read(err, data) {
	if (err) {
            throw err;
	}
	content = data;
	
	// Invoke the next step here however you like
	console.log(content.toString());   // Put all of the code here (not the best solution)
    });
    console.log('done f');
};

const x = () => {
    for(var j = 0; j<500; j++) {
	i = j;
    }
    console.log('done x');
}
const func = () => {
    f();
    x();
}

func();



console.log(i);
