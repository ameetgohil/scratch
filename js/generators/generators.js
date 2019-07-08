function * foo(x) {
    console.log("generator");
    while(true) {
	x = x * 2;
	yield x;
	yield 1234;
    }
}

var g = foo(2);
console.log('not next');
console.log(g.next());
console.log(g);
console.log(g.next());
console.log(g.next());
