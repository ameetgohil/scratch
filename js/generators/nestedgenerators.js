const _ = require('lodash');
function* risingedge(clk) {
    yield 1;
    yield 2;
}

function* driver(clk, count) {
    for(let i of _.range(count))
	yield* risingedge(clk);
    //yield 3;
}

x = driver(0,5);
console.log(x.next());
console.log(x.next());
console.log(x.next());
console.log(x.next());
console.log(x.next());
console.log(x.next());
console.log(x.next());
console.log(x.next());

console.log(x.next());
console.log(x.next());
console.log(x.next());
console.log(x.next());
